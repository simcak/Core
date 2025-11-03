#!/bin/bash
set -e

echo "Starting WordPress container initialization..."

# ──────────────────────────────────────────────
# Wait for MariaDB service to become available
# ──────────────────────────────────────────────
echo "Waiting for MariaDB to be ready..."
until php -r "
  \$conn = @fsockopen('mariadb', 3306, \$errno, \$errstr, 5);
  if (!\$conn)  { exit(1); }
  else          { fclose(\$conn); exit(0); }
"; do
    echo "MariaDB not ready yet, retrying in 2s..."
    sleep 2
done
echo "MariaDB is ready!"

# ──────────────────────────────────────────────
# WordPress initialization
# ──────────────────────────────────────────────
if [ ! -f "/var/www/html/wp-config.php" ]; then
    echo "Generating wp-config.php..."
    /usr/local/bin/wp-config.sh

    # Set proper permissions
    # 755 = drwxr-xr-x
    # 644 = -rw-r--r--
    chown -R www-data:www-data /var/www/html
    find /var/www/html -type d -exec chmod 755 {} \;
    find /var/www/html -type f -exec chmod 644 {} \;

    # 640 = -rw-r-----
    chmod 640 /var/www/html/wp-config.php

    echo "WordPress installation completed!"
else
    echo "WordPress already installed, skipping setup..."
fi

# ──────────────────────────────────────────────
# PHP-FPM preparation
# ──────────────────────────────────────────────
echo "Preparing PHP-FPM logs..."
touch /var/log/php8.2-fpm.log
chown www-data:www-data /var/log/php8.2-fpm.log

# ──────────────────────────────────────────────
# Launch PHP-FPM in foreground (PID 1)
# ──────────────────────────────────────────────
echo "Starting PHP-FPM..."
exec /usr/sbin/php-fpm8.2 --nodaemonize