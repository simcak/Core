# Source Control & CI/CD

← Back to [tools overview](../tools.md) · For the pipeline itself, see [pipeline.md](pipeline.md).

## GitLab

**What:** source control, issue tracking, MR reviews, and CI/CD.

**Why:** required for the 42 school project. We use gitlab.com (hosted) rather than self-hosting GitLab itself — only the runner is self-hosted.

**Key features we use:**
- Merge Requests with required reviewer approval
- GitLab CI/CD (`.gitlab-ci.yml`)
- Container Registry (built into every GitLab project)
- CI/CD Variables for secrets

**Shared runners are disabled** for this project to avoid the 400 min/month limit. All jobs run on our Hetzner runner.

## GitLab Container Registry

**What:** Docker image registry built into GitLab, available at `registry.gitlab.com`.

**Why:** free, already integrated with our GitLab project, and CI jobs authenticate automatically without any extra setup.

**How we use it:** the CI build job pushes images tagged with both the commit SHA and `latest`. The production server pulls these images at deploy time. See [pipeline.md](pipeline.md#4-build--docker-images) for details.
