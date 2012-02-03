<?php
/**
 * @file
 * Parser for the AdlibModule
 */


class AdlibParser extends FeedsParser {
  /*
   * Overwrite the following functions:
   * 1) getMappingSources
   * 2) sourceForm
   * 3) configForm
   * 4) parse
   *
   */
  private $raw;
  private $fields;

  private $field_regex = "[a-zA-Z0-9\._]+\s*";
  private $separator_regex="[a-zA-Z0-9\s,;\:\._\<\>\/]+\s*";

  /**
   * Implementation of FeedsParser::parse().
   */

  public function parse(FeedsSource $source, FeedsFetcherResult $fetcher_result) {
    $this->source_config = $source->getConfigFor($this);

    if (empty($this->source_config)) {
      $this->source_config = $this->config;
    }

    // Set link so we can set the result link attribute.
    $fetcher_config = $source->importer->fetcher->config;
    $this->fields = $fetcher_config['fields'];

    $mappings = $source->importer->processor->config['mappings'];
    $this->mappings = $this->filterMappings($mappings);
    $this->raw = trim($fetcher_result->getRaw());

    // Parse the adlib response to an array of adlib documents.
    $adlib_items = $this->_parseAdlibResponse();

    // Perform the so called adlib query in which tokes are replaced by values.
    $items = $this->_performAdlibQuery($adlib_items);
    // In Drupal 6 the items are added to the batch: $batch->items = $items;
    // in Drupal 7 we return a FeedsParserResult object with the items
    $result = new FeedsParserResult();
    $result->items = $items;
    return $result;
  }

  /**
   * Override parent::getMappingSources().
   */
  public function getMappingSources() {
    $mappings = $this->filterMappings(feeds_importer($this->id)->processor->config['mappings']);
    $next = 0;
    if (!empty($mappings)) {
      $last_mapping = end(array_keys($mappings));
      $next = explode(':', $last_mapping);
      $next = $next[1] + 1;
    }
    return array(
      'adlibparser:' . $next => array(
        'name' => t('Adlib Expression'),
        'description' => t('Allows you to configure an Adlib expression that will populate this field.'),
    ),
    ) + parent::getMappingSources();
  }

  /**
   * Filters mappings, returning the ones that belong to us.
   * @param array $mappings with all mappings
   * @return array with mappings that start with 'adlibparser:'
   */
  private function filterMappings($mappings) {
    $our_mappings = array();
    foreach ($mappings as $mapping) {
      if (strpos($mapping['source'], 'adlibparser:') === 0) {
        $our_mappings[$mapping['source']] = $mapping['target'];
      }
    }
    return $our_mappings;
  }

