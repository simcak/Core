# Databases & Storage

← Back to [tools overview](../tools.md)

## PostgreSQL

**What:** relational database, version 16.

**Why:** solid, well-understood, and well-supported by SQLAlchemy and Alembic. All services share one PostgreSQL instance but use separate schemas (`auth`, `catalog`, `audio`) to isolate their data.

**Schema ownership:** each service owns its own schema. Migrations are managed by Alembic and run automatically on deploy.

## Redis

**What:** in-memory key-value store. *(v7-alpine)*

**Why:** used for caching and session storage. Fast and simple to operate.

Redis has no external port exposed in production — it is only reachable from inside the Docker network.

## MinIO

**What:** S3-compatible object storage, run as a container. *(`minio/minio:latest`)*

**Why:** the `audio` service stores audiobook media files (and other large binary assets) as objects rather than in PostgreSQL. MinIO gives us the same API as Amazon S3 but self-hosted and free.

**How we use it:** backend services talk to it through the official `minio` Python client (v7.2.20). The companion `minio/mc` container provisions buckets and policies on startup.

## pgAdmin

**What:** web-based PostgreSQL administration UI. *(`dpage/pgadmin4`)*

**Why:** convenient browser GUI to inspect tables and run queries during development. Defined in the base compose file; **development only** — not part of the production stack.
