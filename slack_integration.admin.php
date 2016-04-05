<?php
/**
 * @file
 * Admin functions.
 */

/**
 * Admin settings form.
 *
 * @var array $form
 * @return array
 */
function slack_integration_config_form($form) {
  $form['slack_integration_token'] = array(
    '#type' => 'textfield',
    '#title' => t('Slack Api Token'),
    '#description' => 'For doing interactions with the slack API, you need a token. That token can be generated in the Slack API admin pages or can be created on OAuth login of the slack application.',
    '#default_value' => variable_get('slack_integration_token'),
    '#size' => 60,
    '#maxlength' => 128,
    '#required' => TRUE,
  );

  $form['slack_integration_channel'] = array(
    '#type' => 'textfield',
    '#title' => t('Slack Api Channel'),
    '#default_value' => variable_get('slack_integration_channel'),
    '#size' => 60,
    '#maxlength' => 128,
    '#required' => TRUE,
  );

  $form['slack_integration_messages_count'] = array(
    '#type' => 'textfield',
    '#title' => t('Slack Api Channel messages count'),
    '#default_value' => variable_get('slack_integration_messages_count', SLACK_API_MESSAGES_COUNT),
    '#size' => 60,
    '#maxlength' => 128,
    '#required' => FALSE,
  );
  return system_settings_form($form);
}
