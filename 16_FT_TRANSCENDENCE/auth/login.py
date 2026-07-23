import datetime
import os
import re
import secrets

from authlib.integrations.starlette_client import OAuth, OAuthError
from fastapi import APIRouter, Depends, HTTPException, status, Response, Request
from fastapi.responses import RedirectResponse
from sqlalchemy import select
from sqlalchemy.orm import Session
from schemas import (
    UserCreate,
    UserResponse,
    LoginRequest,
    LoginResponse
)

from utils import (
    hash_password,
    validate_username,
    ensure_unique_username,
    verify_password
)
from jwt_handler import create_access_token, hash_token

from config import logger, settings
from models import User, Role, RefreshToken
from database import get_db

router = APIRouter(prefix="/auth", tags=["auth"])
oauth = OAuth()
oauth.register(
    name="fortytwo",
    client_id=os.getenv("42_UID_KEY", ""),
    client_secret=os.getenv("42_API_KEY", ""),
    authorize_url="https://api.intra.42.fr/oauth/authorize",
    access_token_url="https://api.intra.42.fr/oauth/token",
    api_base_url="https://api.intra.42.fr/v2/",
    client_kwargs={
        "scope": "public",
        "token_endpoint_auth_method": "client_secret_post",
    },
)
oauth.register(
    name="google",
    client_id=os.getenv("GOOGLE_CLIENT_ID", ""),
    client_secret=os.getenv("GOOGLE_CLIENT_SECRET", ""),
    server_metadata_url="https://accounts.google.com/.well-known/openid-configuration",
    client_kwargs={"scope": "openid email profile"},
)


def get_or_create_user_role(db: Session) -> Role:
    role = db.scalar(select(Role).where(Role.role_name == "user"))
    if role:
        return role

    role = Role(role_name="user")
    db.add(role)
    db.flush()
    return role


def set_auth_cookies(response: Response, access_token: str, refresh_token: str) -> None:
    access_max_age = settings.access_token_expires_minutes * 60
    refresh_max_age = settings.refresh_token_expires_days * 24 * 60 * 60
    response.set_cookie(
        "access_token",
        access_token,
        httponly=True,
        secure=settings.cookie_secure,
        samesite="lax",
        max_age=access_max_age,
    )
    response.set_cookie(
        "refresh_token",
        refresh_token,
        httponly=True,
        secure=settings.cookie_secure,
        samesite="lax",
        max_age=refresh_max_age,
    )


def create_refresh_token(db: Session, user_id: int) -> str:
    raw_refresh = secrets.token_urlsafe(64)
    now = datetime.datetime.utcnow()
    refresh_rec = RefreshToken(
        token_hash=hash_token(raw_refresh),
        user_id=user_id,
        created_at=now,
        expires_at=now + datetime.timedelta(days=settings.refresh_token_expires_days),
    )
    db.add(refresh_rec)
    return raw_refresh


def optional_text(value: str | None) -> str | None:
    if value is None:
        return None
    value = value.strip()
    return value or None


def require_env(value: str | None, name: str) -> str:
    if not value:
        raise HTTPException(
            status_code=status.HTTP_500_INTERNAL_SERVER_ERROR,
            detail=f"{name} is not configured",
        )
    return value


def oauth_bool(value: object) -> bool:
    if isinstance(value, bool):
        return value
    if isinstance(value, str):
        return value.lower() == "true"
    return False


def google_username_from_profile(profile: dict) -> str:
    email = str(profile.get("email") or "")
    candidates = [
        email.split("@", 1)[0],
        str(profile.get("given_name") or ""),
        str(profile.get("name") or ""),
        "user",
    ]

    for candidate in candidates:
        username = re.sub(r"[^a-zA-Z0-9']", "", candidate.strip().lower())[:25]
        try:
            validate_username(username)
            return username
        except ValueError:
            continue

    return "user"


