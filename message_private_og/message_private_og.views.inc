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

  /* Display: OG Messages */
  $handler = $view->new_display('page', 'OG Messages', 'page_2');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'OG Messages';
  $handler->display->display_options['display_description'] = 'Private messages associates to the groups the current user is a member of.';
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
  $handler->display->display_options['path'] = 'admin/messages-og';
  $handler->display->display_options['menu']['title'] = 'Messages';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;

  $export['message_private'] = $view;

  return $export;
}
