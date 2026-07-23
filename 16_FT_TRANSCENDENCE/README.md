*This project has been created as part of the 42 curriculum by berneri, iasonov, postura, psimcak, relgheit.*

# AudioBerry - ft_transcendence

**An audiobook platform** — browse a catalog, build personal libraries, and stream audiobooks right in the browser. Built as a containerized **microservices** web app for the 42 *ft_transcendence* project.

> **Want the full technical map?**
> Open **[docs/architecture-interactive.html](docs/architecture-interactive.html)** — a clickable reference for every service, endpoint, data model, auth flow, and Nginx route.

---

## Description

AudioBerry is a multi-user audiobook web application. Users sign up (email/password or 42 OAuth or Google), discover books in a searchable catalog, organize them into named libraries ("My Library"), and stream the audio with instant seeking. Admins manage users, books, and API keys.

**Key features**
- 📚 **Catalog** — books, authors, publishers, categories, multi-language translations, reviews & ratings
- 🔊 **Streaming player** — seek-friendly HTTP-Range audio streaming from object storage
- 👤 **Accounts** — email/password + **42 OAuth** + Google, JWT sessions, avatars, follower graph, live online presence
- 🗂️ **Personal libraries** — create named book lists and add/remove books
- 🛠️ **Admin panel** — role-based user/book management and public-API key issuance
- 🔑 **Public API** — key-gated, rate-limited, self-documented (Swagger)
- 📈 **Ops** — Prometheus/Grafana metrics and an ELK logging pipeline

---

## Instructions

### Prerequisites
- **Docker** + the **Docker Compose** plugin (`docker compose`)

### Setup
```bash
cp .env.example .env        # then adjust if needed
```
Key variables in `.env`:

| Variable | Purpose |
|----------|---------|
| `SECRET_KEY` | JWT signing secret (**required**) |
| `DB_*` | Postgres connection (defaults work locally) |
| `MINIO_ROOT_USER` / `MINIO_ROOT_PASSWORD` | Object-storage credentials (defaults work) |
| `CORS_ORIGINS` | Set to `http://localhost:5173` when running the frontend outside Docker |

Download `audiobooks` folder with mp3s for seeding.

### Run
```bash
make up          # = docker compose up -d --build — starts the whole stack
```

| URL | What |
|-----|------|
| https://localhost:4443 | **App** (HTTPS, self-signed cert — accept the warning) |
| http://localhost:8000 | App (HTTP → redirects to HTTPS) |
| http://localhost:5050 | pgAdmin (dev only) |
| http://localhost:9001 | MinIO console |

### Optional overlays & common commands
```bash
make help            # print out what make can do
make up-elk          # add ELK logging  (Filebeat → Logstash → Elasticsearch → Kibana)
make up-monitoring   # add Prometheus + Grafana
make down            # stop (keep DB)
make clean           # stop + wipe volumes
make logs [service=auth]
make frontend        # Vite dev server w/ hot reload
```
Full developer workflow: **[docs/dev/dev_workflow.md](docs/dev/dev_workflow.md)** · How-to (add endpoints, migrations, local dev): **[docs/dev/how_to.md](docs/dev/how_to.md)**

---

## Technical Stack

| Layer              | Choice | Why |
|--------------------|--------|-----|
| **Frontend**       | React 19 + TypeScript + Vite, Tailwind / shadcn | Component model, instant HMR, fast prod bundle |
| **Backend**        | FastAPI (Python) × 3 services | Async, auto-generated OpenAPI docs, Pydantic validation |
| **Database**       | PostgreSQL 16 + SQLAlchemy ORM + Alembic | Reliable, one instance / per-service schemas, versioned migrations |
| **Object storage** | MinIO | S3-compatible storage for audio, covers, avatars |
| **Cache**          | Redis 7 | Caching / queues (internal only) |
| **Edge**           | Nginx | TLS termination, path-based routing, rate limiting |
| **Ops**            | Prometheus + Grafana, ELK | Metrics & centralized logs |
| **CI/CD**          | GitLab CI on a self-hosted Hetzner runner | See [pipeline](docs/tools/pipeline.md) |

