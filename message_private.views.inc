<?php
/**
 * @file
 * message_private_og.views.inc
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
  $view->description = 'Show all relevant private messages.';
  $view->tag = 'default';
  $view->base_table = 'message';
  $view->human_name = 'Message Private';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'User Messages';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'view a private_message message instance';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'timestamp' => 'timestamp',
    'name' => 'name',
    'delete' => 'view',
    'edit' => 'view',
    'view' => 'view',
    'field_message_user_ref' => 'field_message_user_ref',
    'field_message_subject' => 'field_message_subject',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'timestamp' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'name' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'delete' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'edit' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'view' => array(
      'align' => '',
      'separator' => ' ',
      'empty_column' => 0,
    ),
    'field_message_user_ref' => array(
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
  );
  /* Header: Global: Text area */
  $handler->display->display_options['header']['area']['id'] = 'area';
  $handler->display->display_options['header']['area']['table'] = 'views';
  $handler->display->display_options['header']['area']['field'] = 'area';
  $handler->display->display_options['header']['area']['content'] = '<div class="actions">
            <ul class="action-links">
        <li><a href="/admin/content/message/create">Create a new message</a></li>
        </ul>
          </div>';
  $handler->display->display_options['header']['area']['format'] = 'filtered_html';
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['empty'] = TRUE;
  $handler->display->display_options['empty']['area']['content'] = 'No messages created yet.';
  $handler->display->display_options['empty']['area']['format'] = 'filtered_html';
  /* Relationship: Message: User uid */
  $handler->display->display_options['relationships']['user']['id'] = 'user';
  $handler->display->display_options['relationships']['user']['table'] = 'message';
  $handler->display->display_options['relationships']['user']['field'] = 'user';
  /* Field: Message: Users */
  $handler->display->display_options['fields']['field_message_user_ref']['id'] = 'field_message_user_ref';
  $handler->display->display_options['fields']['field_message_user_ref']['table'] = 'field_data_field_message_user_ref';
  $handler->display->display_options['fields']['field_message_user_ref']['field'] = 'field_message_user_ref';
  $handler->display->display_options['fields']['field_message_user_ref']['label'] = 'From';
  $handler->display->display_options['fields']['field_message_user_ref']['settings'] = array(
    'link' => 1,
  );
  $handler->display->display_options['fields']['field_message_user_ref']['delta_offset'] = '0';
  /* Field: Message: Subject */
  $handler->display->display_options['fields']['field_message_subject']['id'] = 'field_message_subject';
  $handler->display->display_options['fields']['field_message_subject']['table'] = 'field_data_field_message_subject';
  $handler->display->display_options['fields']['field_message_subject']['field'] = 'field_message_subject';
  /* Field: Message: Timestamp */
  $handler->display->display_options['fields']['timestamp']['id'] = 'timestamp';
  $handler->display->display_options['fields']['timestamp']['table'] = 'message';
  $handler->display->display_options['fields']['timestamp']['field'] = 'timestamp';
  $handler->display->display_options['fields']['timestamp']['date_format'] = 'long';
  $handler->display->display_options['fields']['timestamp']['second_date_format'] = 'long';
  /* Field: Message: View message */
  $handler->display->display_options['fields']['view']['id'] = 'view';
  $handler->display->display_options['fields']['view']['table'] = 'message';
  $handler->display->display_options['fields']['view']['field'] = 'view';
  $handler->display->display_options['fields']['view']['label'] = '';
  $handler->display->display_options['fields']['view']['element_label_colon'] = FALSE;
  /* Field: Message: Edit message */
  $handler->display->display_options['fields']['edit']['id'] = 'edit';
  $handler->display->display_options['fields']['edit']['table'] = 'message';
  $handler->display->display_options['fields']['edit']['field'] = 'edit';
  /* Field: Message: Delete message */
  $handler->display->display_options['fields']['delete']['id'] = 'delete';
  $handler->display->display_options['fields']['delete']['table'] = 'message';
  $handler->display->display_options['fields']['delete']['field'] = 'delete';
  /* Sort criterion: Message: Timestamp */
  $handler->display->display_options['sorts']['timestamp']['id'] = 'timestamp';
  $handler->display->display_options['sorts']['timestamp']['table'] = 'message';
  $handler->display->display_options['sorts']['timestamp']['field'] = 'timestamp';
  /* Contextual filter: Message: Users (field_message_user_ref) */
  $handler->display->display_options['arguments']['field_message_user_ref_target_id']['id'] = 'field_message_user_ref_target_id';
  $handler->display->display_options['arguments']['field_message_user_ref_target_id']['table'] = 'field_data_field_message_user_ref';
  $handler->display->display_options['arguments']['field_message_user_ref_target_id']['field'] = 'field_message_user_ref_target_id';
  $handler->display->display_options['arguments']['field_message_user_ref_target_id']['default_action'] = 'default';
  $handler->display->display_options['arguments']['field_message_user_ref_target_id']['default_argument_type'] = 'current_user';
  $handler->display->display_options['arguments']['field_message_user_ref_target_id']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_message_user_ref_target_id']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_message_user_ref_target_id']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['field_message_user_ref_target_id']['break_phrase'] = TRUE;
  /* Filter criterion: Message: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'message';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'private_message' => 'private_message',
  );

  /* Display: User Messages */
  $handler = $view->new_display('page', 'User Messages', 'page');
  $handler->display->display_options['path'] = 'user-messages';

  $export['message_private'] = $view;

  return $export;
}
