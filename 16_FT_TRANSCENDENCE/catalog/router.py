import os
import datetime
import structlog
import time

from uuid import uuid4
from fastapi import Depends, HTTPException, Query, UploadFile, File
from fastapi import FastAPI
from fastapi.middleware.cors import CORSMiddleware
from sqlalchemy import text, select, func, delete
from sqlalchemy.orm import Session

from jwt_handler import verify_jwt_access
from schemas import (
    AuthorResponse,
    BookCreateRequest,
    BookResponse,
    BookReviewsResponse,
    BookUpdateRequest,
    PublisherResponse,
    ReviewCreateRequest,
    ReviewResponse,
    ShortBookResponse,
)
from storage import upload_cover
from search import CatalogSearchFilter, SearchResult, search_books
from database import get_db
from models import Book, BookCategory, BookBookCategory, Author, Publisher, BookTranslation, PublisherFollower, \
    BookReview
from minio.error import S3Error
from typing import Annotated, Any, TypeVar
from prometheus_fastapi_instrumentator import Instrumentator
from public_api import router as public_api_router

app = FastAPI()
app.include_router(public_api_router)

T = TypeVar("T")
CurrentUser = Annotated[dict[str, Any], Depends(verify_jwt_access())]
AdminUser = Annotated[dict[str, Any], Depends(verify_jwt_access(["admin"]))]

structlog.configure(
    processors=[
        structlog.stdlib.add_log_level,
        structlog.processors.TimeStamper(fmt="iso"),
        structlog.processors.JSONRenderer(),
    ],
    logger_factory=structlog.PrintLoggerFactory(),
)

log = structlog.get_logger()

cors_env = os.getenv("CORS_ORIGINS", "")
origins = cors_env.split(",") if cors_env else []
app.add_middleware(
    CORSMiddleware,
    allow_origins=origins,
    allow_credentials=True,
    allow_methods=["*"],
    allow_headers=["*"]
)
Instrumentator().instrument(app).expose(app)


def _get_or_create(db: Session, model: type[T], name_col: str, name: str) -> T:
    obj = db.scalars(
        select(model).where(func.lower(getattr(model, name_col)) == name.lower())
    ).one_or_none()
    if not obj:
        obj = model(**{name_col: name})
        db.add(obj)
        db.flush()
    return obj


@app.get("/api/health")
def db_health(db: Session = Depends(get_db)):
    db.execute(text("SELECT 1"))
    return {"status": "ok", "service": "catalog", "db": "connected"}


@app.get("/api/categories")
def get_categories(current_user: CurrentUser, db: Session = Depends(get_db)):
    cats = db.query(BookCategory).all()
    return [
        {"id": c.id, "name": c.category_name, "parent_id": c.parent_id}
        for c in cats
    ]


@app.get("/api/authors")
def get_authors(current_user: CurrentUser, db: Session = Depends(get_db)):
    authors = db.execute(select(Author)).scalars().all()
    return [{"id": a.id, "author_name": a.author_name} for a in authors]


@app.get("/api/authors/{author_id}", response_model=AuthorResponse)
def get_author_by_id(author_id: int, current_user: CurrentUser, db: Session = Depends(get_db)):
    author = db.get(Author, author_id)
    if author is None:
        raise HTTPException(status_code=404, detail="Author not found")
    return author


@app.get("/api/search", response_model=list[SearchResult])
def search_catalog(
        current_user: CurrentUser,
        q: str = Query(min_length=1),
        limit: int = Query(default=6, ge=1, le=50),
        result_type: CatalogSearchFilter | None = Query(default=None, alias="type"),
        db: Session = Depends(get_db),
):
    return search_books(db, q, limit, result_type)


@app.get("/api/books/{book_id}", response_model=BookResponse)
def get_book_by_id(book_id: int, current_user: CurrentUser, db: Session = Depends(get_db)):
    book = db.get(Book, book_id)
    if book is None:
        raise HTTPException(status_code=404, detail="Book not found")
    return book


@app.get("/api/books", response_model=list[ShortBookResponse])
def get_books(
        current_user: CurrentUser,
        category_id: int | None = Query(default=None),
        publisher_id: int | None = Query(default=None),
        author_id: int | None = Query(default=None),
        db: Session = Depends(get_db),
):
    status: str = "active"
    q = select(Book)
    if category_id is not None:
        q = (
            q.join(BookBookCategory, BookBookCategory.book_id == Book.id)
            .filter(BookBookCategory.category_id == category_id)
        )
    if publisher_id is not None:
        q = q.filter(Book.publisher_id == publisher_id)
    if author_id is not None:
        q = q.filter(Book.author_id == author_id)
    if status is not None:
        q = q.filter(Book.product_status == status)
    return db.execute(q).scalars().all()


