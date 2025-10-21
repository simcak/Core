FROM debian:bullseye

# Install MariaDB + envsubst (gettext)
RUN apt-get update -y && \
    apt-get install -y mariadb-server gettext && \
    rm -rf /var/lib/apt/lists/*

# Configure MariaDB to listen on all interfaces
RUN sed -i "s/^bind-address\s*=.*$/bind-address = 0.0.0.0/" /etc/mysql/mariadb.conf.d/50-server.cnf

# Copy SQL init script and entrypoint
COPY tools/init.sql /init.sql
COPY tools/entrypoint.sh /entrypoint.sh
RUN chmod +x /entrypoint.sh

EXPOSE 3306

ENTRYPOINT ["/entrypoint.sh"]
