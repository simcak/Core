import datetime

from sqlalchemy import BigInteger, DateTime, String, Float, Text, UniqueConstraint
from sqlalchemy.orm import Mapped, mapped_column

from database import Base


class AudioFile(Base):
    __tablename__ = "audio_files"
    __table_args__ = (
        UniqueConstraint("storage_key", name="uq_audio_files_storage_key"),
    )

    id: Mapped[int] = mapped_column(BigInteger, primary_key=True, autoincrement=True)
    book_id: Mapped[int] = mapped_column(BigInteger, nullable=False, index=True)
    storage_key: Mapped[str] = mapped_column(Text, nullable=False)
    original_filename: Mapped[str] = mapped_column(String(255), nullable=False)
    file_size: Mapped[int] = mapped_column(BigInteger, nullable=False)
    duration_seconds: Mapped[float | None] = mapped_column(Float, nullable=True)
    mime_type: Mapped[str] = mapped_column(String(50), nullable=False)
    status: Mapped[str] = mapped_column(String(20), nullable=False, server_default="uploading")
    publisher_id: Mapped[int] = mapped_column(BigInteger, nullable=False)
    created_at: Mapped[datetime.datetime] = mapped_column(DateTime, nullable=False)
    updated_at: Mapped[datetime.datetime] = mapped_column(DateTime, nullable=False)
