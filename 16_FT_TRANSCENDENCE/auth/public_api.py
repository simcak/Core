import hashlib
import json
import os
import datetime
from copy import deepcopy
from urllib.error import URLError
from urllib.request import urlopen

from fastapi import APIRouter, Depends, Header, HTTPException, status
from fastapi.openapi.docs import get_swagger_ui_html
from fastapi.openapi.utils import get_openapi
from fastapi.routing import APIRoute
from pydantic import BaseModel, ConfigDict, field_validator
from sqlalchemy import BigInteger, Boolean, Column, DateTime, MetaData, String, Table, func, select, update
from sqlalchemy.orm import Session

from database import get_db
from models import User


router = APIRouter(prefix="/api/public/auth", tags=["public"])
aggregate_router = APIRouter(prefix="/api/public", tags=["public-docs"])
PUBLIC_API_TITLE = "Auth Public API"
AGGREGATE_PUBLIC_API_TITLE = "Audioberry Public API"
PUBLIC_API_VERSION = "1.0.0"
PUBLIC_OPENAPI_SOURCES = {
    "audio": os.getenv(
        "PUBLIC_AUDIO_OPENAPI_URL",
        "http://audio:8000/api/public/audio/openapi.json",
    ),
    "catalog": os.getenv(
        "PUBLIC_CATALOG_OPENAPI_URL",
        "http://catalog:8000/api/public/catalog/openapi.json",
    ),
}
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


class PublicUserData(BaseModel):
    model_config = ConfigDict(from_attributes=True)

    id: int
    username: str
    first_name: str | None
    last_name: str | None
    avatar_filename: str | None
    status: str


class PublicUserDataUpdate(BaseModel):
    username: str | None = None
    first_name: str | None = None
    last_name: str | None = None
    avatar_filename: str | None = None

    @field_validator("username")
    @classmethod
    def username_valid(cls, value: str | None) -> str | None:
        if value is None:
            raise ValueError("Username cannot be null")
        value = value.strip().lower()
        if not value:
            raise ValueError("Username cannot be empty")
        if len(value) > 50:
            raise ValueError("Username must be 50 characters or fewer")
        return value

    @field_validator("first_name", "last_name")
    @classmethod
    def short_text_valid(cls, value: str | None) -> str | None:
        if value is None:
            return value
        value = value.strip()
        if len(value) > 150:
            raise ValueError("Value must be 150 characters or fewer")
        return value or None

    @field_validator("avatar_filename")
    @classmethod
    def avatar_filename_valid(cls, value: str | None) -> str | None:
        if value is None:
            return value
        value = value.strip()
        if len(value) > 255:
            raise ValueError("Avatar filename must be 255 characters or fewer")
        return value or None


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


def _fetch_openapi_schema(service: str, url: str) -> dict:
    try:
        with urlopen(url, timeout=3) as response:
            return json.loads(response.read().decode("utf-8"))
    except (OSError, URLError, json.JSONDecodeError) as exc:
        raise HTTPException(
            status_code=status.HTTP_502_BAD_GATEWAY,
            detail=f"Unable to load {service} public OpenAPI schema",
        ) from exc


def _rewrite_refs(value, renamed_refs: dict[str, str]):
    if isinstance(value, dict):
        for key, item in value.items():
            if key == "$ref" and isinstance(item, str):
                value[key] = renamed_refs.get(item, item)
            else:
                _rewrite_refs(item, renamed_refs)
    elif isinstance(value, list):
        for item in value:
            _rewrite_refs(item, renamed_refs)


def _merge_components(target: dict, source: dict, service: str, source_schema: dict) -> None:
    renamed_refs: dict[str, str] = {}
    source_components = source.get("components", {})
    target_components = target.setdefault("components", {})
    for section_name, section_values in source_components.items():
        target_section = target_components.setdefault(section_name, {})
        for component_name, component_value in section_values.items():
            final_name = component_name
            if final_name in target_section and target_section[final_name] != component_value:
                final_name = f"{service}_{component_name}"
                renamed_refs[
                    f"#/components/{section_name}/{component_name}"
                ] = f"#/components/{section_name}/{final_name}"
            target_section[final_name] = component_value
    _rewrite_refs(source_schema, renamed_refs)


def aggregate_public_openapi_schema() -> dict:
    merged_schema = {
        "openapi": "3.1.0",
        "info": {
            "title": AGGREGATE_PUBLIC_API_TITLE,
            "version": PUBLIC_API_VERSION,
        },
        "paths": {},
        "components": {},
    }

    schemas = {"auth": public_openapi_schema()}
    schemas.update({
        service: _fetch_openapi_schema(service, url)
        for service, url in PUBLIC_OPENAPI_SOURCES.items()
    })

    for service, schema in schemas.items():
        source_schema = deepcopy(schema)
        _merge_components(merged_schema, source_schema, service, source_schema)
        merged_schema["paths"].update(source_schema.get("paths", {}))

    return merged_schema


@aggregate_router.get("/openapi.json", include_in_schema=False)
def aggregate_public_openapi():
    return aggregate_public_openapi_schema()


@aggregate_router.get("/docs", include_in_schema=False)
def aggregate_public_docs():
    return get_swagger_ui_html(
        openapi_url=f"{aggregate_router.prefix}/openapi.json",
        title=f"{AGGREGATE_PUBLIC_API_TITLE} docs",
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


def _get_user_or_404(user_id: int, db: Session) -> User:
    user = db.get(User, user_id)
    if not user:
        raise HTTPException(status_code=status.HTTP_404_NOT_FOUND, detail="User not found")
    return user


@router.get(
    "/users/{user_id}",
    response_model=PublicUserData,
    dependencies=[Depends(verify_public_api_key)],
)
def get_public_user_data(user_id: int, db: Session = Depends(get_db)):
    return _get_user_or_404(user_id, db)


@router.patch(
    "/users/{user_id}",
    response_model=PublicUserData,
    dependencies=[Depends(verify_public_api_key)],
)
def update_public_user_data(
        user_id: int,
        body: PublicUserDataUpdate,
        db: Session = Depends(get_db),
):
    user = _get_user_or_404(user_id, db)
    updates = body.model_dump(exclude_unset=True)
    username = updates.get("username")
    if username and username != user.username:
        existing = db.scalar(
            select(User).where(
                User.username == username,
                User.id != user.id,
            )
        )
        if existing:
            raise HTTPException(status_code=status.HTTP_409_CONFLICT, detail="Username is already taken")
    for field, value in updates.items():
        setattr(user, field, value)
    user.updated_at = datetime.datetime.now(datetime.UTC)
    db.commit()
    db.refresh(user)
    return user


@router.delete(
    "/users/{user_id}",
    status_code=status.HTTP_204_NO_CONTENT,
    dependencies=[Depends(verify_public_api_key)],
)
def delete_public_user_data(user_id: int, db: Session = Depends(get_db)):
    user = _get_user_or_404(user_id, db)
    user.first_name = None
    user.last_name = None
    user.avatar_filename = None
    user.updated_at = datetime.datetime.now(datetime.UTC)
    db.commit()


@router.get("/test", dependencies=[Depends(verify_public_api_key)])
def test_public_api():
    return {"message": "hello world", "service": "auth"}
