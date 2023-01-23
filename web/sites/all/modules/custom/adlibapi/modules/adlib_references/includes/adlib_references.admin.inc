<?php
/**
 * @file
 * Transform text-references in Adlib objectes to node-references
 */
/*
 *  Form to start batch operation
 */
function adlib_references_form(&$form_state) {

  $form['adlib_references'] = array(
   '#type' => 'fieldset',
   '#title' => t('Update Adlib references'),
   '#description' => t('Update references in Adlib objects in a batch-operation.'),
   '#collapsible' => TRUE,
   '#collapsed' => FALSE,
  );

  $form['adlib_references']['adlib_references_submit'] = array(
    '#type' => 'submit',
    '#value' => t('Start update operation'),
  );

  return $form;
}

/*
 *  Submit function to start batch operation
 */
function adlib_references_form_submit($form, &$form_state) {
  $count =  db_query('SELECT COUNT(DISTINCT nid) FROM {adlib_objects}')->fetchField();
  $message = t('Total items in batch: ' . $count);
  $batch = array(
    'title' => t('Updating Adlib objects'), // Title to display while running.
    'operations' => array(), // Operations to complete, in order
    'finished' => '_adlib_references_finished', // Last function to call.
    'init_message' => t('Initializing...'),
    'progress_message' => t('Item @current of @total.'),
    'error_message' => t('The reference update failed'),
    'progressive' => FALSE,
    // NB the file parameter is ALWAYS necessary if the functions are not! in a file with
    // the extension .module
    'file' => drupal_get_path('module', 'adlib_references') . '/includes/adlib_references.functions.inc',
  );

  $batch['operations'][] = array('adlib_references_batchstep', array());
  // Start batch operation
  batch_set($batch);
  watchdog("adlib_references", $message);
}

