<?php
/**
 * In this file, all local settings for MuS can be made. This includes database and solr server settings.
 */
$conf = array();
/*
 * Environment specific variables.
 * Use debug FALSE and mode production on production environments.
 */
$conf['debug'] = TRUE;
$conf['mode'] = 'development';

/*
 * Database credentials for the apikey functionality.
 */
$host = 'db';
$port = 3306;
$driver = "mysql";

// If DDEV_PHP_VERSION is not set but IS_DDEV_PROJECT *is*, it means we're running (drush) on the host,
// so use the host-side bind port on docker IP
if (empty(getenv('DDEV_PHP_VERSION') && getenv('IS_DDEV_PROJECT') == 'true')) {
  $host = "127.0.0.1";
  $port = 49161;
}
$conf['db_database'] = 'key_db';
$conf['db_username'] = 'db';
$conf['db_password'] = 'db';
$conf['db_host'] = $host;
$conf['db_port'] = $port;
/*
 * Solr settings.
 */
// http://catch.ddev.site:8983/solr/dev
$conf['solr_host'] = 'catch.ddev.site';
$conf['solr_port'] = '8983';
$conf['solr_path'] = '/solr/dev';

