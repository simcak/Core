import hashlib

from fastapi import APIRouter, Depends, Header, HTTPException, status
from fastapi.openapi.docs import get_swagger_ui_html
from fastapi.openapi.utils import get_openapi
from fastapi.routing import APIRoute
from sqlalchemy import BigInteger, Boolean, Column, DateTime, MetaData, String, Table, func, select, update
from sqlalchemy.orm import Session

from database import get_db


router = APIRouter(prefix="/api/public/audio", tags=["public"])
PUBLIC_API_TITLE = "Audio Public API"
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


@router.get("/test", dependencies=[Depends(verify_public_api_key)])
def test_public_api():
    return {"message": "hello world", "service": "audio"}
