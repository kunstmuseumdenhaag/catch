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

/**
 * Api key management
 *
 */
function mussearch_apikey_management($apikey_id = NULL) {
  $output = array();
  // Get the list of api keys
  $api_key_list = mussearch_load_apikeys();
  // Theme the list
  $header = array(
    t('Key id'),
    t('API key'),
    t('Access rights'),
    t('Bypass blacklist'),
    t('Organisation'),
    t('First name'),
    t('Last name'),
    t('E-mail'),
    t('Phone'),
    t('Filter query'),
    t('Edit'),
  );
  $rows = array();
  foreach ($api_key_list as $apikey_item) {
    $temp_array = (array) $apikey_item;
    $data = array_values($temp_array);
    $data[] = l(t('Edit'), 'admin/config/search/musapikeys/' . $apikey_item->aid);
    $rows[] = array(
      'data' => $data,
    );
  }
  $output['existing_keys'] = array(
    '#theme' => 'table',
    '#header' => $header,
    '#rows' => $rows,
  );
  // Add a link if apikey_id is set, so a new apikey can be made
  if (isset($apikey_id)) {
    $output['create new'] = array(
      '#markup' => l(t('Create new'), 'admin/config/search/musapikeys'),
    );
  }
  // Voeg het formulier voor het aanmaken van een api key toe.
  $form = drupal_get_form('mussearch_add_apikey_form', $apikey_id);
  $output['form'] = $form;
  return $output;
}

/**
 * Form for adding/editing api keys
 * @param $form
 * @param $form_state
 * @param $apikey_id
 */
function mussearch_add_apikey_form($form, &$form_state, $apikey_id = NULL) {
  $form = array();
  $defaults = array();
  if (isset($apikey_id)) {
    // Get the info
    $form['apikey_id'] = array(
      '#type' => 'hidden',
      '#value' => $apikey_id,
    );
    $info = mussearch_load_apikeys($apikey_id);
    if (isset($info[$apikey_id])) {
      $defaults = (array) $info[$apikey_id];
    }
  }
  else {
    $defaults['apikey'] = mussearch_generate_random_apikey();
  }
  $form['apikey'] = array(
    '#type' => 'textfield',
    '#title' => t('Api key'),
    '#default_value' => isset($defaults['apikey']) ? $defaults['apikey'] : '',
    '#disabled' => TRUE,
  );
  $form['access_rights'] = array(
    '#type' => 'textfield',
    '#title' => t('Access rights'),
    '#default_value' => isset($defaults['access_rights']) ? $defaults['access_rights'] : '',
  );
  $form['bypass_blacklist'] = array(
    '#type' => 'checkbox',
    '#title' => t('Bypass parameter blacklist'),
    '#default_value' => isset($defaults['bypass_blacklist']) ? $defaults['bypass_blacklist'] : '',
  );
  $form['organisation'] = array(
    '#type' => 'textfield',
    '#title' => t('Organisation'),
    '#default_value' => isset($defaults['organisation']) ? $defaults['organisation'] : '',
    '#required' => TRUE,
  );
  $form['firstname'] = array(
    '#type' => 'textfield',
    '#title' => t('First name'),
    '#default_value' => isset($defaults['firstname']) ? $defaults['firstname'] : '',
  );
  $form['lastname'] = array(
    '#type' => 'textfield',
    '#title' => t('Last name'),
    '#default_value' => isset($defaults['lastname']) ? $defaults['lastname'] : '',
  );
  $form['email'] = array(
    '#type' => 'textfield',
    '#title' => t('E-mail'),
    '#default_value' => isset($defaults['email']) ? $defaults['email'] : '',
  );
  $form['phone'] = array(
    '#type' => 'textfield',
    '#title' => t('Phone'),
    '#default_value' => isset($defaults['phone']) ? $defaults['phone'] : '',
  );
  $form['filterquery'] = array(
    '#type' => 'textarea',
    '#title' => t('Filterquery'),
    '#default_value' => isset($defaults['filterquery']) ? $defaults['filterquery'] : '',
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit')
  );
  return $form;
}

/**
 * Submit function for apikey edit form
 */
function mussearch_add_apikey_form_submit($form, &$form_state) {
  // Select the musapi database.
  db_set_active('musapi');
  if (isset($form_state['values']['apikey_id'])) {
    $query = db_update('musapi');
    $query->condition('aid', $form_state['values']['apikey_id']);
  }
  else {
    $query = db_insert('musapi');
  }
  $fields_values = array(
    'apikey' => $form_state['values']['apikey'],
  	'access_rights' => $form_state['values']['access_rights'],
  	'bypass_blacklist' => $form_state['values']['bypass_blacklist'],
    'organisation' => $form_state['values']['organisation'],
    'firstname' => $form_state['values']['firstname'],
    'lastname' => $form_state['values']['lastname'],
    'email' => $form_state['values']['email'],
    'phone' => $form_state['values']['phone'],
    'filterquery' => $form_state['values']['filterquery'],
  );
  $query->fields($fields_values);
  $succes = $query->execute();
  if ($succes) {
    drupal_set_message(t('The api key has been generated'));
    $form_state['redirect'] = 'admin/config/search/musapikeys';
  }
  db_set_active();
}

/**
 * Generate a random api key string
 * @return $key
 * 	String: 32 character length string
 */
function mussearch_generate_random_apikey() {
  $time = time();
  $key = md5($time);
  return $key;
}

/**
 * Load an api key
 * @param $apikey_id (optional) if given, only this id is retrieved
 * @return Array $info
 */
function mussearch_load_apikeys($apikey_id = NULL) {
  db_set_active('musapi');
  $query = db_select('musapi', 'm');
  $query->fields('m');
  if (isset($apikey_id)) {
    $query->condition('aid', $apikey_id);
  }
  $info = $query->execute()->fetchAllAssoc('aid');
  db_set_active();
  return $info;
}