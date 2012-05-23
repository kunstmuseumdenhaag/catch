<?php
/**
 * @file
 * gemeentemuseum_adlib.features.user_permission.inc
 */

/**
 * Implementation of hook_user_default_permissions().
 */
function gemeentemuseum_adlib_user_default_permissions() {
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
