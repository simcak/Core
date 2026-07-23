# Architecture Diagrams

For an interactive, clickable version of this architecture (service interactions, API endpoints, data models, auth flows, Nginx routing), open:

**[docs/architecture-interactive.html](architecture-interactive.html)** in a browser.

Source drawio file: [`docs/project/architecture to module mapping.drawio`](project/architecture%20to%20module%20mapping.drawio)

---

## Deployment layout and module dependencies

![Deployment layout](png/architecture%20to%20module%20mapping-Deployment%20control%20and%20module%20deps.drawio.png)

Shows the full runtime topology and how the stack is composed.

**Compose stacks, all driven by `make`:**
- `make up` (`docker compose`) — core stack: Nginx, Frontend, Auth/Catalog/Audio services, Postgres, Redis, MinIO. Each service has a companion migrate container (Alembic `upgrade head` on startup) and a seed container (dev only, dashed pink).
- `make up-elk` — overlay: Filebeat tails Docker container logs → Logstash parses → Elasticsearch stores → Kibana visualises. Kibana available at `/kibana/` through Nginx (basic auth protected).
- `make up-monitoring` — overlay: Prometheus scrapes `/metrics` from all three backend services → Grafana dashboards. Grafana available at `/grafana/` through Nginx.
- `docker compose -f docker-compose.prod.yml` — production variant, uses registry images.

**Request flow:** Browser → Nginx (TLS) → service (Auth / Catalog / Audio) based on URL prefix.

**Data flow:** Services ↔ PostgreSQL (separate schemas). Auth + Catalog + Audio → MinIO (avatars / covers / audio-files buckets). Services stdout → Filebeat → Logstash → Elasticsearch. Kibana reads from Elasticsearch.

**Dev-only containers** (PgAdmin, seed containers) are marked with dashed borders — not present in production.

---

## Nginx URL Routing

| URL Pattern | Upstream | Notes |
|-------------|----------|-------|
| `/auth/*` | auth:8000 | Direct proxy |
| `/api/auth/*` | auth:8000 | Rewrites to `/auth/*` on upstream |
| `= /api/health` | auth:8000/health | Exact match, health check |
| `/api/public/auth/*` | auth:8000 | Public API; rate limited 10 r/m per IP (`429` over limit) |
| `/api/public/catalog/*` | catalog:8000 | Public API; rate limited 10 r/m per IP |
| `/api/public/audio/*` | audio:8000 | Public API; rate limited 10 r/m per IP |
| `= /api/public/docs`, `= /api/public/openapi.json` | auth:8000 | Aggregated public API Swagger UI / schema |
| `/api/audio/*` | audio:8000 | Strips `/api/audio/` prefix; `proxy_buffering off` for streaming |
| `/api/*` | catalog:8000 | Catch-all for catalog API |
| `/` | frontend:80 | React SPA |
| `/kibana/` | kibana:5601 | ELK overlay only; basic auth |
| `/grafana/` | grafana:3000 | Monitoring overlay only |

---

## Local frontend dev mode (`make frontend`)

![Dev local mode](png/architecture%20to%20module%20mapping-Dev%20local.drawio.png)

`make frontend` calls `npm run dev:local` in the frontend package, which:
1. Starts the Docker stack with `docker-compose.dev.yml` overlay — the frontend Docker container is replaced by an Alpine stub, Nginx loads `nginx.dev.conf` (no frontend upstream).
2. Starts Vite on `localhost:5173` outside of Docker.

**What this means in practice:**
- Frontend runs outside Docker with hot reload — code changes appear instantly without rebuilding.
- API calls from Vite go to `localhost:8000/api` → Nginx → backend services as normal.
- CORS must be enabled: set `CORS_ORIGINS=http://localhost:5173` in `.env`.
- See [How to run local dev mode](dev/how_to.md#how-to-run-the-frontend-separately-local-dev-mode).
