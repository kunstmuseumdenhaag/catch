<?php
/**
 * @file
 * Fetcher and batch object declaration for the AdlibFetcher
 */

/**
 * Definition of the import batch object created on the fetching stage by
 * AdlibFetcher.
 */

/* LN20110222: FeedsBatch classes are replaced by FeedsResult classes.
 * See the CHANGELOG.TXT in the feeds module FeedsResult
 * Old:  class FeedsAdlibBatch extends FeedsImportBatch {
 */
class FeedsAdlibBatch extends FeedsFetcherResult {
  // Name of the adlib database setting.
  protected $adlibdb;
  protected $db_settings;
  protected $fetcher;
  /**
   * Constructor.
   */
  public function __construct($fetcher, $feed_nid = 0) {
    $this->fetcher = $fetcher;
    $this->adlibdb = $fetcher->config['database'];
    $this->db_settings = adlibapi_api_get_database_settings($fetcher->config['database']);
    // LN20110222 constructor of FeedsResult class has 1 argument
    parent::__construct($feed_nid);
  }

  /**
   * Implementation of FeedsImportBatch::getRaw();
   */
  public function getRaw() {
    $date = adlibapi_api_get_adlib_date(array('custom' => $this->fetcher->config['changed']));
    // If no date is set, for whatever reason, set the date to 1970.
    if (! $date) {
      $date = adlibapi_api_get_adlib_date(array('timestamp' => 0));
    }
    // Get a basic date query
    $queryoptions = array(
      'date' => $date,
      'date_type' => $this->fetcher->config['datesort'],
    );
    $query = adlibapi_api_build_query('by_date', $queryoptions);
    // Add custom query if applicable
    if ($this->fetcher->config['use_custom_query'] && $this->fetcher->config['custom_query'] != '') {
      $query->addCustomQuery($this->fetcher->config['custom_query']);
    }
    // Set the limit and the fields.
    $query->setLimit($this->fetcher->config['items']);
    // Set the startfrom
    $query->startFrom($this->fetcher->config['batch_startfrom']);
    $query->addFields($this->fetcher->config['fields']);
    // Set xmltype to the value set in the config form
    $getType = $this->fetcher->config['xmltype'];
    $query->setXMLtype($getType);
    // $query->setXMLtype('grouped');
    $conn = adlibapi_api_get_connection($this->db_settings);
    $response = $conn->performQuery($query);
    // Set empty xml, so we always have something to present to the parser.
    $xml = "<adlibXML></adlibXML>";

    // check for errors
    if (!$response->getError()) {
      // only return the XML of the recordlist!
      $xmlObject = $response->getXMLObject();
      $items = $xmlObject->recordList;
      $xml = $items->asXML();
      /*
       * Update the fetcher
       */
      $this->updateFetcher($xmlObject);
    }
    else {
      // Write the error to the watchdog and give an error
      drupal_set_message($response->getErrorMessage(), 'error');
      watchdog(ADLIBAPI_WATCHDOG_ERROR, 'Adlib api error: %error', array('%error' => $response->getErrorMessage()), WATCHDOG_ERROR);
    }
    return $xml;
  }

  /**
   * Update fetcher settings based on the response of adlib
   * @param XMLObject $xmlObject
   *   parsed xml response of the adlib request.
   */
  private function updateFetcher($xmlObject) {
    /*
     * Update hits and startfrom in the settings
     */
    $hits = (integer) $xmlObject->diagnostic->hits;
    $firstitem = (integer) $xmlObject->diagnostic->first_item;
    $limit = (integer) $xmlObject->diagnostic->limit;
    $start_from = $firstitem + $limit;
    $status = 1;
    $changed = $this->fetcher->config['changed'];
    if ($start_from > $hits) {
      $hits = 0;
      $start_from = 0;
      $status = 2;
      $changed = format_date(REQUEST_TIME, 'custom', $this->fetcher->getDateFormat());
    }
    $fetch_conf = array(
      'batch_results' => $hits,
      'batch_startfrom' => $start_from,
      'status' => $status,
      'changed' => $changed,
    );

    $this->fetcher->addConfig($fetch_conf);
    $this->fetcher->save();
  }
}


