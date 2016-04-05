<?php
/**
 * @file
 * Functions for integration with Slack.
 */

/**
 * Get content for block with messages.
 */
function slack_integration_block_content() {
  $messages = slack_integration_get_messages();
  $output = theme('slack_integration_block', array('messages' => $messages));
  return $output;
}

/**
 * Get messages using API.
 */
function slack_integration_get_messages() {
  $slack_messages = slack_integration_get_messages_data();
  drupal_alter('slack_integration_messages', $slack_messages);

  return $slack_messages;
}

/**
 * Get raw data from api.
 */
function slack_integration_get_messages_data() {
  $messages = array();
  $data = array(
    'channel' => variable_get('slack_integration_channel'),
    'count' => variable_get('slack_integration_messages_count', SLACK_API_MESSAGES_COUNT),
  );

  if (empty($data['channel'])) {
    watchdog('slack_integration', 'You must to specify the channel id', array(), WATCHDOG_ERROR);
    return $messages;
  }

  $slack_data = slack_integration_request('channels.history', $data);

  if (empty($slack_data['messages'])) {
    return $messages;
  }

  $messages = $slack_data['messages'];
  return $messages;
}

/**
 * Request helper.
 *
 * @var string $method
 * @var array $data
 * @return array
 */
function slack_integration_request($method, $data) {
  $slack_data = null;
  $data += array(
    'token' => variable_get('slack_integration_token'),
  );

  if (empty($data['token'])) {
    watchdog('slack_integration', 'You must to specify the token', array(), WATCHDOG_ERROR);
    return $slack_data;
  }

  // Build query.
  $api_url = SLACK_API_URL . $method;
  $url = url($api_url, array('query' => $data));
  $result = drupal_http_request($url);
  // Check response.
  if ($result->code == SLACK_API_HTTP_OK) {
    $slack_data = json_decode($result->data, TRUE);
  }
  else {
    watchdog('slack_integration', 'Api error. Check Slack settings', array(), WATCHDOG_ERROR);
  }

  return $slack_data;
}
