# Infrastructure & Hosting

← Back to [tools overview](../tools.md)

## Hetzner VPS

**What:** a rented virtual private server that hosts both the application stack and the GitLab CI runner.

**Plan:** CX32 — 4 vCPU, 8 GB RAM, 80 GB SSD, ~€8/month. Billed hourly, can be deleted at any time.

**Why Hetzner over free options:** Oracle Cloud Always Free (ARM, 24 GB RAM) is the cheapest option but ARM capacity is frequently exhausted — provisioning a VM can fail repeatedly across all availability domains. Hetzner is x86, reliable, and cheap enough for a school project.

**What runs on it:**
- The full application stack via `docker-compose.prod.yml`
- The self-hosted GitLab runner (see [pipeline.md](pipeline.md))

**Access:** SSH only, using a dedicated ED25519 key pair. The deploy key is separate from personal SSH keys.
