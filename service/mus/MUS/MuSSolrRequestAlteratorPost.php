<?php
/**
 * Created by PhpStorm.
 * User: jur
 * Date: 03/07/15
 * Time: 15:58
 */

class MuSSolrRequestAlteratorPost extends MuSSolrRequestAlterator {
  function __construct($host = 'localhost', $port = 8180, $path = '/solr/', $post_data) {
    $this->host = $host;
    $this->port = $port;
    $this->path = $path;
    // Create full url
    $this->createBaseUrl();
    // Initiate apikeyObject
    if (isset($_GET['mus_apikey'])) {
      $this->apikeyObject = MuSSolrAPIKey::getInstance($_GET['mus_apikey']);
    }
    else {
      // Create an apikey object using dummy apikey. In this case no rights are given.
      $this->apikeyObject = MuSSolrAPIKey::getInstance('dummy');
    }
    // Set post data
    $this->params = $post_data;
    $this->filterParams();

    // Unset the apikey parameter
    unset($this->params['mus_apikey']);
  }

  public function doSolrRequest() {
    // @Todo: is left as en exercise for the reader.
  }


}