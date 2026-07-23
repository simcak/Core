import os
from uuid import uuid4
import datetime
import time

import structlog
from fastapi import FastAPI, Depends, UploadFile, File, Form, HTTPException, Request, status
from fastapi.middleware.cors import CORSMiddleware
from fastapi.responses import StreamingResponse
from sqlalchemy.orm import Session
from sqlalchemy import text, select
from typing import Annotated, Any, List

from schemas import AudioFileResponse, PublicAudioFileResponse, PresignResponse, PresignRequest, RegisterRequest
from database import get_db
from storage import upload_file, delete_object, get_object_stat, get_object_stream, presign_upload
from models import AudioFile
from minio.error import S3Error
from jwt_handler import verify_jwt_access
from prometheus_fastapi_instrumentator import Instrumentator
from public_api import router as public_api_router

app = FastAPI()
app.include_router(public_api_router)

cors_env = os.getenv("CORS_ORIGINS", "")
origins = cors_env.split(",") if cors_env else []
app.add_middleware(
    CORSMiddleware,
    allow_origins=origins,
    allow_credentials=True,
    allow_methods=["*"],
    allow_headers=["*"],
)

ALLOWED_TYPES = {"audio/mpeg", "audio/wav", "audio/ogg", "audio/mp4", "audio/mp3", "audio/aac"}

structlog.configure(
    processors=[
        structlog.stdlib.add_log_level,
        structlog.processors.TimeStamper(fmt="iso"),
        structlog.processors.JSONRenderer(),
    ],
    logger_factory=structlog.PrintLoggerFactory(),
)

log = structlog.get_logger()

cors_env = os.getenv("CORS_ORIGINS", "")
origins = cors_env.split(",") if cors_env else []
app.add_middleware(
    CORSMiddleware,
    allow_origins=origins,
    allow_credentials=True,
    allow_methods=["*"],
    allow_headers=["*"],
)

Instrumentator().instrument(app).expose(app)

CurrentUser = Annotated[dict[str, Any], Depends(verify_jwt_access())]
PublisherUser = Annotated[dict[str, Any], Depends(verify_jwt_access(["publisher", "admin"]))]


@app.get("/api/audio/health")
@app.get("/health")
def health(db: Session = Depends(get_db)):
    db.execute(text("SELECT 1"))
    return {"status": "ok", "service": "audio", "db": "connected"}


@app.post("/api/audio/upload", response_model=AudioFileResponse, status_code=status.HTTP_201_CREATED)
@app.post("/upload", response_model=AudioFileResponse, status_code=status.HTTP_201_CREATED)
async def upload(current_user: PublisherUser,
                 file: UploadFile = File(...),
                 book_id: int = Form(...),
                 db: Session = Depends(get_db)):
    start = time.monotonic()
    if file.content_type not in ALLOWED_TYPES:
        log.warning("upload_rejected", reason="invalid_content_type",
                    filename=file.filename, content_type=file.content_type, book_id=book_id)
        raise HTTPException(status_code=status.HTTP_400_BAD_REQUEST, detail="File type not allowed")
    contents = await file.read()
    if len(contents) > 500 * 1024 * 1024:
        log.warning("upload_rejected", reason="file_too_large",
                    filename=file.filename, file_size_bytes=len(contents), book_id=book_id)
        raise HTTPException(status_code=status.HTTP_400_BAD_REQUEST, detail="File too large")
    if len(contents) < 1024:
        log.warning("upload_rejected", reason="file too small",
                    filename=file.filename, file_size_bytes=len(contents), book_id=book_id)
        raise HTTPException(status_code=status.HTTP_400_BAD_REQUEST, detail="File too small")
    storage_key = f"books/{book_id}/{uuid4()}/{file.filename}"
    now = datetime.datetime.now(datetime.UTC)
    audio_file = AudioFile(
        book_id=book_id,
        storage_key=storage_key,
        original_filename=file.filename,
        file_size=len(contents),
        mime_type=file.content_type,
        status="uploading",
        publisher_id=current_user["user_id"],
        created_at=now,
        updated_at=now
    )
    db.add(audio_file)
    db.commit()
    db.refresh(audio_file)
    try:
        upload_file(storage_key, contents, file.content_type, len(contents))
        log.info("upload_complete", filename=file.filename, book_id=book_id, file_size_bytes=len(contents),
                 duration_ms=round((time.monotonic() - start) * 1000))
    except S3Error as e:
        audio_file.status = "error"
        db.commit()
        log.error("upload_failed", filename=file.filename, book_id=book_id,
                  audio_file_id=audio_file.id, error=str(e),
                  duration_ms=round((time.monotonic() - start) * 1000))
        raise HTTPException(status_code=status.HTTP_500_INTERNAL_SERVER_ERROR, detail=str(e))
    audio_file.status = "ready"
    audio_file.updated_at = datetime.datetime.now(datetime.UTC)
    db.commit()
    db.refresh(audio_file)
    return audio_file


@app.post("/presign", response_model=PresignResponse)
def presign(
        body: PresignRequest,
        current_user: PublisherUser,
):
    if body.content_type not in ALLOWED_TYPES:
        log.warning("upload_rejected", reason="invalid_content_type",
                    filename=body.filename, content_type=body.content_type, book_id=body.book_id)
        raise HTTPException(status_code=status.HTTP_400_BAD_REQUEST, detail="File type not allowed")
    if body.size > 500 * 1024 * 1024:
        log.warning("upload_rejected", reason="file_too_large",
                    filename=body.filename, file_size_bytes=body.size, book_id=body.book_id)
        raise HTTPException(status_code=status.HTTP_400_BAD_REQUEST, detail="File too large")
    if body.size < 1024:
        log.warning("upload_rejected", reason="file too small",
                    filename=body.filename, file_size_bytes=body.size, book_id=body.book_id)
        raise HTTPException(status_code=status.HTTP_400_BAD_REQUEST, detail="File too small")
    storage_key = f"books/{body.book_id}/{uuid4()}/{body.filename}"
    url = presign_upload(storage_key)
    log.info("presign_issued", book_id=body.book_id, filename=body.filename, user_id=current_user["user_id"])
    return PresignResponse(upload_url=url, object_key=storage_key)


