<?php
/**
 * Booster class to facilitate easy boosting by means of config files
 */
class MusSolrBooster {

  protected $parsedAdvanced = array();
  // Raw arrays
  protected $iniTokens = array();
  protected $rawParams = array();

  // the params
  protected $params = array();

  protected $tokens = array();

  protected $impact = 1;

  function __construct($parsedAdvanced, $config) {
    $this->parsedAdvanced = $parsedAdvanced;
    // Try to parse the ini file
    $filename = MUS_ROOT . '/boosters/' . $config . '.booster';
    if (file_exists($filename)) {
      $this->parseIniFile($filename);
    }
  }

  /**
   * Parse the booster inifile
   * @param $filename
   */
  protected function parseIniFile($filename) {
    $iniArray = parse_ini_file($filename, TRUE);
    $this->iniTokens = $iniArray['tokens'];
    if (isset($this->iniTokens['impact'])) {
      $this->impact = $this->iniTokens['impact'];
    }
    $this->rawParams = $iniArray['params'];
  }

  /**
   * Initialize tokens
   */
  protected function initTokens() {
    // Add the keys of parsed advanced as tokens
    if (sizeof($this->parsedAdvanced) > 0) {
      foreach ($this->parsedAdvanced as $token => $value) {
        $key = '[' . $token . ']';
        $this->tokens[$key] = $value;
      }
    }
    $this->tokens['[impact]'] = $this->impact;
  }

  /**
   * Set the impact
   */
  public function setImpact($impact) {
    $this->impact = $impact;
  }

  /**
   * Write the params
   * @param array $params
   */
  public function writeParams(&$params) {
    // first initialize params
    $this->initializeParams();
    foreach ($this->params as $key => $value) {
      $params[$key] = $value;
    }
  }

  /**
   * Initialize the params
   */
  protected function initializeParams() {
    $this->initTokens();
    foreach ($this->rawParams as $urlParameter => $values) {
      // replace the tokens in each value
      foreach ($values as $key => $value) {
        $parameterValue = $this->replaceTokens($value);
        if ($parameterValue != '') {
          $this->params[$urlParameter][$key] = $parameterValue;
        }
      }
    }
    // Now the params are initialized, check in bf for dependend parameters
    if (isset($this->params['bf'])) {
      foreach ($this->params['bf'] as $key => $bfFunction) {
        // Only if the key is a string, there is a dependency
        if (! is_numeric($key)) {
          // If the key is not in the params array, the dependency is not met, so unset it
          if (! isset($this->params[$key])) {
            unset($this->params['bf'][$key]);
          }
        }
      }
    }
  }

  protected function replaceTokens($string) {
    foreach ($this->tokens as $token => $value) {
      // If the token is in the string, but the value is empty, empty the string, so it is not send!
      if (preg_match($token, $string) && $value == '') {
        $string = '';
        break;
      }
      $string = str_replace($token, $value, $string);
    }
    return $string;
  }
}