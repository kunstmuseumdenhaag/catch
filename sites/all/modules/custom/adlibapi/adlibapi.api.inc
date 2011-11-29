<?php
/**
 * @file
 * All adlibapi functions that are realy meant as api functions can be found in this file
 */

/**
 * Get available adlib databases.
 * @return Returns an array containing all adlib databases for which settings has been saved
 */
function adlibapi_api_get_available_databases() {
  $databaselist = array();
  $databases = ctools_export_load_object(ADLIBAPI_DATABASE_SCHEMA);
  foreach ($databases as $database) {
    _adlibapi_deserialize_config($database);
    $databaselist[$database->name] = $database;
  }
  return $databaselist;
}

/**
 * Get adlib database settings
 * Get database based on the database preset name
 * @param string $databasename
 */
function adlibapi_api_get_database_settings($databasename) {
  $database = ctools_export_load_object(ADLIBAPI_DATABASE_SCHEMA, 'names', array($databasename));
  _adlibapi_deserialize_config($database[$databasename]);
  // Unset the config, as it contains now useless data
  unset($database[$databasename]->config);
  return $database[$databasename];
}

/**
 * Get metadata
 * Get metadata about the fields.
 * From the adlib api docu:
 *
 * Note that field names can be multilingual.
 * When you use wwwopac.ashx to perform a search,
 * you should use either the field tag (case-sensitive)
 * or the English (language 0) field name.
 *
 * @param $database_config
 * 	object containing databases configuration. url en database are needed
 */
function adlibapi_api_get_metadata($database_config) {
  //  Create adlibconnector
  $conn = adlibapi_api_get_connection($database_config);
  $response = $conn->getMetadata();
  $metadata = $response->getXMLObject();
  return $metadata;
}

/**
 * Get a list of fields.
 * This is actualy the same as metadata.
 * TODO: choose which function to keep.
 * @param object $database_config
 * 	object containing databases configuration. url en database are needed
 * @return array of fields.
 */
function adlibapi_api_get_fieldList($database_config, $mode = 'raw') {
  $conn = adlibapi_api_get_connection($database_config);
  if(isset($conn) && $conn){
    $response = $conn->getFieldList();
    $field_list = $response->getXMLArray();
    switch ($mode) {
      case 'raw':
        return $field_list;
        break;
      case 'simple_array':
        $fields = array();
        foreach ($field_list as $field) {
          $fields[$field['fieldName']] = $field['displayName'];
        }
        return $fields;
      default:
        return FALSE;
        break;
    }
  }
}

/**
 * Get all indexed fields from the database.
 * @param object $database_config
 * 	object containing databases configuration. url en database are needed
 * @return array of fields.
 */
function adlibapi_api_get_indexedfields($database_config) {
  $conn = adlibapi_api_get_connection($database_config);
  $response = $conn->getFieldList();
  $field_list = $response->getXMLArray();
  $fields = array();
  foreach ($field_list as $field) {
    if ($field['isIndexed']) {
      $fields[$field['fieldName']] = $field['displayName'];
    }
  }
  return $fields;
}

/**
 * Get the adlib database version info.
 * @param $database_config
 * 	database configuration from database settings.
 */
function adlibapi_api_get_version($database_config) {
  $conn = new AdLibConnector($database_config->url);
  $response = $conn->getVersion();
  if ($response->getError()) {
    watchdog('adlibapi', $response->getErrorMessage(), NULL, WATCHDOG_ERROR);
  }
  $version_info = $response->getXMLObject();
  $raw = $response->getRaw();
  $version = array();
  // Check if there is a hit
  if (isset($version_info->diagnostic->hits) && (integer) $version_info->diagnostic->hits > 0) {
    $version['rawtext'] = (string) $version_info->recordList->record->version;
    // Parse the string
    $elements = explode(', ', $version['rawtext']);
    foreach ($elements as $element) {
      $parts = explode('=', $element);
      if (isset($parts[1])) {
        $version[$parts[0]] = $parts[1];
      }
      else {
        $version[$parts[0]] = $parts[0];
      }
    }
  }
  return $version;
}

/**
 * Get an adlib format date from several dateformats.
 *  TODO: add more date formats.
 * @param $date
 *   A key value array, containing one value:
 *  'timestamp' => unix timestamp
 *  @return adlid date formatted date
 */
function adlibapi_api_get_adlib_date($date) {
  if (isset($date['timestamp'])) {
    $adlib_date = format_date($date['timestamp'], 'custom', 'Y-m-d');
    return $adlib_date;
  }
  if (isset($date['custom'])) {
    $adlib_date = format_date(strtotime($date['custom']), 'custom', 'Y-m-d');
    return $adlib_date;
  }
  return FALSE;
}

/**
 * Get all databaserecords which are altered after a specific date.
 * @param $database_config
 * 	Database config from settings.
 * @param $date
 * 	Date formatted for adlib
 * @param $limit
 * 	Number of results to return
 * @return
 * 	Response of the call.
 */
function adlibapi_api_get_alteredrecords_by_date($database_config, $date) {
  $conn = adlibapi_api_get_connection($database_config);
  $response = $conn->getAlteredRecordsByDate($date);
  return $response;
}

/**
 * Get a base query to get databaserecords which are altered after a specific date.
 * @param String $date
 * 	 Date formatted for adlib
 */
function adlibapi_api_getquery_altered_records_by_date($date) {
  $query = new AdlibSearchQuery();
  $query->addParameter('modification', $date, ' > ');
  $query->addParameter('sort', 'edit.date', ' ', '');
  return $query;
}

/**
 * Generic function to built different types of queries.
 * @param string $type	the type of query to build, possible values:
 * 		- 'by_date'		create a query to get items by date comparison
 * @param array $queryoptions aasiociatvie array with the optins which must be added, possible keys
 * 		- 'date' 		a valid date
 * 		- 'date_type'	the date type (either modification or creation)
 * 		- 'sortfield' 	one of the adlib database fields
 */
function adlibapi_api_build_query($type, $queryoptions) {
  $query = new AdlibSearchQuery();
  switch ($type) {
    case 'by_date':
      if (isset($queryoptions['date'])) {
        // TODO: must $queryoptions['date'] be passed to 'adlibapi_api_get_adlib_date()'?
        $date = $queryoptions['date'];
        $date_type = $queryoptions['date_type'];
        $query->addParameter($date_type, $date, '>');
      }
      if (isset($queryoptions['sortfield'])) {
        $query->addParameter('sort', $queryoptions['sortfield']);
      }
      break;
  }
  return $query;
}

/**
 * Get an image query object
 * @param string $imagename
 * 	filename of the image
 * @return
 * 	AdlibImageQuery object.
 */
function adlibapi_api_get_image_query($imagename) {
  $query = new AdlibImageQuery($imagename);
  return $query;
}

/**
 * Get an adlibconnector from database configuration
 * @param $database_config
 * 	Database configuration from settings.
 * @return A new AdLibConnector.
 */
function adlibapi_api_get_connection($database_config) {
  if(isset($database_config)){
    if (!isset($database_config->database)) {
      drupal_set_message(t('You must select a database in the settings of the database first!'), 'error');
      return FALSE;
    }
    else {
      $conn = new AdLibConnector($database_config->url, $database_config->database, $database_config->imageserver);
      return $conn;
    }

  }
}
