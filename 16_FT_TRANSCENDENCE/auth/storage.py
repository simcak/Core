import os
from io import BytesIO

from minio import Minio

minio_client = Minio(
    os.getenv("MINIO_ENDPOINT", "minio:9000"),
    access_key=os.getenv("MINIO_ACCESS_KEY"),
    secret_key=os.getenv("MINIO_SECRET_KEY"),
    secure=False,
)

BUCKET = os.getenv("MINIO_AVATARS_BUCKET", "avatars")


def upload_avatar(storage_key: str, data: bytes, mime_type: str) -> None:
    minio_client.put_object(BUCKET, storage_key, BytesIO(data), length=len(data), content_type=mime_type)


def get_avatar_stream(storage_key: str):
    return minio_client.get_object(BUCKET, storage_key)


def delete_avatar(storage_key: str) -> None:
    minio_client.remove_object(BUCKET, storage_key)
