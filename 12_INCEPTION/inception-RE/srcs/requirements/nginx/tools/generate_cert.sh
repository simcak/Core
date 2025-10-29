#!/bin/bash
set -e  # Exit on any error

# Create ssl directory if it doesn't exist (matching ssl.conf path)
mkdir -p /etc/nginx/ssl

# Generate new private key + self-signed cert with proper paths
openssl req -x509 -nodes -days 365 \
  -newkey  rsa:2048 \
  -keyout  /etc/nginx/ssl/peta.key \
  -out     /etc/nginx/ssl/peta.crt \
  -subj    "/C=FR/ST=IDF/L=Paris/O=42School/CN=peta.42.fr"

# Set proper permissions for security
chmod 600 /etc/nginx/ssl/peta.key	# Private key: readable only by root
chmod 644 /etc/nginx/ssl/peta.crt	# Certificate: readable by all


# Output success messages only
echo "SSL certificates generated successfully!"
echo "Certificate: /etc/nginx/ssl/peta.crt"
echo "Private key: /etc/nginx/ssl/peta.key"