<?php
/**
 * Features views include file.
 */

/**
 * Implements hook_views_api().
 */
function message_private_views_api() {
  list($module, $api) = func_get_args();
  if ($module == "views" && $api == "views_default") {
    return array("version" => "3.0");
  }
}

/**
 * Implements hook_views_default_views().
 */
function message_private_views_default_views() {

  $export = array();

  $view = new view();
  $view->name = 'message_private';
  $view->description = 'Show private messages for users and groups.';
  $view->tag = 'Message';
  $view->base_table = 'message';
  $view->human_name = 'Message Private';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE;

  /* Display: Defaults */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->display->display_options['title'] = 'User Messages';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'view a private_message message instance';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '30';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'name' => 'name',
    'field_message_subject' => 'field_message_subject',
    'view' => 'view',
    'delete' => 'view',
    'timestamp' => 'timestamp',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'name' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_message_subject' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'view' => array(
      'align' => '',
      'separator' => ' ',
      'empty_column' => 0,
    ),
    'delete' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'timestamp' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['style_options']['sticky'] = TRUE;
  /* Header: Global: Text area */
  $handler->display->display_options['header']['area']['id'] = 'area';
  $handler->display->display_options['header']['area']['table'] = 'views';
  $handler->display->display_options['header']['area']['field'] = 'area';
  $handler->display->display_options['header']['area']['content'] = '<div class="actions">
            <ul class="action-links">
        <li><a href="/en/admin/content/message/create">Create a new message</a></li>
        </ul>
          </div>';
  $handler->display->display_options['header']['area']['format'] = 'filtered_html';
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['content'] = 'No messages created yet.';
  $handler->display->display_options['empty']['area']['format'] = 'filtered_html';
  /* Relationship: Message: User uid */
  $handler->display->display_options['relationships']['user']['id'] = 'user';
  $handler->display->display_options['relationships']['user']['table'] = 'message';
  $handler->display->display_options['relationships']['user']['field'] = 'user';
  /* Field: User: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'user';
  $handler->display->display_options['fields']['name']['label'] = 'From User';
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
  /* Sort criterion: Message: Timestamp */
  $handler->display->display_options['sorts']['timestamp']['id'] = 'timestamp';
  $handler->display->display_options['sorts']['timestamp']['table'] = 'message';
  $handler->display->display_options['sorts']['timestamp']['field'] = 'timestamp';
  $handler->display->display_options['sorts']['timestamp']['order'] = 'DESC';
  /* Contextual filter: User ID */
  $handler->display->display_options['arguments']['user']['id'] = 'user';
  $handler->display->display_options['arguments']['user']['table'] = 'message';
  $handler->display->display_options['arguments']['user']['field'] = 'user';
  $handler->display->display_options['arguments']['user']['ui_name'] = 'User ID';
  $handler->display->display_options['arguments']['user']['default_action'] = 'default';
  $handler->display->display_options['arguments']['user']['default_argument_type'] = 'current_user';
  $handler->display->display_options['arguments']['user']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['user']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['user']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['user']['break_phrase'] = TRUE;
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
  $handler->display->display_options['filters']['field_message_groups_ref_target_id']['expose']['label'] = 'Groups (field_message_groups_ref)';
  $handler->display->display_options['filters']['field_message_groups_ref_target_id']['expose']['operator'] = 'field_message_groups_ref_target_id_op';
  $handler->display->display_options['filters']['field_message_groups_ref_target_id']['expose']['identifier'] = 'field_message_groups_ref_target_id';

  /* Display: Received Messages */
  $handler = $view->new_display('page', 'Received Messages', 'page_1');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Inbox';
  $handler->display->display_options['display_description'] = 'Private messages received by the user.';
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: Message: User uid */
  $handler->display->display_options['relationships']['user']['id'] = 'user';
  $handler->display->display_options['relationships']['user']['table'] = 'message';
  $handler->display->display_options['relationships']['user']['field'] = 'user';
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Message: Users (field_message_user_ref) */
  $handler->display->display_options['arguments']['field_message_user_ref_target_id']['id'] = 'field_message_user_ref_target_id';
  $handler->display->display_options['arguments']['field_message_user_ref_target_id']['table'] = 'field_data_field_message_user_ref';
  $handler->display->display_options['arguments']['field_message_user_ref_target_id']['field'] = 'field_message_user_ref_target_id';
  $handler->display->display_options['arguments']['field_message_user_ref_target_id']['default_action'] = 'default';
  $handler->display->display_options['arguments']['field_message_user_ref_target_id']['default_argument_type'] = 'current_user';
  $handler->display->display_options['arguments']['field_message_user_ref_target_id']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_message_user_ref_target_id']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_message_user_ref_target_id']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['path'] = 'user/%/messages/inbox';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Inbox';
  $handler->display->display_options['menu']['weight'] = '10';
  $handler->display->display_options['menu']['context'] = 1;
  $handler->display->display_options['menu']['context_only_inline'] = 0;

  /* Display: Sent Messages */
  $handler = $view->new_display('page', 'Sent Messages', 'page_3');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Sent';
  $handler->display->display_options['display_description'] = 'Private messages sent by the user.';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Message: Users */
  $handler->display->display_options['fields']['field_message_user_ref']['id'] = 'field_message_user_ref';
  $handler->display->display_options['fields']['field_message_user_ref']['table'] = 'field_data_field_message_user_ref';
  $handler->display->display_options['fields']['field_message_user_ref']['field'] = 'field_message_user_ref';
  $handler->display->display_options['fields']['field_message_user_ref']['label'] = 'To Users';
  $handler->display->display_options['fields']['field_message_user_ref']['settings'] = array(
    'link' => 1,
  );
  $handler->display->display_options['fields']['field_message_user_ref']['delta_offset'] = '0';
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
  $handler->display->display_options['path'] = 'user/%/messages/sent';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Sent';
  $handler->display->display_options['menu']['weight'] = '11';
  $handler->display->display_options['menu']['context'] = 1;
  $handler->display->display_options['menu']['context_only_inline'] = 0;

  $export['message_private'] = $view;

  return $export;
}
