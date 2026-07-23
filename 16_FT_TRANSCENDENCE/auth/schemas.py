from pydantic import BaseModel, ConfigDict, field_validator
from datetime import datetime


class RoleResponse(BaseModel):
    model_config = ConfigDict(from_attributes=True)

    id: int
    role_name: str


class UserInfoResponse(BaseModel):
    model_config = ConfigDict(from_attributes=True)

    id: int
    username: str
    first_name: str | None
    last_name: str | None
    avatar_filename: str | None
    is_online: bool


class UserProfileResponse(BaseModel):
    model_config = ConfigDict(from_attributes=True)

    username: str
    first_name: str | None
    last_name: str | None
    email: str
    phone: str | None
    role: RoleResponse
    email_verified: bool
    created_at: datetime
    updated_at: datetime
    avatar_filename: str | None


class UserResponse(BaseModel):
    model_config = ConfigDict(from_attributes=True)

    id: int  # Added: needed for frontend
    username: str
    email: str
    last_name: str | None
    first_name: str | None
    phone: str | None
    avatar_filename: str | None
    role_id: int  # Added: needed for frontend
    role: RoleResponse
    created_at: datetime
    updated_at: datetime
    last_login_at: datetime | None
    status: str
    is_online: bool


class UserSearchResponse(BaseModel):
    model_config = ConfigDict(from_attributes=True)

    id: int
    username: str
    first_name: str | None
    last_name: str | None
    avatar_filename: str | None
    is_online: bool


class UserCreate(BaseModel):
    email: str
    password: str
    username: str | None = None
    first_name: str | None = None
    last_name: str | None = None
    phone: str | None = None


class UserCreateAdmin(BaseModel):
    """Schema for admin creating users (with optional password)"""
    email: str
    username: str
    password: str | None = None  # Optional, will generate if not provided
    first_name: str | None = None
    last_name: str | None = None
    role_id: int = 2  # Default to 'user' role
    phone: str | None = None


class UserUpdate(BaseModel):
    """Schema for updating user"""
    email: str | None = None
    username: str | None = None
    first_name: str | None = None
    last_name: str | None = None
    role_id: int | None = None
    password: str | None = None  # Optional: only update if provided
    phone: str | None = None


class UserProfileUpdateRequest(BaseModel):
    """Schema for profile updates (all fields optional)"""
    first_name: str | None = None
    last_name: str | None = None
    phone: str | None = None
    avatar_filename: str | None = None


class LoginRequest(BaseModel):
    email: str
    password: str


class LoginResponse(BaseModel):
    access_token: str
    token_type: str
    user: UserResponse


class Token(BaseModel):
    access_token: str
    token_type: str


class PublicApiKeyCreate(BaseModel):
    name: str
    expires_at: datetime | None = None

    @field_validator("name")
    @classmethod
    def name_not_empty(cls, v: str) -> str:
        v = v.strip()
        if not v:
            raise ValueError("API key name cannot be empty")
        if len(v) > 100:
            raise ValueError("API key name must be 100 characters or fewer")
        return v


class PublicApiKeyResponse(BaseModel):
    model_config = ConfigDict(from_attributes=True)

    id: int
    name: str
    created_at: datetime
    expires_at: datetime | None
    last_used_at: datetime | None
    revoked: bool


class PublicApiKeyCreateResponse(PublicApiKeyResponse):
    token: str

# ── Users Library (Whislist) ─────────────────────────────────────────────────────────────


class LibraryCreate(BaseModel):
    name: str

    @field_validator("name")
    @classmethod
    def name_not_empty(cls, v: str) -> str:
        v = v.strip()
        if not v:
            raise ValueError("Library name cannot be empty")
        if len(v) > 100:
            raise ValueError("Library name must be 100 characters or fewer")
        return v


class LibraryOut(BaseModel):
    model_config = ConfigDict(from_attributes=True)
    id: int
    name: str
    book_ids: list[int] = []


class LibraryChecked(BaseModel):
    """Returned when opening AddToListMenu — one entry per library with checked state."""
    id: str       # stringified for the frontend BookShelfEntry type
    label: str
    checked: bool
