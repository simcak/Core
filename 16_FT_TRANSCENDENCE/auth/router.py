import os
import datetime
import secrets
from uuid import uuid4
from typing import Annotated, Any

from fastapi.middleware.cors import CORSMiddleware
from fastapi import FastAPI, Depends, HTTPException, status, Response, Cookie, UploadFile, File, Query
from fastapi.responses import StreamingResponse
from starlette.middleware.sessions import SessionMiddleware

from sqlalchemy import text, select, delete, func, or_
from sqlalchemy.orm import Session
from sqlalchemy.exc import IntegrityError

from schemas import (
    UserResponse,
    UserInfoResponse,
    UserProfileResponse,
    UserCreateAdmin,
    UserSearchResponse,
    UserUpdate,
    UserProfileUpdateRequest,
    LibraryCreate,
    LibraryOut,
    LibraryChecked,
    PublicApiKeyCreate,
    PublicApiKeyCreateResponse,
    PublicApiKeyResponse,
)
from database import get_db
from models import User, Role, RefreshToken, Follower, UsersLibrary, UsersLibraryBook, PublicApiKey
from config import settings

from utils import (
    hash_password,
)
from jwt_handler import (
    hash_token,
    verify_jwt_access,
)
from login import router as login_router
from public_api import aggregate_router as aggregate_public_api_router
from public_api import router as public_api_router
from storage import upload_avatar, get_avatar_stream, delete_avatar
from minio.error import S3Error
from prometheus_fastapi_instrumentator import Instrumentator

app = FastAPI(docs_url="/auth/docs", openapi_url="/auth/openapi.json", redoc_url="/auth/redoc")
app.add_middleware(
    SessionMiddleware,
    secret_key=settings.secret_key.get_secret_value(),
    same_site="lax",
    https_only=settings.cookie_secure,
)

cors_env = os.getenv("CORS_ORIGINS", "")
origins = cors_env.split(",") if cors_env else []
app.add_middleware(
    CORSMiddleware,
    allow_origins=origins,
    allow_credentials=True,
    allow_methods=["*"],
    allow_headers=["*"],
)
app.include_router(login_router)
app.include_router(public_api_router)
app.include_router(aggregate_public_api_router)

CurrentUser = Annotated[dict[str, Any], Depends(verify_jwt_access())]
AdminUser = Annotated[dict[str, Any], Depends(verify_jwt_access(["admin"]))]

ALLOWED_IMAGE_TYPES = {"image/jpeg", "image/png", "image/webp"}

Instrumentator().instrument(app).expose(app)


# ENDPOINTS
@app.get("/health")
def health(db: Session = Depends(get_db)):
    db.execute(text("SELECT 1"))
    return {"status": "ok", "service": "auth", "db": "connected"}


def ensure_unique_email(db: Session, email: str, exclude_id: int | None = None) -> bool:
    """Check if email is unique (excluding a specific user if updating)"""
    query = select(User).where(User.email == email)
    if exclude_id:
        query = query.where(User.id != exclude_id)
    return not db.execute(query).scalar_one_or_none()


# example of using jwt dependency for any role
@app.get("/auth/test")
def test_access(
        current_user: CurrentUser):  # use jwt dependency to check for valid access token
    if current_user:
        return {"test": "ok"}
    return {
        "test": "not ok"}  # this will probably never happen since verify_jwt_access function will raise a http exception


# example of using jwt dependency for admin
@app.get("/auth/test_admin")
def test_access_admin(current_user: AdminUser):  # use jwt dependency to check token
    if current_user:
        return {"test": "ok"}
    return {
        "test": "not ok"}  # this will probably never happen since verify_jwt_access function will raise a http exception


@app.post("/auth/jwt/refresh")
def refresh_access_token(current_user: CurrentUser):
    access_token = current_user.get("access_token")
    if not access_token:
        raise HTTPException(status_code=status.HTTP_400_BAD_REQUEST, detail="Access token is still valid")
    return {"access_token": access_token, "token_type": "bearer"}


