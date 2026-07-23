# Code Quality & Testing

← Back to [tools overview](../tools.md)

## flake8

**What:** Python linter that checks code style and common errors.

**Why:** keeps code consistent across five developers and catches simple mistakes before they reach review.

**Scope:** runs on the service directories (`audio/`, `auth/`, `catalog/`). Config is in `.flake8` at the repo root. Runs automatically in the CI `lint` stage on every push.

## pytest

**What:** the Python testing framework. Config in `pytest.ini`.

**Why:** unit and integration tests for the backend services. `pythonpath` is configured so tests can import service modules directly.

## ESLint & Prettier

**What:** the JavaScript/TypeScript linter (ESLint) and code formatter (Prettier) for the frontend.

**Why:** ESLint catches bugs and enforces React/hooks rules; Prettier keeps formatting uniform so diffs stay clean. `eslint-config-prettier` keeps the two from fighting.

## Husky & lint-staged

**What:** Git hook manager (Husky) plus a staged-file runner (lint-staged).

**Why:** on every commit, Husky triggers lint-staged, which runs `eslint --fix` and `prettier --write` on just the staged JS/TS files — so badly formatted or lint-failing code never gets committed in the first place.
