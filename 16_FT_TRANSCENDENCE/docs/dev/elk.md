# ELK Stack — Developer Guide

Covers local setup, Kibana access, searching logs, and adding logging to a service.

---

## Starting ELK locally

```bash
make up-elk
```

This starts the full app stack plus Elasticsearch, Logstash, Kibana, Filebeat, and a one-shot setup container that creates the ILM retention policy, index template, and Kibana index pattern. First start takes ~2 minutes for Elasticsearch and Kibana to become healthy.

---

## Accessing Kibana

| Environment | URL | Auth |
|---|---|---|
| Dev | `http://localhost:5601` | None |
| Prod | `https://your-server/kibana/` | Basic auth (see server htpasswd) |

In dev you access Kibana directly — port 5601 is exposed and you bypass nginx entirely. The nginx auth proxy is production-only.

---

## Verifying logs are flowing

1. Open Kibana → **Discover** (left sidebar, compass icon)
2. The `transcendence-logs-*` index pattern should be pre-selected
3. Set the time range to **Last 15 minutes** (top right)
4. You should see log entries from all running containers

If Discover shows "No results", check:
```bash
make logs-elk service=filebeat    # is Filebeat shipping events?
make logs-elk service=logstash    # is Logstash processing them?
```

---

## Searching logs (KQL)

Kibana uses **KQL (Kibana Query Language)** in the search bar at the top of Discover.

### Filter by service
```
service.name: "audio"
service.name: "auth" or service.name: "catalog"
```

### Filter by log level
```
structured.level: "warning"
structured.level: "error"
```

### Filter by event type (structlog events from FastAPI services)
```
structured.event: "upload_complete"
structured.event: "file_deleted"
structured.event: "upload_rejected"
```

### Combine filters
```
service.name: "audio" and structured.level: "error"
```

### Free-text search
```
message: "password mismatch"
```

### Useful columns to add in Discover
Click **Columns** and add: `service.name`, `structured.level`, `structured.event`, `message`. This makes the table readable instead of showing raw JSON per row.

---

## Common workflows

### See all errors across all services in the last hour
- Time range: Last 1 hour
- Query: `structured.level: "error"`

### Trace a specific upload
- Query: `structured.event: "upload_complete" and structured.book_id: 42`

### Find rejected uploads
- Query: `structured.event: "upload_rejected"`
- Add column `structured.reason` to see why each was rejected

### Health check noise
Health check requests are dropped in Logstash and never reach Elasticsearch — no need to filter them manually.

---

## Dashboards

### Creating a dashboard
1. Kibana → **Dashboards** → **Create dashboard**
2. **Create visualization** → choose chart type
3. For a log-level breakdown: Lens → Bar chart → X-axis: `@timestamp`, Break down by: `structured.level`
4. Save the visualization, add it to the dashboard, save the dashboard

### Exporting for the repo (so everyone gets it on first start)
1. **Stack Management** → **Saved Objects**
2. Select your dashboard (and any related visualizations)
3. **Export** → download the `.ndjson` file
4. Add its content as a new line in `elk/setup/kibana-objects.ndjson`
5. The `elk-setup` container imports this file on every start (`overwrite=true`), so the dashboard appears automatically for all team members

---

## Adding logging to a service

All three services (auth, catalog, audio) use `structlog`. The pattern is identical across all of them.

**1. Add to `requirements.txt`:**
```
structlog
```

**2. Add to the router file:**
```python
import structlog

structlog.configure(
    processors=[
        structlog.stdlib.add_log_level,
        structlog.processors.TimeStamper(fmt="iso"),
        structlog.processors.JSONRenderer(),
    ],
    logger_factory=structlog.PrintLoggerFactory(),
)

log = structlog.get_logger()
```

**3. Log events:**
```python
log.info("user_created", user_id=user.id, email=user.email)
log.warning("login_failed", reason="invalid_password", email=email)
log.error("db_error", error=str(e), user_id=user_id)
```

The first argument is the event name (`structured.event` in Kibana). All keyword arguments become searchable fields under `structured.*`.

**4. Ensure stdout is unbuffered** — verify the service Dockerfile has:
```dockerfile
ENV PYTHONUNBUFFERED=1
```
Without this, logs appear in Kibana only when Python's stdout buffer fills up (~4KB), causing delays.

---

## Log retention

Indices older than 30 days are automatically deleted by the `transcendence-retention` ILM policy. No manual cleanup needed.

To verify the policy is applied: **Stack Management** → **Index Lifecycle Policies** → look for `transcendence-retention`.
