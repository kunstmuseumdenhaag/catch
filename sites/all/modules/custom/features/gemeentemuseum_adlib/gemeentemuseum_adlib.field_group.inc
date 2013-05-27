<?php
/**
 * @file
 * gemeentemuseum_adlib.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function gemeentemuseum_adlib_field_group_info() {
  $export = array();

  $field_group = new stdClass();
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
    'weight' => '8',
    'children' => array(
      0 => 'field_adlib_material',
      1 => 'field_adlib_material_present',
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

  $field_group = new stdClass();
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
    'weight' => '10',
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
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_adlib_relations|node|adlib_object|form'] = $field_group;

  $field_group = new stdClass();
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
      0 => 'field_adlib_description',
      1 => 'field_adlib_object_name',
      2 => 'field_adlib_title_short_desc',
      3 => 'title',
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

  $field_group = new stdClass();
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
    'weight' => '6',
    'children' => array(
      0 => 'field_adlib_inscription_date',
      1 => 'field_adlib_prod_date_end',
      2 => 'field_adlib_prod_date_present',
      3 => 'field_adlib_prod_date_start',
      4 => 'field_adlib_production_period',
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

  $field_group = new stdClass();
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
      0 => 'field_adlib_prod_place_present',
      1 => 'field_adlib_production_place',
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

  $field_group = new stdClass();
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
      1 => 'field_adlib_inscription_maker',
      2 => 'field_adlib_institution_name',
      3 => 'field_adlib_creation_present',
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

  return $export;
}
