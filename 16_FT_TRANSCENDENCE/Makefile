COMPOSE            := docker compose -f docker-compose.yml
COMPOSE_ELK        := $(COMPOSE) -f docker-compose.elk.yml -f docker-compose.elk.dev.yml
COMPOSE_MONITORING := $(COMPOSE) -f docker-compose.monitoring.yml -f docker-compose.monitoring.dev.yml
COMPOSE_ALL        := $(COMPOSE) -f docker-compose.elk.yml -f docker-compose.elk.dev.yml -f docker-compose.monitoring.yml -f docker-compose.monitoring.dev.yml
COMPOSE_PROD       := docker compose -f docker-compose.prod.yml -f docker-compose.elk.yml -f docker-compose.elk.prod.yml -f docker-compose.monitoring.yml -f docker-compose.monitoring.prod.yml

.PHONY: help up down restart logs rebuild shell psql \
        up-elk down-elk \
        up-monitoring down-monitoring \
        up-all down-all \
        up-prod down-prod \
        frontend install \
        clean clean-all \
        rebuild-elk rebuild-monitoring

# ── default ────────────────────────────────────────────────────────────────────

help:
	@echo ""
	@echo "  Usage: make <target> [service=<name>]"
	@echo ""
	@echo "  Dev stack"
	@echo "    up              Build and start all services"
	@echo "    down            Stop all services (keep volumes)"
	@echo "    restart         Restart one service:  make restart service=catalog"
	@echo "    logs            Follow logs:          make logs service=catalog"
	@echo "    rebuild         Rebuild one service:  make rebuild service=catalog"
	@echo "    shell           Open shell in a container: make shell service=catalog"
	@echo ""
	@echo "  Database"
	@echo "    psql            Open psql in the postgres container"
	@echo "    seed            Run seed scripts for all services"
	@echo ""
	@echo "  ELK"
	@echo "    up-elk          Start full stack + ELK"
	@echo "    down-elk        Stop full stack + ELK"
	@echo "    logs-elk        Follow ELK logs:  make logs-elk service=filebeat"
	@echo ""
	@echo "  Monitoring"
	@echo "    up-monitoring   Start full stack + Prometheus + Grafana"
	@echo "    down-monitoring Stop full stack + Prometheus + Grafana"
	@echo "    logs-monitoring Follow monitoring logs: make logs-monitoring service=grafana"
	@echo ""
	@echo "  Full stack (app + ELK + monitoring)"
	@echo "    up-all          Build and start everything"
	@echo "    down-all        Stop everything"
	@echo ""
	@echo "  Frontend"
	@echo "    frontend        Run Vite dev server (hot reload, separate from Docker)"
	@echo "    install         Install frontend dependencies and set up git hooks"
	@echo ""
	@echo "  Cleanup"
	@echo "    clean           Stop containers and remove volumes (fresh DB)"
	@echo "    clean-all       clean + remove all built images"
	@echo ""

# ── dev stack ──────────────────────────────────────────────────────────────────

up:
	$(COMPOSE) up --build -d

down:
	$(COMPOSE) down

restart:
	$(COMPOSE) restart $(service)

logs:
	$(COMPOSE) logs -f $(service)

rebuild:
	$(COMPOSE) up --build -d --no-deps $(service)

shell:
	$(COMPOSE) exec $(service) sh

# ── database ───────────────────────────────────────────────────────────────────

psql:
	docker exec -it postgres psql -U transcendence -d transcendence

seed:
	$(COMPOSE) run --rm catalog-seed
	$(COMPOSE) run --rm auth-seed

# ── elk ────────────────────────────────────────────────────────────────────────

up-elk:
	$(COMPOSE_ELK) up --build -d

down-elk:
	$(COMPOSE_ELK) down

down-elk-service:
	$(COMPOSE_ELK) down $(service)

logs-elk:
	$(COMPOSE_ELK) logs -f $(service)

restart-elk:
	$(COMPOSE_ELK) restart $(service)

rebuild-elk:
	$(COMPOSE_ELK) up --build -d --no-deps $(service)

# ── monitoring ─────────────────────────────────────────────────────────────────

up-monitoring:
	$(COMPOSE_MONITORING) up --build -d

down-monitoring:
	$(COMPOSE_MONITORING) down

logs-monitoring:
	$(COMPOSE_MONITORING) logs -f $(service)

rebuild-monitoring:
	$(COMPOSE_MONITORING) up --build -d --no-deps $(service)

# ── full stack (app + ELK + monitoring) ───────────────────────────────────────

up-all:
	$(COMPOSE_ALL) up --build -d

down-all:
	$(COMPOSE_ALL) down

# ── production ─────────────────────────────────────────────────────────────────

up-prod:
	$(COMPOSE_PROD) up -d --remove-orphans

down-prod:
	$(COMPOSE_PROD) down

# ── frontend ───────────────────────────────────────────────────────────────────

frontend:
	cd frontend && npm run dev:local

install:
	cd frontend && npm install

# ── cleanup ────────────────────────────────────────────────────────────────────

clean:
	$(COMPOSE) down -v

clean-all:
	$(COMPOSE) down -v --rmi all
