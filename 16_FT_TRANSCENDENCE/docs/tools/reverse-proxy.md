# Reverse Proxy

← Back to [tools overview](../tools.md)

## Nginx

**What:** reverse proxy and static file server sitting in front of all services.

**Why:** routes incoming HTTP requests to the correct backend service based on the URL path. Also serves the frontend static files directly without going through a Node process.

**Ports:** the container listens on `80` (HTTP) and `443` (HTTPS) internally. The standard ports are blocked on the school network, so they are remapped on the host:

| Environment | HTTP (host → container) | HTTPS (host → container) |
| ----------- | ----------------------- | ------------------------ |
| dev         | `8000 → 80`             | `4443 → 443`             |
| prod        | `80 → 80`               | `443 → 443`              |

**HTTP → HTTPS redirect:** the `listen 80` server block returns `301 https://$host:${HTTPS_PORT}$request_uri`. Because `$host` carries no port and nginx inside the container has no knowledge of the host port mapping, the externally exposed HTTPS port is injected via the `HTTPS_PORT` environment variable (`4443` in dev, `443` in prod). The variable is substituted at container startup by nginx's built-in template mechanism — `nginx.conf` is shipped as `/etc/nginx/templates/nginx.conf.template` (see `nginx/Dockerfile`), and `NGINX_ENVSUBST_FILTER` restricts substitution to `HTTPS_PORT` so nginx's own `$variables` are left untouched.

So in dev, browsing to `http://localhost:8000` redirects to `https://localhost:4443`.