  /**
   * Source form
   */
  public function sourceForm($source_config) {
    $form = array();
    $importer = feeds_importer($this->id);
    $mappings_ = $importer->processor->config['mappings'];

    if (empty($source_config)) {
      $source_config = $this->config;
    }

    $uniques = $mappings = array();
    foreach ($mappings_ as $mapping) {
      if (strpos($mapping['source'], 'adlibparser:') === 0) {
        $mappings[$mapping['source']] = $mapping['target'];
        if ($mapping['unique']) {
          $uniques[] = $mapping['target'];
        }
      }
    }
    $form['adlib'] = array(
      '#type' => 'fieldset',
      '#tree' => TRUE,
      '#title' => t('Adlib Parser Settings'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );
    if (empty($mappings)) {
      $form['adlib']['error_message']['#value'] = 'AdlibParser: No mappings are defined yet. Please create at least one mapping at the processor.<br>';
      form_set_error('adlib', 'AdlibParser: No mappings are defined.<br>');
      return $form;
    }
    if (!empty($uniques)) {
      $items = array(
      format_plural(count($uniques),
      t('Field <strong>!column</strong> is mandatory and considered unique: only one item per !column value will be created.',
      array('!column' => implode(', ', $uniques))),
      t('Fields <strong>!columns</strong> are mandatory and values in these columns are considered unique: only one entry per value in one of these columns will be created.',
      array('!columns' => implode(', ', $uniques)))),
      );
      $form['adlib']['sources']['help']['#markup'] = '<div class="help">' . theme('item_list', array('items' => $items)) . '</div>';
    }
    foreach ($mappings as $source => $target) {
      $field_info = field_info_field($target);
      // If the type of the field starts with text_ then display a textarea, otherwise display a field.
      $input_type = (isset($field_info['type']) && strpos($field_info['type'], 'text_') !== FALSE) ? 'textarea' : 'textfield';
      $form['adlib']['sources'][$source] = array(
        '#type' => $input_type,
        '#title' => $target,
        '#description' => t('The Adlib query to run.'),
        '#default_value' => isset($source_config['sources'][$source]) ? $source_config['sources'][$source] : '',
        '#maxlength' => 1024,
        '#size' => 80,
      );
    }
    /*
     * Get the fields from the adlib fetcher and transform them in markup.
     * This way the user is onformed about the tokens which can be used when parsing.
     */
    $fields = $importer->fetcher->config['fields'];
    $tokens = array();
    foreach ($fields as $field) {
      $tokens[] = '[' . $field . ']';
    }
    // Add the "raw_xml" token. This field is not retrieved from Adlib but added in $this->_parseAdlibResponse() 
    $tokens[] = '[raw_xml]';
    $list_vars = array(
      'items' => $tokens,
      'type' => 'ul',
      'title' => t('The following tokens can be used to describe the field.'),
    );
    $helpoutput = '<h3>' . t('Token usage') . '</h3>';
    $helpoutput .= '<p>' . t('If tokens for fields are used in combination or in single valued cck-fields, a seperator string can be given in the following way: [token:&lt;seperator&gt;].') . '</p>';
    $helpoutput .= '<p>' . t('For example: the field \'tags\' has multiple values, which need to be mapped to the body field of a node. In the end the tags should be displayed as an unordered list. The way to do this is as follows:') . '<br />';
    $helpoutput .= t('&lt;ul&gt;&lt;li&gt; [tags:&lt;/li&gt;&lt;li&gt;] &lt;/li&gt;&lt;/ul&gt;') . '</p>';

    $form['adlib']['fields'] = array(
      '#type' => 'markup',
      '#markup' => '<div class="help">' . $helpoutput . theme('item_list', $list_vars) . '</div>'
    );
    return $form;
  }

  /**
   * Override parent::sourceFormValidate().
   * TODO: this is misuse of the validate function. Sources must be a top level array entry.
   */
  public function sourceFormValidate(&$values) {
    $dummy="dummy";
    if (isset($values['adlib'])) {
      $values = $values['adlib'];

      // get mappings
      $mappings = $this->filterMappings(feeds_importer($this->id)->processor->config['mappings']);
      // get info about all fields
      $all_fields = field_info_fields();

      // basic validation for each field
      foreach ($values['sources'] as $field => $value) {
        // 1) If target field is a multiple CCK field, do not allow separators in field, e.g. do not allow '[tag: sep]'
        $cck_multiple = FALSE;
        $field_name = $mappings[$field];
        // D6 version: $field_info = content_fields($field_name);
        unset($field_info);
        if (isset($all_fields[$field_name])) {
          $field_info = $all_fields[$field_name];
        }
        if (isset($field_info) && $field_info['cardinality'] == -1 ) {
          $cck_multiple = TRUE;
        }
        if ($cck_multiple) {
           $adlib_value_regex = '/\[' . $this->field_regex . ':' . $this->separator_regex . '\]/';
           if (preg_match($adlib_value_regex, $value)) {
             form_set_error($field, t('The field %field can not have a separator in it is definition (<em>[&lt;field&gt;: &lt;separator&gt;]</em>), because it\'s a multiple CCK-field', array('%field' => $field_name)));
           }
        }
        // 2) Check for each field if the expression is valid
        $token_regexp = '/\[' . $this->field_regex . ':' . $this->separator_regex . '\]|\[' . $this->field_regex . '\]/';
        if (preg_match_all($token_regexp, $value, $tokens)==0 && $value != '') {
          form_set_error($field, t('The expression in field %field is not valid, syntax is <em>[&lt;field&gt;]</em> or <em>[&lt;field&gt;: &lt;separator&gt;]</em>', array('%field' => $field_name)));
        }
        // 3) Do not accept empty fields
        if ($value == '') {
          form_set_error($field, t('The expression in field %field should not be empty', array('%field' => $field_name)));
        }
      }
    }
  }

  /**
   * Override parent::configForm().
   */
  public function configForm(&$form_state) {
    $form = $this->sourceForm($this->config);
    $form['adlib']['context']['#required'] = FALSE;
    $form['adlib']['#collapsed'] = FALSE;
    return $form;
  }

  public function configFormValidate(&$values) {
    $this->sourceFormValidate($values);
  }

  /**
   * Define defaults.
   */

  public function sourceDefaults() {
    return array();
  }

  /**
   * Define defaults.
   */
  public function configDefaults() {
    return array(
      'sources' => array(),
      'rawXML' => array(),
    );
  }

  /**
   * Parse the XML response from the Adlib server
   * in an array
   * @return associative array with 1 row per Adlib object
   */
  private function _parseAdlibResponse() {
    $xml = new SimpleXMLElement($this->raw);
    $results = $xml->xpath('//record');
    $docs = array();
    foreach ($results as $result) {
      $doc = array();
      foreach ($this->fields as $field) {
        // check if we have multiple values
        $children = $result->xpath($field);
        // $children = $result->{$field}->children();
        if (count($children)>1) {
          $field_array = array();
          // get all values
          foreach ($children as $value) {
            $field_array[]=(string) $value[0];
          }
          // and put the resulting array in $doc[$field]
          $doc[$field]=$field_array;
        }
        else {
          // single value
          $value = $result->{$field};
          // put string in $doc[$field]
          $doc[$field] = (string) $value[0];
        }
      }
      // Put the raw xml value of one result in the document
      $doc['raw_xml'] = $result->asXML();
      $docs[] = $doc;
    }
    return $docs;
  }

  /**
   * Create array with import items filled from the array with Adlib items
   * @param $adlib_items associative array with 1 row per Adlib object
   * @return array with import-items
   */
  private function _performAdlibQuery($adlib_items) {
    $items = array();
    foreach ($adlib_items as $adlib_item) {
      $items[] = $this->_parseAdlibSingleItem($adlib_item);
    }
    return $items;
  }

  /**
   * Create an associative array for one import item
   * @param $adlib_item array with item parsed from the XML the adlib server returned
   * @return array with 1 import item
   */
  private function _parseAdlibSingleItem($adlib_item) {
    $sources = $this->source_config['sources'];
    $item = array();
    // get mappings
    $mappings = $this->filterMappings(feeds_importer($this->id)->processor->config['mappings']);
    // get info about fields
    $all_fields = field_info_fields();
    // $source is the string with the replacement values, e.g. '<h2>[title]</h2>'
    foreach ($this->source_config['sources'] as $source_key => $source) {
      /*
       * Analyze the source. There are two possibilities:
       * 1) There is only one token
       * 2) There are more than one tokens
       */
      //$token_regexp = '/(\[[a-zA-Z\._]+:+[a-zA-Z\._\<\>\/]+\]|\[[a-zA-Z\._]+\])/';
      $token_regexp = '/\[' . $this->field_regex . ':' . $this->separator_regex . '\]|\[' . $this->field_regex . '\]/';
      $token_count = preg_match_all($token_regexp, $source, $tokens);
      $token_multiple = FALSE;
      if ($token_count > 1) {
        $token_multiple = TRUE;
      }
      /*
       * Analyze the target field. There are two possibilities
       * 1) It's a single field
       * 2) It's multiple field
       */
      // get info about cck_field
      $cck_multiple = FALSE;
      // D6 version $field_info = content_fields($this->mappings[$source_key]);

      $field_name = $mappings[$source_key];
      unset($field_info);
        if (isset($all_fields[$field_name])) {
          $field_info = $all_fields[$field_name];
        }
      if (isset($field_info) && $field_info['cardinality'] == -1 ) {
        $cck_multiple = TRUE;
      }
      // e.g. $value = '[creator] | [material]'
      $value = $source;
      foreach ($adlib_item as $adlib_key => $adlib_value) {
        /*
         * After analyzing, there are two possibilities:
         * 1) There is a multivalued cck field, and only one token which might be multivalued: multi
         * 2) The rest: single.
         *
         * In the first case we generate an array which can be mapped to the multivalued cck field
         * In the second case, we explode the multivalued tokens in one string and put this in place of the token.
         */
        //$adlib_value_regex = '/(\[' . $adlib_key . ':+[a-zA-Z\._\<\>\/]+\]|\[' . $adlib_key . '\])/';
        $adlib_value_regex = '/\[' . $adlib_key . ':' . $this->separator_regex . '\]|\[' . $adlib_key . '\]/';
        if ($cck_multiple && ! $token_multiple) {
          $dummy = 'dummy';
          if (preg_match($adlib_value_regex, $value) > 0) {
            if (is_array($adlib_value)) {
              $value_array = array();
              foreach ($adlib_value as $val) {
                $value_array[] = preg_replace($adlib_value_regex, $val, $value);
              }
              $value = $value_array;
            }
            else {
              $value = preg_replace($adlib_value_regex, $adlib_value, $value);
            }
            // Leave the foreach for $adlib_item
            break;
          }
        }
        // All values must be put in single field.
        else {
          // If the adlib_value is an array, get the glue string
          if (is_array($adlib_value)) {
            $adlib_value_regex = '/\[(' . $adlib_key . '):(' . $this->separator_regex . ')\]/';
            $count = preg_match($adlib_value_regex, $source, $parts);
            // if count > 0 we have a field with separator, otherwise we do not have a separator
            if ($count==0) {
               $adlib_value_regex = '/\[' . $adlib_key . '\]/';
            }
            $glue = (isset($parts[2])) ? $parts[2] : ' ';
            $glued_string = implode($glue, $adlib_value);
            $value = preg_replace($adlib_value_regex, $glued_string, $value);
          }
          else {
            $value = preg_replace($adlib_value_regex, $adlib_value, $value);
          }
        }
      }
       if (is_array($value)) {
       foreach ($value as $key => $val) {
         // if we have any more [<tags>] remove them here
         $value[$key] = preg_replace('/\[.*?\]/', '' , $val);
         // remove redundant spaces
         $value[$key] = trim($value[$key]);
       }
     }
     else {
     // if we have any more [<tags>] remove them here
       $value = preg_replace('/\[.*?\]/', '' , $value);
       // remove redundant spaces
       $value = trim($value);
     }
 
      $item[$source_key] = $value;
    }
    return $item;
  }
}
