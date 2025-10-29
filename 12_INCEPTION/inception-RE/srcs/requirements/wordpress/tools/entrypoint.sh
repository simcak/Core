#!/bin/bash
set -e

echo "Starting WordPress container initialization..."

# Wait for MariaDB to be ready
echo "Waiting for MariaDB to be ready..."
while ! php -r "
\$connection = @fsockopen('mariadb', 3306, \$errno, \$errstr, 5);
if (!\$connection) { exit(1); } else { fclose(\$connection); exit(0); }
"; do
    echo "Waiting for MariaDB..."
    sleep 2
done
echo "MariaDB is ready!"

# Check if WordPress is already installed
if [ ! -f "/var/www/html/wp-config.php" ]; then
    echo "WordPress not found. Installing..."
    
    # # Download WordPress if not present
    # if [ ! -f "/var/www/html/index.php" ]; then
    #     echo "Downloading WordPress..."
    #     wget https://wordpress.org/latest.tar.gz -O /tmp/wordpress.tar.gz
    #     tar -xzf /tmp/wordpress.tar.gz -C /tmp/
    #     cp -r /tmp/wordpress/* /var/www/html/
    #     rm -rf /tmp/wordpress /tmp/wordpress.tar.gz
    #     echo "WordPress downloaded and extracted."
    # fi
    
    # Generate wp-config.php
    echo "Generating wp-config.php..."
    /usr/local/bin/wp-config.sh
    
    # Set proper permissions
    chown -R www-data:www-data /var/www/html
    find /var/www/html -type d -exec chmod 755 {} \;
    find /var/www/html -type f -exec chmod 644 {} \;
    
    echo "WordPress installation completed!"
else
    echo "WordPress already installed, skipping setup..."
fi

# Create PHP-FPM log file
touch /var/log/php7.4-fpm.log
chown www-data:www-data /var/log/php7.4-fpm.log

# Ensure proper ownership
chown -R www-data:www-data /var/www/html

echo "Starting PHP-FPM..."
exec php-fpm -F