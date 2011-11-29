<?php
class AdlibImageResponse extends AdlibBaseResponse{
  // methods
  /**
  * Contructor
  * @param string $rawResponse the raw response we get from the adlib server
  * @param string $httpHeaders the HTTP headers created when the request was made
  */
  public function __construct($rawResponse, $httpHeaders = array()){
    parent::__construct($rawResponse, $httpHeaders);
    try{
      // disable warnings from XML parser
      libxml_use_internal_errors(true);
      $xmlObject = simplexml_load_string($rawResponse);
      /* check for error in XML */
      try{
        if(isset($xmlObject->diagnostic)){
          $errorXML = $xmlObject->diagnostic->error;
          if(!empty($errorXML->info)){
            $this->_error=true;
            $this->_errorString=$errorXML->info . " : " . $errorXML->message;
          }
        }
      }catch(Exception $e){
        // if we have an exception, the request returned binary data and we have NO error
        // so in this case an emtpy catch is actually correct
      }
    }
    catch(Exception $e){
      // if we have an exception, the request returned binary data and we have NO error
      // so in this case an emtpy catch is actually correct
    }
    // re-enable warnings from XML parser
    libxml_use_internal_errors(false);
  }

}