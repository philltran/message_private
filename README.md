**D8 Status : Under Development (non functional)**

CONTENTS OF THIS FILE
---------------------
 * Introduction
 * Dependencies
 * Installation
 * Configuration
 * How to use
 * Security
 * Development and Test
 * Maintainers


INTRODUCTION
------------
A message type and entity reference fields, enabling sending and receiving 
private messages using The Message Stack. Messages of type "Private Message" can 
be sent by creating the private_message message instance with fields referencing 
user entities.

The message_private module includes the following.
+ A message type "Private Message" with entity reference field referencing users
+ A message view, message_private for "User Messages"


DEPENDENCIES
------------
The message_private module requires the following modules:
 * Message (https://drupal.org/project/message)
 * Message UI (https://drupal.org/project/message_ui)


INSTALLATION
------------
 * Install as you would normally install a contributed drupal module. See:
   https://drupal.org/documentation/install/modules-themes/modules-8
   for further information.


CONFIGURATION
-------------
Enabling Permissions: 
"View a new message instance for Private Message" &
"Create a new message instance for Private Message" for users needing to create
and view private messages.
To hide private messages from this view, 
you must override view provided by Message module:
admin/structure/views/view/message/edit

When enabled, the module will provide a new message type "Private Message" and a 
Message Private View.

Message Create Limits:
Message creation limits can be managed per role on the module settings form. A
message create limit can be set per interval per role. Users with more than one
role get the maximum limit by calculating the lowest time per message over each 
role. Users with the 'bypass private message access control' permission bypass
these limitations.


HOW TO USE
----------
To Create messages:
Visit /admin/content/message/create/private-message and Save the message to send
or
Visit the "Messages" tab detailed below and find the "Create a new message" 
local action.

To View inbox and sent messages:
Visit your user page at /user and find the "Messages" tab which displays 
received messages (Inbox local task), the "Sent" local task under that tab which
displays sent messages and the "Group" local task which displays group messages.
  /user/USER_ID/messages/inbox
  /user/USER_ID/messages/sent


SECURITY
--------
This module does not come with any security features out-of-the-box, but you can
easily configure your own, using methods and modules of your choice.

E.G:
Honeypot and timestamp methods: https://www.drupal.org/project/honeypot
CAPTCHA method: https://www.drupal.org/project/recaptcha


DEVELOPMENT AND TEST
--------------------
 * Threads / Conversations will be created: https://www.drupal.org/node/2504863. 
   An admin setting can be used to enable or disable threads to turn on/off 
   replies on all private messages (Reply, Reply All). Perhaps a css file will 
   need to be added for indentation / presentation. Integrate with MessageJS,
   nodeJS or socket.io.
 * Flag module on user entity to block/unblock users from messaging them
 * Flag module on message entity to show/hide (delete) messages from users own 
   display
 * Allow Operations links to display correctly on views, i.e. - show 'View' for
   users with view permissions. Not showing currently due to custom permissions.
 * Integrate with rolereference module or similar to provide sending to users
   within a certain role.
 * Tests should be created in a "tests" folder.


MAINTAINERS
-----------
Current maintainers:
 * Paul McCrodden - https://www.drupal.org/user/678774
