# Audio Service

Owns audio delivery: file upload, MinIO storage, and **HTTP-Range streaming** for the in-browser player.

Nginx forwards `/api/audio/*` to this service and **strips the `/api/audio/` prefix**, with `proxy_buffering off` so partial (`206`) responses stream straight to the client. Every route below is therefore reachable both as `/api/audio/<path>` (through Nginx) and `/<path>` (on the container).

---

## Endpoints

| Method | Path | Purpose |
|--------|------|---------|
| GET | `/health` | Health check (also `/api/audio/health`) |
| POST | `/upload` | Upload an audio file (publisher/admin). Stores to MinIO, creates `audio_files` row |
| POST | `/presign` | Get a presigned MinIO URL for direct upload |
| POST | `/files/register` | Register a file uploaded via presigned URL |
| GET | `/files/{book_id}` | List audio files for a book |
| DELETE | `/files/{file_id}` | Delete an audio file (and its MinIO object) |
| GET | `/public/{book_id}` | Public-facing audio file list for a book |
| GET | `/stream/{file_id}` | **Stream audio** — honours `Range`, returns `206 Partial Content` |

---

## Public API

A key-gated surface lives at `/api/public/audio/` (mirrors auth & catalog). Send `X-API-Key: <key>` or `Authorization: Bearer <key>`; Nginx rate-limits `/api/public/*` to 10 req/min per IP. Connectivity check: `GET /api/public/audio/test`.

---

## Data Model

| Table | Key fields |
|-------|-----------|
| `audio_files` | id, book_id (indexed), `storage_key` (unique, MinIO object key), original_filename, file_size, duration_seconds, mime_type, status (`uploading` → ready), publisher_id, created_at, updated_at |

## Migrations

Alembic migrations in `audio/migrations/versions/`, run automatically on `make up` via the `audio-migrate` container. See [Alembic notes](../docs/tools/alembic.md).

---

## Module of Choice — Audio Streaming (Major, 2 pts)

- **Why we chose it.** AudioBerry is an audiobook platform, so audio delivery *is* the product. No listed module covers seek-friendly media streaming from object storage.
- **Technical challenges.** Correct **HTTP Range streaming** in [`/stream/{file_id}`](router.py): parse the `Range` header (incl. suffix ranges), stream *only* that byte slice from MinIO via `offset`/`length` (no whole-file buffering, flat memory under load), return `206 Partial Content` with `Content-Range`/`Accept-Ranges`/`Content-Length`, and `416` for unsatisfiable ranges. Plus presigned direct-to-storage uploads and keeping partials intact through Nginx (`proxy_buffering off`).
- **How it adds value.** Enables instant seeking and immediate playback on multi-hour files — the difference between a usable app and a demo — and scales cheaply because memory stays flat with file size and concurrent listeners.
- **Why Major (2 pts).** A standalone, independently deployed service: MinIO object storage, two upload paths, JWT role gating, rate-limited public API, Alembic migrations, structured logs, and Prometheus metrics — substantial and materially harder than "return the file".

> **In plain terms:** a non-streaming server photocopies the whole book every time you ask "what's on page 200?". Range streaming flips straight to page 200 and hands you that page.

**Implementation:** FastAPI microservice ([router.py](router.py), [storage.py](storage.py), [models.py](models.py), [public_api.py](public_api.py)) behind Nginx; audio bytes in MinIO, metadata in `audio_files`; `StreamingResponse` over MinIO's range read.

**Contributors:** iasonov, psimcak, pkostura.

**Demo:** upload via `POST /api/audio/upload` → play → drag the seek bar and show the `Range` request returning **`206 Partial Content`** in DevTools → request past EOF for a **`416`**.
