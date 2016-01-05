<?php
/**
 * @file
 * Contains \Drupal\message_ui\Controller\MessagePrivateController.
 */

namespace Drupal\message_private\Controller;

use Drupal\Core\Link;
use Drupal\Core\Url;
use Drupal\Core\Controller\ControllerBase;
use Drupal\message\MessageInterface;
use Drupal\message\Entity\MessageType;
use Drupal\message\Entity\Message;
use Drupal\Core\DependencyInjection\ContainerInjectionInterface;
use Drupal\message_ui\Controller\MessageViewController;
use Drupal\message_ui\MessageAccessControlHandler;


class MessagePrivateController extends ControllerBase implements ContainerInjectionInterface {

  /**
   * Constructs a MessageUiController object.
   */
  public function __construct() {
    // @todo: should I be using Dependency Injection here?
    $this->entityManager = \Drupal::entityManager();
  }

  /**
   * Display list of message types to create an instance for them.
   *
   */
  // @todo - remove note: message_private_create_new_message_instance_list in D7.
  public function getAllowedInstanceList() {
    // $access_controller = new MessageAccessControlHandler('message');
    // $allowed_types = $access_controller->userCreateMessageAccess();

    // @todo - replace this line with access controlled type list:
    $allowed_types = MessageType::loadMultiple();

    if ($types = MessageType::loadMultiple()) {
      foreach ($types as $type) {
        if ($allowed_types || (is_array($allowed_types) && array_key_exists($type, $allowed_types))) {
          return $allowed_types;
        }
      }
    }
    return FALSE;
  }

  /**
   * Generates output of all message type entities with permission to create.
   *
   * @return array
   *   An array as expected by drupal_render().
   */
  public function showTypes() {
    // $account = $this->currentUser();

    // @todo add access control for message_type, see message_ui_access_control.

    $items = array();
    // @todo : Use the following or MessageType's method? $this->entityManager()->getStorage('message_type')->loadMultiple()
    // Only use node types the user has access to.
    // @todo - override the path for private messages, or is there a better way?
    foreach ($this->getAllowedInstanceList() as $type => $entity) {
      if ($type != 'private_message') {
        // @todo - get access control working below.
        // \Doctrine\Common\Util\Debug::dump($this->entityManager()->getAccessControlHandler('message')->createAccess($type->id()));
        // if ($this->entityManager()->getAccessControlHandler('message')->createAccess($type->id())) {
        /* @var $entity MessageType */
        $url = Url::fromUri('internal:/admin/content/messages/create/' . str_replace('_', '-', $type));
        $items[] = array(
          'type' => $type,
          'name' => $entity->label(),
          'internal_link' => Link::fromTextAndUrl(ucfirst(str_replace('_', ' ', $type)), $url),
        );
        //\Doctrine\Common\Util\Debug::dump($content);
        // }
      }
      else {
        // Create link to customised menu item for private_message create.
        /* @var $entity MessageType */
        $url = Url::fromUri('internal:/message/create/' . str_replace('_', '-', $type));
        $items[] = array(
          'type' => $type,
          'name' => $entity->label(),
          'internal_link' => Link::fromTextAndUrl(ucfirst(str_replace('_', ' ', $type)), $url),
        );
      }
    }

    // Bypass the admin/content/messages/create listing if only one content type is available.
    /* if (count($content) == 1) {
      $type = array_shift($content);
      return $this->redirect('message_ui.create_message_by_type', array('message_type' => $type->id()));
    } */

    if ($items) {
      return array(
        '#theme' => 'instance_item_list',
        '#items' => $items,
        '#type' => 'ul'
      );
    }
    else {
      $url = Url::fromRoute('message.type_add');
      return t("There are no messages types. You can create a new message type <a href='$url'>here</a>.");
    }
  }
}
