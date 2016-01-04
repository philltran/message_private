<?php

/**
 * @file
 * Contains \Drupal\message_private\Routing\RouteSubscriber.
 */

namespace Drupal\message_private\Routing;

use Drupal\Core\Routing\RouteSubscriberBase;
use Symfony\Component\Routing\RouteCollection;

/**
 * Listens to the dynamic route events.
 */
class RouteSubscriber extends RouteSubscriberBase {

  /**
   * {@inheritdoc}
   */
  protected function alterRoutes(RouteCollection $collection) {
    // @todo - check for message_type of 'private_message' and if so, set.
    // Message viewing.
    $route = $collection->get('message_ui.show_message');
    if ($route) {
      $route->setRequirements(array(
        '_message_private_view_access' => '{message}',
      ));
    }
    // Message creation types list.
    $route = $collection->get('message_ui.create_message');
    if ($route) {
      // $route->setDefault('controller', '\Drupal\message_private\Controller\MessagePrivateController::showTypes');
    }
    // Message create by private message type.
    $route = $collection->get('message_ui.create_message_by_type');
    if ($route) {
      $route->setRequirements(array(
        '_message_private_add_access:' => 'message:private_message',
      ));
    }
    // Modify Message edit form to have private message access permissions.
    $route = $collection->get('message_ui.edit_message');
    if ($route) {
      $route->setRequirements(array(
        '_message_private_edit_access' => '{message}',
      ));
    }
    // Message deletion.
    $route = $collection->get('message_ui.delete_message');
    if ($route) {
      $route->setRequirements(array(
        '_message_private_delete_access' => '{message}',
      ));
    }
  }
}
