<?php

/**
 * @file
 * Definition of Drupal\message_private\Tests\MessagePrivatePermissions.
 */

namespace Drupal\message_private\Tests;

use Drupal\Component\Render\FormattableMarkup;
use Drupal\user\Entity\Role;
use Drupal\user\RoleInterface;
use Drupal\message\Tests\MessageTestBase;
use Drupal\message\Entity\Message;

/**
 * Testing the private message access use case.
 *
 * @group Message Private
 */
class MessagePrivatePermissions extends MessageTestBase {

  /**
   * The message access control handler.
   *
   * @var \Drupal\Core\Entity\EntityAccessControlHandlerInterface
   */
  protected $accessHandler;

  /**
   * The user account object.
   * @var
   */
  protected $account;

  /**
   * The user role.
   * @var
   */
  protected $rid;

  /**
   * Modules to enable.
   *
   * @var array
   */
  public static $modules = ['message', 'message_notify', 'message_ui', 'message_private'];

  public static function getInfo() {
    return array(
      'name' => 'Message Private permissions',
      'description' => 'Testing the use case of message_private_message_access hook.',
      'group' => 'Message Private',
    );
  }

  /**
   * {@inheritdoc}
   */
  function setUp() {
    parent::setUp();

    $this->accessHandler = \Drupal::entityManager()->getAccessControlHandler('message');

    $this->account = $this->drupalCreateUser();

    // Load 'authenticated' user role.
    $this->rid = Role::load(RoleInterface::AUTHENTICATED_ID)->id();
  }

  /**
   * Test private message workflow.
   */
  function testMessageUiPermissions() {
    $this->drupalLogin($this->account); // User login.
    $create_url = '/message/add/private_message'; // Set our create url.

    // Verify the user can't create the message.
    $this->drupalGet($create_url);
    $this->assertResponse(403, t("The user can't create a private message."));

    // Grant and check create permissions for a message.
    $this->grantMessagePrivatePermission('create');
    $this->drupalGet($create_url);

    // If we get a valid response, create a message.
    if ($this->assertResponse(200, t("The user can create a private message."))) {
      // Create a message at current page / url.
      $this->drupalPostForm(NULL, array(), t('Save'));
    }

    $msg_url = '/message/1'; // Create the message url.

    // Verify the user now can see the text.
    $this->grantMessagePrivatePermission('view');
    $this->drupalGet($msg_url);
    $this->assertResponse(200, "The user can view a private message.");

    // Verify can't edit the message.
    $this->drupalGet($msg_url . '/edit');
    $this->assertResponse(403, "The user can't edit a private message.");

    // Grant permission to the user.
    $this->grantMessagePrivatePermission('edit');
    $this->drupalGet($msg_url . '/edit');
    $this->assertResponse(200, "The user can't edit a private message.");

    // Verify the user can't delete the message.
    $this->drupalGet($msg_url . '/delete');
    $this->assertResponse(403, "The user can't delete the private message");

    // Grant the permission to the user.
    $this->grantMessagePrivatePermission('delete');
    $this->drupalPostForm($msg_url . '/delete', array(), t('Delete'));
    $this->assertResponse(200, "The user can delete a private message.");

    // Set up admin url.
    $admin_url = '/admin/config/system/message-private';
    // User has no permission for the admin page - verify access denied.
    $this->drupalGet($admin_url);
    $this->assertResponse(403, t("The user cannot administer message_private."));

    user_role_grant_permissions($this->rid, array('administer message private'));
    $this->drupalGet($admin_url);
    $this->assertResponse(200, "The user can administer message_private.");

    // Create a new user with the bypass access permission and verify the bypass.
    $this->drupalLogout();
    $user = $this->drupalCreateUser(array('bypass private message access control'));

    // Verify the user can by pass the message access control.
    $this->drupalLogin($user);
    $this->drupalGet($create_url);
    $this->assertResponse(200, 'The user can bypass the private message access control.');
  }

  /**
   * Grant to the user a specific permission.
   *
   * @param $operation
   *  The type of operation - create, update, delete or view.
   */
  private function grantMessagePrivatePermission($operation) {
    user_role_grant_permissions($this->rid, array($operation . ' private_message message'));
  }

  /**
   * Checking the message_private_message_access hook.
   */
  public function testMessagePrivateAccessHook() {
    $this->drupalLogin($this->account);

    // Setting up the operation and the expected value from the access callback.
    $permissions = array(
      'create' => TRUE,
      'view' => TRUE,
      'delete' => FALSE,
      'update' => FALSE,
    );

    // Get the message type and create an instance.
    $message_type = $this->loadMessageType('private_message');
    /* @var $message Message */
    $message = Message::create(array('type' => $message_type->id()));
    $message->setOwner($this->account);
    $message->save();

    foreach ($permissions as $op => $value) {
      // When the hook access of the dummy module will get in action it will
      // check which value need to return. If the access control function will
      // return the expected value then we know the hook got in action.
      $message->{$op} = $value;
      $params = array(
        '@operation' => $op,
        '@value' => $value,
      );

      $this->assertEqual($value, $this->accessHandler->access($message, $op, $this->account), new FormattableMarkup('The hook return @value for @operation', $params));
    }
  }
}
