import hashlib
import json
import os
import urllib.error
import urllib.request
from datetime import datetime as _dt, timedelta, timezone
from typing import Any

import jwt
from fastapi import Cookie, Header, HTTPException, Response, status


def _secret_key() -> str:
    return os.getenv("SECRET_KEY", "dev-secret")


def _algorithm() -> str:
    return os.getenv("ALGORITHM", "HS256")


def _access_token_expires_minutes() -> int:
    return int(os.getenv("ACCESS_TOKEN_EXPIRES_MINUTES", "15"))


def _cookie_secure() -> bool:
    return os.getenv("COOKIE_SECURE", "false").lower() == "true"


def _auth_refresh_url() -> str:
    return os.getenv("AUTH_REFRESH_URL", "http://auth:8000/auth/jwt/refresh")


def create_access_token(subject: int, role: str, expires_minutes: int | None = None) -> str:
    now = _dt.now(timezone.utc)
    expire = now + timedelta(minutes=expires_minutes or _access_token_expires_minutes())
    payload = {
        "sub": str(subject),
        "role": role,
        "iat": int(now.timestamp()),
        "exp": int(expire.timestamp()),
    }
    return jwt.encode(payload, _secret_key(), algorithm=_algorithm())


def decode_access_token(token: str) -> dict[str, Any]:
    try:
        return jwt.decode(token, _secret_key(), algorithms=[_algorithm()])
    except jwt.ExpiredSignatureError:
        raise HTTPException(status_code=status.HTTP_401_UNAUTHORIZED, detail="Token expired")
    except jwt.InvalidTokenError:
        raise HTTPException(status_code=status.HTTP_401_UNAUTHORIZED, detail="Invalid token")


def hash_token(token: str) -> str:
    return hashlib.sha256(token.encode("utf-8")).hexdigest()


def set_access_token_cookie(response: Response, access_token: str) -> None:
    response.set_cookie(
        "access_token",
        access_token,
        httponly=True,
        secure=_cookie_secure(),
        samesite="lax",
        max_age=_access_token_expires_minutes() * 60,
    )


def _get_bearer_token(authorization: str | None) -> str | None:
    if not authorization:
        return None

    scheme, _, token = authorization.partition(" ")
    if scheme.lower() != "bearer" or not token:
        raise HTTPException(
            status_code=status.HTTP_401_UNAUTHORIZED,
            detail="Invalid authorization header",
        )
    return token


def _payload_to_user_context(payload: dict[str, Any]) -> dict[str, Any]:
    user_id = payload.get("sub")
    role = payload.get("role")
    if not user_id or not role:
        raise HTTPException(status_code=status.HTTP_401_UNAUTHORIZED, detail="Invalid access token")

    return {
        "user_id": int(user_id),
        "role": role,
        "claims": payload,
    }


def _refresh_access_token(response: Response, refresh_token: str) -> dict[str, Any]:
    request = urllib.request.Request(
        _auth_refresh_url(),
        data=b"",
        method="POST",
        headers={"Cookie": f"refresh_token={refresh_token}"},
    )
    try:
        with urllib.request.urlopen(request, timeout=3) as refresh_response:
            body = json.loads(refresh_response.read().decode("utf-8"))
    except urllib.error.HTTPError as exc:
        if exc.code == status.HTTP_401_UNAUTHORIZED:
            raise HTTPException(status_code=status.HTTP_401_UNAUTHORIZED, detail="Invalid refresh token")
        raise HTTPException(status_code=status.HTTP_502_BAD_GATEWAY, detail="Auth refresh failed")
    except (urllib.error.URLError, TimeoutError, json.JSONDecodeError):
        raise HTTPException(status_code=status.HTTP_502_BAD_GATEWAY, detail="Auth service unavailable")

    access_token = body.get("access_token")
    if not access_token:
        raise HTTPException(status_code=status.HTTP_502_BAD_GATEWAY, detail="Auth refresh failed")

    set_access_token_cookie(response, access_token)
    response.headers["X-Access-Token-Refreshed"] = "true"
    current_user = _payload_to_user_context(decode_access_token(access_token))
    current_user["access_token"] = access_token
    return current_user


def verify_jwt_access(roles: list[str] | None = None):
    async def verifier(
        response: Response,
        access_token: str | None = Cookie(None, alias="access_token"),
        refresh_token: str | None = Cookie(None, alias="refresh_token"),
        authorization: str | None = Header(None),
    ) -> dict[str, Any]:
        token = access_token or _get_bearer_token(authorization)
        if not token:
            if not refresh_token:
                raise HTTPException(status_code=status.HTTP_401_UNAUTHORIZED, detail="Missing access token")
            current_user = _refresh_access_token(response, refresh_token)
        else:
            try:
                current_user = _payload_to_user_context(decode_access_token(token))
            except HTTPException as exc:
                if exc.detail != "Token expired" or not refresh_token:
                    raise
                current_user = _refresh_access_token(response, refresh_token)

        if roles and current_user["role"] not in roles:
            raise HTTPException(status_code=status.HTTP_403_FORBIDDEN, detail="Insufficient privileges")

        return current_user

    return verifier
