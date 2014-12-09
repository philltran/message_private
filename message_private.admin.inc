<?php

/**
 * Get the admin settings form for message_private.
 *
 * @return mixed
 *   Form array returned from system_settings_form().
 */
function message_private_admin_settings() {

  $form['message_private_email_notifications'] = array(
    '#type' => 'checkbox',
    '#title' => t('Message Private Email Notifications'),
    '#default_value' => variable_get('message_private_email_notifications', TRUE),
    '#description' => t('Global On / Off checkbox for emails notifying users of a new private message'),
  );

  return system_settings_form($form);
}
