<?php

/**
 * @file
 *
 * Contains \Drupal\message_private\Form\MessagePrivateSettingsForm.
 */

namespace Drupal\message_private\Form;

use Drupal\Core\Config\ConfigFactoryInterface;
use Drupal\Core\Entity\EntityManagerInterface;
use Drupal\Core\Form\ConfigFormBase;
use Drupal\Core\Form\FormStateInterface;
use Symfony\Component\DependencyInjection\ContainerInterface;

/**
 * Configure file system settings for this site.
 */
class MessagePrivateSettingsForm extends ConfigFormBase {

  /**
   * The entity manager object.
   *
   * @var \Drupal\Core\Entity\EntityManagerInterface
   */
  protected $entityManager;

  /**
   * {@inheritdoc}
   */
  public function getFormId() {
    return 'message_private_system_settings';
  }

  /**
   * {@inheritdoc}
   */
  protected function getEditableConfigNames() {
    return array('message_private.settings');
  }

  /**
   * Holds the name of the keys we holds in the variable.
   */
  public function defaultKeys() {
    // @todo - update with message_private keys.
    return array(
      'purge_enable',
      'purge_quota',
      'purge_days',
      'delete_on_entity_delete',
    );
  }

  /**
   * {@inheritdoc}
   */
  public static function create(ContainerInterface $container) {
    return new static(
      $container->get('config.factory'),
      $container->get('entity.manager')
    );
  }

  /**
   * Constructs a \Drupal\system\ConfigFormBase object.
   *
   * @param \Drupal\Core\Config\ConfigFactoryInterface $config_factory
   *   The factory for configuration objects.
   * @param \Drupal\Core\Entity\EntityManagerInterface $entity_manager
   *   The entity manager object.
   */
  public function __construct(ConfigFactoryInterface $config_factory, EntityManagerInterface $entity_manager) {
    $this->setConfigFactory($config_factory);
    $this->entityManager = $entity_manager;
  }

  /**
   * {@inheritdoc}
   */
  public function buildForm(array $form, FormStateInterface $form_state) {
    $config = $this->config('message_private.settings');

    // Global email notifications on/off checkbox.
    $form[MESSAGE_PRIVATE_EMAIL_NOTIFICATIONS] = array(
     '#type' => 'checkbox',
     '#title' => t('Message Private Email Notifications'),
     '#default_value' => variable_get(MESSAGE_PRIVATE_EMAIL_NOTIFICATIONS, TRUE),
     '#description' => t('Global On / Off checkbox for emails notifying users of a new private message'),
    );

    // Local action links on/off checkbox.
    $form[MESSAGE_PRIVATE_LOCAL_ACTION] = array(
      '#type' => 'checkbox',
      '#title' => t('Disable Create a New Message local action links'),
      '#default_value' => variable_get(MESSAGE_PRIVATE_LOCAL_ACTION, FALSE),
      '#description' => t('Disable local action links to create new message on user pages.'),
    );

     // Role based message create limit on/off checkbox.
     $form[MESSAGE_PRIVATE_MESSAGE_LIMIT] = array(
         '#type' => 'checkbox',
         '#title' => t('Limit Message Create By Role'),
         '#default_value' => variable_get(MESSAGE_PRIVATE_MESSAGE_LIMIT, FALSE),
         '#description' => t('Impose a message creation limit per interval. Users with multiple roles, get the highest limit from these roles'),
     );


    // Conditional fieldset for all message limitation settings.
    $form['interval_limit'] = array(
      '#title' => t('Message interval limits'),
      '#type' => 'fieldset',
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
      '#states' => array(
        'invisible' => array(
          ':input[name="' . MESSAGE_PRIVATE_MESSAGE_LIMIT . '"]' => array('checked' => FALSE),
        ),
      ),
    );

    // Add a default fieldset.
    $form['interval_limit'][MESSAGE_PRIVATE_DEFAULT_INDEX] = array(
      '#type' => 'fieldset',
      '#title' => 'Default limit',
      '#description' => t('Applies to all roles with blank entries below'),
      '#collapsible' => TRUE,
      '#collapsed' => FALSE,
    );

    $form['interval_limit'][MESSAGE_PRIVATE_DEFAULT_INDEX][MESSAGE_PRIVATE_DEFAULT_LIMIT] = array(
      '#type' => 'textfield',
      '#title' => t('Limit'),
      '#default_value' => variable_get(MESSAGE_PRIVATE_DEFAULT_LIMIT),
      '#description' => t('Enter a message limit') . ' ' . MESSAGE_PRIVATE_MESSAGE_LIMIT_MIN . ' - ' . MESSAGE_PRIVATE_MESSAGE_LIMIT_MAX,
    );


     $form['interval_limit'][MESSAGE_PRIVATE_DEFAULT_INDEX][MESSAGE_PRIVATE_DEFAULT_INTERVAL] = array(
       '#type' => 'textfield',
       '#title' => t('Interval'),
       '#default_value' => variable_get(MESSAGE_PRIVATE_DEFAULT_INTERVAL),
       '#description' => t('Enter an interval in minutes') . ' ' . MESSAGE_PRIVATE_MESSAGE_INTERVAL_MIN . ' - ' . MESSAGE_PRIVATE_MESSAGE_INTERVAL_MAX,
     );


    // Generate variable names for all roles used with get/set in admin form.
    foreach (user_roles() as $id => $role) {
      $role_name = str_replace(' ', '_', $role);
      $limit_name = 'message_private_' . $role_name . '_limit';
      $interval_name = 'message_private_' . $role_name . '_interval';

      $form['interval_limit'][$id] = array(
        '#type' => 'fieldset',
        '#title' => $role,
        '#collapsible' => TRUE,
        '#collapsed' => TRUE,
      );

      $form['interval_limit'][$id][$limit_name] = array(
        '#type' => 'textfield',
        '#title' => t('Limit'),
        '#default_value' => variable_get($limit_name),
        '#description' => t('Enter a message limit') . ' ' . MESSAGE_PRIVATE_MESSAGE_LIMIT_MIN . ' - ' . MESSAGE_PRIVATE_MESSAGE_LIMIT_MAX,
      );

      $form['interval_limit'][$id][$interval_name] = array(
        '#type' => 'textfield',
        '#title' => t('Interval'),
        '#default_value' => variable_get($interval_name),
        '#description' => t('Enter an interval in minutes') . ' ' . MESSAGE_PRIVATE_MESSAGE_INTERVAL_MIN . ' - ' . MESSAGE_PRIVATE_MESSAGE_INTERVAL_MAX,
      );
    }

    return parent::buildForm($form, $form_state);
  }

