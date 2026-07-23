"""
audio/seed.py

Reads MP3s from AUDIOBOOKS_DIR and seeds them into MinIO + Postgres.
Safe to run multiple times — skips files already uploaded.

Expected folder structure in ./audiobooks/:
  audiobooks/
    1/               ← this is the book_id (must exist in your catalog DB)
      chapter01.mp3
      chapter02.mp3
    2/
      chapter01.mp3

Why book_id as folder name? Simple and unambiguous.
"""

import os
import datetime
from io import BytesIO
from pathlib import Path

from minio import Minio
from minio.error import S3Error
from sqlalchemy import create_engine, text
from sqlalchemy.orm import sessionmaker

# ---------------------------------------------------------------------------
# Config from environment (same vars as the audio service itself)
# ---------------------------------------------------------------------------
AUDIOBOOKS_DIR = Path(os.getenv("AUDIOBOOKS_DIR", "/audiobooks"))
MINIO_ENDPOINT = os.getenv("MINIO_ENDPOINT", "minio:9000")
MINIO_ACCESS = os.getenv("MINIO_ACCESS_KEY", "minio")
MINIO_SECRET = os.getenv("MINIO_SECRET_KEY", "minio1234")
MINIO_BUCKET = os.getenv("MINIO_BUCKET", "audio-files")
PUBLISHER_ID = int(os.getenv("SEED_PUBLISHER_ID", "1"))  # a real user id from auth

DB_URL = (
    f"postgresql+psycopg://{os.getenv('DB_USER', 'transcendence')}:"
    f"{os.getenv('DB_PASSWORD', 'transcendence')}@"
    f"{os.getenv('DB_HOST', 'postgres')}:"
    f"{os.getenv('DB_PORT', '5432')}/"
    f"{os.getenv('DB_NAME', 'transcendence')}"
)


# ---------------------------------------------------------------------------
# Helpers
# ---------------------------------------------------------------------------

def minio_client():
    return Minio(MINIO_ENDPOINT, access_key=MINIO_ACCESS,
                 secret_key=MINIO_SECRET, secure=False)


def db_session():
    engine = create_engine(DB_URL, connect_args={"options": "-c search_path=audio"})
    return sessionmaker(bind=engine)()


def already_in_minio(client, key):
    try:
        client.stat_object(MINIO_BUCKET, key)
        return True
    except S3Error:
        return False


def already_in_db(session, key):
    row = session.execute(
        text("SELECT id FROM audio_files WHERE storage_key = :key"),
        {"key": key}
    ).fetchone()
    return row is not None


def upload(client, key, path: Path):
    data = path.read_bytes()
    client.put_object(
        MINIO_BUCKET, key, BytesIO(data),
        length=len(data), content_type="audio/mpeg"
    )
    return len(data)


def insert_row(session, *, book_id, key, filename, size):
    now = datetime.datetime.now(datetime.UTC)
    session.execute(text("""
                         INSERT INTO audio_files
                         (book_id, publisher_id, storage_key, original_filename,
                          file_size, mime_type, status, created_at, updated_at)
                         VALUES (:book_id, :pub, :key, :filename,
                                 :size, 'audio/mpeg', 'ready', :now, :now)
                         """), dict(book_id=book_id, pub=PUBLISHER_ID, key=key,
                                    filename=filename, size=size, now=now))


# ---------------------------------------------------------------------------
# Main
# ---------------------------------------------------------------------------

def seed():
    if not AUDIOBOOKS_DIR.exists():
        print(f"[seed] {AUDIOBOOKS_DIR} does not exist — nothing to seed.")
        print("[seed] Create the folder and put your MP3s in subfolders named by book_id.")
        return

    client = minio_client()
    session = db_session()
    total = uploaded = skipped_minio = skipped_db = 0

    # Walk audiobooks/<book_id>/<file.mp3>
    for book_dir in sorted(AUDIOBOOKS_DIR.iterdir()):
        if not book_dir.is_dir():
            continue
        try:
            book_id = int(book_dir.name)
        except ValueError:
            print(f"[seed] Skipping '{book_dir.name}' — folder name must be a book_id integer.")
            continue

        for mp3 in sorted(book_dir.glob("*.mp3")):
            total += 1
            # Stable key: no UUID — same file always gets the same key
            key = f"books/{book_id}/{mp3.name}"

            in_minio = already_in_minio(client, key)
            in_db = already_in_db(session, key)

            if in_minio:
                print(f"  [skip-minio]  {key}")
                skipped_minio += 1
            else:
                size = upload(client, key, mp3)
                print(f"  [uploaded]    {key}  ({size / 1024 / 1024:.1f} MB)")
                uploaded += 1

            if in_db:
                print(f"  [skip-db]     {key}")
                skipped_db += 1
            else:
                insert_row(session, book_id=book_id, key=key,
                           filename=mp3.name, size=mp3.stat().st_size)
                print(f"  [db-inserted] {key}")

    session.commit()
    session.close()
    print(f"\n[seed] Done. {total} files total: "
          f"{uploaded} uploaded, {skipped_minio} already in MinIO, "
          f"{skipped_db} already in DB.")


if __name__ == "__main__":
    seed()