@app.post("/api/books")
def create_book(
        body: BookCreateRequest,
        current_user: AdminUser,
        db: Session = Depends(get_db)
):
    author = _get_or_create(db, Author, "author_name", body.author_name)
    publisher = None
    if body.publisher_name:
        publisher = _get_or_create(db, Publisher, "publisher_name", body.publisher_name)
    now = datetime.datetime.now(datetime.UTC)
    book = Book(
        author_id=author.id,
        publisher_id=publisher.id if publisher else None,
        price=body.price,
        currency=body.currency,
        language_code=body.language_code,
        isbn=body.isbn,
        product_status=body.product_status,
        created_at=now,
        updated_at=now,
    )
    db.add(book)
    db.flush()

    for t in body.translations:
        db.add(BookTranslation(
            book_id=book.id,
            lang=t.lang,
            title=t.title,
            description=t.description,
            cover_image_filename=t.cover_image_filename,
            created_at=now,
            updated_at=now,
        ))

    for cat_id in body.category_ids:
        db.add(BookBookCategory(book_id=book.id, category_id=cat_id))

    db.commit()
    db.refresh(book)
    return book


@app.put("/api/books/{book_id}", response_model=BookResponse)
def update_book(
        book_id: int,
        body: BookUpdateRequest,
        current_user: AdminUser,
        db: Session = Depends(get_db),
):
    book = db.get(Book, book_id)
    if not book:
        raise HTTPException(status_code=404, detail="Book not found")

    now = datetime.datetime.now(datetime.UTC)

    if body.author_name is not None:
        book.author_id = _get_or_create(db, Author, "author_name", body.author_name).id

    if body.publisher_name is not None:
        book.publisher_id = _get_or_create(db, Publisher, "publisher_name", body.publisher_name).id

    for field in ("price", "currency", "language_code", "isbn", "product_status"):
        val = getattr(body, field)
        if val is not None:
            setattr(book, field, val)

    if body.translations is not None:
        existing = {t.lang: t for t in book.translations}
        for t in body.translations:
            if t.lang in existing:
                tr = existing[t.lang]
                tr.title = t.title
                tr.description = t.description
                tr.updated_at = now
            else:
                db.add(BookTranslation(
                    book_id=book.id,
                    lang=t.lang,
                    title=t.title,
                    description=t.description,
                    cover_image_filename=t.cover_image_filename,
                    created_at=now,
                    updated_at=now,
                ))

    if body.category_ids is not None:
        db.execute(
            BookBookCategory.__table__.delete().where(BookBookCategory.book_id == book_id)
        )
        for cat_id in body.category_ids:
            db.add(BookBookCategory(book_id=book.id, category_id=cat_id))

    book.updated_at = now
    db.commit()
    db.refresh(book)
    return book


@app.delete("/api/books/{book_id}/permanent", status_code=204)
def permanent_delete_book(
        book_id: int,
        current_user: AdminUser,
        db: Session = Depends(get_db),
):
    book = db.get(Book, book_id)
    if not book:
        raise HTTPException(status_code=404, detail="Book not found")
    if book.product_status != "deleted":
        raise HTTPException(status_code=400, detail="Book must have status 'deleted' before it can be permanently removed")
    db.delete(book)
    db.commit()


@app.delete("/api/books/{book_id}", status_code=200, response_model=BookResponse)
def soft_delete_book(
        book_id: int,
        current_user: AdminUser,
        db: Session = Depends(get_db),
):
    book = db.get(Book, book_id)
    if not book:
        raise HTTPException(status_code=404, detail="Book not found")
    book.product_status = "deleted"
    book.updated_at = datetime.datetime.now(datetime.UTC)
    db.commit()
    db.refresh(book)
    return book


ALLOWED_IMAGE_TYPES = {"image/jpeg", "image/png", "image/webp"}


@app.post("/api/books/{book_id}/cover", status_code=200)
async def upload_cover_image(
        book_id: int,
        current_user: AdminUser,
        file: UploadFile = File(...),
        db: Session = Depends(get_db),
):
    start = time.monotonic()
    if file.content_type not in ALLOWED_IMAGE_TYPES:
        log.warning("upload_rejected", reason="invalid_content_type",
                    filename=file.filename, content_type=file.content_type, book_id=book_id)
        raise HTTPException(status_code=400, detail="Image must be JPEG, PNG, or WebP")
    contents = await file.read()
    if len(contents) > 10 * 1024 * 1024:
        log.warning("upload_rejected", reason="file_too_large",
                    filename=file.filename, file_size_bytes=len(contents), book_id=book_id)
        raise HTTPException(status_code=400, detail="Cover image must be under 10 MB")
    book = db.get(Book, book_id)
    if not book:
        log.error("upload_failed", reason="book not found", book_id=book_id)
        raise HTTPException(status_code=404, detail="Book not found")

    storage_key = f"books/{book_id}/{uuid4()}/{file.filename}"
    try:
        upload_cover(storage_key, contents, file.content_type)
        log.info("upload_complete", filename=file.filename, book_id=book_id, file_size_bytes=len(contents),
                 duration_ms=round((time.monotonic() - start) * 1000))
    except S3Error as e:
        log.error("upload_failed", filename=file.filename, book_id=book_id,
                  storage_key=storage_key, error=str(e),
                  duration_ms=round((time.monotonic() - start) * 1000))
        raise HTTPException(status_code=500, detail=str(e))

    now = datetime.datetime.now(datetime.UTC)
    for translation in book.translations:
        translation.cover_image_filename = storage_key
        translation.updated_at = now

    db.commit()
    return {"cover_image_filename": storage_key}


