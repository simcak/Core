# Observability — Metrics

← Back to [tools overview](../tools.md) · For logging, see [observability-logging.md](observability-logging.md).

Brought up with `make up-monitoring` (`docker-compose.monitoring.yml`). Config lives in `monitoring/`.

## Prometheus

**What:** time-series metrics database and scraper. *(v2.52.0)*

**Why:** pulls metrics from each service's `/metrics` endpoint (exposed by `prometheus-fastapi-instrumentator`) plus the exporters below, and stores them for querying and alerting.

## Grafana

**What:** metrics visualization and dashboards. *(v11.0.0)*

**Why:** turns Prometheus data into dashboards — request rates, latency, resource usage. Dashboards and data sources are provisioned from `monitoring/grafana/`.

## node-exporter & cAdvisor

**What:** the two metric exporters Prometheus scrapes for infrastructure data.

| Exporter | Version | Exposes |
|---|---|---|
| **node-exporter** | v1.8.1 | Host machine metrics (CPU, RAM, disk, network) |
| **cAdvisor** | v0.49.1 | Per-container resource usage |
