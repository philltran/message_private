<?php
/**
 * @file
 * message_private_og.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function message_private_og_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'message-private_message-field_message_groups_ref'
  $field_instances['message-private_message-field_message_groups_ref'] = array(
    'bundle' => 'private_message',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'entityreference',
        'settings' => array(
          'link' => FALSE,
        ),
        'type' => 'entityreference_label',
        'weight' => 1,
      ),
      'message_notify_email_body' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'message_notify_email_subject' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'message',
    'field_name' => 'field_message_groups_ref',
    'label' => 'Groups',
    'required' => 0,
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(),
      'type' => 'options_select',
      'weight' => 0,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Groups');

  return $field_instances;
}