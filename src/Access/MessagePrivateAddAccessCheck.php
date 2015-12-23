<?php

/**
 * @file
 * Contains \Drupal\message_private\Access\MessagePrivateAddAccessCheck.
 */

namespace Drupal\message_private\Access;

use Drupal\Core\Access\AccessResult;
use Drupal\Core\Entity\EntityManagerInterface;
use Drupal\Core\Routing\Access\AccessInterface;
use Drupal\Core\Session\AccountInterface;
use Drupal\message\MessageTypeInterface;

/**
 * Determines access to for message add pages for private messages.
 *
 * @ingroup message_access
 */
class MessagePrivateAddAccessCheck implements AccessInterface {

  /**
   * The entity manager.
   *
   * @var \Drupal\Core\Entity\EntityManagerInterface
   */
  protected $entityManager;

  /**
   * Constructs a EntityCreateAccessCheck object.
   *
   * @param \Drupal\Core\Entity\EntityManagerInterface $entity_manager
   *   The entity manager.
   */
  public function __construct(EntityManagerInterface $entity_manager) {
    $this->entityManager = $entity_manager;
  }

  /**
   * Checks access to the message add page for the message type.
   *
   * @param \Drupal\Core\Session\AccountInterface $account
   *   The currently logged in account.
   * @param \Drupal\message\MessageTypeInterface $message_type
   *   (optional) The node type. If not specified, access is allowed if there
   *   exists at least one node type for which the user may create a node.
   *
   * @return string
   *   A \Drupal\Core\Access\AccessInterface constant value.
   */
  public function access(AccountInterface $account, MessageTypeInterface $message_type = NULL) {
    $access_control_handler = $this->entityManager->getAccessControlHandler('message');
    // If checking whether a node of a particular type may be created.
    if ($account->hasPermission('administer message private')
      || $account->hasPermission('bypass private message access control')) {
      return AccessResult::allowed()->cachePerPermissions();
    }
    if ($message_type) {
      return $access_control_handler->createAccess($message_type->id(), $account, [], TRUE);
    }
    // If checking whether a node of any type may be created.
    foreach ($this->entityManager->getStorage('message_type')->loadMultiple() as $message_type) {
      if (($access = $access_control_handler->createAccess($message_type->id(), $account, [], TRUE)) && $access->isAllowed()) {
        return $access;
      }
    }

    // @todo: go through the below, previously message_private_access_control().
    /**
    if (empty($user_obj)) {
    $user = \Drupal::currentUser();
    $account = \Drupal::entityManager()->getStorage('user')->load($user->uid);
    }
    else {
    $user = $user_obj;
    $account = \Drupal::entityManager()->getStorage('user')->load($user->uid);
    }

    // Get the message type from the function argument or from the message object.
    $type = is_object($message) ? $message->type : $message;

    // If this is not a private message then use the message callback provided by
    // message_ui module.
    if ($type != 'private_message') {
    return message_ui_access_control($operation, $message);
    }
    else {

    if ($account->hasPermission('bypass private message access control')) {
    return TRUE;
    }

    // Verify that the user can apply the op.
    if ($account->hasPermission($operation . ' any message instance')
    || $account->hasPermission($operation . ' a ' . $type . ' message instance')
    ) {
    if ($type == 'private_message' && $operation != 'create') {
    // Check if the user is message author.
    if ($message->uid == $account->uid) {
    return TRUE;
    }
    $users = field_get_items('message', $message, 'field_message_user_ref');
    if ($users && is_array($users)) {
    foreach ($users as $user_ref) {
    if ($user_ref['target_id'] == $account->uid) {
    return TRUE;
    }
    }
    }
    }
    else {
    return TRUE;
    }
    }
    }
    return FALSE;
     */

    // No opinion.
    return AccessResult::neutral();
  }

}
