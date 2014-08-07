<?php
/**
 * @file
 * message_private.features.inc
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
      "token options" : { "clear" : 0 },
      "purge" : { "override" : 0, "enabled" : 0, "quota" : "", "days" : "" }
    },
    "language" : "en",
    "arguments" : null,
    "message_text" : { "en" : [
        {
          "value" : "A private message between drupal entities.",
          "format" : "filtered_html",
          "safe_value" : "\\u003Cp\\u003EA private message between drupal entities.\\u003C\\/p\\u003E\\n"
        }
      ]
    },
    "rdf_mapping" : []
  }');
  return $items;
}
