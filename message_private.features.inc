<?php
/**
 * Features definition file
 * message_private.features.inc.
 */

/**
 * Implements hook_default_message_type().
 */
function message_private_default_message_type() {
  $items = array();
  $items['private_message'] = entity_import('message_type', '{
    "name" : "private_message",
    "description" : "Private Message",
    "argument_keys" : [],
    "argument" : [],
    "category" : "message_type",
    "data" : {
      "token options" : { "clear" : 1 },
      "purge" : { "override" : 0, "enabled" : 0, "quota" : "", "days" : "" }
    },
    "language" : "en",
    "arguments" : null,
    "message_text" : { "und" : [
        {
          "value" : "Private Message - ",
          "format" : "filtered_html",
          "safe_value" : "\\u003Cp\\u003EPrivate Message -\\u003C\\/p\\u003E\\n"
        },
        {
          "value" : "This message was sent by [message:user:mail]. Please login to \\u003Ca href=\\u0022\\/message\\/[message:mid]\\u0022\\u003Eview your message\\u003C\\/a\\u003E.",
          "format" : "filtered_html",
          "safe_value" : "\\u003Cp\\u003EThis message was sent by [message:user:mail]. Please login to \\u003Ca href=\\u0022\\/message\\/[message:mid]\\u0022\\u003Eview your message\\u003C\\/a\\u003E.\\u003C\\/p\\u003E\\n"
        }
      ]
    },
    "rdf_mapping" : []
  }');
  return $items;
}
