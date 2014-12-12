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

  $form['message_private_message_limit'] = array(
    '#type' => 'checkbox',
    '#title' => t('Limit Message Create By Role'),
    '#default_value' => variable_get('message_private_message_limit', FALSE),
    '#description' => t('Impose a message creation limit per interval. Users with multiple roles, get the highest limit from these roles'),
  );

  $form['message_private_message_interval_limit'] = array(
    '#title' => t('Message interval limits'),
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#states' => array(
    'invisible' => array(
      ':input[name="message_private_message_limit"]' => array('checked' => FALSE),
      ),
    ),
  );

  // Add a default fieldset.
  $form['message_private_message_interval_limit'][MESSAGE_PRIVATE_DEFAULT_INDEX] = array(
    '#type' => 'fieldset',
    '#title' => 'Default limit',
    '#description' => t('Applies to all roles with blank entries below')
  );

  $form['message_private_message_interval_limit'][MESSAGE_PRIVATE_DEFAULT_INDEX]['limit'] = array(
    '#type' => 'textfield',
    '#title' => t('Limit'),
    '#default_value' => variable_get('message_private_default_limit', TRUE),
    '#description' => t('Enter a message limit ' . MESSAGE_PRIVATE_MESSAGE_LIMIT_MIN . ' - ' . MESSAGE_PRIVATE_MESSAGE_LIMIT_MAX),
  );

  $form['message_private_message_interval_limit'][MESSAGE_PRIVATE_DEFAULT_INDEX]['interval'] = array(
    '#type' => 'textfield',
    '#title' => t('Interval'),
    '#default_value' => variable_get('message_private_default_interval', TRUE),
    '#description' => t('Enter an interval in minutes ' . MESSAGE_PRIVATE_MESSAGE_INTERVAL_MIN . ' - ' . MESSAGE_PRIVATE_MESSAGE_INTERVAL_MAX),
  );

  foreach(user_roles() as $id => $role) {
    $role_name = str_replace(' ', '_', $role);
    $limit_name = 'message_private_' . $role_name . '_limit';
    $interval_name = 'message_private_' . $role_name . '_interval';

    $form['message_private_message_interval_limit'][$id] = array(
      '#type' => 'fieldset',
      '#title' => $role,
    );
    $form['message_private_message_interval_limit'][$id][$limit_name] = array(
      '#type' => 'textfield',
      '#title' => t('Limit'),
      '#default_value' => variable_get($limit_name),
      '#description' => t('Enter a message limit ' . MESSAGE_PRIVATE_MESSAGE_LIMIT_MIN . ' - ' . MESSAGE_PRIVATE_MESSAGE_LIMIT_MAX),
    );
    $form['message_private_message_interval_limit'][$id][$interval_name] = array(
      '#type' => 'textfield',
      '#title' => t('Interval'),
      '#default_value' => variable_get($interval_name),
      '#description' => t('Enter an interval in minutes ' . MESSAGE_PRIVATE_MESSAGE_INTERVAL_MIN . ' - ' . MESSAGE_PRIVATE_MESSAGE_INTERVAL_MAX),
    );
  }

  return system_settings_form($form);
}

/**
 * Validate the admin settings form.
 *
 * @param $form
 * @param $form_state
 */
function message_private_admin_settings_validate($form, &$form_state) {

  foreach (user_roles() as $id => $role) {
    $role_name = str_replace(' ', '_', $role);
    $limit_name = 'message_private_' . $role_name . '_limit';
    $interval_name = 'message_private_' . $role_name . '_interval';

    // Check both textfields per fieldset are set, give error if only 1 is set.
    if (isset($form_state['values'][$limit_name]) && isset($form_state['values'][$interval_name])) {
      // Check is numeric and between the boundaries.
      if (!ctype_digit($form_state['values'][$limit_name])
        || $form_state['values'][$limit_name] > MESSAGE_PRIVATE_MESSAGE_LIMIT_MAX
        || $form_state['values'][$limit_name] < MESSAGE_PRIVATE_MESSAGE_LIMIT_MIN) {
        form_error($form['message_private_message_interval_limit'][$id][$limit_name],
          t('Enter a numerical message limit between '
            . MESSAGE_PRIVATE_MESSAGE_LIMIT_MIN . ' - ' . MESSAGE_PRIVATE_MESSAGE_LIMIT_MAX . '.'));
      }
      // Check is numeric and between the boundaries.
      if (!ctype_digit($form_state['values'][$interval_name])
        || $form_state['values'][$interval_name] > MESSAGE_PRIVATE_MESSAGE_INTERVAL_MAX
        || $form_state['values'][$interval_name] < MESSAGE_PRIVATE_MESSAGE_INTERVAL_MIN) {
        form_error($form['message_private_message_interval_limit'][$id][$interval_name],
          t('Enter a numerical interval in minutes between '
            . MESSAGE_PRIVATE_MESSAGE_INTERVAL_MIN . ' - ' . MESSAGE_PRIVATE_MESSAGE_INTERVAL_MAX . '.'));
      }
    } elseif (isset($form_state['values'][$limit_name]) || isset($form_state['values'][$interval_name])) {
      form_error($form['message_private_message_interval_limit'][$id][$limit_name], t('Both a limit and interval value are required.'));
      form_error($form['message_private_message_interval_limit'][$id][$interval_name]);
    }
  }
}
