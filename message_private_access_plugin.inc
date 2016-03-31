<?php
/**
 * Message Private views access plugin.
 */

/**
 * Access plugin allowing for user based access control.
 */
class message_private_access_plugin extends views_plugin_access {

  /**
   * Get the pulgin summary title.
   *
   * @return string
   */
  function summary_title() {
    return t('Message Private access plugin');
  }

  /**
   * Determine if the current user has access or not.
   *
   * @param $account
   * @return mixed
   */
  function access($account) {
    return message_private_inbox_access($account);
  }

  /**
   * Get the access callback function.
   *
   * @return array
   */
  function get_access_callback() {
    return array('message_private_inbox_access', array());
  }
}