@app.post("/auth/logout")
def logout_user(
        current_user: CurrentUser,
        response: Response = None,
        refresh_token: str | None = Cookie(None, alias="refresh_token"),
        db: Session = Depends(get_db),
):
    if refresh_token:
        hashed = hash_token(refresh_token)
        rec = db.scalar(select(RefreshToken).where(RefreshToken.token_hash == hashed))
        if rec:
            rec.revoked = True
            db.add(rec)
            db.commit()
    if response is not None:
        response.delete_cookie("access_token")
        response.delete_cookie("refresh_token")
    return None


@app.get("/auth/me", response_model=UserResponse)
def get_current_user(
        token_user: CurrentUser,
        db: Session = Depends(get_db),
) -> User:
    user = db.scalar(select(User).where(User.id == token_user["user_id"]))
    if not user:
        raise HTTPException(status_code=status.HTTP_401_UNAUTHORIZED, detail="User not found")
    return user


AuthenticatedUser = Annotated[User, Depends(get_current_user)]


@app.post("/auth/heartbeat", status_code=status.HTTP_204_NO_CONTENT)
def heartbeat(
        current_user: AuthenticatedUser,
        db: Session = Depends(get_db),
):
    """Mark the authenticated user as recently active for online presence."""
    current_user.last_seen_at = datetime.datetime.now(datetime.UTC)
    db.commit()
    return None


@app.get("/auth/search/users", response_model=list[UserSearchResponse])
def search_users(
        _current_user: AuthenticatedUser,
        q: str = Query(min_length=1),
        limit: int = Query(default=10, ge=1, le=30),
        db: Session = Depends(get_db),
):
    needle = q.strip().lower()
    if not needle:
        return []

    pattern = f"%{needle}%"
    full_name_expr = func.lower(
        func.concat(
            func.coalesce(User.first_name, ""),
            " ",
            func.coalesce(User.last_name, ""),
        )
    )
    users = db.execute(
        select(User).where(
            or_(
                func.lower(User.username).like(pattern),
                func.lower(func.coalesce(User.first_name, "")).like(pattern),
                func.lower(func.coalesce(User.last_name, "")).like(pattern),
                full_name_expr.like(pattern),
            )
        )
    ).scalars().all()
    ranked: list[tuple[int, User]] = []
    for user in users:
        username = user.username.lower()
        first_name = (user.first_name or "").lower()
        last_name = (user.last_name or "").lower()
        full_name = f"{first_name} {last_name}".strip()

        if needle == username:
            score = 100
        elif username.startswith(needle):
            score = 80
        elif full_name.startswith(needle):
            score = 70
        elif first_name.startswith(needle) or last_name.startswith(needle):
            score = 60
        elif needle in username or needle in full_name:
            score = 40
        else:
            continue

        ranked.append((score, user))

    ranked.sort(key=lambda item: (-item[0], item[1].username.lower(), item[1].id))
    return [user for _, user in ranked[:limit]]


@app.get("/auth/users/{user_id}", response_model=UserInfoResponse)
def get_user_by_id(
        user_id: int,
        current_user: AuthenticatedUser,
        db: Session = Depends(get_db),
):
    user = db.execute(select(User).where(User.id == user_id)).scalar_one_or_none()
    if not user:
        raise HTTPException(status_code=status.HTTP_404_NOT_FOUND, detail=f"User with id {user_id} not found")
    return user


# ── GET ALL USERS (Admin panel only) ────────────────────────────────────────

@app.get("/auth/admin/users", response_model=list[UserResponse])
def get_all_users_admin(current_user: AdminUser, db: Session = Depends(get_db)):
    users = db.execute(select(User).order_by(User.id)).scalars().all()
    return users


