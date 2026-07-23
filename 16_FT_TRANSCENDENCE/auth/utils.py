from argon2 import PasswordHasher
from argon2.exceptions import VerifyMismatchError, VerificationError, InvalidHashError
import re
from sqlalchemy.orm import Session
from sqlalchemy import select
from models import User


ph = PasswordHasher()


def hash_password(password: str) -> str:
    return ph.hash(password)


def verify_password(password: str, password_hash: str | None) -> bool:
    if not password_hash:
        return False

    try:
        return ph.verify(password_hash, password)
    except (VerifyMismatchError, VerificationError, InvalidHashError):
        return False


def ensure_unique_username(db: Session, desired: str) -> str:
    base = desired.strip().lower() if desired else "user"
    candidate = base
    suffix = 0
    while db.execute(select(User).where(User.username == candidate)).scalar_one_or_none():
        suffix += 1
        candidate = f"{base}{suffix}"
    return candidate


def validate_username(username: str) -> None:
    if not (2 <= len(username) <= 25):
        raise ValueError("Username must be between 2 and 25 characters")
    if not re.match(r"^[a-zA-Z0-9']+$", username):
        raise ValueError(
            "Username can only contain alphanumeric characters and apostrophes"
        )
    if all(c == "'" for c in username):
        raise ValueError("Username cannot be only apostrophes")


def validate_password(password: str) -> None:
    if not (8 <= len(password) <= 25):
        raise ValueError("Password must be between 8 and 25 characters")
    if not re.search(r"[A-Z]", password):
        raise ValueError("Password must contain at least one uppercase letter")
    if not re.search(r"[a-z]", password):
        raise ValueError("Password must contain at least one lowercase letter")
    if not re.search(r"\d", password):
        raise ValueError("Password must contain at least one number")
    if not re.search(r'[!@#$%^&*()_+\-=\[\]{};\':"\\|,.<>\/\?]', password):
        raise ValueError("Password must contain at least one special character")
