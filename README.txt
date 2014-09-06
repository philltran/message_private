CONTENTS OF THIS FILE
---------------------
 * Introduction
 * Requirements
 * Installation
 * Configuration
 * Development & Test
 * Maintainers

INTRODUCTION
------------
A message type and entity reference fields to enable Message Stack to
send and receive private messages. Messages of type "Private Message" are created
and associated to user entities. The CRUD permissions associated to this message
type are based on these entity reference fields, with the exception of CREATE, it
uses the standard permission defined in the message_ui module.

The message_private module includes the following.
+ A message type "Private Message" with entity reference field referencing users
+ A message view, message_private for "User Messages"

The sub-module message_private_og includes the following.
+ An entity reference field for groups to associate messages to groups
+ A "Group Messages" display for the message_private view


REQUIREMENTS
------------
The message_private module requires the following modules:
 * Message (https://drupal.org/project/message)
 * Message UI (https://drupal.org/project/message_ui)
 * Message Notify (https://drupal.org/project/message_notify)

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
The module has no menu or modifiable settings.  There is not much
configuration.  When enabled, the module will provide a new message type
"Private Message" and a Message Private View.

When using the Message Private OG sub-module, the Group Messages display has
a contextual filter which filters by group ID of the logged in user. This is
developed taking into account that a content type called "Group" exists for all
Group instances. Anything other than this setup requires user customisation.


DEVELOPMENT & TEST
------------------
 * Combine "Inbox", "Sent" and "Group" as sub-tabs under one called "Messages"
 * Add "Messages" tab to message entity view
 * Add to admin screen the option to turn on or off email notifications. Also per
   user basis using a flag on user account.
 * Threads can be created using a hidden message reference field that gets
   populated using a reply link on each message. A new permission to reply to
   messages can be created if necessary. An admin screen can be used to enable or
   disable threads to turn on/off replies on all private messages
   (Reply, Reply All). A tpl.php template will need to be added for
   indentation/presentation.
 * Flag module could be used to show/hide messages from users own display
 * Tests should be created in the 'tests' folder

MAINTAINERS
-----------
Current maintainers:
 * Paul McCrodden - https://www.drupal.org/user/678774
