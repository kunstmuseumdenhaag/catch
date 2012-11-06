<?php
/**
 * In this file, all local settings for MuS can be made. This includes database and solr server settings.
 * Enter description here ...
 * @var unknown_type
 */
$conf = array();
$conf['debug'] = TRUE;
$conf['mode'] = 'development';


$conf['db_database'] = 'gemeenapi';
$conf['db_username'] = 'gemeenapi';
$conf['db_password'] = 'z31lb00t';
$conf['db_host'] = 'localhost';
$conf['solr_host'] = '10.211.55.25';
$conf['solr_port'] = '8080';
//$conf['solr_path'] = '/solr36/mus_nieuw';
$conf['solr_path'] = '/solr36/gemeentemuseum';

/*
$conf['db_database'] = 'gemeenapi';
$conf['db_username'] = 'gemeenapi';
$conf['db_password'] = 'z31lb00t';
$conf['db_host'] = 'localhost';
$conf['solr_host'] = 'vps5470.xlshosting.net';
$conf['solr_port'] = '8080';
$conf['solr_path'] = '/solr/mus';*/
