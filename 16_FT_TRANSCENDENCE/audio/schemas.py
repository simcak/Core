from datetime import datetime
from pydantic import BaseModel, ConfigDict


class AudioFileResponse(BaseModel):
    model_config = ConfigDict(from_attributes=True)

    id: int
    book_id: int
    original_filename: str
    file_size: int
    mime_type: str
    status: str
    duration_seconds: float | None
    created_at: datetime


class PublicAudioFileResponse(BaseModel):
    model_config = ConfigDict(from_attributes=True)

    id: int
    original_filename: str
    mime_type: str
    duration_seconds: float | None


class PresignRequest(BaseModel):
    book_id: int
    filename: str
    content_type: str
    size: int


class PresignResponse(BaseModel):
    upload_url: str
    object_key: str


class RegisterRequest(BaseModel):
    book_id: int
    object_key: str
    original_filename: str
    file_size: int
    mime_type: str
