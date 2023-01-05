<?php
/*
 * Include Slim
 */
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

// GET route for Search
$app->get('/search', function () use ($app) {
  $alterator = new MuSSolrRequestAlterator($app->config('solr_host'), $app->config('solr_port'), $app->config('solr_path'), $_SERVER['QUERY_STRING']);
  // Add highlighting
  $alterator->addParam('hl','true');
  $alterator->addParam('hl.fl', MuSSolrRequestAlterator::HIGHLIGHT_FIELDS);
  try {
    $alterator->addParam('wt', 'xml');
  }
  catch (Exception $exception) {
    // @todo handle this correctly, if the param is already set, let it be.
  }

  $response = $alterator->doSolrRequest();
  $solrHeaders = $response->getHeaderInfo();
  $appResponse = $app->response();
  $appResponse['Content-Type'] = $solrHeaders['Content-Type'];
  $appResponse->body($response->getRaw());
});

// GET route for Object details
$app->get('/detail/:id', function ($id) use ($app) {
  $alterator = new MuSSolrRequestAlterator($app->config('solr_host'), $app->config('solr_port'), $app->config('solr_path'), $_SERVER['QUERY_STRING']);
  $query = 'PIDnumber:' . $id;
  $alterator->addParam('q', $query);
  $alterator->addParam('qt', 'detail');
  try {
    $alterator->addParam('wt', 'xml');
  }
  catch (Exception $exception) {
    // @todo handle this correctly, if the param is already set, let it be.
  }

  $response = $alterator->doSolrRequest();
  $solrHeaders = $response->getHeaderInfo();
  $appResponse = $app->response();
  $appResponse['Content-Type'] = $solrHeaders['Content-Type'];
  $appResponse->body($response->getRaw());
});

$app->run();
