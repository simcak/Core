import os

from datetime import timedelta
from io import BytesIO
from minio import Minio

minio_client = Minio(
    os.getenv("MINIO_ENDPOINT", "minio:9000"),
    access_key=os.getenv("MINIO_ACCESS_KEY"),
    secret_key=os.getenv("MINIO_SECRET_KEY"),
    secure=False,
)

BUCKET = os.getenv("MINIO_BUCKET", "audio-files")

EXTERNAL_ENDPOINT = os.getenv("MINIO_EXTERNAL_ENDPOINT", "host.docker.internal:9000")

presigned_client = Minio(
    EXTERNAL_ENDPOINT,
    access_key=os.getenv("MINIO_ACCESS_KEY"),
    secret_key=os.getenv("MINIO_SECRET_KEY"),
    secure=False,
)


def ensure_bucket_exists():
    """Create the audio bucket on first upload when local MinIO is empty."""
    if not minio_client.bucket_exists(BUCKET):
        minio_client.make_bucket(BUCKET)


def upload_file(storage_key, data, mime_type, size):
    ensure_bucket_exists()
    minio_client.put_object(BUCKET, storage_key, BytesIO(data), content_type=mime_type, length=size)


def get_object_stat(storage_key):
    return minio_client.stat_object(BUCKET, storage_key)


def get_object_stream(storage_key, offset, length):
    """ .close() and release_conn() is a caller responsibility"""
    return minio_client.get_object(BUCKET, storage_key, offset=offset, length=length)


def delete_object(storage_key):
    minio_client.remove_object(BUCKET, storage_key)


def presign_upload(storage_key: str) -> str:
    url = presigned_client.presigned_put_object(
        BUCKET,
        storage_key,
        expires=timedelta(hours=1),
    )
    internal = os.getenv("MINIO_ENDPOINT", "minio:9000")
    return url.replace(f"http://{internal}", f"http://{EXTERNAL_ENDPOINT}", 1)