async def fetch_google_profile(client, token: dict) -> dict:
    profile = token.get("userinfo")
    if profile:
        return dict(profile)

    response = await client.get(
        "https://openidconnect.googleapis.com/v1/userinfo",
        token=token,
    )
    if response.status_code != status.HTTP_200_OK:
        raise HTTPException(status_code=400, detail="Failed to fetch Google profile")
    return response.json()


@router.post("/register", response_model=UserResponse, status_code=status.HTTP_201_CREATED)
def register_user(payload: UserCreate, db: Session = Depends(get_db)):
    email = payload.email.strip().lower()
    existing = db.execute(
        select(User).where(User.email == email)
    ).scalar_one_or_none()
    if existing:
        raise HTTPException(
            status_code=status.HTTP_409_CONFLICT, detail="Email already registered"
        )

    username = payload.username.strip().lower()
    role = get_or_create_user_role(db)
    try:
        validate_username(username)
    except ValueError as e:
        raise HTTPException(status_code=status.HTTP_400_BAD_REQUEST, detail=str(e))

    existing_username = db.execute(
        select(User).where(User.username == username)
    ).scalar_one_or_none()
    if existing_username:
        raise HTTPException(
            status_code=status.HTTP_409_CONFLICT, detail="Username already taken"
        )

    now = datetime.datetime.utcnow()
    password_hash = hash_password(payload.password)
    user = User(
        username=username,
        email=email,
        password_hash=password_hash,
        role_id=role.id,
        first_name=optional_text(payload.first_name),
        last_name=optional_text(payload.last_name),
        phone=optional_text(payload.phone),
        created_at=now,
        updated_at=now,
    )
    db.add(user)
    db.commit()
    db.refresh(user)
    return user


@router.post("/login", response_model=LoginResponse)
def login_user(payload: LoginRequest, db: Session = Depends(get_db), response: Response = None):
    user: User | None = db.scalar(select(User).where(User.email == payload.email))
    if not user:
        raise HTTPException(
            status_code=status.HTTP_401_UNAUTHORIZED, detail="Invalid email"
        )
    if not verify_password(payload.password, user.password_hash):
        raise HTTPException(
            status_code=status.HTTP_401_UNAUTHORIZED, detail="Invalid credentials"
        )

    now = datetime.datetime.now(datetime.UTC)
    user.last_login_at = now
    user.last_seen_at = now
    user.updated_at = now
    db.commit()
    # Create access token (JWT)
    access_token = create_access_token(subject=user.id, role=user.role.role_name)

    raw_refresh = create_refresh_token(db, user.id)
    db.commit()

    if response is not None:
        set_auth_cookies(response, access_token, raw_refresh)

    return {
        "access_token": access_token,
        "token_type": "bearer",
        "user": user
    }


@router.get("/42")
async def login_oauth42(request: Request):
    redirect_uri = require_env(
        os.getenv("OAUTH_42_REDIRECT_URI"),
        "OAUTH_42_REDIRECT_URI",
    )
    client = oauth.create_client("fortytwo")
    return await client.authorize_redirect(request, redirect_uri)


@router.get("/42/callback")
async def oauth42_callback(
    request: Request,
    db: Session = Depends(get_db),
):
    logger.info("CALLBACK REACHED")
    client = oauth.create_client("fortytwo")
    try:
        token = await client.authorize_access_token(request)
        me_response = await client.get("me", token=token)
    except OAuthError as exc:
        logger.exception("42 OAuth failed")
        raise HTTPException(status_code=400, detail=exc.error)

    if me_response.status_code != status.HTTP_200_OK:
        raise HTTPException(status_code=400, detail="Failed to fetch 42 profile")

    ft_user = me_response.json()
    oauth_id = str(ft_user["id"])
    email = ft_user["email"]
    login = ft_user["login"]
    first_name = ft_user["first_name"]
    last_name = ft_user["last_name"]
    now = datetime.datetime.utcnow()

    user = db.scalar(
        select(User).where(
            User.oauth_provider == "42",
            User.oauth_id == oauth_id,
        )
    )
    if not user:
        user = db.scalar(select(User).where(User.email == email))

    if user:
        user.oauth_provider = "42"
        user.oauth_id = oauth_id
        user.email_verified = True
        user.email_verified_at = user.email_verified_at or now
    else:
        role = get_or_create_user_role(db)
        user = User(
            email=email,
            username=ensure_unique_username(db, login),
            first_name=first_name,
            last_name=last_name,
            password_hash=None,
            role_id=role.id,
            created_at=now,
            updated_at=now,
            last_login_at=now,
            email_verified=True,
            email_verified_at=now,
            oauth_provider="42",
            oauth_id=oauth_id,
        )
        db.add(user)
        db.flush()

    user.last_login_at = now
    user.last_seen_at = now
    user.updated_at = now
    access_token = create_access_token(subject=user.id, role=user.role.role_name)
    raw_refresh = create_refresh_token(db, user.id)
    db.commit()

    redirect_response = RedirectResponse(
        url=os.getenv("OAUTH_FRONTEND_REDIRECT_URI", "/"),
        status_code=302,
    )
    set_auth_cookies(redirect_response, access_token, raw_refresh)
    return redirect_response