@app.get("/api/books/{book_id}/reviews", response_model=BookReviewsResponse)
def get_book_review(book_id: int,
                    current_user: CurrentUser,
                    db: Session = Depends(get_db)):
    book = db.get(Book, book_id)
    if not book:
        raise HTTPException(status_code=404, detail="Book not found")
    reviews = db.scalars(
        select(BookReview)
        .where(BookReview.book_id == book_id)
        .order_by(BookReview.created_at.desc())
    ).all()
    avg = db.scalar(select(func.avg(BookReview.rating)).where(BookReview.book_id == book_id))
    return BookReviewsResponse(
        average_rating=round(float(avg), 1) if avg else None,
        count=len(reviews),
        reviews=reviews,
    )


@app.post("/api/books/{book_id}/reviews", response_model=ReviewResponse, status_code=201)
def create_review(
        book_id: int,
        body: ReviewCreateRequest,
        current_user: CurrentUser,
        db: Session = Depends(get_db),
):
    book = db.get(Book, book_id)
    if not book:
        raise HTTPException(status_code=404, detail="Book not found")
    existing = db.scalar(
        select(BookReview).where(BookReview.book_id == book_id, BookReview.user_id == current_user["user_id"])
    )
    if existing:
        raise HTTPException(status_code=409, detail="You have already reviewed this book")
    if not 1 <= body.rating <= 5:
        raise HTTPException(status_code=422, detail="Rating must be 1-5")
    review = BookReview(
        book_id=book_id,
        user_id=current_user["user_id"],
        username=body.username,
        rating=body.rating,
        text=body.text,
        created_at=datetime.datetime.now(datetime.UTC),
    )
    db.add(review)
    db.commit()
    db.refresh(review)
    return review


@app.get("/api/publishers/{publisher_id}", response_model=PublisherResponse)
def get_publisher_by_id(publisher_id: int, current_user: CurrentUser, db: Session = Depends(get_db)):
    publisher = db.get(Publisher, publisher_id)
    if publisher is None:
        raise HTTPException(status_code=404, detail="Publisher not found")
    return publisher


@app.post("/api/publishers/{publisher_id}/follow", status_code=204)
def follow_publisher(
        publisher_id: int,
        current_user: CurrentUser,
        db: Session = Depends(get_db),
):
    publisher = db.get(Publisher, publisher_id)
    if publisher is None:
        raise HTTPException(status_code=404, detail="Publisher not found")

    existing = db.execute(
        select(PublisherFollower).where(
            PublisherFollower.user_id == current_user["user_id"],
            PublisherFollower.publisher_id == publisher_id,
        )
    ).scalar_one_or_none()
    if existing:
        raise HTTPException(status_code=400, detail="Already following this publisher")

    db.add(PublisherFollower(user_id=current_user["user_id"], publisher_id=publisher_id))
    db.commit()
    return None


@app.delete("/api/publishers/{publisher_id}/follow", status_code=204)
def unfollow_publisher(
        publisher_id: int,
        current_user: CurrentUser,
        db: Session = Depends(get_db),
):
    result = db.execute(
        delete(PublisherFollower).where(
            PublisherFollower.user_id == current_user["user_id"],
            PublisherFollower.publisher_id == publisher_id,
        )
    )
    if result.rowcount == 0:
        raise HTTPException(status_code=404, detail="Not following this publisher")
    db.commit()
    return None


@app.get("/api/me/following/publishers", response_model=list[PublisherResponse])
def get_my_followed_publishers(
        current_user: CurrentUser,
        db: Session = Depends(get_db),
):
    return db.execute(
        select(Publisher)
        .join(PublisherFollower, PublisherFollower.publisher_id == Publisher.id)
        .where(PublisherFollower.user_id == current_user["user_id"])
        .order_by(PublisherFollower.created_at.desc())
    ).scalars().all()
