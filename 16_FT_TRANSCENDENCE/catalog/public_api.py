import hashlib
import datetime

from fastapi import APIRouter, Depends, Header, HTTPException, status
from fastapi.openapi.docs import get_swagger_ui_html
from fastapi.openapi.utils import get_openapi
from fastapi.routing import APIRoute
from pydantic import BaseModel, ConfigDict, field_validator
from sqlalchemy import BigInteger, Boolean, Column, DateTime, MetaData, String, Table, func, select, update
from sqlalchemy.orm import Session

from database import get_db
from models import Author, Book, BookBookCategory, BookCategory, BookTranslation, Publisher


router = APIRouter(prefix="/api/public/catalog", tags=["public"])
PUBLIC_API_TITLE = "Catalog Public API"
PUBLIC_API_VERSION = "1.0.0"
public_api_keys = Table(
    "public_api_keys",
    MetaData(),
    Column("id", BigInteger, primary_key=True),
    Column("token_hash", String(255), nullable=False),
    Column("expires_at", DateTime, nullable=True),
    Column("last_used_at", DateTime, nullable=True),
    Column("revoked", Boolean, nullable=False),
    schema="auth",
)


class PublicAuthorData(BaseModel):
    model_config = ConfigDict(from_attributes=True)

    id: int
    author_name: str


class PublicPublisherData(BaseModel):
    model_config = ConfigDict(from_attributes=True)

    id: int
    publisher_name: str


class PublicBookCategoryData(BaseModel):
    model_config = ConfigDict(from_attributes=True)

    id: int
    category_name: str


class PublicBookTranslationData(BaseModel):
    model_config = ConfigDict(from_attributes=True)

    id: int
    lang: str
    title: str
    description: str | None
    cover_image_filename: str | None
    sample_url: str | None


class PublicBookData(BaseModel):
    model_config = ConfigDict(from_attributes=True)

    id: int
    author: PublicAuthorData
    publisher: PublicPublisherData | None
    translations: list[PublicBookTranslationData]
    categories: list[PublicBookCategoryData]
    price: float
    currency: str
    language_code: str | None
    isbn: str | None
    product_status: str


class PublicBookTranslationInput(BaseModel):
    lang: str
    title: str
    description: str | None = None
    cover_image_filename: str | None = None
    sample_url: str | None = None

    @field_validator("lang")
    @classmethod
    def lang_valid(cls, value: str) -> str:
        value = value.strip().lower()
        if not value:
            raise ValueError("Language cannot be empty")
        if len(value) > 10:
            raise ValueError("Language must be 10 characters or fewer")
        return value

    @field_validator("title")
    @classmethod
    def title_valid(cls, value: str) -> str:
        value = value.strip()
        if not value:
            raise ValueError("Title cannot be empty")
        if len(value) > 255:
            raise ValueError("Title must be 255 characters or fewer")
        return value


class PublicBookDataUpdate(BaseModel):
    author_name: str | None = None
    publisher_name: str | None = None
    price: float | None = None
    currency: str | None = None
    language_code: str | None = None
    isbn: str | None = None
    product_status: str | None = None
    translations: list[PublicBookTranslationInput] | None = None
    category_ids: list[int] | None = None

    @field_validator("author_name", "publisher_name", "product_status")
    @classmethod
    def short_required_text_valid(cls, value: str | None) -> str | None:
        if value is None:
            return value
        value = value.strip()
        if not value:
            raise ValueError("Value cannot be empty")
        return value

    @field_validator("currency")
    @classmethod
    def currency_valid(cls, value: str | None) -> str | None:
        if value is None:
            return value
        value = value.strip().upper()
        if len(value) != 3:
            raise ValueError("Currency must be a 3-letter code")
        return value


def _extract_api_key(
        x_api_key: str | None = Header(default=None, alias="X-API-Key"),
        authorization: str | None = Header(default=None),
) -> str:
    if x_api_key:
        return x_api_key
    if authorization:
        scheme, _, token = authorization.partition(" ")
        if scheme.lower() == "bearer" and token:
            return token
    raise HTTPException(status_code=status.HTTP_401_UNAUTHORIZED, detail="Missing API key")


