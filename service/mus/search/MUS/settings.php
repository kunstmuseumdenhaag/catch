<?php
/*
 * Use a simple function for settings
 */
function musSettings($key) {
  $settings = array();
  $settings['db_database'] = 'gemeenapi';
  $settings['db_username'] = 'gemeenapi';
  $settings['db_password'] = 'z31lb00t';
  $settings['db_host'] = 'localhost';
  $settings['solr_host'] = '10.211.55.25';
  $settings['solr_port'] = '8080';
  $settings['solr_path'] = '/solr36/gemeentemuseum';
  return $settings[$key];
}