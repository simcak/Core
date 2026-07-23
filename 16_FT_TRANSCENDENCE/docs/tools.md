# Tools

Every tool we use to build, run, observe, and ship this project — at a glance, grouped by what it does.

> **How to read this page:** the table below is the full overview with versions and roles. Each tool links to its category file in [`tools/`](tools/) where you'll find the *what* and *why* in detail. Two topics have their own deep-dive guides: [Alembic migrations](tools/alembic.md) and the [CI/CD pipeline](tools/pipeline.md).

## Overview

| Category       |  Tool  |  Version  |  Role  |
|----------------|--------|-----------|--------|
| **Infrastructure & Hosting**    | [Hetzner VPS](tools/infrastructure.md#hetzner-vps) | CX32 | Hosts the prod stack + CI runner |
| **Source Control & CI/CD**      | [GitLab](tools/cicd.md#gitlab) | gitlab.com | Source control, MRs, pipelines |
| | [GitLab Container Registry](tools/cicd.md#gitlab-container-registry) | — | Docker image registry |
| **Containers** | [Docker & Docker Compose](tools/containers.md#docker--docker-compose) | — | Build & orchestrate services |
| **Reverse Proxy**      | [Nginx](tools/reverse-proxy.md#nginx) | — | Reverse proxy + static files |
| **Backend**    | [FastAPI](tools/backend.md#fastapi) | 0.136.1 | Web framework for all services |
| | [Uvicorn](tools/backend.md#uvicorn) | 0.46.0 | ASGI server |
| | [SQLAlchemy](tools/backend.md#sqlalchemy) | 2.0.49 | ORM |
| | [Alembic](tools/backend.md#alembic) | 1.18.4 | DB migrations |
| | [Pydantic](tools/backend.md#pydantic) | 2.13.3 | Validation / schemas |
| | [Authlib](tools/backend.md#auth-libraries) / [PyJWT](tools/backend.md#auth-libraries) / [Argon2](tools/backend.md#auth-libraries) | — | OAuth, JWTs, password hashing |
| **Databases & Storage**       | [PostgreSQL](tools/databases.md#postgresql) | 16 | Relational database |
| | [Redis](tools/databases.md#redis) | 7-alpine | Cache & sessions |
| | [MinIO](tools/databases.md#minio) | latest | S3-compatible object storage |
| | [pgAdmin](tools/databases.md#pgadmin) | 4 | DB admin UI (dev) |
| **Frontend**   | [React](tools/frontend.md#react) | 19 | UI framework |
| | [Vite](tools/frontend.md#vite) | 6 | Build tool & dev server |
| | [TypeScript](tools/frontend.md#typescript) | 6 | Typed JavaScript |
| | [Tailwind CSS](tools/frontend.md#tailwind-css) | 4 | Styling |
| | [shadcn/ui](tools/frontend.md#shadcnui--radix-ui) + [Radix UI](tools/frontend.md#shadcnui--radix-ui) | — | Component library |
| **Observability — Metrics**    | [Prometheus](tools/observability-metrics.md#prometheus) | v2.52.0 | Metrics collection |
| | [Grafana](tools/observability-metrics.md#grafana) | 11.0.0 | Metrics dashboards |
| | [node-exporter](tools/observability-metrics.md#node-exporter--cadvisor) / [cAdvisor](tools/observability-metrics.md#node-exporter--cadvisor) | — | Host & container metrics |
| **Observability — Logging**    | [Elasticsearch](tools/observability-logging.md#elasticsearch) | 8.13.4 | Log storage & search |
| | [Logstash](tools/observability-logging.md#logstash) | 8.13.4 | Log processing |
| | [Kibana](tools/observability-logging.md#kibana) | 8.13.4 | Log exploration UI |
| | [Filebeat](tools/observability-logging.md#filebeat) | 8.13.4 | Log shipping |
| **Code Quality & Testing**    | [flake8](tools/code-quality.md#flake8) | — | Python linting |
| | [pytest](tools/code-quality.md#pytest) | — | Python tests |
| | [ESLint](tools/code-quality.md#eslint--prettier) / [Prettier](tools/code-quality.md#eslint--prettier) | — | JS/TS lint & format |
| | [Husky](tools/code-quality.md#husky--lint-staged) / [lint-staged](tools/code-quality.md#husky--lint-staged) | — | Pre-commit hooks |

## Detailed docs

Each category has its own page under [`tools/`](tools/):

| Page | Covers |
|---|---|
| [infrastructure.md](tools/infrastructure.md) | Hetzner VPS |
| [cicd.md](tools/cicd.md) | GitLab, Container Registry |
| [containers.md](tools/containers.md) | Docker & Docker Compose |
| [reverse-proxy.md](tools/reverse-proxy.md) | Nginx |
| [backend.md](tools/backend.md) | FastAPI, Uvicorn, SQLAlchemy, Alembic, Pydantic, auth libraries |
| [databases.md](tools/databases.md) | PostgreSQL, Redis, MinIO, pgAdmin |
| [frontend.md](tools/frontend.md) | React, Vite, TypeScript, Tailwind, shadcn/ui + Radix |
| [observability-metrics.md](tools/observability-metrics.md) | Prometheus, Grafana, node-exporter, cAdvisor |
| [observability-logging.md](tools/observability-logging.md) | Elasticsearch, Logstash, Kibana, Filebeat |
| [code-quality.md](tools/code-quality.md) | flake8, pytest, ESLint, Prettier, Husky, lint-staged |
| [alembic.md](tools/alembic.md) | Deep dive — running database migrations |
| [pipeline.md](tools/pipeline.md) | Deep dive — the CI/CD pipeline |