@app.get("/auth/admin/public-api-keys", response_model=list[PublicApiKeyResponse])
def get_public_api_keys(
        current_user: AdminUser,
        db: Session = Depends(get_db),
):
    return db.execute(select(PublicApiKey).order_by(PublicApiKey.id)).scalars().all()


@app.post(
    "/auth/admin/public-api-keys",
    response_model=PublicApiKeyCreateResponse,
    status_code=status.HTTP_201_CREATED,
)
def create_public_api_key(
        body: PublicApiKeyCreate,
        current_user: AdminUser,
        db: Session = Depends(get_db),
):
    raw_token = f"abp_{secrets.token_urlsafe(32)}"
    api_key = PublicApiKey(
        token_hash=hash_token(raw_token),
        name=body.name,
        expires_at=body.expires_at,
        created_at=datetime.datetime.now(datetime.UTC),
        revoked=False,
    )
    db.add(api_key)
    db.commit()
    db.refresh(api_key)
    response = PublicApiKeyResponse.model_validate(api_key).model_dump()
    return PublicApiKeyCreateResponse(**response, token=raw_token)


@app.patch(
    "/auth/admin/public-api-keys/{api_key_id}/revoke",
    response_model=PublicApiKeyResponse,
)
def revoke_public_api_key(
        api_key_id: int,
        current_user: AdminUser,
        db: Session = Depends(get_db),
):
    api_key = db.get(PublicApiKey, api_key_id)
    if not api_key:
        raise HTTPException(status_code=status.HTTP_404_NOT_FOUND, detail="Public API key not found")
    api_key.revoked = True
    db.commit()
    db.refresh(api_key)
    return api_key


@app.delete("/auth/admin/public-api-keys/{api_key_id}", status_code=status.HTTP_204_NO_CONTENT)
def delete_public_api_key(
        api_key_id: int,
        current_user: AdminUser,
        db: Session = Depends(get_db),
):
    api_key = db.get(PublicApiKey, api_key_id)
    if not api_key:
        raise HTTPException(status_code=status.HTTP_404_NOT_FOUND, detail="Public API key not found")
    db.delete(api_key)
    db.commit()


# ── CREATE USER (Admin panel only) ────────────────────────────────────────


@app.get("/auth/admin/users/{user_id}", response_model=UserResponse)
def get_user_by_id_admin(
        user_id: int,
        current_user: AdminUser,
        db: Session = Depends(get_db),
):
    user = db.execute(select(User).where(User.id == user_id)).scalar_one_or_none()
    if not user:
        raise HTTPException(status_code=status.HTTP_404_NOT_FOUND, detail=f"User with id {user_id} not found")
    return user


@app.post("/auth/admin/users", response_model=UserResponse, status_code=status.HTTP_201_CREATED)
def admin_create_user(
        payload: UserCreateAdmin,
        current_user: AdminUser,
        db: Session = Depends(get_db),
):
    # Username: required, must be unique
    if not payload.username or not payload.username.strip():
        raise HTTPException(status_code=status.HTTP_400_BAD_REQUEST, detail="Username is required")

    username = payload.username.strip().lower()
    if db.execute(select(User).where(User.username == username)).scalar_one_or_none():
        raise HTTPException(status_code=status.HTTP_409_CONFLICT, detail="Username is already taken")

    # Email: required, must be unique
    email = payload.email.strip().lower()
    if db.execute(select(User).where(User.email == email)).scalar_one_or_none():
        raise HTTPException(status_code=status.HTTP_409_CONFLICT, detail="Email is already taken")

    # Role must exist
    role = db.execute(select(Role).where(Role.id == payload.role_id)).scalar_one_or_none()
    if not role:
        raise HTTPException(status_code=status.HTTP_404_NOT_FOUND, detail=f"Role {payload.role_id} not found")

    # Password is required (no silent generation)
    if not payload.password:
        raise HTTPException(status_code=status.HTTP_400_BAD_REQUEST, detail="Password is required")

    now = datetime.datetime.utcnow()
    user = User(
        username=username,
        email=email,
        password_hash=hash_password(payload.password),
        role_id=payload.role_id,
        first_name=payload.first_name,
        last_name=payload.last_name,
        phone=payload.phone,
        created_at=now,
        updated_at=now,
    )

    try:
        db.add(user)
        db.commit()
        db.refresh(user)
    except IntegrityError:
        db.rollback()
        raise HTTPException(status_code=status.HTTP_409_CONFLICT, detail="Username or email is already taken")

    return user