  /**
   * {@inheritdoc}
   */
  public function submitForm(array &$form, FormStateInterface $form_state) {
    $config = $this->config('message_private.settings');

    foreach ($this->defaultKeys() as $key) {
      $config->set($key, $form_state->getValue($key));
    }

    $config->save();

    parent::submitForm($form, $form_state);
  }

  /**
   * {@inheritdoc}
   */
  public function validateForm(array &$form, FormStateInterface $form_state) {
    if (strlen($form_state->getValue('phone_number')) < 3) {
      $form_state->setErrorByName('phone_number', $this->t('The phone number is too short. Please enter a full phone number.'));
    }
    // Validate the default fieldset values.
    $this->validateFieldset($form_state,
      $form['interval_limit'][MESSAGE_PRIVATE_DEFAULT_INDEX][MESSAGE_PRIVATE_DEFAULT_LIMIT],
      $form['interval_limit'][MESSAGE_PRIVATE_DEFAULT_INDEX][MESSAGE_PRIVATE_DEFAULT_INTERVAL],
      $form_state->getValue(MESSAGE_PRIVATE_DEFAULT_LIMIT),
      $form_state->getValue(MESSAGE_PRIVATE_DEFAULT_INTERVAL)
    );
    // Cycle through the settings for each role and validate.
    foreach (user_roles() as $id => $role) {
      $role_name = str_replace(' ', '_', $role);
      $limit_name = 'message_private_' . $role_name . '_limit';
      $interval_name = 'message_private_' . $role_name . '_interval';

      $this->validateFieldset(
        $form_state,
        $form['interval_limit'][$id][$limit_name],
        $form['interval_limit'][$id][$interval_name],
        $form_state['values'][$limit_name],
        $form_state['values'][$interval_name]
      );
    }
  }

  /**
   * Validate limit and interval values and show any errors on the form elements.
   *
   * @param \Drupal\Core\Form\FormStateInterface $form_state
   * @param mixed $limit_element
   *   Limit form element reference.
   * @param mixed $interval_element
   *   Interval form element reference.
   * @param string|int $limit
   *   Limit value to validate.
   * @param string|int $interval
   *   Interval value to validate.
   */
  private function validateFieldset(FormStateInterface $form_state, &$limit_element, &$interval_element, $limit, $interval) {
    // Validate role settings, check both textfields per fieldset are set.
    if (!empty($limit) && !empty($interval)) {
      // Check is numeric and between the boundaries.
      if (!ctype_digit($limit) || $limit > MESSAGE_PRIVATE_MESSAGE_LIMIT_MAX || $limit < MESSAGE_PRIVATE_MESSAGE_LIMIT_MIN) {
        $form_state->setErrorByName($limit_element,
          t('Enter a numerical message limit between') . ' '
          . MESSAGE_PRIVATE_MESSAGE_LIMIT_MIN . ' - ' . MESSAGE_PRIVATE_MESSAGE_LIMIT_MAX . '.');
      }
      // Check is numeric and between the boundaries.
      if (!ctype_digit($interval) || $interval > MESSAGE_PRIVATE_MESSAGE_INTERVAL_MAX || $interval < MESSAGE_PRIVATE_MESSAGE_INTERVAL_MIN) {
         $form_state->setErrorByName($interval_element,
          t('Enter a numerical interval in minutes between') . ' '
          . MESSAGE_PRIVATE_MESSAGE_INTERVAL_MIN . ' - ' . MESSAGE_PRIVATE_MESSAGE_INTERVAL_MAX . '.');
      }
    }
    elseif (!empty($limit) || !empty($interval)) {
      // Show error if only 1 textfield is set in each fieldset.
      $form_state->setErrorByName($limit_element, t('Both a limit and interval value are required.'));
      $form_state->setErrorByName($interval_element);
    }
  }
}
