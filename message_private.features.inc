<?php
/**
 * Features definition file.
 */

/**
 * Implements hook_views_api().
 */
function message_private_views_api() {
  list($module, $api) = func_get_args();
  if ($module == "views" && $api == "views_default") {
    return array("version" => "3.0");
  }
}

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
          "format" : "plain_text",
          "safe_value" : "\u003Cp\u003EPrivate Message -\u003C\/p\u003E\n"
        },
        {
          "value" : "This message was sent by [message:user:mail]. Please login to [site:url]message\/[message:mid] to view your message.",
          "format" : "plain_text",
          "safe_value" : "\u003Cp\u003EThis message was sent by [message:user:mail]. Please login to [site:url]message\/[message:mid] to view your message.\u003C\/p\u003E\n"
        }
      ]
    }
  }');
  return $items;
}
