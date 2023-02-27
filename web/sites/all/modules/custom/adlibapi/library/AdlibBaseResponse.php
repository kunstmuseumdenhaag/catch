<?php
class AdlibBaseResponse{

  /*
   * Todo items here.
   */
  // Members
  /**
   * Boolean that indicates if an error occured
   */
  protected $_error;

  /**
   * String for errormessage
   */
  protected $_errorString = 'Unknown error';

  /**
   * HTTP response
   */
  protected $_httpStatus;
  protected $_httpStatusMessage;
    protected $_headers;

    /**
   * The raw response
   */
  protected $_raw;

  // methods
  /**
  * Contructor
  * @param string $rawResponse the raw response we get from the adlib server
  * @param string $httpHeaders the HTTP headers created when the request was made
  */
  public function __construct($responseWithHeader, $httpInfo = array()){
    $this->_error = false;
    $this->_httpStatus = -1;
    $this->_httpStatusMessage = 'No request';
    // if $responseWithHeader is 'false' the request failed completely
    if (!$responseWithHeader) {
      $this->_error=true;
      $this->_errorString = 'No response from adlibserver. Probably the adress is wrong.';
    }
    else {
      $this->parse($responseWithHeader);
    }

    if (is_array($httpInfo) && count($httpInfo) > 0 && !$this->_error) {
      // if we received any other status then 200 OK we have an error and we assume no valid XML was returned
      if ($httpInfo['http_code'] != 200) {
        $this->_error = true;
        $this->_errorString = $this->_headers['Status-Message'] . ': ' . $this->_headers['Error-Message'];
      }
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

    $this->_httpStatus = $this->_headers['Status-Code'];
    $this->_httpStatusMessage = $this->_headers['Status-Message'];

    # Convert headers into an associative array
    foreach ($headers as $header) {
      preg_match('#(.*?)\:\s(.*)#', $header, $matches);
      $this->_headers[$matches[1]] = $matches[2];
    }

    # Remove the headers from the response body
    $this->_raw = preg_replace($pattern, '', $responseWithHeader);
  }


    /**
   * Get the error
   * @return bool indicating is there was an error
   */
  public function getError(){
    return $this->_error;
  }

  /**
   * Get the errorMessage
   * @return string containing errormessage
   */
  public function getErrorMessage(){
    return $this->_errorString;
  }

  /**
   * Manually set the Error message.
   *
   * @param $error_message
   */
  public  function setErrorMessage($error_message) {
    $this->_errorString .= $error_message;
  }

  /**
   * Get the HTTP status
   * @return string the HTTP status
   */
  public function getHTTPStatus(){
    return $this->_httpStatus;
  }

  /**
   * Get the HTTP status message
   * @return string the HTTP status message
   */
  public function getHTTPStatusMessage(){
    return $this->_httpStatusMessage;

  }

  /**
   * Get the raw data the requerst returned
   * @return string the raw data
   */
  public function getRaw(){
    return $this->_raw;
  }
}
