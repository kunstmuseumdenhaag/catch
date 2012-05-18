<?php
/**
 * @file
 * MuSSolrResponse class for the response of solr. Errors will be handled in this class.
 */
class MuSSolrResponse {
/**
   * Boolean that indicates if an error occured
   */
  protected $_error;

  /**
   * String for errormessage
   */
  protected $_errorString;

  /**
   * HTTP response
   */
  protected $_headers;

    /**
   * The raw response
   */
  protected $_raw;

  /**
   * The parsed xml.
   */
  protected $_xml;

  // methods
  /**
  * Contructor
  * @param string $rawResponse the raw response we get
  * @param string $httpHeaders the HTTP headers created when the request was made
  * TODO: rewrite for curl info
  */
  public function __construct($responseWithHeader, $httpInfo = array()){
    $this->_error=false;
    $this->_headers['Status-Code'] = -1;
    $this->_headers['Status-Message'] = 'No request';
    // if $responseWithHeader is 'false' the request failed completely
    if (!$responseWithHeader) {
      $this->_error=true;
    }
    else {
      $this->parse($responseWithHeader);
//      if ($httpInfo['content_type'] == 'application/xml;charset=UTF-8') {
//        $this->_xml = simplexml_load_string($this->getRaw());
//      }
    }

    if (is_array($httpInfo) && count($httpInfo) > 0) {

      // if we received any other status then 200 OK we have an error and we assume no valid XML was returned
      if ($httpInfo['http_code'] != 200) {
        $this->_error=true;
      }
    }
    else {
      // no $httpHeaders, error = true
      $this->_error=true;
    }
  }

  /**
   * Parse the response with headers
   * @param string $responseWithHeader
   * 	Response from curl including the header
   */
  protected function parse($responseWithHeader) {
    # Extract headers from response
    $pattern = '#HTTP/\d\.\d.*?$.*?\r\n\r\n#ims';
    preg_match_all($pattern, $responseWithHeader, $matches);
    $headers = explode("\r\n", str_replace("\r\n\r\n", '', array_pop($matches[0])));

    # Extract the version and status from the first header
    $version_and_status = array_shift($headers);
    preg_match('#HTTP/(\d\.\d)\s(\d\d\d)\s(.*)#', $version_and_status, $matches);
    $this->_headers['Http-Version'] = $matches[1];
    $this->_headers['Status-Code'] = $matches[2];
    $this->_headers['Status-Message'] = $matches[2].' '.$matches[3];
    $this->_headers['Error-Message'] = ($this->_headers['Status-Code'] != 200) ? $matches[3] : '';

    # Convert headers into an associative array
    foreach ($headers as $header) {
      preg_match('#(.*?)\:\s(.*)#', $header, $matches);
      $this->_headers[$matches[1]] = $matches[2];
    }

    # Remove the headers from the response body
    $this->_raw = preg_replace($pattern, '', $responseWithHeader);
  }

  /**
   * Add items to the MuS debug information.
   * @param $name
   * @param $value
   */
  public function addQueryDebugInformation($name, $value) {
    // Add the parsed query to the xml and rebuild the raw xml
    static $musDebug;
    if (!isset($musDebug)) {
      $musDebug = $this->_xml->addChild('lst');
      $musDebug->addAttribute('name', 'musDebug');
    }
    $musDebugItem = $musDebug->addChild('lst', $value);
    $musDebugItem->addAttribute('name', $name);
    $this->_raw = $this->_xml->asXml();
  }
    /**
   * Get the error
   * @return bool indicating is there was an error
   */
  public function getError() {
    return $this->_error;
  }

  /**
   * Get the errorMessage
   * @return string containing errormessage
   */
  public function getErrorMessage() {
    return $this->_headers['Error-Message'];
  }

  /**
   * Get the HTTP status
   * @return string the HTTP status
   */
  public function getHTTPStatus() {
    return $this->_headers['Status-Code'];
  }

  /**
   * Get the HTTP status message
   * @return string the HTTP status message
   */
  public function getHTTPStatusMessage() {
    return $this->_headers['Status-Message'];

  }

  /**
   * Get the header information
   * @return
   * 	array containing header info.
   */
  public function getHeaderInfo() {
    return $this->_headers;
  }
  /**
   * Get the raw data the requerst returned
   * @return string the raw data
   */
  public function getRaw() {
    return $this->_raw;
  }

}