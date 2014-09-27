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
A message type and entity reference fields to enable Message Stack to
send and receive private messages. Messages of type "Private Message" are
created and associated to user entities. The CRUD permissions associated to this
message type are based on these entity reference fields, with the exception of
CREATE, it uses the standard permission defined in the message_ui module.

The message_private module includes the following.
+ A message type "Private Message" with entity reference field referencing users
+ A message view, message_private for "User Messages"

The sub-module message_private_og includes the following.
+ An entity reference field for groups to associate messages to groups
+ A "Group Messages" display for the message_private view


DEPENDENCIES
------------
The message_private module requires the following modules:
 * Message (https://drupal.org/project/message)
 * Message UI (https://drupal.org/project/message_ui)
 * Message Notify (https://drupal.org/project/message_notify)
 * Token (https://www.drupal.org/project/token
 * Features (https://www.drupal.org/project/features)
 * Entity Reference (https://www.drupal.org/project/entityreference)

The message_private_og module requires the following modules:
 * OG (https://drupal.org/project/og)


INSTALLATION
------------
 * Install as you would normally install a contributed drupal module. See:
   https://drupal.org/documentation/install/modules-themes/modules-7
   for further information.
 * If using message_private_og, make sure you have created an OG group content
   type named "Group".


CONFIGURATION
-------------
Enable the permission "View a new message instance for Private Message" and
"Create a new message instance for Private Message" for users needing to create
and view private messages.

The module has no menu or modifiable settings.  There is not much
configuration.  When enabled, the module will provide a new message type
"Private Message" and a Message Private View.

When using the Message Private OG sub-module, the Group Messages display has
a contextual filter which filters by group ID of the logged in user. This is
developed taking into account that a content type called "Group" exists for all
Group instances. Anything other than this setup requires user customisation. You
must manually set the field_message_groups_ref contextual filter to use group
bundle to enable group filter on views.

HOW TO USE
----------
To create messages:
Visit /admin/content/message/create/private-message and Save the message to send

For received messages:
Visit your user page at /user and find the "Inbox" tab which displays received
messages /user/USER_ID/messages/inbox

For sent messages:
Visit your user page at /user and find the "Sent" tab which displays sent
messages /user/USER_ID/messages/sent

For group messages:
Visit your user page at /user and find the "Group" tab which displays group
messages /user/USER_ID/messages/group

SECURITY
--------
This module does not come with any security features out-of-the-box, but you can
easily configure your own using methods and modules of you choice.

Examples:

Honeypot and timestamp methods: https://www.drupal.org/project/honeypot
CAPTCHA method: https://www.drupal.org/project/recaptcha


DEVELOPMENT AND TEST
------------------
 * Create og permissions and permission checking for private messages.
 * Auto set the group in views code for group messages or provide warning.
 * Integrate with Help or Advanced Help module to hold all instructions.
 * Combine "Inbox", "Sent" and "Group" as sub-tabs under one called "Messages".
 * Add "Messages" tab to private_message entity view.
 * Add to admin screen the option to turn on or off email notifications. Also
   per user basis using a flag on user account.
 * Threads can be created using a hidden message reference field that gets
   populated using a reply link on each message. A new permission to reply to
   messages can be created if necessary. An admin screen can be used to enable
   or disable threads to turn on/off replies on all private messages
   (Reply, Reply All). A tpl.php template will need to be added for
   indentation/presentation.
 * Flag module could be used to show/hide messages from users own display
 * Research the benefits of Rules module integration and what could be provided.
 * Tests should be created in the 'tests' folder.

MAINTAINERS
-----------
Current maintainers:
 * Paul McCrodden - https://www.drupal.org/user/678774
