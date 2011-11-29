<?php
class AdlibSearchResponse extends AdlibBaseResponse{

  /*
   * Todo items here.
   */
  // members
  /**
  * The simpleXMLObject that is filled by the request
  */
  protected $_xmlObject;

  /**
   * Number of records returned
   */
  protected $_numberRecordsReturned;

  /**
   * Total number of records found
   */
  protected $_numberRecordsfound;

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
    // call base constructor
    parent::__construct($rawResponse, $httpHeaders);
    // Only if no errors occured, continue.
    if (! $this->getError()) {
      try {
        // disable warnings from XML parser
        libxml_use_internal_errors(true);
        $this->_xmlObject = simplexml_load_string($rawResponse);
        /* check for error in XML */
        $errorXML = $this->_xmlObject->diagnostic->error;
        if(!empty($errorXML->info)){
          $this->_error = true;
          $this->_errorString = $errorXML->info . " : " . $errorXML->message;
        }
        // save number of records returnd, number records found = (int)$this->_xmlObject->diagnostic->hits;
        $this->_numberRecordsReturned = (int)$this->_xmlObject->diagnostic->hits_on_display;
        $this->_numberRecordsfound = (int)$this->_xmlObject->diagnostic->hits;
      } catch (Exception $e){
        $this->_error = true;
        $this->_errorString = "Query did not return valid XML";
      }
      // re-enable warnings from XML parser
      libxml_use_internal_errors(false);
    }
  }

  /**
   * Get the simpleXML Object
   * @return simpleXML
   */

  public function getXMLObject(){
    return $this->_xmlObject;
  }

  /**
   * Get fields as an array
   *  @return string all the fields in a assiociative array
   */
  public function getXMLArray() {
    // TODO: this method is only usefull when getFieldlist is asked. Maybe it should be more general.
    // traverse XML to find all the fields and put them in associative array
    $fields=array();
    if(!$this->_error && isset($this->_xmlObject)){
      $results = $this->_xmlObject->xpath('/adlibXML/recordList/record');
      foreach($results as $node) {
        $result = array();
        $tag = (string) $node->tag;
        if (isset($node->fieldName->value[0])) {
          $result['fieldName'] = (string) $node->fieldName->value[0];
        }
        if (isset($node->displayName->value[0])) {
          $result['displayName'] = (string) $node->displayName->value[0];
        }
        if (isset($node->length)) {
          $result['length'] = (integer) $node->length;
        }
        if (isset($node->type)) {
          $result['type'] = (string) $node->type;
        }
        if (isset($node->repeated)) {
          $result['repeated'] = $node->repeated == 'True' ? TRUE : FALSE;
        }
        if (isset($node->isLinked)) {
          $result['isLinked'] = $node->isLinked == 'True' ? TRUE : FALSE;
        }
        if (isset($node->isIndexed)) {
          $result['isIndexed'] = $node->isIndexed == 'True' ? TRUE : FALSE;;
        }

        $fields[$tag] = $result;
      }
    }
    return $fields;
  }

  /**
   * Return the XML as a string
   * @return string the simpleXML object as a string
   */
  public function getXMLString() {
    if(isset($this->_xmlObject)){
      return $this->_xmlObject->asXML();
    } else {
      return "";
    }
  }

  /**
   * @return integer number of records returned by search
   */
  public function getNumberOfRecords(){
    return $this->_numberRecordsReturned;
  }

  /**
   * @return integer number of records that match thesearch
   */
  public function getNumberOfMatches(){
    return $this->_numberRecordsfound;
  }

}