# ── UPDATE USER (Admin panel only) ────────────────────────────────────────


@app.put("/auth/admin/users/{user_id}", response_model=UserResponse)
def update_user_admin(
        user_id: int,
        payload: UserUpdate,
        current_user: AdminUser,
        db: Session = Depends(get_db),
):
    """Update an existing user from admin panel"""

    # Get user
    user = db.execute(select(User).where(User.id == user_id)).scalar_one_or_none()
    if not user:
        raise HTTPException(
            status_code=status.HTTP_404_NOT_FOUND,
            detail=f"User with id {user_id} not found"
        )

    # Check email uniqueness if updating email
    if payload.email and payload.email != user.email:
        if not ensure_unique_email(db, payload.email, exclude_id=user_id):
            raise HTTPException(
                status_code=status.HTTP_409_CONFLICT,
                detail="Email already registered"
            )
        user.email = payload.email

    # Check username uniqueness if updating username
    if payload.username and payload.username != user.username:
        existing = db.execute(
            select(User).where(User.username == payload.username, User.id != user_id)
        ).scalar_one_or_none()
        if existing:
            raise HTTPException(
                status_code=status.HTTP_409_CONFLICT,
                detail="Username already taken"
            )
        user.username = payload.username

    # Update role if provided
    if payload.role_id is not None and payload.role_id != user.role_id:
        role = db.execute(select(Role).where(Role.id == payload.role_id)).scalar_one_or_none()
        if not role:
            raise HTTPException(
                status_code=status.HTTP_404_NOT_FOUND,
                detail=f"Role with id {payload.role_id} not found"
            )
        user.role_id = payload.role_id

    # Update password if provided
    if payload.password:
        user.password_hash = hash_password(payload.password)

    # Update name fields
    if payload.first_name is not None:
        user.first_name = payload.first_name
    if payload.last_name is not None:
        user.last_name = payload.last_name
    if payload.phone is not None:
        user.phone = payload.phone

    # Update timestamp
    user.updated_at = datetime.datetime.utcnow()

    db.commit()
    db.refresh(user)
    return user

# ── ENABLE USER (Admin panel only) ────────────────────────────────────────


@app.patch("/auth/admin/users/{user_id}/enable", response_model=UserResponse)
def enable_user(
    user_id: int,
    current_user: AdminUser,
    db: Session = Depends(get_db),
):
    user = db.execute(select(User).where(User.id == user_id)).scalar_one_or_none()
    if not user:
        raise HTTPException(status_code=404, detail="User not found")
    user.status = "active"
    user.updated_at = datetime.datetime.utcnow()
    db.commit()
    db.refresh(user)
    return user


# ── DISABLE USER (Admin panel only) ────────────────────────────────────────


@app.patch("/auth/admin/users/{user_id}/disable", response_model=UserResponse)
def disable_user(
    user_id: int,
    current_user: AdminUser,
    db: Session = Depends(get_db),
):
    user = db.execute(select(User).where(User.id == user_id)).scalar_one_or_none()
    if not user:
        raise HTTPException(status_code=404, detail="User not found")
    if user.id == current_user["user_id"]:
        raise HTTPException(status_code=400, detail="Cannot disable your own account")
    user.status = "disabled"
    user.updated_at = datetime.datetime.utcnow()
    db.commit()
    db.refresh(user)
    return user


