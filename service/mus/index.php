<?php
/*
 * Include Slim
 */
//require 'Slim/Slim.php';
require 'vendor/autoload.php';
/*
 *
 * Include MUS
 */
require_once 'MUS/MuSSolrAPIKey.php';
require_once 'MUS/MuSSolrRequestAlterator.php';
require_once 'MUS/MuSSolrResponse.php';
require_once 'MUS/MuSSolrBooster.php';
require_once 'MUS/init.php';

$app = new \Slim\Slim();

// Root directory of MuS
define('MUS_ROOT', getcwd());

// Initialize the settings
initializeMus($app);

/**
 * Step 3: Define the Slim application routes
 *
 * Here we define several Slim application routes that respond
 * to appropriate HTTP request methods. In this example, the second
 * argument for `Slim::get`, `Slim::post`, `Slim::put`, and `Slim::delete`
 * is an anonymous function. If you are using PHP < 5.3, the
 * second argument should be any variable that returns `true` for
 * `is_callable()`. An example GET route for PHP < 5.3 is:
 *
 * $app = new Slim();
 * $app->get('/hello/:name', 'myFunction');
 * function myFunction($name) { echo "Hello, $name"; }
 *
 * The routes below work with PHP >= 5.3.
 */


//GET route
//$app->get('/search', 'musSearch');
$app->get('/search', function () use ($app) {
  $alterator = new MuSSolrRequestAlterator($app->config('solr_host'), $app->config('solr_port'), $app->config('solr_path'), $_SERVER['QUERY_STRING']);
  // Add highlighting
  $alterator->addParam('hl','true');
  $alterator->addParam('hl.fl', MuSSolrRequestAlterator::HIGHLIGHT_FIELDS);

  $response = $alterator->doSolrRequest();
  $solrHeaders = $response->getHeaderInfo();
  $appResponse = $app->response();
  $appResponse['Content-Type'] = $solrHeaders['Content-Type'];
  $appResponse->body($response->getRaw());
});
//$app->get('/detail/:id', 'musDetail');
$app->get('/detail/:id', function ($id) use ($app) {
  // Create a new mus sorl request alterator
  $alterator = new MuSSolrRequestAlterator($app->config('solr_host'), $app->config('solr_port'), $app->config('solr_path'), $_SERVER['QUERY_STRING']);
  $query = 'PIDnumber:' . $id;
  $alterator->addParam('q', $query);
  $alterator->addParam('qt', 'detail');
  $response = $alterator->doSolrRequest();
  $solrHeaders = $response->getHeaderInfo();
  $appResponse = $app->response();
  $appResponse['Content-Type'] = $solrHeaders['Content-Type'];
  $appResponse->body($response->getRaw());
});

/*
 * The actual application
 */
//function musSearch() {
//  $app = Slim::getInstance();
//  // Create a new mus sorl request alterator
//  $alterator = new MuSSolrRequestAlterator($app->config('solr_host'), $app->config('solr_port'), $app->config('solr_path'), $_SERVER['QUERY_STRING']);
//  // Add highlighting
//  $alterator->addParam('hl','true');
//  $alterator->addParam('hl.fl', MuSSolrRequestAlterator::HIGHLIGHT_FIELDS);
//
//  $response = $alterator->doSolrRequest();
//  $solrHeaders = $response->getHeaderInfo();
//  $appResponse = $app->response();
//  $appResponse['Content-Type'] = $solrHeaders['Content-Type'];
//  $appResponse->body($response->getRaw());
//}

//function musDetail($id) {
////  $app = Slim::getInstance();
//  $app = new \Slim\Slim();
//  // Create a new mus sorl request alterator
//  $alterator = new MuSSolrRequestAlterator($app->config('solr_host'), $app->config('solr_port'), $app->config('solr_path'), $_SERVER['QUERY_STRING']);
//  $query = 'PIDnumber:' . $id;
//  $alterator->addParam('q', $query);
//  $alterator->addParam('qt', 'detail');
//  $response = $alterator->doSolrRequest();
//  $solrHeaders = $response->getHeaderInfo();
//  $appResponse = $app->response();
//  $appResponse['Content-Type'] = $solrHeaders['Content-Type'];
//  $appResponse->body($response->getRaw());
//}

$app->run();