class AdlibFetcher extends FeedsFetcher {
  private $format = 'Y-m-d H:i';
  /**
   * Implementation of FeedsFetcher::fetch().
   */
  public function fetch(FeedsSource $source) {
    return new FeedsAdlibBatch($this, $source->feed_nid);
  }


  /**
   * Override parent::configDefaults().
   */
  public function configDefaults() {
    /*
     * Datesort can only have two options: creation and modification.
     *
     * In this fetcher, there are some fields that are needed to administer the progress of a batch
     * They are stored as settings, although they cannot be altered by the user.
     * The fields are:
     * - batch_results: the number of results of the query to adlib
     * - batch_startfrom: result number to start from
     * - status: 0: not yet started
     * 			 1: busy
     * 			 2: finished
     */
    return array(
      'database' => 'unknown',
      'use_custom_query' => 0,
      'custom_query' => '',
      'changed' => format_date(100, 'custom', $this->format),
      'items' => 100,
      'fields' => array('no' => 0),
      'datesort' => 'creation',
      'batch_results' => 0,
      'batch_startfrom' => 0,
      'status' => 0,
      'xmltype' => 'unstructured',
    );
  }

  /**
   * Override parent::configForm().
   */
  public function configForm(&$form_state) {
    $form = array();
    // Get the available databases
    $dbs = adlibapi_api_get_available_databases();
    $db_options = array('unknown' => t('-- Select database --'));
    foreach ($dbs as $db) {
      $db_options[$db->name] = $db->description;
    }
    $adlib_settings_url = l('admin/settings/adlibapi', 'admin/settings/adlibapi');
    $form['database'] = array(
      '#type' => 'select',
      '#title' => t('Adlib database'),
      '#description' => t('Adlib database as configured in: '). $adlib_settings_url,
      '#options' => $db_options,
      '#default_value' => $this->config['database'],
    );
    /*
     * Add field select checkboxes and date order field if database is selected.
     */
    if ($this->config['database'] != 'unknow') {
      $database_config = adlibapi_api_get_database_settings($this->config['database']);
      // Get the fields and create options
      $fields = adlibapi_api_get_fieldList($database_config, 'simple_array');
      $index_fields = array(
        'creation' => t('Creation date'),
        'modification' => t('Modification date'),
      );
      // checkbox to enable custom query
      $form['use_custom_query'] = array(
        '#type' => 'checkbox',
        '#title' => t('Use custom query'),
        '#default_value' => $this->config['use_custom_query'],
        '#disabled' => (! $this->config['status'] == '1') ? FALSE : TRUE,
      );
      $form['custom_query'] = array(
        '#type' => 'textarea',
        '#title' => t('Custom adlib query'),
        '#description' => t('Check the adlib api home page for details about creating a query.'),
        '#default_value' => $this->config['custom_query'],
      );
      // Create the checkboxes
      $form['fields'] = array(
        '#type' => 'fieldset',
        '#title' => t('Select fields for retrieval'),
        '#collapsible' => TRUE,
        '#collapsed' => TRUE,
      );
      $form['fields']['fields'] = array(
        '#type' => 'checkboxes',
        '#title' => t('Fields to retrieve'),
        '#description' => t('Select the fields to retrieve. Retrieved fields are available in parser.'),
        '#options' => $fields,
        '#default_value' => $this->config['fields'],
      );
      $form['datesort'] = array(
        '#type' => 'select',
        '#title' => t('Select date field for sorting'),
        '#description' => t('The adlib database should have an indexed field on which the edit date can be sorted.'),
        '#options' => $index_fields,
        '#default_value' => $this->config['datesort'],
      );
      $xmltype_options = array(
        'grouped' => t('grouped'),
        'unstructured' => t('unstructured'),
      );
      $form['xmltype'] = array(
        '#type' => 'radios',
        '#title' => t('Select XML type to return'),
        '#description' => t('XML type can either be "grouped" or "unstructured". If the parser is set to the adlib parser, "unstructered" is required.'),
        '#options' => $xmltype_options,
        '#default_value' => isset($this->config['xmltype']) ? $this->config['xmltype'] : 'unstructered',
      );
    }
    $form['items'] = array(
      '#type' => 'textfield',
      '#title' => t('Maximum number of items to retrieve each run.'),
      '#default_value' => $this->config['items'],
    );
    /*
     * Create the information text
     */
    // Only show status if the fetcher is busy
    if ($this->config['status'] == '1') {
      $form['info'] = array(
      	'#markup' => theme('adlibfeeds_fetcher_info', array('vars' => $this->config)),
      );
    }

    $form['restart_fetcher'] = array(
       '#type' => 'checkbox',
       '#title' => t('Restart fetcher from first object in Adlib database.'),
       '#return_value' => 'do_reset',
    );
    // TODO: Alter description.
    // TODO: date_popup en/of date_select toevoegen aan dependencies in module
    $form['changed'] = array(
      '#type' => 'date_popup',
      '#title' => t('Last updated date'),
      '#description' => t('Last updated date.
      					   All adlib items modified after this date will be retrieved.
      					   If no adlib item is retrieved yet, set it to a date far in the past (for instance 1970).
      					   After a first sync is done, this date is set to the date on which the sync was started.'),
      '#disabled' => (! $this->config['status'] == '1' || ! isset($this->config['changed'])) ? FALSE : TRUE,
      '#default_value' => $this->config['changed'],
      '#date_format' => $this->format,
    );
    return $form;
  }

  public function configFormValidate(&$values) {
    if (! is_numeric($values['items'])) {
      form_set_error('items', t('Only integers are allowed!'));
    }
    // If a custom query is set, validate by performing an adlib query and looking if no error is returned.
    if ($values['use_custom_query']) {
      $date = adlibapi_api_get_adlib_date(array('custom' => $values['changed']));
      // If no date is set, for whatever reason, set the date to 1970.
      if (! $date) {
        $date = adlibapi_api_get_adlib_date(array('timestamp' => 0));
      }
      // Get a basic date query
      $queryoptions = array(
        'date' => $date,
        'date_type' => $values['datesort'],
      );
      $query = adlibapi_api_build_query('by_date', $queryoptions);

      $getType = $values['xmltype'];
      $query->setXMLtype($getType);
      $query->addCustomQuery($values['custom_query']);
      $db_settings = adlibapi_api_get_database_settings($values['database']);
      $conn = adlibapi_api_get_connection($db_settings);
      $response = $conn->performQuery($query);
      // check for errors
      if ($response->getError()) {
        form_set_error('custom_query', t('The adlib server didn\'t accept the custom query. The server responded with the following error: %error.', array('%error' => $response->getErrorMessage())));
      }
    }

  }

  public function configFormSubmit(&$values) {
    // check for reset
    $check_reset = $values['restart_fetcher'];
    if ($check_reset === 'do_reset') {
      $this->config['batch_startfrom'] = 0;
      $this->config['status'] = 0;
    }
    // For some strange reason, a disabled date field is uninitialized when set to disabled. Therefor set it to the value that is already in the fetcher settings.
    if (! isset($values['changed'])) {
      $values['changed'] = $this->config['changed'];
    }
    if (! isset($values['custom_query'])) {
      $values['custom_query'] = $this->config['custom_query'];
    }
    // Adjust the field settings and pass
    $newfields = array();
    foreach ($values['fields'] as $key => $field) {
      if ($field != '0') {
        $newfields[] = $key;
      }
    }
    $values['fields'] = $newfields;
    parent::configFormSubmit($values);
    // Set busy to zero if reset is requested.

  }

  public function getDateFormat() {
    return $this->format;
  }
}
