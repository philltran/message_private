<?php
/**
 * @file
 * message_private_message.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function message_private_message_field_group_info() {
  $export = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_message_receiver|message|private_message|form';
  $field_group->group_name = 'group_message_receiver';
  $field_group->entity_type = 'message';
  $field_group->bundle = 'private_message';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Receiver',
    'weight' => '0',
    'children' => array(
      0 => 'field_node_groups_ref',
      1 => 'field_message_user_ref',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-message-receiver field-group-fieldset',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_message_receiver|message|private_message|form'] = $field_group;

  return $export;
}
