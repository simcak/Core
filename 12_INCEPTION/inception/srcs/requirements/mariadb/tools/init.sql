-- Create the database
CREATE DATABASE IF NOT EXISTS ${MYSQL_DATABASE};

-- Create the user and set password
CREATE USER IF NOT EXISTS '${MYSQL_USER}'@'%' IDENTIFIED BY '${MYSQL_PASSWORD}';

-- Give that user full access to the database
GRANT ALL PRIVILEGES ON ${MYSQL_DATABASE}.* TO '${MYSQL_USER}'@'%';

-- Set the root user password
ALTER USER 'root'@'localhost' IDENTIFIED BY '${MYSQL_ROOT_PASSWORD}';

-- Apply changes
FLUSH PRIVILEGES;