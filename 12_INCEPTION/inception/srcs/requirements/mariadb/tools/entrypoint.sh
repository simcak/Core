#!/bin/bash
set -e

# export MYSQL_DATABASE  MYSQL_USER  MYSQL_PASSWORD  MYSQL_ROOT_PASSWORD

# Check if this is first time setup - look for a more specific marker
if [ ! -f "/var/lib/mysql/inception_initialized" ]; then
    # Initialize MariaDB data directory if it doesn't exist
    if [ ! -d "/var/lib/mysql/mysql" ]; then
        mysql_install_db --user=mysql --datadir=/var/lib/mysql
    fi

    # Start MariaDB temporarily
    mysqld_safe --skip-networking &
    pid="$!"

    # Wait 1s in loop for server to be up
    until mysqladmin ping --silent; do
        sleep 1
    done

    # Run init.sql with variable substitution (no password needed on first run)
    envsubst < /init.sql | mysql -u root

    # Create marker file to indicate initialization is complete
    touch /var/lib/mysql/inception_initialized

    # Shutdown temporary server
    mysqladmin -u root -p"$MYSQL_ROOT_PASSWORD" shutdown || true
    wait "$pid" || true
fi

# Start MariaDB in foreground (normal mode)
exec mysqld_safe
