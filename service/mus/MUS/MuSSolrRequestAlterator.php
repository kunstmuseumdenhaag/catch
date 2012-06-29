<?php
class MuSSolrRequestAlterator {
  protected $host;
  protected $port;
  protected $path;
  protected $baseUrl;
  protected $params;
  protected $apikeyObject;

  protected $parsedAdvancedQuery;

  protected $lastCall;
  protected $parameterBlacklist = array('echoParams','q','musallowedlevel','qf','defType',);

  const PARSED_ADVANCED_ORIGINAL  = 'originalMusAdvancedQuery';
  const PARSED_ADVANCED_FULL      = 'parsedMusAdvancedQuery';
  const PARSED_ADVANCED_WHAT      = 'whatQuery';
  const PARSED_ADVANCED_WHO       = 'whoQuery';
  const PARSED_ADVANCED_WHERE     = 'whereQuery';
  const PARSED_ADVANCED_WHEN      = 'whenQuery';
  const PARSED_ADVANCED_HOW       = 'howQuery';
  const PARSED_ADVANCED_REST      = 'restQuery';

  function __construct($host = 'localhost', $port = 8180, $path = '/solr/', $querystring) {
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
    // Parse the query string
    $this->parseQeuryString($querystring);
    // Unset the apikey parameter
    unset($this->params['mus_apikey']);
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
    // Then add boosting
    $this->addBoosting();
    $querystring = $this->getQueryString();
    $fullUrl = $this->baseUrl . '?' . $querystring;
    $response = $this->_doRequest($fullUrl);
    return $response;
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
    // Rewrite mus_aq
    if (isset($this->params['mus_aq'])) {
      $this->rewriteAdvancedQuery();
      $this->params['q'] = $this->parsedAdvancedQuery[self::PARSED_ADVANCED_FULL];
      unset($this->params['mus_aq']);
    }
    // Rewrite mus_sq
    if (isset($this->params['mus_sq'])) {
      $this->params['q'] = $this->params['mus_sq'];
      unset($this->params['mus_sq']);
    }
    // Handle api key
    if (isset($this->apikeyObject)) {
      $this->params['musallowedlevel'] = $this->apikeyObject->getAccessString();
      unset($this->params['mus_apikey']);
    }
    // Rewrite fq
    if (isset($this->params['fq']) && sizeof($this->params['fq']) > 0) {
      foreach ($this->params['fq'] as $key => $fq) {
        $this->params['fq'][$key] = $this->rewriteFq($fq);
      }
    }
  }

  /**
   * Add boosting
   */
  protected function addBoosting($boosttype = 'marijn') {
    $booster = new MusSolrBooster($this->parsedAdvancedQuery, $boosttype);
    $booster->writeParams($this->params);
  }

  /**
   * Rewrite the filter queries.
   * @param $fq
   * @return $rewrittenFq
   */
  protected function rewriteFq($fq) {
    // replace what
    $fq = str_replace('what:', 'what_search:', $fq);
    // replace who
    $fq = str_replace('who:', 'who_search:', $fq);
    // replace where
    $fq = str_replace('where:', 'where_search:', $fq);
    // Replace when
    $fq = str_replace('when:', 'when_search:', $fq);
    // replace how
    $fq = str_replace('how:', 'how_search:', $fq);
    return $fq;
  }

