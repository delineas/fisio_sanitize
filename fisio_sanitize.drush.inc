<?php

/**
 * @file
 * Provide Drush integration for release building and dependency building.
 */

/**
 * Implements hook_drush_help().
 */
function fisio_sanitize_drush_help($section) {
  switch ($section) {
    case 'drush:fisio-sanitize':
      return dt('Run sanitization operations on the current database for Fisioterapia-online. You can add more sanitization to this command by implementing hook_drush_sql_sync_sanitize().');
  }
}

/**
 * Implements hook_drush_command().
 */
function fisio_sanitize_drush_command() {
  $items = array();

  $items['fisio-sanitize'] = array(
    'description' => 'Sanitize additional table for Fisioterapia-online',
    'callback' => 'drush_fisio_sanitize',
    'bootstrap' => DRUSH_BOOTSTRAP_DRUSH, // No bootstrap.
    'aliases' => array('fisa'),
  );

  return $items;
}

function drush_fisio_sanitize() {
  drush_sql_bootstrap_further();
  if (drush_get_option('db-prefix')) {
    drush_bootstrap_max(DRUSH_BOOTSTRAP_DRUPAL_DATABASE);
  }
  drush_include(DRUSH_BASE_PATH . '/commands/sql', 'sync.sql');

  if (!drush_confirm(dt('Do you really want to sanitize the current database for Fisioterapia-online?'))) {
    return drush_user_abort();
  }
  $query_list = array(
    "DELETE FROM system WHERE name IN ('devel', 'googleanalytics');",
    "UPDATE users SET mail = CONCAT('user+', uid, '@localhost'), init = CONCAT('user+', uid, '@localhost'), pass = MD5(CONCAT('HIDDENSECRET', name)), name = CONCAT('username',uid) WHERE uid NOT IN  (SELECT uid FROM users_roles WHERE rid=3) AND uid > 0;",
    "UPDATE IGNORE url_alias SET alias = CONCAT('users/', REPLACE(source,'/', '')) WHERE source IN (SELECT CONCAT('user/',u.uid) FROM users u WHERE u.uid NOT IN (SELECT uid FROM users_roles WHERE rid=3) AND u.uid > 1);",
    "UPDATE comment SET name=CONCAT('Nombre com. ', cid), mail='', homepage='http://localhost' WHERE uid=0;",
    "UPDATE field_data_field_email SET field_email_value = CONCAT(entity_id, '@localhost');",
    "UPDATE field_revision_field_email SET field_email_value = CONCAT(entity_id, '@localhost');",
    "UPDATE field_data_field_name SET field_name_value = CONCAT('Nombre ', entity_id);",
    "UPDATE field_revision_field_name SET field_name_value = CONCAT('Nombre ', entity_id);",
    "UPDATE field_data_field_surname SET field_surname_value = CONCAT('Apellido ', entity_id);",
    "UPDATE field_revision_field_surname SET field_surname_value = CONCAT('Apellido ', entity_id);",
    "UPDATE field_data_field_phone SET field_phone_value = CONCAT('111 ', entity_id);",
    "UPDATE field_revision_field_phone SET field_phone_value = CONCAT('111 ', entity_id);",
    "UPDATE webform_submitted_data set data='satinize';",
    "TRUNCATE accesslog;",
    "TRUNCATE `captcha_points`;",
    "TRUNCATE `captcha_sessions`;",
    "TRUNCATE flood;",
    "TRUNCATE history;",
    "TRUNCATE sessions;",
    "TRUNCATE watchdog;",
  );

  $sanitize_query = '';
  foreach ($query_list as $id => $query) {
    $sanitize_query .= $query . " ";
  }
  if ($sanitize_query) {
    if (!drush_get_context('DRUSH_SIMULATE')) {
      drush_sql_query($sanitize_query);
    }
    else {
      drush_print("Executing: $sanitize_query");
    }
  }
}

/**
 * Implementation of hook_drush_sql_sync_sanitize().
 */
function fisio_sanitize_drush_sql_sync_sanitize($source) {
  if (!drush_confirm(dt('Do you really want to sanitize the current database for Fisioterapia-online?'))) {
    return drush_user_abort();
  }
  $query_list = array(
    "DELETE FROM system WHERE name IN ('devel', 'googleanalytics');",
    "UPDATE users SET mail = CONCAT('user+', uid, '@localhost'), init = CONCAT('user+', uid, '@localhost'), pass = MD5(CONCAT('HIDDENSECRET', name)), name = CONCAT('username',uid) WHERE uid NOT IN  (SELECT uid FROM users_roles WHERE rid=3) AND uid > 0;",
    "UPDATE IGNORE url_alias SET alias = CONCAT('users/', REPLACE(source,'/', '')) WHERE source IN (SELECT CONCAT('user/',u.uid) FROM users u WHERE u.uid NOT IN (SELECT uid FROM users_roles WHERE rid=3) AND u.uid > 1);",
    "UPDATE comment SET name=CONCAT('Nombre com. ', cid), mail='', homepage='http://localhost' WHERE uid=0;",
    "UPDATE field_data_field_email SET field_email_value = CONCAT(entity_id, '@localhost');",
    "UPDATE field_revision_field_email SET field_email_value = CONCAT(entity_id, '@localhost');",
    "UPDATE field_data_field_name SET field_name_value = CONCAT('Nombre ', entity_id);",
    "UPDATE field_revision_field_name SET field_name_value = CONCAT('Nombre ', entity_id);",
    "UPDATE field_data_field_surname SET field_surname_value = CONCAT('Apellido ', entity_id);",
    "UPDATE field_revision_field_surname SET field_surname_value = CONCAT('Apellido ', entity_id);",
    "UPDATE field_data_field_phone SET field_phone_value = CONCAT('111 ', entity_id);",
    "UPDATE field_revision_field_phone SET field_phone_value = CONCAT('111 ', entity_id);",
    "UPDATE webform_submitted_data set data='satinize';",
    "TRUNCATE accesslog;",
    "TRUNCATE `captcha_points`;",
    "TRUNCATE `captcha_sessions`;",
    "TRUNCATE flood;",
    "TRUNCATE history;",
    "TRUNCATE sessions;",
    "TRUNCATE watchdog;",
  );

  $sanitize_query = '';
  foreach ($query_list as $id => $query) {
    $sanitize_query .= $query . " ";
  }

  drush_sql_register_post_sync_op('fisio-sanitize', 'Sanitize Fisioterapia-online', $sanitize_query);
}
