<?php
/**
 * @file
 * message_private_message.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function message_private_message_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_default_message_type().
 */
function message_private_message_default_message_type() {
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
          "value" : "A private message to users and organic groups.",
          "format" : "filtered_html",
          "safe_value" : "\\u003Cp\\u003EA private message to users and organic groups.\\u003C\\/p\\u003E\\n"
        }
      ]
    },
    "rdf_mapping" : []
  }');
  return $items;
}
