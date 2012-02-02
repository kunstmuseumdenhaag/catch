<?php
class MuSSolrRequestAlterator {
  protected $host;
  protected $port;
  protected $path;
  protected $baseUrl;
  protected $params;

  protected $lastCall;

  function __construct($host = 'localhost', $port = 8180, $path = '/solr/', $querystring) {
    $this->host = $host;
    $this->port = $port;
    $this->path = $path;
    // Create full url
    $this->createBaseUrl();
    // Parse the query string
    $this->parseQeuryString($querystring);
  }

  /**
   * Create the base url
   */
  protected function createBaseUrl() {
    $this->baseUrl = 'http://' . $this->host . ':' . $this->port . $this->path . '/select';
  }

  /**
   * Perform a solr Request
   * @return MuSSolrResponse
   */
  public function doSolrRequest() {
    // First rewrite all params for MuS
    $this->rewriteMuSParams();
    $querystring = $this->getQueryString();
    $fullUrl = $this->baseUrl . '?' . $querystring;
    return $this->_doRequest($fullUrl);
  }

  /**
   * Add a simple parameter
   * @param $name
   * @param $value
   * @throws Exception
   */
  public function addParam($name, $value) {
    // Only add simple parameters for now, and don't overwrite
    if (!isset($this->params[$name])) {
      $this->params[$name] = $value;
    } else {
      throw new Exception('Param is already set!');
    }
  }

  /**
   * Generate a query string from the params
   * @return $querystring
   */
  protected function getQueryString() {
    $parts = array();
    foreach ($this->params as $name => $values) {
      if (! is_array($values)) {
        $name = urlencode($name);
        $parts[] = $name . '=' . urlencode($values);
      }
      else {
        foreach ($values as $value) {
          $parts[] = $name . '=' . urlencode($value);
        }
      }
    }
    $querystring = implode('&', $parts);
    return $querystring;
  }

  /**
   * Do a rewrite to normal solr parameters.
   */
  protected function rewriteMuSParams() {
    // Rewrite mus_q
    if (isset($this->params['mus_q'])) {
      $this->params['q'] = $this->params['mus_q'];
      unset($this->params['mus_q']);
    }
  }

  /**
   * Do a raw get request usering curl
   * @param string $fullUrl
   * @return MuSSolrResponse
   */
  protected function _doRequest($fullUrl) {
        // create a context
    $context_options = array(
      'http' => array(
        'method' => 'GET',
        'ignore_errors' => '0',
        'header' => array('Accept-language: en-gb,en;q=0.5')
      )
    );

    $context = stream_context_create($context_options);

    $this->lastCall = $fullUrl;

    // TODO: make nicer
    $ch = curl_init();
    curl_setopt($ch, CURLOPT_URL, $fullUrl);
    curl_setopt($ch, CURLOPT_HEADER, true);
    curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
    curl_setopt($ch, CURLOPT_USERAGENT, 'MuS search proxy');
    $rawdata = curl_exec($ch);
    $httpInfo = curl_getinfo($ch);

    // create PubServerResponse object, any request errors are handled in the constructor
    $response = new MuSSolrResponse($rawdata, $httpInfo);
    return $response;

  }

  /**
   * Parse a query string to get the normal solr behavior instead of having to put [] for items having the same name.
   * @param $querystring
   */
  protected function parseQeuryString($querystring) {
    if ($querystring != '') {
      $query = explode('&', $querystring);
      $params = array();

      if (sizeof($query) > 0) {
        foreach ($query as $param) {
          list($name, $value) = explode('=', $param);
          $params[urldecode($name)][] = urldecode($value);
        }
        // Now set each parameter containing only 1 value to just a string instead of array
        foreach ($params as $name => $param) {
          if (sizeof($param) == 1) {
            $params[$name] = $param[0];
          }
        }
      }
      $this->params = $params;
    }
  }


}