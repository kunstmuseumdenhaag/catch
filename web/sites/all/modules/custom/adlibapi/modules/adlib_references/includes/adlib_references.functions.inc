<?php
/**
 * @file
 * Batch operations to transform text-references in Adlib objectes to node-references
 */
/*
 * the function called for each batch-step
 */
function adlib_references_batchstep(&$context) {

  $limit = 20;
  // check of we have added our data to the context object
  if (!isset($context['sandbox']['progress'])) {
    // no, add initial data
    $context['sandbox']['progress'] = 0;
    $context['sandbox']['current_node'] = 0;
    $context['sandbox']['max'] = db_query('SELECT COUNT(DISTINCT nid) FROM {adlib_objects}')->fetchField();
  }
  // select the current range of nodes to process
  $query = "SELECT nid FROM {adlib_objects} WHERE nid > " . $context['sandbox']['current_node'] . " ORDER BY nid ASC LIMIT " . $from . ", " . $limit;
  $result = db_query_range("SELECT nid FROM {adlib_objects} WHERE nid > :nid ORDER BY nid ASC", 0, $limit, array(':nid' => $context['sandbox']['current_node']));
  foreach ($result as $row) {
    $node = node_load($row->nid, NULL, TRUE);
    _adlib_references_add_reference($node);
    //TODO: remove update node from ablib_objects table
    $context['results'][] = $node->nid . ' : ' . $node->title;
    $context['sandbox']['progress']++;
    $context['sandbox']['current_node'] = $node->nid;
    $context['message'] = $node->title;
    $message= "Last updated node in current step: " . $node->title . " (nid: " . $node->nid . ").";
  }
  if ($context['sandbox']['progress'] <= $context['sandbox']['max']) {
    $context['finished'] = $context['sandbox']['progress'] / $context['sandbox']['max'];

  }
  else {
    $context['finished'] = 1;
  }
  drupal_set_message(check_plain($message));
  watchdog("adlib_references", 'In Adlib objects batch update: ' . $message);
}


/*
 * Function to add the actual reference and save the node
 * The node we get has a textfield in which any reference (a title, a object_number) to another
 * object. Here we find the node that is referenced and add a actualk node_reference
 * @param $node node to check
 */
function _adlib_references_add_reference(&$node) {
  // get the text field in which the reference is stored from the config
  $reference_source_field=variable_get('adlib_reference_source_field_' . $node->type, 0);
  $reference_field=variable_get('adlib_reference_field_' . $node->type, 0);
  $reference_target_field = variable_get('adlib_reference_target_field_' . $node->type, 0);
  // remove all previous references
  $node->{$reference_field}= array();
  // get the value of the current node
  $ref_ctr=0;
  foreach ($node->{$reference_source_field} as $references) {
    foreach ($references as $field) {
      $ref_value = $field['value'];
      if (isset($ref_value)) {
        $table_name = 'field_data_' . $reference_target_field;
        $value_field = $reference_target_field . '_value';
        // find the objects which the field references
        $query = "SELECT entity_id FROM {$table_name} WHERE $value_field = $ref_value";
        // Drupal 6: $result = db_query_range("'SELECT entity_id FROM {$table_name}' WHERE $value_field=%value", $ref_value);
        $result = db_query("SELECT entity_id FROM {$table_name} WHERE $value_field = :val", array(':val' => $ref_value));
        foreach ($result as $record) {
          //TODO: check if reference is not already present
          $node->{$reference_field}['und'][$ref_ctr]['nid']= $record->entity_id;
          node_save($node);
          watchdog("adlib_references", "Updated reference to %from in node %to", array('%from' => $record->entity_id, '%to' => $node->id));
        }
        $ref_ctr++;
      }
    }
  }
}

/*
 * Callback for finished batch
 */
function _adlib_references_finished($success, $results, $operations) {
  drupal_set_message(t("Finished"));
  if ($success) {
    // remove all rows from the Adlib_objects table
    db_truncate('{adlib_objects}')->execute();
    $message = t("All Ablib objects updated.");
  }
  else {
    $message = t('Finished with error.');
  }
  drupal_set_message(check_plain($message));
}

