<?php
/**
 * @file
 * message_private_og.views.inc
 */

if(!empty($handler)) {
  /* Display: OG Messages */
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'OG Messages';
  $handler->display->display_options['display_description'] = 'Private messages associates to the groups the current user is a member of.';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: User: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'user';
  $handler->display->display_options['fields']['name']['label'] = 'From User';
  /* Field: Message: Groups */
  $handler->display->display_options['fields']['field_message_groups_ref']['id'] = 'field_message_groups_ref';
  $handler->display->display_options['fields']['field_message_groups_ref']['table'] = 'field_data_field_message_groups_ref';
  $handler->display->display_options['fields']['field_message_groups_ref']['field'] = 'field_message_groups_ref';
  $handler->display->display_options['fields']['field_message_groups_ref']['label'] = 'To Groups';
  $handler->display->display_options['fields']['field_message_groups_ref']['settings'] = array(
    'link' => 1,
  );
  $handler->display->display_options['fields']['field_message_groups_ref']['delta_offset'] = '0';
  /* Field: Message: Subject */
  $handler->display->display_options['fields']['field_message_subject']['id'] = 'field_message_subject';
  $handler->display->display_options['fields']['field_message_subject']['table'] = 'field_data_field_message_subject';
  $handler->display->display_options['fields']['field_message_subject']['field'] = 'field_message_subject';
  /* Field: Message: View message */
  $handler->display->display_options['fields']['view']['id'] = 'view';
  $handler->display->display_options['fields']['view']['table'] = 'message';
  $handler->display->display_options['fields']['view']['field'] = 'view';
  $handler->display->display_options['fields']['view']['label'] = 'Operations';
  $handler->display->display_options['fields']['view']['element_label_colon'] = FALSE;
  /* Field: Message: Delete message */
  $handler->display->display_options['fields']['delete']['id'] = 'delete';
  $handler->display->display_options['fields']['delete']['table'] = 'message';
  $handler->display->display_options['fields']['delete']['field'] = 'delete';
  $handler->display->display_options['fields']['delete']['label'] = '';
  $handler->display->display_options['fields']['delete']['element_label_colon'] = FALSE;
  /* Field: Message: Timestamp */
  $handler->display->display_options['fields']['timestamp']['id'] = 'timestamp';
  $handler->display->display_options['fields']['timestamp']['table'] = 'message';
  $handler->display->display_options['fields']['timestamp']['field'] = 'timestamp';
  $handler->display->display_options['fields']['timestamp']['date_format'] = 'short';
  $handler->display->display_options['fields']['timestamp']['second_date_format'] = 'long';
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Group ID */
  $handler->display->display_options['arguments']['user']['id'] = 'user';
  $handler->display->display_options['arguments']['user']['table'] = 'message';
  $handler->display->display_options['arguments']['user']['field'] = 'user';
  $handler->display->display_options['arguments']['user']['ui_name'] = 'Group ID';
  $handler->display->display_options['arguments']['user']['default_action'] = 'default';
  $handler->display->display_options['arguments']['user']['default_argument_type'] = 'og_user_groups';
  $handler->display->display_options['arguments']['user']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['user']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['user']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['user']['break_phrase'] = TRUE;
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Message: Type */
  $handler->display->display_options['filters']['type_1']['id'] = 'type_1';
  $handler->display->display_options['filters']['type_1']['table'] = 'message';
  $handler->display->display_options['filters']['type_1']['field'] = 'type';
  $handler->display->display_options['filters']['type_1']['value'] = array(
    'private_message' => 'private_message',
  );
  /* Filter criterion: Message: Groups (field_message_groups_ref) */
  $handler->display->display_options['filters']['field_message_groups_ref_target_id']['id'] = 'field_message_groups_ref_target_id';
  $handler->display->display_options['filters']['field_message_groups_ref_target_id']['table'] = 'field_data_field_message_groups_ref';
  $handler->display->display_options['filters']['field_message_groups_ref_target_id']['field'] = 'field_message_groups_ref_target_id';
  $handler->display->display_options['filters']['field_message_groups_ref_target_id']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_message_groups_ref_target_id']['expose']['operator_id'] = 'field_message_groups_ref_target_id_op';
  $handler->display->display_options['filters']['field_message_groups_ref_target_id']['expose']['label'] = 'Groups';
  $handler->display->display_options['filters']['field_message_groups_ref_target_id']['expose']['operator'] = 'field_message_groups_ref_target_id_op';
  $handler->display->display_options['filters']['field_message_groups_ref_target_id']['expose']['identifier'] = 'field_message_groups_ref_target_id';
  $handler->display->display_options['filters']['field_message_groups_ref_target_id']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
  );
  $handler->display->display_options['path'] = 'user/%/messages/groups';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Group';
  $handler->display->display_options['menu']['weight'] = '8';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
}