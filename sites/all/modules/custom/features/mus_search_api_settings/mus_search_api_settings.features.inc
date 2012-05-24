<?php
/**
 * @file
 * mus_search_api_settings.features.inc
 */

/**
 * Implementation of hook_default_search_api_index().
 */
function mus_search_api_settings_default_search_api_index() {
  $items = array();
  $items['mus_index_1'] = entity_import('search_api_index', '{
    "name" : "MuS index 1",
    "machine_name" : "mus_index_1",
    "description" : "MuS index 1",
    "server" : "dummy",
    "item_type" : "node",
    "options" : {
      "index_directly" : 1,
      "cron_limit" : "50",
      "fields" : {
        "title" : { "type" : "text" },
        "url" : { "type" : "uri" },
        "field_adlib_chronicle_title" : { "type" : "list\\u003cstring\\u003e" },
        "field_adlib_chronicle_title_lref" : { "type" : "string" },
        "field_adlib_creation_present" : { "type" : "string" },
        "field_adlib_creator" : { "type" : "string" },
        "field_adlib_credit_line" : { "type" : "list\\u003ctext\\u003e" },
        "field_adlib_description" : { "type" : "text" },
        "field_adlib_dim_presentation" : { "type" : "string" },
        "field_adlib_doc_title_lref" : { "type" : "string" },
        "field_adlib_documentation_title" : { "type" : "string" },
        "field_adlib_edit_date" : { "type" : "list\\u003cstring\\u003e" },
        "field_adlib_how_raw" : { "type" : "string" },
        "field_adlib_image" : { "type" : "list\\u003cstring\\u003e" },
        "field_adlib_inscription_date" : { "type" : "string" },
        "field_adlib_inscription_maker" : { "type" : "string" },
        "field_adlib_institution_name" : { "type" : "string" },
        "field_adlib_material" : { "type" : "string" },
        "field_adlib_material_present" : { "type" : "string" },
        "field_adlib_object_name" : { "type" : "string" },
        "field_adlib_object_number" : { "type" : "string" },
        "field_adlib_paragraph_present" : { "type" : "list\\u003ctext\\u003e" },
        "field_adlib_part_of_reference" : { "type" : "string" },
        "field_adlib_part_of_title" : { "type" : "string" },
        "field_adlib_parts_reference" : { "type" : "string" },
        "field_adlib_parts_title" : { "type" : "string" },
        "field_adlib_pid" : { "type" : "string" },
        "field_adlib_pidnumber" : { "type" : "string" },
        "field_adlib_prod_date_end" : { "type" : "string" },
        "field_adlib_prod_date_present" : { "type" : "string" },
        "field_adlib_prod_date_start" : { "type" : "string" },
        "field_adlib_prod_place_present" : { "type" : "string" },
        "field_adlib_production_period" : { "type" : "string" },
        "field_adlib_production_place" : { "type" : "string" },
        "field_adlib_production_reason" : { "type" : "list\\u003ctext\\u003e" },
        "field_adlib_publication_access" : { "type" : "string" },
        "field_adlib_qualific_present" : { "type" : "list\\u003ctext\\u003e" },
        "field_adlib_raw_xml" : { "type" : "string" },
        "field_adlib_rel_obj_reference" : { "type" : "string" },
        "field_adlib_rel_obj_title" : { "type" : "string" },
        "field_adlib_repro_reference" : { "type" : "list\\u003ctext\\u003e" },
        "field_adlib_tag" : { "type" : "list\\u003ctext\\u003e" },
        "field_adlib_technique" : { "type" : "string" },
        "field_adlib_title" : { "type" : "text" },
        "field_adlib_title_short_desc" : { "type" : "string" },
        "field_adlib_what_raw" : { "type" : "string" },
        "field_adlib_when_raw" : { "type" : "string" },
        "field_adlib_where_raw" : { "type" : "string" },
        "field_adlib_who_raw" : { "type" : "string" },
        "field_adlib_alternative_number" : { "type" : "list\\u003cstring\\u003e" },
        "field_adlib_alt_number_type" : { "type" : "list\\u003cstring\\u003e" },
        "search_api_language" : { "type" : "string" }
      },
      "data_alter_callbacks" : {
        "search_api_alter_bundle_filter" : {
          "status" : 0,
          "weight" : "-10",
          "settings" : { "default" : "1", "bundles" : [] }
        },
        "search_api_alter_node_access" : { "status" : 0, "weight" : "0", "settings" : [] },
        "search_api_alter_add_hierarchy" : { "status" : 0, "weight" : "0", "settings" : { "fields" : [] } },
        "search_api_alter_add_aggregation" : { "status" : 0, "weight" : "0", "settings" : [] },
        "search_api_alter_add_url" : { "status" : 0, "weight" : "0", "settings" : [] },
        "search_api_alter_add_viewed_entity" : { "status" : 0, "weight" : "0", "settings" : { "mode" : "full" } }
      },
      "processors" : {
        "search_api_case_ignore" : { "status" : 0, "weight" : "0", "settings" : { "fields" : [] } },
        "search_api_html_filter" : {
          "status" : 1,
          "weight" : "10",
          "settings" : {
            "fields" : [],
            "title" : 1,
            "alt" : 1,
            "tags" : "h1 = 5\\r\\nh2 = 3\\r\\nh3 = 2\\r\\nstrong = 2\\r\\nb = 2\\r\\nem = 1.5\\r\\nu = 1.5"
          }
        },
        "search_api_tokenizer" : {
          "status" : 0,
          "weight" : "20",
          "settings" : { "fields" : [], "spaces" : "[^\\\\p{L}\\\\p{N}^\']", "ignorable" : "[-]" }
        },
        "search_api_stopwords" : {
          "status" : 0,
          "weight" : "30",
          "settings" : {
            "fields" : [],
            "file" : "",
            "stopwords" : "but\\r\\ndid\\r\\nthe this that those\\r\\netc"
          }
        }
      }
    },
    "enabled" : "0",
    "read_only" : "0",
    "rdf_mapping" : []
  }');
  return $items;
}