# ── DELETE USER (Admin panel only) ────────────────────────────────────────

@app.delete("/auth/admin/users/{user_id}", status_code=status.HTTP_204_NO_CONTENT)
def delete_user_admin(
        user_id: int,
        current_user: AdminUser,
        db: Session = Depends(get_db),
):
    """Delete a user from admin panel"""

    # Get user
    user = db.execute(select(User).where(User.id == user_id)).scalar_one_or_none()
    if not user:
        raise HTTPException(status_code=404, detail=f"User with id {user_id} not found")

    # Delete FK-dependent rows first
    db.execute(delete(RefreshToken).where(RefreshToken.user_id == user_id))

    # Delete user
    db.delete(user)
    db.commit()
    return None


# ── EDIT USER PROFILE (Admin panel only) ────────────────────────────────────────

@app.put("/auth/editProfile", response_model=UserProfileResponse)
def update_profile(
        payload: UserProfileUpdateRequest,
        current_user: AuthenticatedUser,
        db: Session = Depends(get_db),
):
    """Allow user to update their own profile (name, phone, avatar)"""
    # Update name fields
    if payload.first_name is not None:
        current_user.first_name = payload.first_name
    if payload.last_name is not None:
        current_user.last_name = payload.last_name
    if payload.phone is not None:
        current_user.phone = payload.phone
    if payload.avatar_filename is not None:
        current_user.avatar_filename = payload.avatar_filename

    # Update timestamp
    current_user.updated_at = datetime.datetime.utcnow()

    db.commit()
    return current_user


@app.post("/auth/me/avatar", status_code=200)
async def upload_my_avatar(
        current_user: AuthenticatedUser,
        file: UploadFile = File(...),
        db: Session = Depends(get_db),
):
    if file.content_type not in ALLOWED_IMAGE_TYPES:
        raise HTTPException(status_code=status.HTTP_400_BAD_REQUEST, detail="Image must be JPEG, PNG, or WebP")

    contents = await file.read()
    if len(contents) > 10 * 1024 * 1024:
        raise HTTPException(status_code=status.HTTP_400_BAD_REQUEST, detail="Avatar image must be under 10 MB")

    storage_key = f"users/{current_user.id}/{uuid4()}/{file.filename}"
    try:
        upload_avatar(storage_key, contents, file.content_type)
    except S3Error as exc:
        raise HTTPException(status_code=status.HTTP_500_INTERNAL_SERVER_ERROR, detail=str(exc)) from exc

    current_user.avatar_filename = storage_key
    current_user.updated_at = datetime.datetime.utcnow()
    db.commit()
    return {"avatar_filename": storage_key}


@app.get("/auth/me/avatar")
def get_my_avatar(
        current_user: AuthenticatedUser,
        db: Session = Depends(get_db),
):
    if not current_user.avatar_filename:
        raise HTTPException(status_code=status.HTTP_404_NOT_FOUND, detail="No avatar uploaded")

    try:
        stream = get_avatar_stream(current_user.avatar_filename)
        ext = current_user.avatar_filename.rsplit('.', 1)[-1].lower()
        mime = {'jpg': 'image/jpeg', 'jpeg': 'image/jpeg', 'png': 'image/png', 'webp': 'image/webp'}.get(ext,
                                                                                                         'image/jpeg')
        return StreamingResponse(stream, media_type=mime)
    except Exception as exc:
        raise HTTPException(status_code=status.HTTP_404_NOT_FOUND, detail="Avatar not found in storage") from exc


