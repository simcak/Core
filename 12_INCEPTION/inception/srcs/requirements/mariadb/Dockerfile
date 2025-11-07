# ──────────────────────────────────────────────────────────────────────────── #
#                              MariaDB Dockerfile                              #
# ──────────────────────────────────────────────────────────────────────────── #
FROM debian:bookworm

# Apt check + installing MariaDB + cleanup apt cache
RUN apt-get update && \
	apt-get install -y --no-install-recommends mariadb-server gettext && \
	apt-get clean && rm -rf /var/lib/apt/lists/* /var/cache/apt/archives/*.deb

# Set MariaDB to listen on all interfaces - Otherwise wordpress can't connect
RUN sed -i "s/^bind-address\s*=.*$/bind-address = 0.0.0.0/" \
	/etc/mysql/mariadb.conf.d/50-server.cnf

#copy from:                 to:
COPY  tools/init.sql        /init.sql
COPY  tools/entrypoint.sh   /entrypoint.sh

RUN   chmod +x              /entrypoint.sh

EXPOSE 3306

ENTRYPOINT ["/entrypoint.sh"]

# ──────────────────────────────────────────────────────────────────────────── #