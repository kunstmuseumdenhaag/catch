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
  protected $_errorString;

  /**
   * HTTP response
   */
  protected $_httpStatus;
  protected $_httpStatusMessage;

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
  public function __construct($rawResponse, $httpHeaders = array()){
    $this->_error = false;
    $this->_raw = $rawResponse;
    $this->_httpStatus = -1;
    $this->_httpStatusMessage = 'No request';
    // if $rawResponse is 'false' the request failed completely
    if(!$rawResponse){
      $this->_error = true;
      $this->_errorString = 'No response from adlibserver. Probably the adress is wrong.';
    }

    if (is_array($httpHeaders) && count($httpHeaders) > 0){
      while (isset($httpHeaders[0]) && substr($httpHeaders[0], 0, 4) == 'HTTP')
      {
        $parts = explode(' ', substr($httpHeaders[0], 9), 2);
        $status = $parts[0];
        $statusMessage = trim($parts[1]);
        array_shift($httpHeaders);
      }
      $this->_httpStatus = $status;
      $this->_httpStatusMessage = $statusMessage;
      // if we received any other status then 200 OK we have an error and we assume no valid XML was returned
      if($status != 200){
        $this->_error = true;
      }
    } else {
      // no $httpHeaders, error = true
      $this->_error = true;
    }
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