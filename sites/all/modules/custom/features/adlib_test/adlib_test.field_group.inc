<?php
/**
 * @file
 * adlib_test.field_group.inc
 */

/**
 * Implementation of hook_field_group_info().
 */
function adlib_test_field_group_info() {
  $export = array();

  $field_group = new stdClass;
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_adlib_how|node|adlib_object|default';
  $field_group->group_name = 'group_adlib_how';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'adlib_object';
  $field_group->mode = 'default';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'How',
    'weight' => '8',
    'children' => array(
      0 => 'field_adlib_dim_presentation',
      1 => 'field_adlib_material',
      2 => 'field_adlib_material_present',
      3 => 'field_adlib_technique',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => '',
      ),
    ),
  );
  $export['group_adlib_how|node|adlib_object|default'] = $field_group;

  $field_group = new stdClass;
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_adlib_how|node|adlib_object|form';
  $field_group->group_name = 'group_adlib_how';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'adlib_object';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'How',
    'weight' => '7',
    'children' => array(
      0 => 'field_adlib_material_present',
      1 => 'field_adlib_material',
      2 => 'field_adlib_technique',
      3 => 'field_adlib_dim_presentation',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => '',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_adlib_how|node|adlib_object|form'] = $field_group;

  $field_group = new stdClass;
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_adlib_ranking|node|adlib_object|default';
  $field_group->group_name = 'group_adlib_ranking';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'adlib_object';
  $field_group->mode = 'default';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Ranking',
    'weight' => '11',
    'children' => array(
      0 => 'field_adlib_edit_date',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => '',
      ),
    ),
  );
  $export['group_adlib_ranking|node|adlib_object|default'] = $field_group;

  $field_group = new stdClass;
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_adlib_relations|node|adlib_object|default';
  $field_group->group_name = 'group_adlib_relations';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'adlib_object';
  $field_group->mode = 'default';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Relations',
    'weight' => '9',
    'children' => array(
      0 => 'field_adlib_chronicle_title',
      1 => 'field_adlib_doc_title_lref',
      2 => 'field_adlib_documentation_title',
      3 => 'field_adlib_part_of_reference',
      4 => 'field_adlib_part_of_title',
      5 => 'field_adlib_parts_reference',
      6 => 'field_adlib_parts_title',
      7 => 'field_adlib_rel_obj_reference',
      8 => 'field_adlib_rel_obj_title',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => '',
      ),
    ),
  );
  $export['group_adlib_relations|node|adlib_object|default'] = $field_group;

  $field_group = new stdClass;
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_adlib_relations|node|adlib_object|form';
  $field_group->group_name = 'group_adlib_relations';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'adlib_object';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Relations',
    'weight' => '8',
    'children' => array(
      0 => 'field_adlib_chronicle_title_lref',
      1 => 'field_adlib_rel_obj_title',
      2 => 'field_adlib_rel_obj_reference',
      3 => 'field_adlib_documentation_title',
      4 => 'field_adlib_chronicle_title',
      5 => 'field_adlib_part_of_title',
      6 => 'field_adlib_part_of_reference',
      7 => 'field_adlib_parts_title',
      8 => 'field_adlib_parts_reference',
      9 => 'field_adlib_doc_title_lref',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => '',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_adlib_relations|node|adlib_object|form'] = $field_group;

  $field_group = new stdClass;
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_adlib_what|node|adlib_object|default';
  $field_group->group_name = 'group_adlib_what';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'adlib_object';
  $field_group->mode = 'default';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'What',
    'weight' => '4',
    'children' => array(
      0 => 'field_adlib_description',
      1 => 'field_adlib_object_name',
      2 => 'field_adlib_title',
      3 => 'field_adlib_title_short_desc',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => '',
      ),
    ),
  );
  $export['group_adlib_what|node|adlib_object|default'] = $field_group;

  $field_group = new stdClass;
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_adlib_what|node|adlib_object|form';
  $field_group->group_name = 'group_adlib_what';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'adlib_object';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'What',
    'weight' => '2',
    'children' => array(
      0 => 'field_adlib_title_short_desc',
      1 => 'field_adlib_description',
      2 => 'field_adlib_tags',
      3 => 'field_adlib_object_name',
      4 => 'title',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => '',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_adlib_what|node|adlib_object|form'] = $field_group;

  $field_group = new stdClass;
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_adlib_when|node|adlib_object|default';
  $field_group->group_name = 'group_adlib_when';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'adlib_object';
  $field_group->mode = 'default';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'When',
    'weight' => '7',
    'children' => array(
      0 => 'field_adlib_acquisition_date',
      1 => 'field_adlib_inscription_date',
      2 => 'field_adlib_prod_date_end',
      3 => 'field_adlib_prod_date_present',
      4 => 'field_adlib_prod_date_start',
      5 => 'field_adlib_production_period',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => '',
      ),
    ),
  );
  $export['group_adlib_when|node|adlib_object|default'] = $field_group;

  $field_group = new stdClass;
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_adlib_when|node|adlib_object|form';
  $field_group->group_name = 'group_adlib_when';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'adlib_object';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'When',
    'weight' => '5',
    'children' => array(
      0 => 'field_adlib_production_period',
      1 => 'field_adlib_prod_date_present',
      2 => 'field_adlib_prod_date_start',
      3 => 'field_adlib_prod_date_end',
      4 => 'field_adlib_acquisition_date',
      5 => 'field_adlib_inscription_date',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => '',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_adlib_when|node|adlib_object|form'] = $field_group;

  $field_group = new stdClass;
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_adlib_where|node|adlib_object|default';
  $field_group->group_name = 'group_adlib_where';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'adlib_object';
  $field_group->mode = 'default';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Where',
    'weight' => '6',
    'children' => array(
      0 => 'field_adlib_acquisition_place',
      1 => 'field_adlib_prod_place_present',
      2 => 'field_adlib_production_place',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => '',
      ),
    ),
  );
  $export['group_adlib_where|node|adlib_object|default'] = $field_group;

  $field_group = new stdClass;
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_adlib_where|node|adlib_object|form';
  $field_group->group_name = 'group_adlib_where';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'adlib_object';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Where',
    'weight' => '4',
    'children' => array(
      0 => 'field_adlib_production_place',
      1 => 'field_adlib_acquisition_place',
      2 => 'field_adlib_prod_place_present',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => '',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_adlib_where|node|adlib_object|form'] = $field_group;

  $field_group = new stdClass;
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_adlib_who|node|adlib_object|default';
  $field_group->group_name = 'group_adlib_who';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'adlib_object';
  $field_group->mode = 'default';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Who',
    'weight' => '5',
    'children' => array(
      0 => 'field_adlib_acquisition_source',
      1 => 'field_adlib_creation_present',
      2 => 'field_adlib_creator',
      3 => 'field_adlib_inscription_maker',
      4 => 'field_adlib_institution_name',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => '',
      ),
    ),
  );
  $export['group_adlib_who|node|adlib_object|default'] = $field_group;

  $field_group = new stdClass;
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_adlib_who|node|adlib_object|form';
  $field_group->group_name = 'group_adlib_who';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'adlib_object';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Who',
    'weight' => '3',
    'children' => array(
      0 => 'field_adlib_creator',
      1 => 'field_adlib_acquisition_source',
      2 => 'field_adlib_inscription_maker',
      3 => 'field_adlib_institution_name',
      4 => 'field_adlib_creation_present',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => '',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_adlib_who|node|adlib_object|form'] = $field_group;

  $field_group = new stdClass;
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_adlib_xml|node|adlib_object|default';
  $field_group->group_name = 'group_adlib_xml';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'adlib_object';
  $field_group->mode = 'default';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Raw xml',
    'weight' => '10',
    'children' => array(
      0 => 'field_adlib_raw_xml',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Raw xml',
      'instance_settings' => array(
        'classes' => '',
        'description' => '',
      ),
      'formatter' => 'collapsed',
    ),
  );
  $export['group_adlib_xml|node|adlib_object|default'] = $field_group;

  return $export;
}
