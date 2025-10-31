################################################################################
#                             WordPress Dockerfile                             #
################################################################################
FROM debian:bookworm

# No interactive prompts during package installation
ENV DEBIAN_FRONTEND=noninteractive

# Install necessary packages and PHP extensions
RUN apt-get update && apt-get install -y \
        unzip curl mariadb-client \
        php8.2-fpm php8.2-mysql php8.2-zip php8.2-xml php8.2-mbstring php8.2-bcmath \
    && rm -rf /var/lib/apt/lists/*

# Configure PHP-FPM
RUN mkdir -p /run/php /var/log/php8.2-fpm \
    && chown -R www-data:www-data /run/php /var/log/php8.2-fpm

WORKDIR /var/www/html

# Download and extract WordPress
RUN curl -O https://wordpress.org/latest.tar.gz \
    && tar xzvf latest.tar.gz --strip-components=1 \
    && rm latest.tar.gz \
    && chown -R www-data:www-data /var/www/html \
    && find /var/www/html -type d -exec chmod 755 {} \; \
    && find /var/www/html -type f -exec chmod 644 {} \;

COPY ./tools/www.conf /etc/php/8.2/fpm/pool.d/www.conf

COPY ./tools/entrypoint.sh /entrypoint.sh
COPY ./tools/wp-config.sh /usr/local/bin/wp-config.sh
RUN chmod +x /entrypoint.sh /usr/local/bin/wp-config.sh

# Expose FPM port (for NGINX connection)
EXPOSE 9000

# Start PHP-FPM
ENTRYPOINT ["/entrypoint.sh"]
################################################################################
# Workflow Explanation:

# NGINX receives HTTPS
# → forwards .php requests to PHP-FPM over FastCGI
# → PHP-FPM runs WordPress
# → WordPress connects to MariaDB and returns HTML.

# To make WordPress’s PHP code work, we enable extensions for DB, text, XML,
# compression, and math.
################################################################################