  /**
   * Rewrite the advanced query
   */
  protected function rewriteAdvancedQuery() {
    $keywords = array();
    $this->parsedAdvancedQuery[self::PARSED_ADVANCED_ORIGINAL] = $this->params['mus_aq'];

    // Extract what
    $this->parsedAdvancedQuery[self::PARSED_ADVANCED_WHAT] = $this->extractFieldQuery('what', $this->params['mus_aq']);
    // Extract the keywords from what
    $parsedKeywords = $this->extractKeyWords($this->parsedAdvancedQuery[self::PARSED_ADVANCED_WHAT]);
    if (sizeof($parsedKeywords) > 0) {
      $keywords = array_merge($keywords, $parsedKeywords);
    }

    // Extract who
    $this->parsedAdvancedQuery[self::PARSED_ADVANCED_WHO] = $this->extractFieldQuery('who', $this->params['mus_aq']);
    // Extract the keywords from who
    $parsedKeywords = $this->extractKeyWords($this->parsedAdvancedQuery[self::PARSED_ADVANCED_WHO]);
    if (sizeof($parsedKeywords) > 0) {
      $keywords = array_merge($keywords, $parsedKeywords);
    }

    // Extract where
    $this->parsedAdvancedQuery[self::PARSED_ADVANCED_WHERE] = $this->extractFieldQuery('where', $this->params['mus_aq']);
    // Extract the keywords from where
    $parsedKeywords = $this->extractKeyWords($this->parsedAdvancedQuery[self::PARSED_ADVANCED_WHERE]);
    if (sizeof($parsedKeywords) > 0) {
      $keywords = array_merge($keywords, $parsedKeywords);
    }

    // Extract when
    $this->parsedAdvancedQuery[self::PARSED_ADVANCED_WHEN] = $this->extractFieldQuery('when', $this->params['mus_aq']);
    // Extract the keywords from when
    $parsedKeywords = $this->extractKeyWords($this->parsedAdvancedQuery[self::PARSED_ADVANCED_WHEN]);
    if (sizeof($parsedKeywords) > 0) {
      $keywords = array_merge($keywords, $parsedKeywords);
    }

    // Extract how
    $this->parsedAdvancedQuery[self::PARSED_ADVANCED_HOW] = $this->extractFieldQuery('how', $this->params['mus_aq']);
    // Extract the keywords from how
    $parsedKeywords = $this->extractKeyWords($this->parsedAdvancedQuery[self::PARSED_ADVANCED_HOW]);
    if (sizeof($parsedKeywords) > 0) {
      $keywords = array_merge($keywords, $parsedKeywords);
    }

    // Extract the rest
    // Remove the field queries first
    $regex = '/\w+:\(.*\)/iU';
    $restQuery = trim(preg_replace($regex, '', $this->params['mus_aq']));
    // Remove unnecessary whitespaces
    $this->parsedAdvancedQuery[self::PARSED_ADVANCED_REST] = preg_replace('/\s{2,}/', ' ', $restQuery);
    // Add the keywords to the restQuery
    $this->parsedAdvancedQuery[self::PARSED_ADVANCED_REST] .= ' ' . implode(' ', $keywords);

    // Now create the full query
    $parsedAdvanced = array();
    $queryParts = array(self::PARSED_ADVANCED_HOW,self::PARSED_ADVANCED_WHEN, self::PARSED_ADVANCED_WHAT, self::PARSED_ADVANCED_WHERE, self::PARSED_ADVANCED_WHO, self::PARSED_ADVANCED_REST);
    foreach ($this->parsedAdvancedQuery as $key => $query) {
   // Only add, if the qeury is not empty
      if (in_array($key, $queryParts) && $query != '') {
        switch ($key) {
          case self::PARSED_ADVANCED_HOW:
            $query = 'how_search:(' . $query . ')';
            break;
          case self::PARSED_ADVANCED_WHEN:
            $query = 'when_search:(' . $query . ')';
            break;
          case self::PARSED_ADVANCED_WHAT:
            $query = 'what_search:(' . $query . ')';
            break;
          case self::PARSED_ADVANCED_WHERE:
            $query = 'where_search:(' . $query . ')';
            break;
          case self::PARSED_ADVANCED_WHO:
            $query = 'who_search:(' . $query . ')';
            break;
          case self::PARSED_ADVANCED_REST:
            $query = 'fulltext:(' . $query . ')';
            break;
        }
        $parsedAdvanced[] = $query;
      }
    }
    $this->parsedAdvancedQuery[self::PARSED_ADVANCED_FULL] = implode(' ', $parsedAdvanced);
  }

  /**
   * Extract a field query out of a query
   * @param unknown_type $field
   * @param unknown_type $query
   * return_type
   */
  protected function extractFieldQuery($field, $query) {
    // Construct the regex
    $regex = '/' . $field . ':\((.*)\)/iU';
    preg_match($regex, $query, $matches);
    $fieldQuery = isset($matches[1]) ? $matches[1] : '';
    return $fieldQuery;
  }

  /**
   * Extract the single keywords out of string of keywords. Negated keywords will be ignored.
   * @param $string
   * @return $keywords
   * 	Array containing keywords
   */
  protected function extractKeyWords($string) {
    // Filter out OR and AND and other characters
    $regex = '/(AND|OR)/';
    $string = preg_replace($regex, '', $string);
    // split on spaces
    $keywords = preg_split('/\s/', $string);
    // remove all keywords prepended by minus sign
    foreach ($keywords as $key => &$word) {
      if (preg_match('/-.+/', $word) || $word == '') {
        unset($keywords[$key]);
      }
      // Trim the word
      trim($word);
    }
    return $keywords;
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
          // Try to explode the param
          $exploded = explode('=', $param);
          if (isset($exploded[1])) {
            list($name, $value) = $exploded;
            $params[urldecode($name)][] = urldecode($value);
          }
        }
        // Now set each parameter containing only 1 value to just a string instead of array, except for fq.
        foreach ($params as $name => $param) {
          if (sizeof($param) == 1 && $name != 'fq') {
            $params[$name] = $param[0];
          }
        }
      }
      $this->params = $params;
      // Filter the params
      $this->filterParams();
    }
  }

  /**
   * Filter the params. For instance apply blacklisting
   */
  protected function filterParams() {
    // Apply blacklisting
    if (! $this->apikeyObject->mayBypassBlacklist() ) {
      foreach ($this->params as $name => $param) {
        if (in_array($name, $this->parameterBlacklist)) {
          unset($this->params[$name]);
        }
      }
    }
  }

  /**
   * Add debug information to the response
   * @param $response
   */
  protected function addDebugInfo($response) {
    // Add the parsed advanced query info
    if (isset($this->parsedAdvancedQuery) && sizeof($this->parsedAdvancedQuery) > 0) {
      foreach ($this->parsedAdvancedQuery as $key => $value) {
        $response->addQueryDebugInformation($key, $value);
      }
    }
  }

}