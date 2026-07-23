# Observability — Logging (ELK)

← Back to [tools overview](../tools.md) · For metrics, see [observability-metrics.md](observability-metrics.md).

Brought up with `make up-elk` (`docker-compose.elk.yml`). Config lives in `elk/`. All four components are pinned to **8.13.4**.

## Elasticsearch

**What:** search and analytics engine that stores all application logs. *(v8.13.4)*

**Why:** indexes logs so they can be searched and aggregated quickly in Kibana.

## Logstash

**What:** log processing pipeline. *(v8.13.4)*

**Why:** receives logs from Filebeat, parses/transforms them, and forwards them into Elasticsearch. Pipeline config in `elk/logstash/`.

## Kibana

**What:** the web UI for exploring logs stored in Elasticsearch. *(v8.13.4)*

**Why:** lets us search, filter, and build visualizations over the logs — the human-facing front door to the ELK stack.

## Filebeat

**What:** lightweight log shipper. *(v8.13.4)*

**Why:** runs alongside the services, collects their container logs, and ships them to Logstash. Our backend services emit structured logs via `structlog`, which Filebeat forwards. Config in `elk/filebeat/`.
