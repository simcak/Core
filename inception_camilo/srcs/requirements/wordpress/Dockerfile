FROM php:8.2-fpm-bullseye

# Install system dependencies required for PHP extensions
RUN apt-get update && apt-get install -y \
        unzip \
        curl \
        mariadb-client \
        libzip-dev \
        libxml2-dev \
        libonig-dev \
    && docker-php-ext-install mysqli zip bcmath mbstring xml \
    && rm -rf /var/lib/apt/lists/*

# Create PHP-FPM runtime directory
RUN mkdir -p /run/php && chown www-data:www-data /run/php

# Set working directory
WORKDIR /var/www/html

# Download WordPress
RUN curl -O https://wordpress.org/latest.tar.gz \
    && tar xzvf latest.tar.gz --strip-components=1 \
    && rm latest.tar.gz

# Fix permissions
RUN chown -R www-data:www-data /var/www/html \
    && chmod -R 755 /var/www/html

# Copy entrypoint
COPY ./tools/entrypoint.sh /entrypoint.sh
RUN chmod +x /entrypoint.sh

# Copy wp-config script
COPY ./tools/wp-config.sh /usr/local/bin/wp-config.sh
RUN chmod +x /usr/local/bin/wp-config.sh

EXPOSE 9000
ENTRYPOINT ["/entrypoint.sh"]