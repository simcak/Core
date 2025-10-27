################################################################################
#                              MariaDB Dockerfile                              #
################################################################################
FROM debian:bullseye

# Apt check + installing MariaDB + cleanup apt cache
RUN apt-get update && \
	apt-get install -y --no-install-recommends mariadb-server gettext && \
	apt-get clean && rm -rf /var/lib/apt/lists/* /var/cache/apt/archives/*.deb

# Configure MariaDB to listen on all interfaces
RUN sed -i "s/^bind-address\s*=.*$/bind-address = 0.0.0.0/" \
	/etc/mysql/mariadb.conf.d/50-server.cnf

# HEALTHCHECK --interval=30s --timeout=5s --start-period=30s \
# 	CMD mysqladmin ping -h 127.0.0.1 || exit 1

#copy from:                 to:
COPY  tools/init.sql        /init.sql
COPY  tools/entrypoint.sh   /entrypoint.sh

RUN   chmod +x              /entrypoint.sh

EXPOSE 3306

ENTRYPOINT ["/entrypoint.sh"]

################################################################################
# TODO: look at the 0.0.0.0 bind-address line - is it secure?