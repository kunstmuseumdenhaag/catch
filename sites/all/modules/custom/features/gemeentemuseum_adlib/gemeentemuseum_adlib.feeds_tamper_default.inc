<?php
/**
 * @file
 * gemeentemuseum_adlib.feeds_tamper_default.inc
 */

/**
 * Implementation of hook_feeds_tamper_default().
 */
function gemeentemuseum_adlib_feeds_tamper_default() {
  $export = array();

  $feeds_tamper = new stdClass;
  $feeds_tamper->disabled = FALSE; /* Edit this to true to make a default feeds_tamper disabled initially */
  $feeds_tamper->api_version = 2;
  $feeds_tamper->id = 'adlib_object_importer-adlibparser_58-set_default_value';
  $feeds_tamper->importer = 'adlib_object_importer';
  $feeds_tamper->source = 'adlibparser:58';
  $feeds_tamper->plugin_id = 'default_value';
  $feeds_tamper->settings = array(
    'default_value' => 'volledig',
  );
  $feeds_tamper->weight = 0;
  $feeds_tamper->description = 'Set default value';
  $export['adlib_object_importer-adlibparser_58-set_default_value'] = $feeds_tamper;

  return $export;
}
