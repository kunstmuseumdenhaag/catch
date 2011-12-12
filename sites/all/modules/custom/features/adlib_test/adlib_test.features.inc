<?php
/**
 * @file
 * adlib_test.features.inc
 */

/**
 * Implementation of hook_ctools_plugin_api().
 */
function adlib_test_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "adlibapi" && $api == "default_adlibapi_presets") {
    return array("version" => "1");
  }
  list($module, $api) = func_get_args();
  if ($module == "feeds" && $api == "feeds_importer_default") {
    return array("version" => "1");
  }
  list($module, $api) = func_get_args();
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
}

/**
 * Implementation of hook_views_api().
 */
function adlib_test_views_api() {
  list($module, $api) = func_get_args();
  if ($module == "views" && $api == "views_default") {
    return array("version" => "3.0");
  }
}

/**
 * Implementation of hook_node_info().
 */
function adlib_test_node_info() {
  $items = array(
    'adlib_object' => array(
      'name' => t('Adlib Object'),
      'base' => 'node_content',
      'description' => t('Imported object form an Adlib database'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