def verify_public_api_key(
        api_key: str = Depends(_extract_api_key),
        db: Session = Depends(get_db),
) -> int:
    token_hash = hashlib.sha256(api_key.encode("utf-8")).hexdigest()
    result = db.execute(
        select(public_api_keys.c.id)
        .where(
            public_api_keys.c.token_hash == token_hash,
            public_api_keys.c.revoked.is_(False),
            (public_api_keys.c.expires_at.is_(None)) | (public_api_keys.c.expires_at > func.now()),
        )
        .limit(1)
    ).scalar_one_or_none()
    if result is None:
        raise HTTPException(status_code=status.HTTP_401_UNAUTHORIZED, detail="Invalid API key")
    db.execute(
        update(public_api_keys)
        .where(public_api_keys.c.id == result)
        .values(last_used_at=func.now())
    )
    db.commit()
    return int(result)


def public_openapi_schema() -> dict:
    routes = [
        route for route in router.routes
        if isinstance(route, APIRoute) and route.include_in_schema
    ]
    return get_openapi(
        title=PUBLIC_API_TITLE,
        version=PUBLIC_API_VERSION,
        routes=routes,
    )


@router.get("/openapi.json", include_in_schema=False)
def public_openapi():
    return public_openapi_schema()


@router.get("/docs", include_in_schema=False)
def public_docs():
    return get_swagger_ui_html(
        openapi_url=f"{router.prefix}/openapi.json",
        title=f"{PUBLIC_API_TITLE} docs",
    )


def _get_book_or_404(book_id: int, db: Session) -> Book:
    book = db.get(Book, book_id)
    if not book:
        raise HTTPException(status_code=status.HTTP_404_NOT_FOUND, detail="Book not found")
    return book


def _get_or_create(db: Session, model, name_col: str, name: str):
    obj = db.scalars(
        select(model).where(func.lower(getattr(model, name_col)) == name.lower())
    ).one_or_none()
    if not obj:
        obj = model(**{name_col: name})
        db.add(obj)
        db.flush()
    return obj


@router.get(
    "/books/{book_id}",
    response_model=PublicBookData,
    dependencies=[Depends(verify_public_api_key)],
)
def get_public_book_data(book_id: int, db: Session = Depends(get_db)):
    return _get_book_or_404(book_id, db)


@router.patch(
    "/books/{book_id}",
    response_model=PublicBookData,
    dependencies=[Depends(verify_public_api_key)],
)
def update_public_book_data(
        book_id: int,
        body: PublicBookDataUpdate,
        db: Session = Depends(get_db),
):
    book = _get_book_or_404(book_id, db)
    now = datetime.datetime.now(datetime.UTC)

    if body.author_name is not None:
        book.author_id = _get_or_create(db, Author, "author_name", body.author_name).id
    if body.publisher_name is not None:
        book.publisher_id = _get_or_create(db, Publisher, "publisher_name", body.publisher_name).id

    for field in ("price", "currency", "language_code", "isbn", "product_status"):
        value = getattr(body, field)
        if value is not None:
            setattr(book, field, value)

    if body.translations is not None:
        existing = {translation.lang: translation for translation in book.translations}
        for translation in body.translations:
            if translation.lang in existing:
                existing_translation = existing[translation.lang]
                existing_translation.title = translation.title
                existing_translation.description = translation.description
                existing_translation.cover_image_filename = translation.cover_image_filename
                existing_translation.sample_url = translation.sample_url
                existing_translation.updated_at = now
            else:
                db.add(BookTranslation(
                    book_id=book.id,
                    lang=translation.lang,
                    title=translation.title,
                    description=translation.description,
                    cover_image_filename=translation.cover_image_filename,
                    sample_url=translation.sample_url,
                    created_at=now,
                    updated_at=now,
                ))

    if body.category_ids is not None:
        existing_categories = db.scalars(
            select(BookCategory.id).where(BookCategory.id.in_(body.category_ids))
        ).all()
        missing_categories = set(body.category_ids) - set(existing_categories)
        if missing_categories:
            raise HTTPException(
                status_code=status.HTTP_400_BAD_REQUEST,
                detail=f"Unknown category ids: {sorted(missing_categories)}",
            )
        db.execute(
            BookBookCategory.__table__.delete().where(BookBookCategory.book_id == book_id)
        )
        for category_id in body.category_ids:
            db.add(BookBookCategory(book_id=book.id, category_id=category_id))

    book.updated_at = now
    db.commit()
    db.refresh(book)
    return book


@router.delete(
    "/books/{book_id}",
    status_code=status.HTTP_204_NO_CONTENT,
    dependencies=[Depends(verify_public_api_key)],
)
def delete_public_book_data(book_id: int, db: Session = Depends(get_db)):
    book = _get_book_or_404(book_id, db)
    db.delete(book)
    db.commit()


@router.get("/test", dependencies=[Depends(verify_public_api_key)])
def test_public_api():
    return {"message": "hello world", "service": "catalog"}
