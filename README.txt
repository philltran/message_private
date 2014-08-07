CONTENTS OF THIS FILE
---------------------
 * Introduction
 * Requirements
 * Installation
 * Configuration
 * Troubleshooting
 * Maintainers

INTRODUCTION
------------
Customised message type and entity reference fields to enable Message Stack to
send and receive private messages. Messages of type "Private Message" are created
and associated to user entities. The CRUD permissions associated to this message type
are based on these entity reference fields, with the exception of CREATE, it uses the
standard permission defined in the message_ui module.

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

The message_private_og module requires the following modules:
 * OG (https://drupal.org/project/og)


INSTALLATION
------------
 * Install as you would normally install a contributed drupal module. See:
   https://drupal.org/documentation/install/modules-themes/modules-7
   for further information.
 * If using message_private_og, make sure you have created an OG group type named "Group".


CONFIGURATION
-------------
The module has no menu or modifiable settings.  There is no
configuration.  When enabled, the module will provide a new message type
"Private Message" and a Message Private View.


TROUBLESHOOTING
---------------
 * If the OG view does not display after reverting the view
   - Uninstall and reinstall the message_private_og module


MAINTAINERS
-----------
Current maintainers:
 * Paul McCrodden - https://www.drupal.org/user/678774