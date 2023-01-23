<?php

include_once("AdlibSearchQuery.php");
include_once("AdlibImageQuery.php");
include_once("AdlibBaseResponse.php");
include_once("AdlibSearchResponse.php");
include_once("AdlibImageResponse.php");

/*
 * TODO: There are two response classes now, which have some methods in common. I guess there should be an abstract base class.
 */

class AdLibConnector{
  /**
   * Todo items here.
   * TODO: add documentation
   * TODO: addfields function
   * TODO: number of results
   */
  // members
  /**
   * The URL on which the Adlib server is reachable
   */
  private $baseurl;

  /**
   * Name of the database on the server
   */
  private $database;
  /**
   * Name of the image server
   */
  private $imageserver;

  /**
   * User credentials
   */
  private $user;
  private $pwd;
  // domain of which the user is a memeber
  private $domain;
  // indicate if the user is authenticated
  private $isAuthenticated;

  /**
   * Errorhandling
   */
  // last call that was made to the Adlib server
  public $lastCall;
  // indicate if there was a error during the last call
  public $hasError;
  // string nwhich contains the last error
  public $lastError;

  // methods
  /**
  * Contructor
  * @param $baseurl
  * @param $database
  * @param $user
  * @param $pwd
  * @param $domain
  * 	$connection: array with uri of server, username, password
  */
  function __construct($baseurl, $database="", $imageserver="", $user="", $pwd="", $domain="") {
    $this->baseurl = $baseurl;
    $this->database = $database;
    $this->imageserver = $imageserver;
    $this->user = $user;
    $this->pwd = $pwd;
    $this->domain = $domain;
    $this->isAuthenticated = false;
    $this->hasError = false;
    $this->lastError = "";
  }

  /**
   * Set database
   * @param string $dbname
   */
  public function setDatabase($dbname) {
    $this->database = $dbname;
  }

  /**
   * Authenticate user and start session
   */
  function startSession(){
    if(isset($this->user) && isset($this->pwd)){
      $fullurl=$baseurl.'?database='.$this->database.'&command=login&username='.urlencode($this->user).'&password='.urlencode($this->pwd);
      $response= $this->_doCall($fullurl);
      // check response
      $fullurl=$baseurl.'?database='.$this->database.'command=startsession';
    }
    else{
      $xml= simplexml_load_string(formatErrorFromString('No valid user and password'));
    }
    return $xml;
  }

  /**
   * End the session
   */
  function endSession(){
    $fullurl=$this->baseurl.'?command=endsession';
    $this->_doCall($fullurl);
    if(!$this->hasError){
      $fullurl=$this->baseurl.'?command=logout';
      $response=$this->_doCall($fullurl);
    }
  }

  /**
   * Perform a search on de database, paramaters are given in string
   * @param $searchparameters string with all the arguments for the raw search
   * @param $xmltype teh type of XML to return
   * @return AdlibSearchResponse object with the result of the query
   */
  function rawQueryServer($searchparameters, $xmltype="grouped"){
    $fullurl=$this->baseurl.'?database='.urlencode($this->database).'&search='.urlencode($searchparameters).'&xmltype='.urlencode($xmltype);
    $response =  $this->_doCall($fullurl);
    return $response;
  }



  /**
   * Perform as query with the parameters in the object
   * @param AdlibSearchQuery $query the object with the query to perform
   * @return AdlibSearchResponse object with the result of the query
   */
  function performQuery($query){
    // construct parameters
    $queryItems = $query->getQueryItems();
    $fullurl=$this->baseurl.'?database='.urlencode($this->database).'&search='.$queryItems;
    $response =  $this->_doCall($fullurl);
    return $response;
  }

  /**
   * Get the version of the Adlib server we are conntected to
   * @return AdlibSearchResponse object with the result of the query
   */
  public function getVersion() {
    $fullurl=$this->baseurl.'?command=getversion';
    $response =  $this->_doCall($fullurl);
    return $response;
  }

  /**
   * Function to returns all the fields in the current database
   * @return AdlibSearchResponse object with the result of the query
   */
  function getFieldList(){
    $fullurl=$this->baseurl.'?database='.$this->database.'&command=getmetadata';
    $response = $this->_doCall($fullurl);
    return $response;
  }

  /**
   * Function to returns the fields in the current database as associative array
   * @deprecated
   * @return array associative array with all the available fields
   */
  function getFieldListAsArray(){
    // get fields in XML
    $response = $this->getFieldList();
    $xml = $response->getXMLObject();
    // traverse XML to find all the fields and put them in associative array
    $fields=array();

    $results = $xml->xpath('/adlibXML/recordList/record');
    foreach($results as $node) {
      $tag =(string) $node->tag;
      $fieldName=(string) $node->fieldName->value[0];
      $displayName=(string) $node->displayName->value[0];
      $fields[$tag]=array("fieldName"=>$fieldName, "displayName"=>$displayName);
    }
    return $fields;
  }

  /**
   * Get all records altered after given date. Date format is 'Y-m-d'
   * @param string alter date
   * @return AdlibSearchResponse object with the result of the query
   */
  function getAlteredRecordsByDate($date){
    $fullurl=$this->baseurl."?database=".urlencode($this->database)."&limit=1000&search=".urlencode("modification greater '$date'");
    $response = $this->_doCall($fullurl);
    return $response;
  }

  /**
   * listDatabases
   * Get a list of adlib databases that can be accessed using the baseurl.
   * @return AdlibSearchResponse object with the result of the query
   */
  public function listDatabases() {
    $fullurl=$this->baseurl . "?command=listdatabases";
    $response = $this->_doCall($fullurl);
    return $response;
  }

  /**
   * Get the metadata of the fields in the adlib database
   * @return AdlibSearchResponse object with the result of the query
   */
  public function getMetadata() {
    $fullurl = $this->baseurl . "?command=getmetadata&database=" . urlencode($this->database);
    $response = $this->_doCall($fullurl);
    return $response;
  }

  /**
   * Get an image from the image server
   * @param AdlibImageQuery $imageQuery
   *   Image query object containing at the least the filename
   */
  public function getImage($imageQuery) {
    $fullurl = $this->baseurl . "?command=getcontent&server=" . $this->imageserver . "&" . $imageQuery->getQueryString();
    $response = $this->_doCall($fullurl, 'image');
    return $response;
  }

  /**
   * Helper function to actually perform calls to AdLib server
   * @param $fullurl the complete URL with in it th request for the HTTP request to the server
   * @param (optional) type of response (search or image)
   * @return AdlibSearchResponse object with the result of the query
   */
  private function _doCall($fullurl, $type='search'){
    $this->lastCall = $fullurl;

    $ch = curl_init();
    curl_setopt($ch, CURLOPT_URL, $fullurl);
    curl_setopt($ch, CURLOPT_HEADER, true);
    curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
    curl_setopt($ch, CURLOPT_USERAGENT, 'MuS search proxy');

    $rawdata = curl_exec($ch);
    $httpInfo = curl_getinfo($ch);

    switch ($type) {
      case 'image':
        // create AdlibImageResponse object, any request errors are handled in the constructor
        $response = new AdlibImageResponse($rawdata, $httpInfo);
        break;
      default:
        // create AdlibSearchResponse object, any request errors are handled in the constructor
        $response = new AdlibSearchResponse($rawdata, $httpInfo);
        break;
    }

    if ($response->getError() && $response->getHTTPStatus() == -1 ) {
      $curl_error = curl_error($ch);
      $response->setErrorMessage($curl_error);
    }

    return $response;
  }
}