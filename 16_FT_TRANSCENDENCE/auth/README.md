# Auth Service

The identity service for the platform. It owns everything about **who a user is**:

- Registration & login (email + password, or 42 OAuth)
- JWT session management (access + refresh tokens, delivered as cookies)
- Profiles, avatars (stored in MinIO), and user search
- The social graph (followers / following) and online presence
- Personal book lists ("My Library")
- A key-gated **Public API** for external integrations
- Admin tools for managing users and API keys

Built with **FastAPI** + **Uvicorn**, **SQLAlchemy 2.0** over **PostgreSQL**, **Alembic** for migrations, **argon2** for password hashing, **PyJWT** for tokens, **Authlib** for 42 OAuth, and **MinIO** for avatar storage.

| Interactive API docs (Swagger) | URL |
|--------------------------------|-----|
| Through Nginx | `https://localhost:4443/auth/docs` |
| Container direct | `http://localhost:8000/auth/docs` |

---

## Contents

1. [How requests reach this service](#how-requests-reach-this-service)
2. [How authentication works](#how-authentication-works)
3. [Validation rules](#validation-rules)
4. [Endpoints](#endpoints)
5. [Public API](#public-api)
6. [curl examples](#curl-examples)
7. [Database & migrations](#database--migrations)

---

## How requests reach this service

| Context | Base URL |
|---------|----------|
| Full stack (via Nginx) | `https://localhost:4443` |

Every endpoint below is written as its path on the auth service. The paths are identical whether you go through Nginx or hit the container directly — Nginx forwards `/auth/*` and `/api/auth/*` to this service.

---

## How authentication works

Sessions are **cookie-based**. On login the service issues two tokens:

| Token | Lifetime | Where it lives | What it is |
|-------|----------|----------------|------------|
| **Access token** | 15 min (default) | `access_token` cookie | A signed JWT with payload `{ user_id, role, exp }` |
| **Refresh token** | 7 days (default) | `refresh_token` cookie | An opaque random token; only its hash is stored in the DB |

Both cookies are set `HttpOnly; Secure; SameSite=Lax`.

- **Other services verify the access token locally** with `verify_jwt_access()` — no network round-trip back to auth is needed.
- **Role checks** are done by passing allowed roles, e.g. `verify_jwt_access(["admin"])` or `verify_jwt_access(["publisher", "admin"])`.
- When the access token expires, call **`POST /auth/jwt/refresh`** to mint a new one from the refresh token.
- **`POST /auth/logout`** marks the refresh token revoked in the DB and clears both cookies.

---

## Validation rules

Applied at the API schema level (Pydantic) during registration and user creation.

### Username

| Rule | Value |
|------|-------|
| Length | 2–25 characters |
| Allowed characters | Alphanumeric (`a-z`, `A-Z`, `0-9`) and apostrophe (`'`) |
| Restriction | Cannot be entirely apostrophes |
| Uniqueness | Must be unique system-wide |

If no username is supplied at registration, it is auto-generated from the email (the part before `@`) and checked against these same rules.

### Password

| Rule | Value |
|------|-------|
| Length | 8–25 characters |
| Uppercase | At least one (`A-Z`) |
| Lowercase | At least one (`a-z`) |
| Number | At least one (`0-9`) |
| Special character | At least one of `` !@#$%^&*()_+-=[]{}|;':",./<>? `` |

---

## Endpoints

### Registration & login

**`POST /auth/register`** — Create a new user (email + password)

```json
{
  "email": "user@example.com",
  "password": "Str0ngPass!",
  "username": "myhandle",
  "first_name": "Jane",
  "last_name": "Doe",
  "phone": "+420..."
}
```

Returns `201 UserResponse`, or `409 Conflict` if the email or username is already taken. See [Validation rules](#validation-rules) for username/password requirements.

**`POST /auth/login`** — Authenticate and receive JWT cookies

```json
{ "email": "user@example.com", "password": "Str0ngPass!" }
```

Returns `200 { access_token, token_type, user }` and sets the `access_token` and `refresh_token` cookies.

**`POST /auth/logout`** — Revoke the refresh token and clear auth cookies. Requires the `access_token` cookie.

**`POST /auth/jwt/refresh`** — Mint a new access token. The refresh-token cookie is checked even if the access token has expired. Returns the new `access_token` in JSON and refreshes the cookie.

### Current user

All of these require the `access_token` cookie.

**`GET /auth/me`** — Get the authenticated user's profile.

**`PUT /auth/editProfile`** — Update your own profile.

```json
{ "first_name": "Jane", "last_name": "Doe", "phone": "+420...", "avatar_filename": "..." }
```

**`POST /auth/me/avatar`** — Upload an avatar image (JPEG/PNG/WebP, max 10 MB). Multipart upload via the `file` field. Stored in the MinIO `avatars` bucket at `users/{id}/{uuid}/{filename}`.

**`GET /auth/me/avatar`** — Stream your own avatar from MinIO.

**`POST /auth/heartbeat`** — Mark yourself as recently active (`204`). Stamps `last_seen_at = now`. A user is reported **online** while `last_seen_at` is within the last 60 s (`User.is_online`). The frontend pings this periodically so friends see live online/offline state.

### Followers

**`GET /auth/me/followers`** — Users who follow me (newest first).

**`GET /auth/me/following`** — Users I follow (newest first).

**`POST /auth/me/follow/{target_user_id}`** — Follow a user (`204`; `400` if following yourself or already following).

### Book lists ("My Library")

Personal, named lists of books owned by the current user. Surfaced on the Shelf page.

**`GET /auth/me/libraries`** — List my libraries (each with its books).

**`POST /auth/me/libraries`** — Create a library. Returns `201 LibraryOut`; names are unique per user (`409` on duplicate).

```json
{ "name": "Want to read" }
```

**`PATCH /auth/me/libraries/{library_id}`** — Rename a library.

**`DELETE /auth/me/libraries/{library_id}`** — Delete a library and its book links (`204`).

**`GET /auth/me/books/{book_id}/libraries`** — Which of my libraries contain this book (used to render checkboxes).

**`POST /auth/me/libraries/{library_id}/books/{book_id}`** — Add a book to a library (`201`).

**`DELETE /auth/me/libraries/{library_id}/books/{book_id}`** — Remove a book from a library (`204`).

### User lookup

**`GET /auth/users/{user_id}`** — Get a user by ID (requires auth).

**`GET /auth/users/{user_id}/avatar`** — Get any user's avatar (public, no auth needed).

**`GET /auth/search/users?q=<query>&limit=10`** — Search users by username or name. Results are ranked exact match → prefix → contains, capped at 30.

### 42 OAuth

**`GET /auth/42`** — Redirect to the 42 intra authorization page.

**`GET /auth/42/callback`** — OAuth callback: creates or links the user, sets cookies, and redirects to the frontend.

### Admin — users (require `admin` role)

**`GET /auth/admin/users`** — List all users.

**`POST /auth/admin/users`** — Create a user.

```json
{
  "username": "newuser",
  "email": "new@example.com",
  "password": "Str0ng!",
  "role_id": 1,
  "first_name": "New",
  "last_name": "User",
  "phone": null
}
```

**`PUT /auth/admin/users/{user_id}`** — Update a user (partial update).

**`DELETE /auth/admin/users/{user_id}`** — Delete a user and their refresh tokens (`204`).

### Admin — Public API keys (require `admin` role)

Issue and manage the keys used by the [Public API](#public-api).

**`GET /auth/admin/public-api-keys`** — List all keys. Hashes are never exposed; shows name, created/expiry, `last_used_at`, and revoked status.

**`POST /auth/admin/public-api-keys`** — Create a key.

```json
{ "name": "partner-integration", "expires_at": null }
```

Returns `201 PublicApiKeyCreateResponse`. This is the **only** time the raw `token` (`abp_…`) is shown — store it immediately, since only its SHA-256 hash is persisted.

**`PATCH /auth/admin/public-api-keys/{api_key_id}/revoke`** — Revoke a key (keeps the row, sets `revoked = true`).

**`DELETE /auth/admin/public-api-keys/{api_key_id}`** — Permanently delete a key (`204`).

---

## Public API

A key-gated public surface under `/api/public/auth/` (mirrored by the catalog and audio services). It is **separate** from the cookie-based session auth above.

- **Auth:** send `X-API-Key: <key>` or `Authorization: Bearer <key>`. The key is looked up by SHA-256 hash; revoked or expired keys get `401`. Each successful call updates `last_used_at`.
- **Rate limit:** Nginx caps `/api/public/*` at **10 requests/minute per IP** (`429` when exceeded).
- **Docs:** `/api/public/auth/docs` (this service) and the aggregated `/api/public/docs` (all three services merged).

**`GET /api/public/auth/users/{user_id}`** — Public user data (id, username, names, avatar, status).

**`PATCH /api/public/auth/users/{user_id}`** — Update username / names / avatar (validated; enforces unique username).

**`DELETE /api/public/auth/users/{user_id}`** — Scrub personal fields (names, avatar). A soft erase that keeps the account.

**`GET /api/public/auth/test`** — Connectivity check (`{ "message": "hello world", "service": "auth" }`).

---

## curl examples

```bash
# Register
curl -X POST https://localhost:4443/auth/register -k \
  -H 'Content-Type: application/json' \
  -d '{"email":"user@example.com","password":"Str0ng!","username":"myhandle"}'

# Login (saves cookies to a file)
curl -X POST https://localhost:4443/auth/login -k \
  -H 'Content-Type: application/json' \
  -c /tmp/cookies.txt \
  -d '{"email":"user@example.com","password":"Str0ng!"}'

# Get current user (reuses saved cookies)
curl https://localhost:4443/auth/me -k -b /tmp/cookies.txt

# Search users
curl 'https://localhost:4443/auth/search/users?q=jane' -k -b /tmp/cookies.txt
```

---

## Database & migrations

Alembic migrations live in `auth/migrations/versions/` and run automatically on `make up`.

```bash
# Run migrations manually
docker compose run --rm auth-migrate

# Seed dev data
docker compose run --rm auth-seed

# Create a new migration (after changing models.py)
docker compose run --rm auth-migrate \
  alembic -c migrations/alembic.ini revision --autogenerate -m "describe change"
```

> Do not delete applied revision files.

### Tables

| Table | Key fields |
|-------|-----------|
| `users` | id, username, email, password_hash (nullable for OAuth), role_id, status, first_name, last_name, avatar_filename, oauth_provider, oauth_id, `last_seen_at` (online presence) |
| `role` | id, role_name (`user` / `admin` / `publisher`) |
| `refresh_tokens` | id, token_hash, user_id, expires_at, revoked |
| `followers` | id, follower_id → users, followed_id → users |
| `public_api_keys` | id, name, token_hash (SHA-256), created_at, expires_at (nullable), last_used_at, revoked |
| `users_library` | id, user_id → users, name (unique per user) |
| `users_library_book` | library_id → users_library, book_id (composite PK) |