@app.get("/auth/users/{user_id}/avatar")
def get_user_avatar(
        user_id: int,
        current_user: CurrentUser,
        db: Session = Depends(get_db),
):
    user = db.scalar(select(User).where(User.id == user_id))
    if not user:
        raise HTTPException(status_code=status.HTTP_404_NOT_FOUND, detail=f"User with id {user_id} not found")
    if not user.avatar_filename:
        raise HTTPException(status_code=status.HTTP_404_NOT_FOUND, detail="No avatar uploaded")

    try:
        stream = get_avatar_stream(user.avatar_filename)
        ext = user.avatar_filename.rsplit('.', 1)[-1].lower()
        mime = {'jpg': 'image/jpeg', 'jpeg': 'image/jpeg', 'png': 'image/png', 'webp': 'image/webp'}.get(ext,
                                                                                                         'image/jpeg')
        return StreamingResponse(stream, media_type=mime)
    except Exception as exc:
        raise HTTPException(status_code=status.HTTP_404_NOT_FOUND, detail="Avatar not found in storage") from exc


@app.get("/auth/me/followers", response_model=list[UserResponse])
def get_my_followers(
        current_user: AuthenticatedUser,
        db: Session = Depends(get_db),
):
    """Get the users who follow the authenticated user."""
    followers = db.execute(
        select(User)
        .join(Follower, Follower.follower_id == User.id)
        .where(Follower.followed_id == current_user.id)
        .order_by(Follower.created_at.desc())
    ).scalars().all()

    return followers


@app.get("/auth/me/following", response_model=list[UserResponse])
def get_my_following(
        current_user: AuthenticatedUser,
        db: Session = Depends(get_db),
):
    """Get the users that the authenticated user is following."""
    following = db.execute(
        select(User)
        .join(Follower, Follower.followed_id == User.id)
        .where(Follower.follower_id == current_user.id)
        .order_by(Follower.created_at.desc())
    ).scalars().all()

    return following


@app.post("/auth/me/follow/{target_user_id}", status_code=status.HTTP_204_NO_CONTENT)
def follow_user(
        target_user_id: int,
        current_user: AuthenticatedUser,
        db: Session = Depends(get_db),
):
    """Follow another user."""
    if target_user_id == current_user.id:
        raise HTTPException(status_code=status.HTTP_400_BAD_REQUEST, detail="Cannot follow yourself")

    target_user = db.execute(select(User).where(User.id == target_user_id)).scalar_one_or_none()
    if not target_user:
        raise HTTPException(status_code=status.HTTP_404_NOT_FOUND, detail=f"User with id {target_user_id} not found")

    existing_follow = db.execute(
        select(Follower).where(
            Follower.follower_id == current_user.id,
            Follower.followed_id == target_user_id
        )
    ).scalar_one_or_none()

    if existing_follow:
        raise HTTPException(status_code=status.HTTP_400_BAD_REQUEST, detail="Already following this user")

    new_follow = Follower(
        follower_id=current_user.id,
        followed_id=target_user_id,
        created_at=datetime.datetime.now(datetime.UTC),
    )
    db.add(new_follow)
    db.commit()
    return None


@app.delete("/auth/me/unfollow/{target_user_id}", status_code=status.HTTP_204_NO_CONTENT)
def unfollow_user(
        target_user_id: int,
        current_user: AuthenticatedUser,
        db: Session = Depends(get_db),
):
    """Unfollow another user."""
    if target_user_id == current_user.id:
        raise HTTPException(status_code=status.HTTP_400_BAD_REQUEST, detail="Cannot unfollow yourself")

    existing_follow = db.execute(
        select(Follower).where(
            Follower.follower_id == current_user.id,
            Follower.followed_id == target_user_id
        )
    ).scalar_one_or_none()

    if not existing_follow:
        raise HTTPException(status_code=status.HTTP_400_BAD_REQUEST, detail="Not following this user")

    db.delete(existing_follow)
    db.commit()
    return None

# ── Return all the roles from role table ────────────────────────────────────────


@app.get("/auth/roles")
def get_roles(current_user: CurrentUser, db: Session = Depends(get_db)):
    roles = db.execute(select(Role).order_by(Role.role_name)).scalars().all()

    return [{"id": r.id, "role_name": r.role_name} for r in roles]