@app.post("/files/register", response_model=AudioFileResponse, status_code=status.HTTP_201_CREATED)
def register_file(
        body: RegisterRequest,
        current_user: PublisherUser,
        db: Session = Depends(get_db),
):
    start = time.monotonic()
    now = datetime.datetime.now(datetime.UTC)
    audio_file = AudioFile(
        book_id=body.book_id,
        storage_key=body.object_key,
        original_filename=body.original_filename,
        file_size=body.file_size,
        mime_type=body.mime_type,
        status="ready",
        publisher_id=current_user["user_id"],
        created_at=now,
        updated_at=now
    )
    db.add(audio_file)
    db.commit()
    db.refresh(audio_file)
    log.info("file_registered", filename=body.original_filename, book_id=body.book_id, file_size_bytes=body.file_size,
             duration_ms=round((time.monotonic() - start) * 1000))
    return audio_file


@app.get("/api/audio/files/{book_id}", response_model=List[AudioFileResponse])
@app.get("/files/{book_id}", response_model=List[AudioFileResponse])
def get_files(
        book_id: int,
        current_user: PublisherUser,
        db: Session = Depends(get_db)
):
    files = db.execute(
        select(AudioFile).where(AudioFile.book_id == book_id)
    ).scalars().all()
    return files


@app.delete("/api/audio/files/{file_id}", status_code=status.HTTP_204_NO_CONTENT)
@app.delete("/files/{file_id}", status_code=status.HTTP_204_NO_CONTENT)
def delete_file(
        file_id: int,
        current_user: PublisherUser,
        db: Session = Depends(get_db)
):
    audio_file = db.get(AudioFile, file_id)
    if not audio_file:
        log.warning("delete_not_found", file_id=file_id, user_id=current_user["user_id"])
        raise HTTPException(status_code=status.HTTP_404_NOT_FOUND, detail="File not found")
    try:
        delete_object(audio_file.storage_key)
        db.delete(audio_file)
        db.commit()
        log.info("file_deleted", file_id=file_id, storage_key=audio_file.storage_key,
                 user_id=current_user["user_id"])
    except S3Error as e:
        log.error("delete_storage_failed", file_id=file_id,
                  storage_key=audio_file.storage_key, user_id=current_user["user_id"], error=str(e))
        raise HTTPException(status_code=status.HTTP_500_INTERNAL_SERVER_ERROR, detail="Storage error")
    except Exception as e:
        log.error("delete_db_failed_after_storage", file_id=file_id,
                  storage_key=audio_file.storage_key, user_id=current_user["user_id"], error=str(e))
        raise HTTPException(status_code=status.HTTP_500_INTERNAL_SERVER_ERROR, detail="Database error")


@app.get("/api/audio/public/{book_id}", response_model=List[PublicAudioFileResponse])
@app.get("/public/{book_id}", response_model=List[PublicAudioFileResponse])
def get_public_files(book_id: int, current_user: CurrentUser, db: Session = Depends(get_db)):
    files = db.execute(
        select(AudioFile)
        .where(AudioFile.book_id == book_id, AudioFile.status == "ready")
        .order_by(AudioFile.id)
    ).scalars().all()
    return files


@app.get("/api/audio/stream/{file_id}")
@app.get("/stream/{file_id}")
async def stream_audio(
        file_id: int,
        request: Request,
        current_user: CurrentUser,
        db: Session = Depends(get_db),
):
    audio_file = db.get(AudioFile, file_id)
    if not audio_file or audio_file.status != "ready":
        raise HTTPException(status_code=status.HTTP_404_NOT_FOUND, detail="Audio file not found")

    stat = get_object_stat(audio_file.storage_key)
    file_size = stat.size

    range_header = request.headers.get("range")
    start = 0
    end = file_size - 1

    if range_header:
        try:
            unit, range_value = range_header.split("=", 1)
            if unit.strip().lower() != "bytes":
                raise ValueError("Only byte ranges are supported")

            start_s, end_s = range_value.split("-", 1)
            if start_s == "":
                # Suffix range, e.g. bytes=-500 means the last 500 bytes.
                suffix_length = int(end_s)
                start = max(file_size - suffix_length, 0)
            else:
                start = int(start_s)
                end = int(end_s) if end_s else file_size - 1

            if start < 0 or end >= file_size or start > end:
                raise ValueError("Requested range is not satisfiable")
        except ValueError:
            raise HTTPException(
                status_code=status.HTTP_416_REQUESTED_RANGE_NOT_SATISFIABLE,
                detail="Invalid range",
                headers={"Content-Range": f"bytes */{file_size}"},
            )

    length = end - start + 1

    def generate():
        stream = None
        try:
            stream = get_object_stream(audio_file.storage_key, start, length)
            for chunk in stream:
                yield chunk
        finally:
            if stream:
                stream.close()
                stream.release_conn()

    headers = {
        "Content-Range": f"bytes {start}-{end}/{file_size}",
        "Accept-Ranges": "bytes",
        "Content-Length": str(length),
    }
    log.info("stream_request", file_id=file_id, book_id=audio_file.book_id,
             start=start, end=end, length=length)
    return StreamingResponse(
        generate(),
        status_code=206 if range_header else 200,
        headers=headers,
        media_type=audio_file.mime_type,
    )
