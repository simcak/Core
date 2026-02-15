# ──────────────────────────────────────────────────────────────────────────── #
#                               Nginx Dockerfile                               #
# ──────────────────────────────────────────────────────────────────────────── #
FROM debian:bookworm

# Install nginx and openssl
RUN apt-get update -y \
    && apt-get install -y nginx openssl \
    && rm -rf /var/lib/apt/lists/* \
    && apt-get clean

# Copy configuration files and a certificate generation script
COPY conf/nginx.conf         /etc/nginx/nginx.conf
COPY conf/ssl.conf           /etc/nginx/conf.d/ssl.conf
COPY tools/generate_cert.sh  /generate_cert.sh

# Generates a self-signed SSL certificate for HTTPS access, make it +x && run it
RUN chmod +x /generate_cert.sh \
    && /generate_cert.sh

# Create nginx user and set permissions
RUN chown -R www-data:www-data /var/www/html \
    && chown -R www-data:www-data /var/log/nginx

# Remove default nginx site (to avoid conflicts)
RUN rm -f /etc/nginx/sites-enabled/default

# Create required directories
RUN mkdir -p /var/run/nginx

# Expose ports
EXPOSE 80 443

# Start nginx in foreground
CMD ["nginx", "-g", "daemon off;"]

# ──────────────────────────────────────────────────────────────────────────── #