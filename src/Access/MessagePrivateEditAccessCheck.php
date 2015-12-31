<?php

/**
 * @file
 * Contains \Drupal\message_private\Access\MessagePrivateEditAccessCheck.
 */

namespace Drupal\message_private\Access;

use Drupal\Core\Access\AccessResult;
use Drupal\Core\Entity\EntityManagerInterface;
use Drupal\Core\Routing\Access\AccessInterface;
use Drupal\Core\Session\AccountInterface;
use Drupal\message\MessageInterface;

/**
 * Determines access to for message edit pages for private messages.
 *
 * @ingroup message_access
 */
class MessagePrivateEditAccessCheck implements AccessInterface {

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
   * Checks access to the message edit page for the message entity.
   *
   * @param \Drupal\Core\Session\AccountInterface $account
   *   The currently logged in account.
   * @param \Drupal\message\MessageInterface $message
   *
   * @return string
   *   A \Drupal\Core\Access\AccessInterface constant value.
   */
  public function access(AccountInterface $account, MessageInterface $message = NULL) {
    $access_control_handler = $this->entityManager->getAccessControlHandler('message');
    // If checking whether a node of a particular type may be created.
    if ($account->hasPermission('administer message private')
      || $account->hasPermission('bypass private message access control')) {
      return AccessResult::allowed()->cachePerPermissions();
    }

    // @todo: go through the below, previously message_private_access_control().

    // Get the message type from the function argument or from the message object.
    $type = $message->bundle();

    // If this is not a private message then use the message callback provided
    // by message_ui module.
    if ($type != 'private_message') {
      // No opinion.
      return AccessResult::neutral();
    }
    else {
      if ($account->hasPermission('bypass private message access control')) {
        return TRUE;
      }

      $operation = 'edit';

      // Verify that the user can apply the op.
      if ($account->hasPermission($operation . ' any message instance')
      || $account->hasPermission($operation . ' a ' . $type . ' message instance')
      ) {
        if ($type == 'private_message' && $operation != 'create') {
          // Check if the user is message author.
          /* @var $message \Drupal\message\Entity\Message */
          if ($message->getAuthorId() == $account->id()) {
            return TRUE;
          }
          $users = $message->get('field_message_user_ref');
          if ($users && is_array($users)) {
            foreach ($users as $user_ref) {
              if ($user_ref['target_id'] == $account->id()) {
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
  }
}
