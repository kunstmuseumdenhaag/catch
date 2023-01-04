<?php

/**
 * @file
 * gemeentemuseum_adlib.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function gemeentemuseum_adlib_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'use text format full_html'.
  $permissions['use text format full_html'] = array(
    'name' => 'use text format full_html',
    'roles' => array(
      'administrator' => 'administrator',
      'anonymous user' => 'anonymous user',
    ),
    'module' => 'filter',
  );

  return $permissions;
}
