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
      "token options" : { "clear" : 0 },
      "purge" : { "override" : 0, "enabled" : 0, "quota" : "", "days" : "" }
    },
    "language" : "en",
    "arguments" : null,
    "message_text" : [],
    "rdf_mapping" : []
  }');
  return $items;
}
