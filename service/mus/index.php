<?php
/*
 * Include Slim
 */

use Slim\Http\Request;
use Slim\Http\Response;

require 'vendor/autoload.php';
/*
 *
 * Include MUS
 */
require_once 'MUS/MuSSolrAPIKey.php';
require_once 'MUS/MuSSolrRequestAlterator.php';
require_once 'MUS/MuSSolrResponse.php';
require_once 'MUS/MuSSolrBooster.php';

// Root directory of MuS
define('MUS_ROOT', getcwd());

$conf_filename = 'conf.php';

// Initialize the app with the conf from the environment.
if (file_exists(MUS_ROOT . '/environment/' . $conf_filename)) {
  include_once MUS_ROOT . '/environment/' . $conf_filename;
}
if (isset($conf)) {
  // Now add the settings to Slim
  $app = new \Slim\App(['settings' => $conf]);
}
else {
  $c = new \Slim\Container();
  $c['errorHandler'] = static function() {
    return static function ($request, $response) {
      return $response->withStatus(500)
        ->withHeader('Content-Type', 'text/html')
        ->write('Configuration not found.');
    };
  };
  $app = new \Slim\App($c);

}

// GET route for Search
$app->get('/search', function (Request $request, Response $response) {
  $alterator = new MuSSolrRequestAlterator(
    $this->get('settings')['solr_host'],
    $this->get('settings')['solr_port'],
    $this->get('settings')['solr_path'],
    $_SERVER['QUERY_STRING']);
  // Add highlighting
  $alterator->addParam('hl','true');
  $alterator->addParam('hl.fl', MuSSolrRequestAlterator::HIGHLIGHT_FIELDS);
  try {
    $alterator->addParam('wt', 'xml');
  }
  catch (Exception $exception) {
    // The parameter has already been set.
  }

  $solrResponse = $alterator->doSolrRequest();
  $solrHeaders = $solrResponse->getHeaderInfo();
  $response = $response->withHeader('Content-type', $solrHeaders['Content-Type']);
  $response->getBody()->write($solrResponse->getRaw());
  return $response;
});

// GET route for Object details
$app->get('/detail/{id}', function (Request $request, Response $response, array $args) {
  $alterator = new MuSSolrRequestAlterator(
    $this->get('settings')['solr_host'],
    $this->get('settings')['solr_port'],
    $this->get('settings')['solr_path'],
    $_SERVER['QUERY_STRING']);
  $query = 'PIDnumber:' . $args['id'];
  $alterator->addParam('q', $query);
  $alterator->addParam('qt', 'detail');
  try {
    $alterator->addParam('wt', 'xml');
  }
  catch (Exception $exception) {
    // The parameter has already been set.
  }

  $solrResponse = $alterator->doSolrRequest();
  $solrHeaders = $solrResponse->getHeaderInfo();
  $response = $response->withHeader('Content-type', $solrHeaders['Content-Type']);
  $response->getBody()->write($solrResponse->getRaw());
  return $response;
});

$app->run();