# ── USERS LIBRARY (Whishlist)─────────────────────────────────────────────────────────────
#    Get all libraries for the authenticated user.

@app.get("/auth/me/libraries", response_model=list[LibraryOut])
def get_my_libraries(
    current_user: AuthenticatedUser,
    db: Session = Depends(get_db),
):
    libraries = db.execute(
        select(UsersLibrary)
        .where(UsersLibrary.user_id == current_user.id)
        .order_by(UsersLibrary.id)
    ).scalars().all()
    return [
        LibraryOut(
            id=lib.id,
            name=lib.name,
            book_ids=[b.book_id for b in lib.books]  # ← added
        )
        for lib in libraries
    ]


#    Create a new named library.
@app.post("/auth/me/libraries", response_model=LibraryOut, status_code=status.HTTP_201_CREATED)
def create_library(
    payload: LibraryCreate,
    current_user: AuthenticatedUser,
    db: Session = Depends(get_db),
):
    library = UsersLibrary(user_id=current_user.id, name=payload.name)
    db.add(library)
    try:
        db.commit()
    except IntegrityError:
        db.rollback()
        raise HTTPException(status.HTTP_409_CONFLICT, detail=f"A library named '{payload.name}' already exists")
    db.refresh(library)
    return library


#    Delete a library and all its books (cascade).
@app.delete("/auth/me/libraries/{library_id}", status_code=status.HTTP_204_NO_CONTENT)
def delete_library(
    library_id: int,
    current_user: AuthenticatedUser,
    db: Session = Depends(get_db),
):
    library = db.execute(
        select(UsersLibrary)
        .where(UsersLibrary.id == library_id, UsersLibrary.user_id == current_user.id)
    ).scalar_one_or_none()
    if not library:
        raise HTTPException(status.HTTP_404_NOT_FOUND, detail="Library not found")
    db.delete(library)
    db.commit()


#    Rename a library.
@app.patch("/auth/me/libraries/{library_id}", response_model=LibraryOut)
def rename_library(
    library_id: int,
    payload: LibraryCreate,
    current_user: AuthenticatedUser,
    db: Session = Depends(get_db),
):
    library = db.execute(
        select(UsersLibrary)
        .where(UsersLibrary.id == library_id, UsersLibrary.user_id == current_user.id)
    ).scalar_one_or_none()
    if not library:
        raise HTTPException(status.HTTP_404_NOT_FOUND, detail="Library not found")
    library.name = payload.name
    try:
        db.commit()
    except IntegrityError:
        db.rollback()
        raise HTTPException(status.HTTP_409_CONFLICT, detail=f"A library named '{payload.name}' already exists")
    db.refresh(library)
    return library


# ── LIBRARY ↔ BOOK ────────────────────────────────────────────────────────────
#    Called when AddToListMenu opens.
#    Returns all libraries with a checked flag for whether this book is in each one.
@app.get("/auth/me/books/{book_id}/libraries", response_model=list[LibraryChecked])
def get_book_library_states(
    book_id: int,
    current_user: AuthenticatedUser,
    db: Session = Depends(get_db),
):
    rows = db.execute(
        select(UsersLibrary, UsersLibraryBook.book_id.label("in_library"))
        .outerjoin(
            UsersLibraryBook,
            (UsersLibraryBook.library_id == UsersLibrary.id) & (UsersLibraryBook.book_id == book_id)
        )
        .where(UsersLibrary.user_id == current_user.id)
        .order_by(UsersLibrary.id)
    ).all()

    return [
        LibraryChecked(id=str(lib.id), label=lib.name, checked=in_library is not None)
        for lib, in_library in rows
    ]