Detailed rationale for every tool: **[docs/tools.md](docs/tools.md)**.

---

## Architecture

Browser → **Nginx** (TLS) → the right service by URL prefix. Services own separate Postgres schemas and share MinIO for files.

| Service | Responsibility | Docs |
|---------|----------------|------|
| **nginx** | Reverse proxy, TLS, routing, rate limiting | [routing table](docs/architecture.md#nginx-url-routing) |
| **frontend** | React SPA | [frontend UI](docs/dev/frontend_ui.md) |
| **auth** | Users, JWT, 42 OAuth, avatars, followers, libraries | [auth/README.md](auth/README.md) |
| **catalog** | Books, authors, publishers, categories, reviews, covers | — |
| **audio** | Upload + HTTP-Range streaming | [audio/README.md](audio/README.md) |
| **postgres / minio / redis** | Data, object storage, cache | — |

Full diagrams, request/data flow, and the Nginx route table: **[docs/architecture.md](docs/architecture.md)**.

---

## Database Schema

One PostgreSQL instance, **three isolated schemas** (one per service):

- **`auth`** — `users`, `role`, `refresh_tokens`, `followers`, `public_api_keys`, `users_library`, `users_library_book`
- **`catalog`** — `book`, `author`, `publisher`, `publisher_followers`, `book_category`, `book_book_category`, `book_translations`, `book_review`
- **`audio`** — `audio_files`

Key relationships: a `book` belongs to one `author` and an optional `publisher`, has many `book_translations`, and links to `book_category` through `book_book_category` (many-to-many). `book_review` and `audio_files` reference a `book` by id; `audio_files` are stored in MinIO and keyed by a unique `storage_key`.

---

## Modules

| Module                                         | Category          | Type  | Pts   | Status |
|------------------------------------------------|-------------------|-------|-------|--------|
| Framework (FE + BE)                            | Web               | Major |   2   |   ✅   |
| Public API (key, rate limit, docs)             | Web               | Major |   2   |   ✅   |
| ORM for database                               | Web               | Minor |   1   |   ✅   |
| Search                                         | Web               | Minor |   1   |   ✅   |
| File uploading system                          | Web               | Minor |   1   |   ✅   |
| Multiple Languages                             | Accessibility     | Minor |   1   |   ✅   |
| RTL language support                           | Accessibility     | Minor |   1   |   ✅   |
| Support for additional browsers                | Accessibility     | Minor |   1   |   ✅   |
| Standard user management + auth                | User Mgmt         | Major |   2   |   ✅   |
| OAuth 2.0 (42 intra, Google)                   | User Mgmt         | Minor |   1   |   ✅   |
| Advanced permissions (roles, CRUD)             | User Mgmt         | Major |   2   |   ✅   |
| ELK (Elasticsearch, Logstash, Kibana)          | DevOps            | Major |   2   |   ✅   |
| Prometheus + Grafana monitoring                | DevOps            | Major |   2   |   ✅   |
| Backend as microservices                       | DevOps            | Major |   2   |   ✅   |
| [Audio streaming](audio/README.md)             | Modules of choice | Major |   2   |   ✅   |
| [Alembic db migrations](docs/tools/alembic.md) | Modules of choice | Minor |   1   |   ✅   |
| **Total**                                      |                   |       | **24**|        |
Maybe Minor:  Custom-made design system with reusable components
---

## Features

- **Accounts & profiles** — register/login, 42 OAuth, JWT cookie sessions, editable profile, avatar upload, follower graph, live online presence
- **Personal libraries** — create named lists, add/remove books, see which lists contain a book
- **Catalog** — browse/search books by title, author, genre; book detail with reviews, ratings, translations
- **Audio playback** — streaming player with seeking, narrator/language selection
- **Admin** — role-gated user & book CRUD, public-API key management
- **Public API** — key-authenticated, rate-limited, Swagger-documented surface across all three services

---

## Team

| Member (42 login) | Role(s) | Responsibilities |
|----------|------------------|--------------------|
| cberneri |  Developer       | Implements features and fixes across services, writes tests, reviews merge requests |
| iasonov  |  Tech Lead       | Owns technical direction and architecture decisions, sets coding standards, reviews/approves merge requests, unblocks the team on hard technical problems |
| postura  |  Developer       | Implements features and fixes across services, writes tests, reviews merge requests |
| psimcak  |  Product Owner   | Defines and prioritizes scope/requirements, represents user needs, signs off on what gets built |
| relgheit |  Project Manager | Plans and tracks progress, runs stand-ups/coordination, manages timeline and blockers |

---

## Project Management

- **Source control & CI/CD:** GitLab — Merge Requests with reviewer approval, GitLab CI on a self-hosted runner ([pipeline](docs/tools/pipeline.md))
- **Task tracking:** GitLab: Issues in Milestones && Slack
- **Communication:** Slack (with Canvas and files), Google Meet
- **Workflow:** branch → MR → review → CI → merge. See **[docs/dev/dev_workflow.md](docs/dev/dev_workflow.md)**.

---

## Individual Contributions

**cberneri**: Framework, ORM, Advanced permissions, Backend as microservices, Alembic
**iasonov**:  Framework, ORM, File uploading system, Support for additional browsers, Advanced permissions, Backend as microservices, Prometheus + Grafana, ELK, Alembic
**postura**:  Framework, Public API, Search, Support for additional browsers, Standard user management + auth, OAuth 2.0 (42 intra, Google), Backend as microservices, Alembic
**psimcak**:  Framework, Multiple Languages, RTL lang. supp., Support for additional browsers, Backend as microservices, Alembic, Audio streaming
**relgheit**: Framework, ORM, Search, Standard user management + auth, Backend as microservices, Alembic
---

## Documentation Map

Docs are layered from gentle to deep:

1. **[Web app explainer](docs/web_app_architecture_explainer.html)** — colorful, no-jargon intro to how a web app works *(start here if you're new)*
2. **[Architecture overview](docs/architecture.md)** + **[interactive diagram](docs/architecture-interactive.html)** — the system, visually
3. **[Data flows](docs/dataflow_diagram.md)** · **[Tools & why](docs/tools.md)**
4. **Service references** — [auth](auth/README.md) · [audio](audio/README.md) — endpoints, models, examples
5. **Dev guides** — [workflow](docs/dev/dev_workflow.md) · [how-to](docs/dev/how_to.md) · [CI/CD pipeline](docs/tools/pipeline.md) · [ELK](docs/dev/elk.md) · [user validation](docs/user_validation.md) · [FAQ](docs/FAQ.md)

---

## Resources

### References
- [FastAPI](https://fastapi.tiangolo.com/) · [SQLAlchemy](https://docs.sqlalchemy.org/) · [Alembic](https://alembic.sqlalchemy.org/)
- [React](https://react.dev/) · [Vite](https://vitejs.dev/) · [Tailwind CSS](https://tailwindcss.com/) · [shadcn/ui](https://ui.shadcn.com/)
- [PostgreSQL](https://www.postgresql.org/docs/) · [MinIO](https://min.io/docs/) · [Nginx](https://nginx.org/en/docs/) · [Docker Compose](https://docs.docker.com/compose/)
- [Prometheus](https://prometheus.io/docs/) · [Grafana](https://grafana.com/docs/) · [Elastic Stack](https://www.elastic.co/guide/)

### Use of AI
LLMs were used as a productivity aid for: scaffolding boilerplate, drafting and organizing documentation, writing migration/test snippets, and debugging. All AI-generated content was reviewed, tested, and adapted by the team — every member can explain the code they shipped. _Team: refine this with the specific tasks/parts where AI was used._
