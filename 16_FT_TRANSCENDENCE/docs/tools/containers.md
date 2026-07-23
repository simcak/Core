# Containerization

← Back to [tools overview](../tools.md)

## Docker & Docker Compose

**What:** Docker packages each service into a container image. Docker Compose orchestrates multiple containers as a stack.

**Why:** standardizes the environment across all team members' machines and production. Everyone runs the same stack with `docker compose up`.

**Compose files** (split by concern so each stack can run independently):

| File | Purpose |
|---|---|
| `docker-compose.yml` | Core stack, local development (`build:` from source) |
| `docker-compose.dev.yml` | Local dev overrides |
| `docker-compose.prod.yml` | Production — pulls pre-built images from the registry |
| `docker-compose.monitoring.yml` | Prometheus + Grafana metrics stack |
| `docker-compose.elk.yml` | Elasticsearch + Logstash + Kibana + Filebeat logging stack |

The `Makefile` wraps the common combinations — `make up`, `make up-elk`, `make up-monitoring`, `make up-all`, `make up-prod`.