@router.get("/google")
async def login_oauth_google(request: Request):
    require_env(os.getenv("GOOGLE_CLIENT_ID"), "GOOGLE_CLIENT_ID")
    require_env(os.getenv("GOOGLE_CLIENT_SECRET"), "GOOGLE_CLIENT_SECRET")
    redirect_uri = require_env(
        os.getenv("OAUTH_GOOGLE_REDIRECT_URI", os.getenv("GOOGLE_REDIRECT_URI")),
        "OAUTH_GOOGLE_REDIRECT_URI",
    )
    client = oauth.create_client("google")
    return await client.authorize_redirect(request, redirect_uri)


@router.get("/google/callback")
async def oauth_google_callback(
    request: Request,
    db: Session = Depends(get_db),
):
    client = oauth.create_client("google")
    try:
        token = await client.authorize_access_token(request)
        google_user = await fetch_google_profile(client, token)
    except OAuthError as exc:
        logger.exception("Google OAuth failed")
        raise HTTPException(status_code=400, detail=exc.error)

    oauth_id = optional_text(str(google_user.get("sub") or ""))
    email = optional_text(str(google_user.get("email") or ""))
    if not oauth_id or not email:
        raise HTTPException(status_code=400, detail="Google profile is missing required fields")
    if not oauth_bool(google_user.get("email_verified")):
        raise HTTPException(status_code=400, detail="Google email is not verified")

    email = email.lower()
    now = datetime.datetime.utcnow()

    user = db.scalar(
        select(User).where(
            User.oauth_provider == "google",
            User.oauth_id == oauth_id,
        )
    )
    if not user:
        user = db.scalar(select(User).where(User.email == email))

    if user:
        user.oauth_provider = "google"
        user.oauth_id = oauth_id
        user.email_verified = True
        user.email_verified_at = user.email_verified_at or now
        user.first_name = user.first_name or optional_text(google_user.get("given_name"))
        user.last_name = user.last_name or optional_text(google_user.get("family_name"))
    else:
        role = get_or_create_user_role(db)
        user = User(
            email=email,
            username=ensure_unique_username(db, google_username_from_profile(google_user)),
            password_hash=None,
            role_id=role.id,
            first_name=optional_text(google_user.get("given_name")),
            last_name=optional_text(google_user.get("family_name")),
            created_at=now,
            updated_at=now,
            last_login_at=now,
            email_verified=True,
            email_verified_at=now,
            oauth_provider="google",
            oauth_id=oauth_id,
        )
        db.add(user)
        db.flush()

    user.last_login_at = now
    user.last_seen_at = now
    user.updated_at = now
    access_token = create_access_token(subject=user.id, role=user.role.role_name)
    raw_refresh = create_refresh_token(db, user.id)
    db.commit()

    redirect_response = RedirectResponse(
        url=os.getenv("OAUTH_FRONTEND_REDIRECT_URI", "/"),
        status_code=302,
    )
    set_auth_cookies(redirect_response, access_token, raw_refresh)
    return redirect_response
