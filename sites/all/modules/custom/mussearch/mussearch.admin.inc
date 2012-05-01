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
  $mapping_csv = drupal_get_path('module', 'mussearch') . '/' . MUSSEARCH_MAPPING_CSV;
  if (($handle = fopen($mapping_csv, "r")) !== FALSE) {
    $heading = fgetcsv($handle);
  }
  // Create the strings
  $fieldmappings = '';
  $schema = '';
  while ($mappings = fgetcsv($handle)) {
    $fieldmappings .= _mussearch_create_fieldmapping($mappings);
    $schema .= _mussearch_create_schema($mappings);
  }
  $form['fieldmappings'] = array(
    '#type' => 'textarea',
    '#title' => t('fieldmappings.map content'),
    '#default_value' => $fieldmappings,
  );
  $form['schema'] = array(
    '#type' => 'textarea',
    '#title' => t('schema.xml content'),
    '#default_value' => $schema,
  );
  return $form;
}

/**
 * Create the field mappings
 * @param $mappings as read from the csv
 * @return String $line
 */
function _mussearch_create_fieldmapping($mappings) {
  $drupal_fieldname = $mappings[2];
  $solr_fieldname = $mappings[6];
  $line = sprintf('%s = %s', $drupal_fieldname, $solr_fieldname) . "\n";
  return $line;
}

/**
 * Create the schema definitions
 * @param $mappings as read from the csv
 * @return String $line
 */
function _mussearch_create_schema($mappings) {
  $name = $mappings[6];
  $type = strtolower($mappings[4]);
  $multiValued = $mappings[5] == 0 ? 'false' : 'true';
  $indexed = 'true';
  $stored = 'true';

  $line = sprintf('	<field name="%s" type="%s" multiValued="%s" indexed="%s" stored="%s" required="false" />', $name, $type, $multiValued, $indexed, $stored) . "\n";
  return $line;
}