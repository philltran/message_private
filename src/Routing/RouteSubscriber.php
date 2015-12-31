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
    // Modify Message edit form to have private message access permissions.
    $route = $collection->get('message_ui.edit_message');
    if ($route) {
      $route->setRequirements(array(
        '_message_private_edit_access' => '{message}',
      ));
    }
    $route = $collection->get('message_ui.create_message');
    if ($route) {
      // @todo - check for message_type of 'private_message' and if so, set.
      // $route->setDefault('controller', '\Drupal\message_private\Controller\MessagePrivateController::showTypes');
    }
  }
}
