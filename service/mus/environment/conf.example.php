<?php
/**
 * In this file, all local settings for MuS can be made. This includes database and solr server settings.
 * Enter description here ...
 * @var unknown_type
 */
$conf = array();
/*
 * Environment specific variables.
 * Use debug FALSE and mode production on production environments.
 */
$conf['debug'] = TRUE;
$conf['mode'] = 'development';

/*
 * Database credentials for the the apikey functionality.
 */
$conf['db_database'] = 'apikeydb';
$conf['db_username'] = 'apikeydb_username';
$conf['db_password'] = 'password';
$conf['db_host'] = 'localhost';
/*
 * Solr settings.
 */
$conf['solr_host'] = '127.0.0.1';
$conf['solr_port'] = '8983';
$conf['solr_path'] = '/solr';

