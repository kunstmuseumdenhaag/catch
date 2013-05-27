<?php
/**
 * @file
 * gemeentemuseum_adlib.default_adlibapi_presets.inc
 */

/**
 * Implements hook_default_adlibapi_preset().
 */
function gemeentemuseum_adlib_default_adlibapi_preset() {
  $export = array();

  $preset = new stdClass();
  $preset->disabled = FALSE; /* Edit this to true to make a default preset disabled initially */
  $preset->api_version = 1;
  $preset->name = 'catch';
  $preset->description = 'Catch api for gemeentemuseum';
  $preset->config = 'a:6:{s:3:"url";s:52:"http://adlibapi.gemeentemuseum.nl/catch/wwwopac.ashx";s:8:"database";s:13:"choicecollect";s:11:"imageserver";s:11:"adlibimages";s:13:"require_login";i:0;s:8:"username";s:0:"";s:8:"password";s:0:"";}';
  $export['catch'] = $preset;

  return $export;
}
