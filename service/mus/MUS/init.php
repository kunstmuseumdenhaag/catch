<?php
/*
 * Use a simple function for settings
 */
function initializeMus() {
  $slim = Slim::getInstance();
  // Get the mode (legacy or normal)
  $conf_filename = 'conf.php';
  $legacy_setting = $slim->request()->params('legacymode');
  if (isset($legacy_setting) && $legacy_setting == 'on' && file_exists(MUS_ROOT . '/environment/legacy_conf.php')) {
    $conf_filename = 'legacy_conf.php';
  }
  $settings = array();
  // try to get the conf from the environment
  if (file_exists(MUS_ROOT . '/environment/' . $conf_filename)) {
    include_once MUS_ROOT . '/environment/' . $conf_filename;
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
  $slim->config($settings);
}