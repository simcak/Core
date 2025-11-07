#!/bin/bash
set -e

# Only create wp-config.php if it doesn't exist
if [ ! -f "/var/www/html/wp-config.php" ]; then
    echo "Creating wp-config.php..."
    
    # Generate WordPress authentication keys and salts
    SALT=$(curl -s https://api.wordpress.org/secret-key/1.1/salt/)
    
    cat << EOF > /var/www/html/wp-config.php
<?php
/** WordPress configuration file */

// ** MySQL settings ** //
define( 'DB_NAME', '${WORDPRESS_DB_NAME}' );
define( 'DB_USER', '${WORDPRESS_DB_USER}' );
define( 'DB_PASSWORD', '${WORDPRESS_DB_PASSWORD}' );
define( 'DB_HOST', '${WORDPRESS_DB_HOST}' );
define( 'DB_CHARSET', 'utf8' );
define( 'DB_COLLATE', '' );

/**#@+
 * Authentication Unique Keys and Salts.
 */
${SALT}

/**#@-*/

/** WordPress Database Table prefix. */
\$table_prefix = 'wp_';

/** For developers: WordPress debugging mode. */
define( 'WP_DEBUG', false );
define( 'WP_DEBUG_LOG', false );
define( 'WP_DEBUG_DISPLAY', false );

/** WordPress file system method */
define( 'FS_METHOD', 'direct' );

/** Disable file editing from WordPress admin */
define( 'DISALLOW_FILE_EDIT', true );

/** Absolute path to the WordPress directory. */
if ( ! defined( 'ABSPATH' ) ) {
    define( 'ABSPATH', __DIR__ . '/' );
}

/** Sets up WordPress vars and included files. */
require_once ABSPATH . 'wp-settings.php';
EOF

    echo "wp-config.php created successfully!"
else
    echo "wp-config.php already exists, skipping creation..."
fi