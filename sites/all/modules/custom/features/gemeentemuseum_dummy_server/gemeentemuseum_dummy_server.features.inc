<?php
/**
 * @file
 * gemeentemuseum_dummy_server.features.inc
 */

/**
 * Implements hook_default_search_api_server().
 */
function gemeentemuseum_dummy_server_default_search_api_server() {
  $items = array();
  $items['dummy'] = entity_import('search_api_server', '{
    "name" : "Dummy",
    "machine_name" : "dummy",
    "description" : "Dummy server for transfering index by features",
    "class" : "search_api_solr_service",
    "options" : {
      "host" : "localhost",
      "port" : "8983",
      "path" : "\\/solr",
      "http_user" : "",
      "http_pass" : "",
      "excerpt" : 0,
      "retrieve_data" : 0,
      "highlight_data" : 0
    },
    "enabled" : "0",
    "rdf_mapping" : []
  }');
  return $items;
}
