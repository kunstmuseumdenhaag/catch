<?php
/**
 * @file
 * adlib_test.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function adlib_test_user_default_permissions() {
  $permissions = array();

  // Exported permission: use text format full_html
  $permissions['use text format full_html'] = array(
    'name' => 'use text format full_html',
    'roles' => array(
      0 => 'administrator',
      1 => 'anonymous user',
    ),
    'module' => 'filter',
  );

  return $permissions;
}
