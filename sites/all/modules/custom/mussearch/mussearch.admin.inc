<?php
function mussearch_admin_settings($form, &$form_state) {
  $form = array();
  // Get indexes
  $indexes = array();
  $index_options = array(
    '0' => t('-- Choose index --')
  );

  foreach (search_api_index_load_multiple(FALSE) as $index) {
    $indexes[$index->server][$index->machine_name] = $index;
    $server = search_api_server_load($index->server);
    // Add the index to the options if the server is a solr server
    if ($server->entityType() == 'search_api_server') {
      $key = $index->machine_name;
      $value = $index->name;
      $index_options[$key] = $value;
    }
  }
  $form['mussearch_index'] = array(
    '#type' => 'select',
    '#title' => t('Search index'),
    '#options' => $index_options,
    '#default_value' => variable_get('mussearch_index', '0'),
  );


  return system_settings_form($form);
}


/**
 * Create fieldmappings.map and schema.xml snippets from csv
 */
function mussearch_map_utility($form, &$form_state) {
  $form = array();
  $mappings = array();
  if (($handle = fopen(MUSSEARCH_MAPPING_CSV, "r")) !== FALSE) {
    $mappings = fgetcsv($handle);
  }
  $form['fieldmappings'] = array(
    '#type' => 'textarea',
    '#title' => t('fieldmappings.map content'),
    '#default_value' => 'Contains fieldmappings',
  );
  $form['schema'] = array(
    '#type' => 'textarea',
    '#title' => t('schema.xml content'),
    '#default_value' => 'Contains schema.xml snippet',
  );
  return $form;
}