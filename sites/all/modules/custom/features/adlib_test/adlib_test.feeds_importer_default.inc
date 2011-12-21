<?php
/**
 * @file
 * adlib_test.feeds_importer_default.inc
 */

/**
 * Implementation of hook_feeds_importer_default().
 */
function adlib_test_feeds_importer_default() {
  $export = array();

  $feeds_importer = new stdClass;
  $feeds_importer->disabled = FALSE; /* Edit this to true to make a default feeds_importer disabled initially */
  $feeds_importer->api_version = 1;
  $feeds_importer->id = 'adlib_object_importer';
  $feeds_importer->config = array(
    'name' => 'Adlib Object Importer',
    'description' => '',
    'fetcher' => array(
      'plugin_key' => 'AdlibFetcher',
      'config' => array(
        'database' => 'gemeentemuseum_algemeen',
        'changed' => '2009-01-01 01:01',
        'items' => '100',
        'fields' => array(
          0 => 'object_number',
          1 => 'object_name',
          2 => 'creator',
          3 => 'production.place',
          4 => 'material',
          5 => 'technique',
          6 => 'title',
          7 => 'production.date.start',
          8 => 'production.date.end',
          9 => 'production.period',
          10 => 'inscription.date',
          11 => 'inscription.maker',
          12 => 'acquisition.source',
          13 => 'acquisition.date',
          14 => 'acquisition.place',
          15 => 'documentation.title',
          16 => 'documentation.title.lref',
          17 => 'part_of_reference',
          18 => 'part_of.title',
          19 => 'parts_reference',
          20 => 'related_object.reference',
          21 => 'parts.title',
          22 => 'related_object.title',
          23 => 'edit.date',
          24 => 'institution.name',
          25 => 'reproduction.identifier_URL',
          26 => 'chronicle.title',
          27 => 'title.short_description',
          28 => 'creation_presentation',
          29 => 'dimensions_presentation',
          30 => 'material_technique_presentation',
          31 => 'description',
          32 => 'tags',
        ),
        'datesort' => 'modification',
        'batch_results' => 158241,
        'batch_startfrom' => 13605,
        'status' => 1,
        'xmltype' => 'unstructured',
      ),
    ),
    'parser' => array(
      'plugin_key' => 'FeedsAdlibParser',
      'config' => array(
        'sources' => array(
          'adlibparser:0' => '[object_number]',
          'adlibparser:1' => '[object_number]',
          'adlibparser:2' => '[title.short_description]',
          'adlibparser:3' => '[description]',
          'adlibparser:4' => '[object_name]',
          'adlibparser:6' => '[creation_presententation]',
          'adlibparser:7' => '[creator]',
          'adlibparser:8' => '[acquisition.source]',
          'adlibparser:9' => '[inscription.maker]',
          'adlibparser:10' => '[institution.name]',
          'adlibparser:11' => '[production.place_presentation]',
          'adlibparser:12' => '[production.place]',
          'adlibparser:13' => '[acquisition.place]',
          'adlibparser:14' => '[material_technique_presentation]',
          'adlibparser:15' => '[material]',
          'adlibparser:16' => '[technique]',
          'adlibparser:17' => '[dimensions_presentation]',
          'adlibparser:20' => '[related_object.title]',
          'adlibparser:21' => '[related_object.reference]',
          'adlibparser:22' => '[documentation.title]',
          'adlibparser:24' => '[part_of.title]',
          'adlibparser:25' => '[parts.title]',
          'adlibparser:26' => '[part_of_reference]',
          'adlibparser:27' => '[parts_reference]',
          'adlibparser:29' => '[documentation.title.lref]',
          'adlibparser:30' => '[production.date_presentation]',
          'adlibparser:34' => '[production.period]',
          'adlibparser:36' => '[raw_xml]',
          'adlibparser:37' => '[production.date.start]',
          'adlibparser:38' => '[production.date.end]',
          'adlibparser:39' => '[acquisition.date]',
          'adlibparser:40' => '[inscription.date]',
          'adlibparser:41' => '[edit.date]',
          'adlibparser:42' => '[reproduction.identifier_URL]',
          'adlibparser:43' => '[tags]',
          'adlibparser:44' => '[chronicle.title]',
          'adlibparser:45' => '[title]',
        ),
        'rawXML' => array(),
      ),
    ),
    'processor' => array(
      'plugin_key' => 'FeedsNodeProcessor',
      'config' => array(
        'content_type' => 'adlib_object',
        'expire' => '-1',
        'author' => 0,
        'mappings' => array(
          0 => array(
            'source' => 'adlibparser:0',
            'target' => 'field_adlib_pid',
            'unique' => FALSE,
          ),
          1 => array(
            'source' => 'adlibparser:1',
            'target' => 'title',
            'unique' => FALSE,
          ),
          2 => array(
            'source' => 'adlibparser:2',
            'target' => 'field_adlib_title_short_desc',
            'unique' => FALSE,
          ),
          3 => array(
            'source' => 'adlibparser:3',
            'target' => 'field_adlib_description',
            'unique' => FALSE,
          ),
          4 => array(
            'source' => 'adlibparser:4',
            'target' => 'field_adlib_object_name',
            'unique' => FALSE,
          ),
          5 => array(
            'source' => 'adlibparser:6',
            'target' => 'field_adlib_creation_present',
            'unique' => FALSE,
          ),
          6 => array(
            'source' => 'adlibparser:7',
            'target' => 'field_adlib_creator',
            'unique' => FALSE,
          ),
          7 => array(
            'source' => 'adlibparser:8',
            'target' => 'field_adlib_acquisition_source',
            'unique' => FALSE,
          ),
          8 => array(
            'source' => 'adlibparser:9',
            'target' => 'field_adlib_inscription_maker',
            'unique' => FALSE,
          ),
          9 => array(
            'source' => 'adlibparser:10',
            'target' => 'field_adlib_institution_name',
            'unique' => FALSE,
          ),
          10 => array(
            'source' => 'adlibparser:11',
            'target' => 'field_adlib_prod_place_present',
            'unique' => FALSE,
          ),
          11 => array(
            'source' => 'adlibparser:12',
            'target' => 'field_adlib_production_place',
            'unique' => FALSE,
          ),
          12 => array(
            'source' => 'adlibparser:13',
            'target' => 'field_adlib_acquisition_place',
            'unique' => FALSE,
          ),
          13 => array(
            'source' => 'adlibparser:14',
            'target' => 'field_adlib_material_present',
            'unique' => FALSE,
          ),
          14 => array(
            'source' => 'adlibparser:15',
            'target' => 'field_adlib_material',
            'unique' => FALSE,
          ),
          15 => array(
            'source' => 'adlibparser:16',
            'target' => 'field_adlib_technique',
            'unique' => FALSE,
          ),
          16 => array(
            'source' => 'adlibparser:17',
            'target' => 'field_adlib_dim_presentation',
            'unique' => FALSE,
          ),
          17 => array(
            'source' => 'adlibparser:20',
            'target' => 'field_adlib_rel_obj_title',
            'unique' => FALSE,
          ),
          18 => array(
            'source' => 'adlibparser:21',
            'target' => 'field_adlib_rel_obj_reference',
            'unique' => FALSE,
          ),
          19 => array(
            'source' => 'adlibparser:22',
            'target' => 'field_adlib_documentation_title',
            'unique' => FALSE,
          ),
          20 => array(
            'source' => 'adlibparser:24',
            'target' => 'field_adlib_part_of_title',
            'unique' => FALSE,
          ),
          21 => array(
            'source' => 'adlibparser:25',
            'target' => 'field_adlib_parts_title',
            'unique' => FALSE,
          ),
          22 => array(
            'source' => 'adlibparser:26',
            'target' => 'field_adlib_part_of_reference',
            'unique' => FALSE,
          ),
          23 => array(
            'source' => 'adlibparser:27',
            'target' => 'field_adlib_parts_reference',
            'unique' => FALSE,
          ),
          24 => array(
            'source' => 'adlibparser:29',
            'target' => 'field_adlib_doc_title_lref',
            'unique' => FALSE,
          ),
          25 => array(
            'source' => 'adlibparser:30',
            'target' => 'field_adlib_prod_date_present',
            'unique' => FALSE,
          ),
          26 => array(
            'source' => 'adlibparser:34',
            'target' => 'field_adlib_production_period',
            'unique' => FALSE,
          ),
          27 => array(
            'source' => 'adlibparser:36',
            'target' => 'field_adlib_raw_xml',
            'unique' => FALSE,
          ),
          28 => array(
            'source' => 'adlibparser:37',
            'target' => 'field_adlib_prod_date_start',
            'unique' => FALSE,
          ),
          29 => array(
            'source' => 'adlibparser:38',
            'target' => 'field_adlib_prod_date_end',
            'unique' => FALSE,
          ),
          30 => array(
            'source' => 'adlibparser:39',
            'target' => 'field_adlib_acquisition_date',
            'unique' => FALSE,
          ),
          31 => array(
            'source' => 'adlibparser:40',
            'target' => 'field_adlib_inscription_date',
            'unique' => FALSE,
          ),
          32 => array(
            'source' => 'adlibparser:41',
            'target' => 'field_adlib_edit_date',
            'unique' => FALSE,
          ),
          33 => array(
            'source' => 'adlibparser:42',
            'target' => 'field_adlib_image',
            'unique' => FALSE,
          ),
          34 => array(
            'source' => 'adlibparser:43',
            'target' => 'field_adlib_tag',
            'unique' => FALSE,
          ),
          35 => array(
            'source' => 'adlibparser:44',
            'target' => 'field_adlib_chronicle_title',
            'unique' => FALSE,
          ),
          36 => array(
            'source' => 'adlibparser:45',
            'target' => 'field_adlib_title',
            'unique' => FALSE,
          ),
        ),
        'update_existing' => '0',
        'input_format' => 'plain_text',
      ),
    ),
    'content_type' => '',
    'update' => 0,
    'import_period' => '-1',
    'expire_period' => 3600,
    'import_on_create' => 1,
    'process_in_background' => 0,
  );
  $export['adlib_object_importer'] = $feeds_importer;

  return $export;
}
