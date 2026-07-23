# Backend

← Back to [tools overview](../tools.md)

All three backend services (`auth`, `catalog`, `audio`) share the same Python stack.

## FastAPI

**What:** the Python web framework powering the `auth`, `catalog`, and `audio` services. *(v0.136.1)*

**Why:** async, fast, and generates **OpenAPI/Swagger docs automatically** — which is what powers our public API documentation. Pydantic models give us request/response validation for free.

**Scope:** all three backend services. Each exposes its own `/docs` (Swagger UI) and `/metrics` (Prometheus, via `prometheus-fastapi-instrumentator`).

## Uvicorn

**What:** the ASGI server that actually runs each FastAPI app. *(v0.46.0)*

**Why:** FastAPI is just the framework; Uvicorn is the process that serves it over HTTP inside each service container.

## SQLAlchemy

**What:** the Python ORM (Object-Relational Mapper) used by all three backend services. *(v2.0.49, with the `psycopg` driver)*

**Why:** lets us define tables as Python classes and query the database without writing raw SQL — safer (no string-built queries), portable, and a natural fit with Alembic for migrations.

**Scope:** every DB access in `auth`, `catalog`, and `audio` goes through SQLAlchemy models. No raw SQL in the codebase.

## Alembic

**What:** database migration tool for SQLAlchemy. *(v1.18.4)*

**Why:** tracks schema changes as versioned migration files committed to the repo. Migrations are reproducible, reversible, and run in order.

**How we run it:** each service has a companion `*-migrate` container in `docker-compose.prod.yml` that runs `alembic upgrade head` before the main service starts. This means migrations always run on deploy without any manual steps.

Migration files live in `<service>/migrations/versions/`. Never edit the database schema directly — always create a new migration file.

> **Deep dive:** see [alembic.md](alembic.md) for the hands-on guide — initializing, creating, and running migrations, plus known issues.

## Pydantic

**What:** data-validation and settings library built into FastAPI. *(v2.13.3)*

**Why:** defines request/response schemas and config models as Python classes; FastAPI uses them to validate input, serialize output, and generate the OpenAPI docs.

## Auth libraries

The `auth` service combines three libraries for authentication:

| Library | Version | Role |
|---|---|---|
| **Authlib** | 1.6.4 | OAuth 2.0 / OpenID Connect client (third-party login) |
| **PyJWT** | 2.8.0 | Issues and verifies JSON Web Tokens for sessions |
| **argon2-cffi** | 25.1.0 | Hashes passwords with Argon2 (current best-practice KDF) |
