<?php
abstract class MuSSolrAPIKey {
  protected $apikeyInfo = array();

  /**
   * Use the constructor to load the information from the database.
   */
  abstract function __construct($apikey);

  public function getAccessString() {
    return isset($this->apikeyInfo['access_rights']) ? $this->apikeyInfo['access_rights'] : '';
  }

  public function mayBypassBlacklist() {
    return isset($this->apikeyInfo['bypass_blacklist']) ? $this->apikeyInfo['bypass_blacklist'] : FALSE;
  }

  /**
   * Factory function to get right implementation based on system detection
   * @param String $apikey
   * @return Implementation of MuSSolrAPIKey
   */
  static function getInstance($apikey) {
    // Detect Drupal
    if (function_exists('drupal_get_form')) {
      return new MuSSolrAPIKeyDrupal($apikey);
    }
    // Else Slim is used
    else {
      return new MuSSolrAPIKeySlim($apikey);
    }
  }

}

class MuSSolrAPIKeyDrupal extends MuSSolrAPIKey {
  function __construct($apikey) {
    db_set_active('musapi');
    $query = db_select('musapi', 'm');
    $query->fields('m');
    $query->condition('apikey', $apikey);
    $info = $query->execute()->fetchAssoc();
    if (isset($info['apikey'])) {
      $this->apikeyInfo = $info;
    }
    db_set_active();
  }
}


class MuSSolrAPIKeySlim extends MuSSolrAPIKey {
  function __construct($apikey) {
  }
}