# CI/CD Pipeline

← Back to [tools overview](../tools.md) · GitLab tooling in [cicd.md](cicd.md).

## Table of Contents

1. [Runner Setup](#1-runner-setup)
2. [Pipeline Stages](#2-pipeline-stages)
3. [Branch Rules](#3-branch-rules)
4. [Build — Docker Images](#4-build--docker-images)
5. [Deploy](#5-deploy)
6. [CI/CD Variables](#6-cicd-variables)

---

## 1. Runner Setup

GitLab.com free tier provides 400 CI/CD minutes per month. With multiple services and frequent pushes, this runs out fast and shared runner availability is unreliable.

**Solution:** a self-hosted GitLab runner registered against our project, hosted on the same [Hetzner VPS](infrastructure.md#hetzner-vps) as the application. Shared (instance) runners are disabled for this project.

The runner uses the **Docker executor** with Docker-in-Docker (`docker:24-dind`), which allows it to build Docker images inside CI jobs. The `pull_policy = "if-not-present"` option in the runner config prevents base images from being re-pulled on every run, which would add 2–3 minutes of overhead per job.

---

## 2. Pipeline Stages

The pipeline has four stages that run in order:

```
lint → build → test → deploy
```

| Stage | What it does | When it runs |
|-------|-------------|--------------|
| `lint` | Runs `flake8` across `audio/`, `auth/`, `catalog/` | Every push on every branch |
| `build` | Builds Docker images and pushes them to GitLab Container Registry | `master` branch only |
| `test` | Placeholder — integration tests to be added | Every push on every branch |
| `deploy` | SSHes into the VPS and brings the new stack up | `master` branch, **manual trigger** |

---

## 3. Branch Rules

Images are built **only on `master`**, not on feature branches or MRs.

**Why:** building on a feature branch, then on the MR, then on master produces identical images three times. Docker layer caching saves disk space but not time — each build still takes 2–5 minutes per service. The correct pattern would be to build on MR and retag on master, but for simplicity we build once on master after merge.

```
feature branch push  →  lint, test
merge request        →  lint, test
master push          →  lint, test, build, deploy (manual)
```

---

## 4. Build — Docker Images

Each service has its own Dockerfile. All images are built in a single CI job and pushed to the **GitLab Container Registry** with two tags:

- `:<git-commit-SHA>` — immutable, points to this exact build
- `:latest` — mutable, always points to the most recent master build

```
registry.gitlab.com/sombru-group/ft_transendence/audio:abc123f
registry.gitlab.com/sombru-group/ft_transendence/audio:latest
```

Services built: `audio`, `auth`, `catalog`, `frontend`, `nginx`.

**Two compose files:**

| File | Used by | Image source |
|------|---------|-------------|
| `docker-compose.yml` | Local development | `build:` — builds from Dockerfiles |
| `docker-compose.prod.yml` | Production (VPS) | `image:` — pulls from registry |

This means local dev never needs registry access, and the production server never builds images itself.

Cleanup policy: **weekly**

---

## 5. Deploy

The deploy job runs only on `master` and only when manually triggered from the GitLab CI interface.

**What it does:**

1. Copies `docker-compose.prod.yml` to the VPS via `rsync`
2. SSHes into the VPS
3. Logs into the GitLab Container Registry
4. Pulls the latest images (`docker compose pull`)
5. Brings the stack up with zero-downtime restart (`docker compose up -d --remove-orphans`)

Database migrations run automatically as part of the stack — each service has a companion `*-migrate` container that runs `alembic upgrade head` before the service starts.

**SSH key:** a dedicated ED25519 key pair is used. The private key is stored as a GitLab CI variable (`SSH_PRIVATE_KEY`) base64-encoded to prevent newline stripping. It is decoded in the job with `echo "$SSH_PRIVATE_KEY" | base64 -d`.

---

## 6. CI/CD Variables

Set in GitLab → Project → Settings → CI/CD → Variables.

| Variable | Description | Masked |
|----------|-------------|--------|
| `SSH_PRIVATE_KEY` | Private key for SSH access to the VPS, base64-encoded | Yes |
| `DEPLOY_HOST` | Public IP of the Hetzner VPS | Yes |

`CI_REGISTRY_USER`, `CI_REGISTRY_PASSWORD`, and `CI_REGISTRY` are provided automatically by GitLab — no manual setup needed for registry authentication.
