<?php
/*
 * Use a simple function for settings
 */
function initializeMus() {
  $settings = array();
  // try to get the conf from the environment
  $musDir = getcwd();
  if (file_exists(MUS_ROOT . '/environment/conf.php')) {
    include_once MUS_ROOT . '/environment/conf.php';
  }
  if (isset($conf)) {
    $settings = $conf;
  }
  else {
    $settings['debug'] = TRUE;
    $settings['mode'] = 'development';
    $settings['db_database'] = 'gemeenapi';
    $settings['db_username'] = 'gemeenapi';
    $settings['db_password'] = 'z31lb00t';
    $settings['db_host'] = 'localhost';
    $settings['solr_host'] = '10.211.55.25';
    $settings['solr_port'] = '8080';
    $settings['solr_path'] = '/solr36/gemeentemuseum';
  }
  // Now add the settings to Slim
  $slim = Slim::getInstance();
  $slim->config($settings);
}