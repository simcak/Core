#!/bin/bash
set -e

# Create ssl directory if it doesn't exist (matching ssl.conf path)
mkdir -p /etc/nginx/ssl

# Generate self-signed cert with proper paths
openssl req -x509 -nodes -days 365 \
  -newkey rsa:2048 \
  -keyout /etc/nginx/ssl/cberneri.key \
  -out /etc/nginx/ssl/cberneri.crt \
  -subj "/C=FR/ST=IDF/L=Paris/O=42School/CN=cberneri.42.fr"

# Set proper permissions for security
chmod 600 /etc/nginx/ssl/cberneri.key
chmod 644 /etc/nginx/ssl/cberneri.crt

echo "SSL certificates generated successfully!"
echo "Certificate: /etc/nginx/ssl/cberneri.crt"
echo "Private key: /etc/nginx/ssl/cberneri.key"