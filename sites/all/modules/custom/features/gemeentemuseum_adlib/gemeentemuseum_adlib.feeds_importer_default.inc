<?php
/**
 * @file
 * gemeentemuseum_adlib.feeds_importer_default.inc
 */

/**
 * Implements hook_feeds_importer_default().
 */
function gemeentemuseum_adlib_feeds_importer_default() {
  $export = array();

  $feeds_importer = new stdClass();
  $feeds_importer->disabled = FALSE; /* Edit this to true to make a default feeds_importer disabled initially */
  $feeds_importer->api_version = 1;
  $feeds_importer->id = 'adlib_object_importer';
  $feeds_importer->config = array(
    'name' => 'Adlib Object Importer',
    'description' => '',
    'fetcher' => array(
      'plugin_key' => 'AdlibFetcher',
      'config' => array(
        'database' => 'catch',
        'changed' => '2013-11-20 10:10',
        'items' => '100',
        'fields' => array(
          0 => 'object_number',
          1 => 'alternative_number',
          2 => 'alternative_number.type',
          3 => 'object_name',
          4 => 'creator',
          5 => 'creator.lref',
          6 => 'creator.qualifier',
          7 => 'school_style.lref',
          8 => 'production.place',
          9 => 'production.place.lref',
          10 => 'material',
          11 => 'technique',
          12 => 'title',
          13 => 'production.date.start',
          14 => 'production.date.end',
          15 => 'production.period',
          16 => 'production.date.notes',
          17 => 'inscription.date',
          18 => 'inscription.maker',
          19 => 'priref',
          20 => 'reproduction.reference',
          21 => 'part_of_reference',
          22 => 'part_of.title',
          23 => 'part_of.notes',
          24 => 'parts_reference',
          25 => 'related_object.reference',
          26 => 'parts.title',
          27 => 'parts.notes',
          28 => 'related_object.title',
          29 => 'production.notes',
          30 => 'production.reason',
          31 => 'edit.date',
          32 => 'institution.name',
          33 => 'reproduction.identifier_URL',
          34 => 'chronicle.title',
          35 => 'chronicle.title.lref',
          36 => 'routine.entry.step',
          37 => 'title.short_description',
          38 => 'creation_presentation',
          39 => 'production.place_presentation',
          40 => 'production.date_presentation',
          41 => 'dimensions_presentation',
          42 => 'material_technique_presentation',
          43 => 'credit_line',
          44 => 'description.paragraph_presentation',
          45 => 'description.qualification_presentation',
          46 => 'description',
          47 => 'description_english',
          48 => 'tags',
          49 => 'PIDnumber',
          50 => 'title_english',
          51 => 'title.short_description_english',
          52 => 'creation_presentation_english',
          53 => 'production.place_presentation_english',
          54 => 'production.date_presentation_english',
          55 => 'dimensions_presentation_english',
          56 => 'material_technique_presentation_english',
          57 => 'credit_line.english',
        ),
        'datesort' => 'modification',
        'batch_results' => 0,
        'batch_startfrom' => 0,
        'status' => 2,
        'xmltype' => 'grouped',
        'use_custom_query' => 0,
        'custom_query' => 'routine.entry.step=minimaal',
      ),
    ),
    'parser' => array(
      'plugin_key' => 'FeedsAdlibParser',
      'config' => array(
        'sources' => array(
          'adlibparser:0' => '[object_number]',
          'adlibparser:1' => '[title: | ]',
          'adlibparser:2' => '[title.short_description]',
          'adlibparser:3' => '[description]',
          'adlibparser:4' => '[object_name]',
          'adlibparser:6' => '[creation_presententation]',
          'adlibparser:7' => '[creator]',
          'adlibparser:9' => '[inscription.maker]',
          'adlibparser:10' => '[institution.name]',
          'adlibparser:11' => '[production.place_presentation]',
          'adlibparser:12' => '[production.place]',
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
          'adlibparser:40' => '[inscription.date]',
          'adlibparser:41' => '[edit.date]',
          'adlibparser:42' => '[reproduction.identifier_URL]',
          'adlibparser:43' => '[tags]',
          'adlibparser:44' => '[chronicle.title]',
          'adlibparser:45' => '[title]',
          'adlibparser:46' => '[PIDnumber]',
          'adlibparser:47' => '[credit_line]',
          'adlibparser:48' => '[description.paragraph_presentation]',
          'adlibparser:49' => '[description.qualification_presentation]',
          'adlibparser:50' => '[production.reason]',
          'adlibparser:51' => '[reproduction.reference]',
          'adlibparser:52' => '<dimensions_presentation>[dimensions_presentation:</dimensions_presentation><dimensions_presentation>]</dimensions_presentation>
<material>[material:</material><material>]</material>
<material_technique_presentation>[material_technique_presentation:</material_technique_presentation><material_technique_presentation>]</material_technique_presentation>
<technique>[technique:</technique><technique>]</technique>',
          'adlibparser:53' => '<description>[description:</description><description>]</description>
<object_name>[object_name:</object_name><object_name>]</object_name>
<title.short_description>[title.short_description:</title.short_description><title.short_description>]</title.short_description>
<title>[title:</title><title>]</title>',
          'adlibparser:54' => '<inscription.date>[inscription.date:</inscription.date><inscription.date>]</inscription.date>
<production.date.end>[production.date.end:</production.date.end><production.date.end>]</production.date.end>
<production.date_presentation>[production.date_presentation:</production.date_presentation><production.date_presentation>]</production.date_presentation>
<production.date.start>[production.date.start:</production.date.start><production.date.start>]</production.date.start>
<production.period>[production.period:</production.period><production.period>]</production.period>',
          'adlibparser:55' => '<production.place_presentation>[production.place_presentation:</production.place_presentation><production.place_presentation>]</production.place_presentation>
<production.place>[production.place:</production.place><production.place>]</production.place>',
          'adlibparser:56' => '<creation_presentation>[creation_presentation:</creation_presentation><creation_presentation>]</creation_presentation>
<creator>[creator:</creator><creator>]</creator>
<inscription.maker>[inscription.maker:</inscription.maker><inscription.maker>]</inscription.maker>
<institution.name>[institution.name:</institution.name><institution.name>]</institution.name>',
          'adlibparser:57' => '[object_number]',
          'adlibparser:58' => '[routine.entry.step]',
          'adlibparser:59' => '[PIDnumber]',
          'adlibparser:60' => '[alternative_number]',
          'adlibparser:61' => '[alternative_number.type]',
          'adlibparser:62' => '[chronicle.title.lref]',
          'adlibparser:63' => '[title_english: | ]',
          'adlibparser:64' => '[title.short_description_english]',
          'adlibparser:65' => '[creation_presentation_english]',
          'adlibparser:66' => '[production.place_presentation_english]',
          'adlibparser:67' => '[production.date_presentation_english]',
          'adlibparser:68' => '[material_technique_presentation_english]',
          'adlibparser:69' => '[dimensions_presentation_english]',
          'adlibparser:70' => '[credit_line.english]',
          'adlibparser:71' => '[description_english]',
        ),
        'rawXML' => array(),
        'language' => array(
          'list' => 'nl-NL,1,neutral',
        ),
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
            'source' => 'adlibparser:9',
            'target' => 'field_adlib_inscription_maker',
            'unique' => FALSE,
          ),
          8 => array(
            'source' => 'adlibparser:10',
            'target' => 'field_adlib_institution_name',
            'unique' => FALSE,
          ),
          9 => array(
            'source' => 'adlibparser:11',
            'target' => 'field_adlib_prod_place_present',
            'unique' => FALSE,
          ),
          10 => array(
            'source' => 'adlibparser:12',
            'target' => 'field_adlib_production_place',
            'unique' => FALSE,
          ),
          11 => array(
            'source' => 'adlibparser:14',
            'target' => 'field_adlib_material_present',
            'unique' => FALSE,
          ),
          12 => array(
            'source' => 'adlibparser:15',
            'target' => 'field_adlib_material',
            'unique' => FALSE,
          ),
          13 => array(
            'source' => 'adlibparser:16',
            'target' => 'field_adlib_technique',
            'unique' => FALSE,
          ),
          14 => array(
            'source' => 'adlibparser:17',
            'target' => 'field_adlib_dim_presentation',
            'unique' => FALSE,
          ),
          15 => array(
            'source' => 'adlibparser:20',
            'target' => 'field_adlib_rel_obj_title',
            'unique' => FALSE,
          ),
          16 => array(
            'source' => 'adlibparser:21',
            'target' => 'field_adlib_rel_obj_reference',
            'unique' => FALSE,
          ),
          17 => array(
            'source' => 'adlibparser:22',
            'target' => 'field_adlib_documentation_title',
            'unique' => FALSE,
          ),
          18 => array(
            'source' => 'adlibparser:24',
            'target' => 'field_adlib_part_of_title',
            'unique' => FALSE,
          ),
          19 => array(
            'source' => 'adlibparser:25',
            'target' => 'field_adlib_parts_title',
            'unique' => FALSE,
          ),
          20 => array(
            'source' => 'adlibparser:26',
            'target' => 'field_adlib_part_of_reference',
            'unique' => FALSE,
          ),
          21 => array(
            'source' => 'adlibparser:27',
            'target' => 'field_adlib_parts_reference',
            'unique' => FALSE,
          ),
          22 => array(
            'source' => 'adlibparser:29',
            'target' => 'field_adlib_doc_title_lref',
            'unique' => FALSE,
          ),
          23 => array(
            'source' => 'adlibparser:30',
            'target' => 'field_adlib_prod_date_present',
            'unique' => FALSE,
          ),
          24 => array(
            'source' => 'adlibparser:34',
            'target' => 'field_adlib_production_period',
            'unique' => FALSE,
          ),
          25 => array(
            'source' => 'adlibparser:36',
            'target' => 'field_adlib_raw_xml',
            'unique' => FALSE,
          ),
          26 => array(
            'source' => 'adlibparser:37',
            'target' => 'field_adlib_prod_date_start',
            'unique' => FALSE,
          ),
          27 => array(
            'source' => 'adlibparser:38',
            'target' => 'field_adlib_prod_date_end',
            'unique' => FALSE,
          ),
          28 => array(
            'source' => 'adlibparser:40',
            'target' => 'field_adlib_inscription_date',
            'unique' => FALSE,
          ),
          29 => array(
            'source' => 'adlibparser:41',
            'target' => 'field_adlib_edit_date',
            'unique' => FALSE,
          ),
          30 => array(
            'source' => 'adlibparser:42',
            'target' => 'field_adlib_image',
            'unique' => FALSE,
          ),
          31 => array(
            'source' => 'adlibparser:43',
            'target' => 'field_adlib_tag',
            'unique' => FALSE,
          ),
          32 => array(
            'source' => 'adlibparser:44',
            'target' => 'field_adlib_chronicle_title',
            'unique' => FALSE,
          ),
          33 => array(
            'source' => 'adlibparser:45',
            'target' => 'field_adlib_title',
            'unique' => FALSE,
          ),
          34 => array(
            'source' => 'adlibparser:46',
            'target' => 'guid',
            'unique' => 1,
          ),
          35 => array(
            'source' => 'adlibparser:47',
            'target' => 'field_adlib_credit_line',
            'unique' => FALSE,
          ),
          36 => array(
            'source' => 'adlibparser:48',
            'target' => 'field_adlib_paragraph_present',
            'unique' => FALSE,
          ),
          37 => array(
            'source' => 'adlibparser:49',
            'target' => 'field_adlib_qualific_present',
            'unique' => FALSE,
          ),
          38 => array(
            'source' => 'adlibparser:50',
            'target' => 'field_adlib_production_reason',
            'unique' => FALSE,
          ),
          39 => array(
            'source' => 'adlibparser:51',
            'target' => 'field_adlib_repro_reference',
            'unique' => FALSE,
          ),
          40 => array(
            'source' => 'adlibparser:52',
            'target' => 'field_adlib_how_raw',
            'unique' => FALSE,
          ),
          41 => array(
            'source' => 'adlibparser:53',
            'target' => 'field_adlib_what_raw',
            'unique' => FALSE,
          ),
          42 => array(
            'source' => 'adlibparser:54',
            'target' => 'field_adlib_when_raw',
            'unique' => FALSE,
          ),
          43 => array(
            'source' => 'adlibparser:55',
            'target' => 'field_adlib_where_raw',
            'unique' => FALSE,
          ),
          44 => array(
            'source' => 'adlibparser:56',
            'target' => 'field_adlib_who_raw',
            'unique' => FALSE,
          ),
          45 => array(
            'source' => 'adlibparser:57',
            'target' => 'field_adlib_object_number',
            'unique' => FALSE,
          ),
          46 => array(
            'source' => 'adlibparser:58',
            'target' => 'field_adlib_publication_access',
            'unique' => FALSE,
          ),
          47 => array(
            'source' => 'adlibparser:59',
            'target' => 'field_adlib_pidnumber',
            'unique' => FALSE,
          ),
          48 => array(
            'source' => 'adlibparser:60',
            'target' => 'field_adlib_alternative_number',
            'unique' => FALSE,
          ),
          49 => array(
            'source' => 'adlibparser:61',
            'target' => 'field_adlib_alt_number_type',
            'unique' => FALSE,
          ),
          50 => array(
            'source' => 'adlibparser:62',
            'target' => 'field_adlib_chronicle_title_lref',
            'unique' => FALSE,
          ),
          51 => array(
            'source' => 'adlibparser:63',
            'target' => 'field_adlib_title_en',
            'unique' => FALSE,
          ),
          52 => array(
            'source' => 'adlibparser:64',
            'target' => 'field_adlib_title_short_desc_en',
            'unique' => FALSE,
          ),
          53 => array(
            'source' => 'adlibparser:65',
            'target' => 'field_adlib_creation_present_en',
            'unique' => FALSE,
          ),
          54 => array(
            'source' => 'adlibparser:66',
            'target' => 'field_adlib_prod_place_pres_en',
            'unique' => FALSE,
          ),
          55 => array(
            'source' => 'adlibparser:67',
            'target' => 'field_adlib_prod_date_present_en',
            'unique' => FALSE,
          ),
          56 => array(
            'source' => 'adlibparser:68',
            'target' => 'field_adlib_material_present_en',
            'unique' => FALSE,
          ),
          57 => array(
            'source' => 'adlibparser:69',
            'target' => 'field_adlib_dim_presentation_en',
            'unique' => FALSE,
          ),
          58 => array(
            'source' => 'adlibparser:70',
            'target' => 'field_adlib_credit_line_en',
            'unique' => FALSE,
          ),
          59 => array(
            'source' => 'adlibparser:71',
            'target' => 'field_adlib_description_en',
            'unique' => FALSE,
          ),
        ),
        'update_existing' => '1',
        'input_format' => 'plain_text',
        'authorize' => 1,
        'skip_hash_check' => 1,
      ),
    ),
    'content_type' => '',
    'update' => 0,
    'import_period' => '0',
    'expire_period' => 3600,
    'import_on_create' => 1,
    'process_in_background' => 1,
  );
  $export['adlib_object_importer'] = $feeds_importer;

  return $export;
}