@app.post("/auth/me/libraries/{library_id}/books/{book_id}", status_code=status.HTTP_201_CREATED)
def add_book_to_library(
    library_id: int,
    book_id: int,
    current_user: AuthenticatedUser,
    db: Session = Depends(get_db),
):
    """Toggle ON — add a book to a library."""
    library = db.execute(
        select(UsersLibrary)
        .where(UsersLibrary.id == library_id, UsersLibrary.user_id == current_user.id)
    ).scalar_one_or_none()
    if not library:
        raise HTTPException(status.HTTP_404_NOT_FOUND, detail="Library not found")

    existing = db.get(UsersLibraryBook, (library_id, book_id))
    if existing:
        return {"detail": "Book already in library"}

    db.add(UsersLibraryBook(library_id=library_id, book_id=book_id))
    db.commit()
    return {"detail": "Book added to library"}


@app.delete("/auth/me/libraries/{library_id}/books/{book_id}", status_code=status.HTTP_204_NO_CONTENT)
def remove_book_from_library(
    library_id: int,
    book_id: int,
    current_user: AuthenticatedUser,
    db: Session = Depends(get_db),
):
    """Toggle OFF — remove a book from a library."""
    library = db.execute(
        select(UsersLibrary)
        .where(UsersLibrary.id == library_id, UsersLibrary.user_id == current_user.id)
    ).scalar_one_or_none()
    if not library:
        raise HTTPException(status.HTTP_404_NOT_FOUND, detail="Library not found")

    entry = db.get(UsersLibraryBook, (library_id, book_id))
    if not entry:
        raise HTTPException(status.HTTP_404_NOT_FOUND, detail="Book not in this library")

    db.delete(entry)
    db.commit()


# Allow an admin to upload/replace the avatar of any user ────────────────────────────────────────

@app.post("/auth/admin/users/{user_id}/avatar", status_code=200)
async def upload_user_avatar_admin(
        user_id: int,
        current_user: AdminUser,
        file: UploadFile = File(...),
        db: Session = Depends(get_db),
):
    user = db.execute(select(User).where(User.id == user_id)).scalar_one_or_none()
    if not user:
        raise HTTPException(status_code=status.HTTP_404_NOT_FOUND, detail=f"User with id {user_id} not found")

    if file.content_type not in ALLOWED_IMAGE_TYPES:
        raise HTTPException(status_code=status.HTTP_400_BAD_REQUEST, detail="Image must be JPEG, PNG, or WebP")

    contents = await file.read()
    if len(contents) > 10 * 1024 * 1024:
        raise HTTPException(status_code=status.HTTP_400_BAD_REQUEST, detail="Avatar image must be under 10 MB")

    storage_key = f"users/{user.id}/{uuid4()}/{file.filename}"
    try:
        upload_avatar(storage_key, contents, file.content_type)
    except S3Error as exc:
        raise HTTPException(status_code=status.HTTP_500_INTERNAL_SERVER_ERROR, detail=str(exc)) from exc

    user.avatar_filename = storage_key
    user.updated_at = datetime.datetime.utcnow()
    db.commit()
    return {"avatar_filename": storage_key}


#    Allow an admin to remove a user's avatar (no replacement) ────────────────────────────────────────

@app.delete("/auth/admin/users/{user_id}/avatar", status_code=status.HTTP_204_NO_CONTENT)
def delete_user_avatar_admin(
        user_id: int,
        current_user: AdminUser,
        db: Session = Depends(get_db),
):
    user = db.execute(select(User).where(User.id == user_id)).scalar_one_or_none()
    if not user:
        raise HTTPException(status_code=status.HTTP_404_NOT_FOUND, detail=f"User with id {user_id} not found")

    if not user.avatar_filename:
        raise HTTPException(status_code=status.HTTP_404_NOT_FOUND, detail="User has no avatar to remove")

    try:
        delete_avatar(user.avatar_filename)
    except S3Error as exc:
        raise HTTPException(status_code=status.HTTP_500_INTERNAL_SERVER_ERROR, detail=str(exc)) from exc

    user.avatar_filename = None
    user.updated_at = datetime.datetime.utcnow()
    db.commit()
    return None
