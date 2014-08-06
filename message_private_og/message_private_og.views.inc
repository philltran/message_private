<?php
/**
 * @file
 * message_private_og.views.inc
 */

/**
 * Implements hook_views_api().
 */
function message_private_og_views_api() {
  list($module, $api) = func_get_args();
  if ($module == "views" && $api == "views_default") {
    return array("version" => "3.0");
  }
}

/**
 * Implements hook_views_default_views().
 */
function message_private_og_views_default_views() {
  $export = array();

  $view = views_get_view('message_private');

  /* Display: Group Messages */
  $handler = $view->new_display('page', 'Group Messages', 'page_1');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Group Messages';
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Groups */
  $handler->display->display_options['arguments']['field_message_user_ref_target_id']['id'] = 'field_message_user_ref_target_id';
  $handler->display->display_options['arguments']['field_message_user_ref_target_id']['table'] = 'field_data_field_message_user_ref';
  $handler->display->display_options['arguments']['field_message_user_ref_target_id']['field'] = 'field_message_user_ref_target_id';
  $handler->display->display_options['arguments']['field_message_user_ref_target_id']['ui_name'] = 'Groups';
  $handler->display->display_options['arguments']['field_message_user_ref_target_id']['default_action'] = 'default';
  $handler->display->display_options['arguments']['field_message_user_ref_target_id']['default_argument_type'] = 'og_user_groups';
  $handler->display->display_options['arguments']['field_message_user_ref_target_id']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_message_user_ref_target_id']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_message_user_ref_target_id']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['field_message_user_ref_target_id']['break_phrase'] = TRUE;
  $handler->display->display_options['path'] = 'group-messages';

  $export['message_private'] = $view;

  return $export;
}
