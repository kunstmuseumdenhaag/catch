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
  $feeds_tamper->id = 'adlib_object_importer-adlibparser_1-truncate';
  $feeds_tamper->importer = 'adlib_object_importer';
  $feeds_tamper->source = 'adlibparser:1';
  $feeds_tamper->plugin_id = 'truncate_text';
  $feeds_tamper->settings = array(
    'num_char' => '255',
    'ellipses' => 0,
  );
  $feeds_tamper->weight = 0;
  $feeds_tamper->description = 'Truncate';
  $export['adlib_object_importer-adlibparser_1-truncate'] = $feeds_tamper;

  $feeds_tamper = new stdClass;
  $feeds_tamper->disabled = FALSE; /* Edit this to true to make a default feeds_tamper disabled initially */
  $feeds_tamper->api_version = 2;
  $feeds_tamper->id = 'adlib_object_importer-adlibparser_10-truncate';
  $feeds_tamper->importer = 'adlib_object_importer';
  $feeds_tamper->source = 'adlibparser:10';
  $feeds_tamper->plugin_id = 'truncate_text';
  $feeds_tamper->settings = array(
    'num_char' => '250',
    'ellipses' => 0,
  );
  $feeds_tamper->weight = 0;
  $feeds_tamper->description = 'Truncate';
  $export['adlib_object_importer-adlibparser_10-truncate'] = $feeds_tamper;

  $feeds_tamper = new stdClass;
  $feeds_tamper->disabled = FALSE; /* Edit this to true to make a default feeds_tamper disabled initially */
  $feeds_tamper->api_version = 2;
  $feeds_tamper->id = 'adlib_object_importer-adlibparser_11-truncate';
  $feeds_tamper->importer = 'adlib_object_importer';
  $feeds_tamper->source = 'adlibparser:11';
  $feeds_tamper->plugin_id = 'truncate_text';
  $feeds_tamper->settings = array(
    'num_char' => '250',
    'ellipses' => 0,
  );
  $feeds_tamper->weight = 0;
  $feeds_tamper->description = 'Truncate';
  $export['adlib_object_importer-adlibparser_11-truncate'] = $feeds_tamper;

  $feeds_tamper = new stdClass;
  $feeds_tamper->disabled = FALSE; /* Edit this to true to make a default feeds_tamper disabled initially */
  $feeds_tamper->api_version = 2;
  $feeds_tamper->id = 'adlib_object_importer-adlibparser_12-truncate';
  $feeds_tamper->importer = 'adlib_object_importer';
  $feeds_tamper->source = 'adlibparser:12';
  $feeds_tamper->plugin_id = 'truncate_text';
  $feeds_tamper->settings = array(
    'num_char' => '250',
    'ellipses' => 0,
  );
  $feeds_tamper->weight = 0;
  $feeds_tamper->description = 'Truncate';
  $export['adlib_object_importer-adlibparser_12-truncate'] = $feeds_tamper;

  $feeds_tamper = new stdClass;
  $feeds_tamper->disabled = FALSE; /* Edit this to true to make a default feeds_tamper disabled initially */
  $feeds_tamper->api_version = 2;
  $feeds_tamper->id = 'adlib_object_importer-adlibparser_14-truncate';
  $feeds_tamper->importer = 'adlib_object_importer';
  $feeds_tamper->source = 'adlibparser:14';
  $feeds_tamper->plugin_id = 'truncate_text';
  $feeds_tamper->settings = array(
    'num_char' => '250',
    'ellipses' => 0,
  );
  $feeds_tamper->weight = 0;
  $feeds_tamper->description = 'Truncate';
  $export['adlib_object_importer-adlibparser_14-truncate'] = $feeds_tamper;

  $feeds_tamper = new stdClass;
  $feeds_tamper->disabled = FALSE; /* Edit this to true to make a default feeds_tamper disabled initially */
  $feeds_tamper->api_version = 2;
  $feeds_tamper->id = 'adlib_object_importer-adlibparser_15-truncate';
  $feeds_tamper->importer = 'adlib_object_importer';
  $feeds_tamper->source = 'adlibparser:15';
  $feeds_tamper->plugin_id = 'truncate_text';
  $feeds_tamper->settings = array(
    'num_char' => '250',
    'ellipses' => 0,
  );
  $feeds_tamper->weight = 0;
  $feeds_tamper->description = 'Truncate';
  $export['adlib_object_importer-adlibparser_15-truncate'] = $feeds_tamper;

  $feeds_tamper = new stdClass;
  $feeds_tamper->disabled = FALSE; /* Edit this to true to make a default feeds_tamper disabled initially */
  $feeds_tamper->api_version = 2;
  $feeds_tamper->id = 'adlib_object_importer-adlibparser_16-truncate';
  $feeds_tamper->importer = 'adlib_object_importer';
  $feeds_tamper->source = 'adlibparser:16';
  $feeds_tamper->plugin_id = 'truncate_text';
  $feeds_tamper->settings = array(
    'num_char' => '250',
    'ellipses' => 0,
  );
  $feeds_tamper->weight = 0;
  $feeds_tamper->description = 'Truncate';
  $export['adlib_object_importer-adlibparser_16-truncate'] = $feeds_tamper;

  $feeds_tamper = new stdClass;
  $feeds_tamper->disabled = FALSE; /* Edit this to true to make a default feeds_tamper disabled initially */
  $feeds_tamper->api_version = 2;
  $feeds_tamper->id = 'adlib_object_importer-adlibparser_22-truncate';
  $feeds_tamper->importer = 'adlib_object_importer';
  $feeds_tamper->source = 'adlibparser:22';
  $feeds_tamper->plugin_id = 'truncate_text';
  $feeds_tamper->settings = array(
    'num_char' => '250',
    'ellipses' => 0,
  );
  $feeds_tamper->weight = 0;
  $feeds_tamper->description = 'Truncate';
  $export['adlib_object_importer-adlibparser_22-truncate'] = $feeds_tamper;

  $feeds_tamper = new stdClass;
  $feeds_tamper->disabled = FALSE; /* Edit this to true to make a default feeds_tamper disabled initially */
  $feeds_tamper->api_version = 2;
  $feeds_tamper->id = 'adlib_object_importer-adlibparser_30-truncate';
  $feeds_tamper->importer = 'adlib_object_importer';
  $feeds_tamper->source = 'adlibparser:30';
  $feeds_tamper->plugin_id = 'truncate_text';
  $feeds_tamper->settings = array(
    'num_char' => '250',
    'ellipses' => 0,
  );
  $feeds_tamper->weight = 0;
  $feeds_tamper->description = 'Truncate';
  $export['adlib_object_importer-adlibparser_30-truncate'] = $feeds_tamper;

  $feeds_tamper = new stdClass;
  $feeds_tamper->disabled = FALSE; /* Edit this to true to make a default feeds_tamper disabled initially */
  $feeds_tamper->api_version = 2;
  $feeds_tamper->id = 'adlib_object_importer-adlibparser_4-truncate';
  $feeds_tamper->importer = 'adlib_object_importer';
  $feeds_tamper->source = 'adlibparser:4';
  $feeds_tamper->plugin_id = 'truncate_text';
  $feeds_tamper->settings = array(
    'num_char' => '250',
    'ellipses' => 0,
  );
  $feeds_tamper->weight = 0;
  $feeds_tamper->description = 'Truncate';
  $export['adlib_object_importer-adlibparser_4-truncate'] = $feeds_tamper;

  $feeds_tamper = new stdClass;
  $feeds_tamper->disabled = FALSE; /* Edit this to true to make a default feeds_tamper disabled initially */
  $feeds_tamper->api_version = 2;
  $feeds_tamper->id = 'adlib_object_importer-adlibparser_45-truncate';
  $feeds_tamper->importer = 'adlib_object_importer';
  $feeds_tamper->source = 'adlibparser:45';
  $feeds_tamper->plugin_id = 'truncate_text';
  $feeds_tamper->settings = array(
    'num_char' => '2000',
    'ellipses' => 0,
  );
  $feeds_tamper->weight = 0;
  $feeds_tamper->description = 'Truncate';
  $export['adlib_object_importer-adlibparser_45-truncate'] = $feeds_tamper;

  $feeds_tamper = new stdClass;
  $feeds_tamper->disabled = FALSE; /* Edit this to true to make a default feeds_tamper disabled initially */
  $feeds_tamper->api_version = 2;
  $feeds_tamper->id = 'adlib_object_importer-adlibparser_47-truncate';
  $feeds_tamper->importer = 'adlib_object_importer';
  $feeds_tamper->source = 'adlibparser:47';
  $feeds_tamper->plugin_id = 'truncate_text';
  $feeds_tamper->settings = array(
    'num_char' => '2000',
    'ellipses' => 0,
  );
  $feeds_tamper->weight = 0;
  $feeds_tamper->description = 'Truncate';
  $export['adlib_object_importer-adlibparser_47-truncate'] = $feeds_tamper;

  $feeds_tamper = new stdClass;
  $feeds_tamper->disabled = FALSE; /* Edit this to true to make a default feeds_tamper disabled initially */
  $feeds_tamper->api_version = 2;
  $feeds_tamper->id = 'adlib_object_importer-adlibparser_48-truncate';
  $feeds_tamper->importer = 'adlib_object_importer';
  $feeds_tamper->source = 'adlibparser:48';
  $feeds_tamper->plugin_id = 'truncate_text';
  $feeds_tamper->settings = array(
    'num_char' => '2000',
    'ellipses' => 0,
  );
  $feeds_tamper->weight = 0;
  $feeds_tamper->description = 'Truncate';
  $export['adlib_object_importer-adlibparser_48-truncate'] = $feeds_tamper;

  $feeds_tamper = new stdClass;
  $feeds_tamper->disabled = FALSE; /* Edit this to true to make a default feeds_tamper disabled initially */
  $feeds_tamper->api_version = 2;
  $feeds_tamper->id = 'adlib_object_importer-adlibparser_49-truncate';
  $feeds_tamper->importer = 'adlib_object_importer';
  $feeds_tamper->source = 'adlibparser:49';
  $feeds_tamper->plugin_id = 'truncate_text';
  $feeds_tamper->settings = array(
    'num_char' => '250',
    'ellipses' => 0,
  );
  $feeds_tamper->weight = 0;
  $feeds_tamper->description = 'Truncate';
  $export['adlib_object_importer-adlibparser_49-truncate'] = $feeds_tamper;

  $feeds_tamper = new stdClass;
  $feeds_tamper->disabled = FALSE; /* Edit this to true to make a default feeds_tamper disabled initially */
  $feeds_tamper->api_version = 2;
  $feeds_tamper->id = 'adlib_object_importer-adlibparser_58-find_replace_regex';
  $feeds_tamper->importer = 'adlib_object_importer';
  $feeds_tamper->source = 'adlibparser:58';
  $feeds_tamper->plugin_id = 'find_replace_regex';
  $feeds_tamper->settings = array(
    'find' => '(^$)',
    'replace' => 'volledig',
    'limit' => '',
    'real_limit' => -1,
  );
  $feeds_tamper->weight = 1;
  $feeds_tamper->description = 'Replace empty strings.';
  $export['adlib_object_importer-adlibparser_58-find_replace_regex'] = $feeds_tamper;

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

  $feeds_tamper = new stdClass;
  $feeds_tamper->disabled = FALSE; /* Edit this to true to make a default feeds_tamper disabled initially */
  $feeds_tamper->api_version = 2;
  $feeds_tamper->id = 'adlib_object_importer-adlibparser_7-truncate';
  $feeds_tamper->importer = 'adlib_object_importer';
  $feeds_tamper->source = 'adlibparser:7';
  $feeds_tamper->plugin_id = 'truncate_text';
  $feeds_tamper->settings = array(
    'num_char' => '250',
    'ellipses' => 0,
  );
  $feeds_tamper->weight = 0;
  $feeds_tamper->description = 'Truncate';
  $export['adlib_object_importer-adlibparser_7-truncate'] = $feeds_tamper;

  $feeds_tamper = new stdClass;
  $feeds_tamper->disabled = FALSE; /* Edit this to true to make a default feeds_tamper disabled initially */
  $feeds_tamper->api_version = 2;
  $feeds_tamper->id = 'adlib_object_importer-adlibparser_9-truncate';
  $feeds_tamper->importer = 'adlib_object_importer';
  $feeds_tamper->source = 'adlibparser:9';
  $feeds_tamper->plugin_id = 'truncate_text';
  $feeds_tamper->settings = array(
    'num_char' => '250',
    'ellipses' => 0,
  );
  $feeds_tamper->weight = 0;
  $feeds_tamper->description = 'Truncate';
  $export['adlib_object_importer-adlibparser_9-truncate'] = $feeds_tamper;

  return $export;
}
