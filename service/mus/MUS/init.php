<?php

/**
 * Use a simple function for settings
 *
 * @throws \Exception thrown when configuration could not be set.
 */
function initializeMus(&$app) {
//    $slim = Slim::getInstance();
    // Get the mode (legacy or normal)
    $conf_filename = 'conf.php';
    $legacy_setting = $app->request()->params('legacymode');
    if (isset($legacy_setting) && $legacy_setting == 'on' && file_exists(MUS_ROOT . '/environment/legacy_conf.php')) {
        $conf_filename = 'legacy_conf.php';
    }

    // try to get the conf from the environment
    if (file_exists(MUS_ROOT . '/environment/' . $conf_filename)) {
        include_once MUS_ROOT . '/environment/' . $conf_filename;
    }
    if (isset($conf)) {
        // Now add the settings to Slim
        $app->config($conf);
    }
    else {
        throw new Exception('Configuration not found');
    }
}
