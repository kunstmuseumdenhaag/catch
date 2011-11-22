<?php
/**
 * @file
 * adlib_test.default_adlibapi_presets.inc
 */

/**
 * Implements hook_default_adlibapi_preset().
 */
function adlib_test_default_adlibapi_preset() {
  $export = array();

  $preset = new stdClass;
  $preset->disabled = FALSE; /* Edit this to true to make a default preset disabled initially */
  $preset->api_version = 1;
  $preset->name = 'gemeentemuseum_algemeen';
  $preset->description = 'Algemene database van Gemeentemuseum';
  $preset->config = 'a:6:{s:3:"url";s:52:"http://adlibapi3.gemeentemuseum.nl/ashx/wwwopac.ashx";s:8:"database";s:13:"choicecollect";s:11:"imageserver";s:11:"adlibimages";s:13:"require_login";i:0;s:8:"username";s:0:"";s:8:"password";s:0:"";}';
  $export['gemeentemuseum_algemeen'] = $preset;

  return $export;
}
