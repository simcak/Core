#!/usr/bin/env sh
set -eu

if [ -f .env ]; then
  echo ".env already exists"
  exit 0
fi

if [ ! -f .env.example ]; then
  echo "Error: .env.example not found" >&2
  exit 1
fi

cp .env.example .env
echo "Created .env from .env.example"