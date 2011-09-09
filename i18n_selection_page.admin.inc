<?php

function i18n_selection_page_admin() {

  $form = array();

  $options = array('0' => t('No'), '1' => t('Yes'));
  $form['i18n_selection_page_enable'] = array(
    '#title' => t('Redirect user to a language selection page if no language is detected ?'),
    '#type' => 'radios',
    '#default_value' => variable_get('i18n_selection_page_enable', 0),
    '#options' => $options,
    '#description' => t('Select yes if you want to enable the language selection page when no language is detected from URL.')
  );

  $options = array('0' => t('No'), '1' => t('Yes'), '2' => t('Yes and bypass the selection page.'));
  $form['i18n_selection_page_use_language_cookie'] = array(
    '#title' => t('Use cookie to remember your language ?'),
    '#type' => 'radios',
    '#default_value' => variable_get('i18n_selection_page_use_language_cookie', 0),
    '#options' => $options,
    '#description' => t('Select yes if you want to store the language in a cookie. If you want to use the cookie and bypass the selection page, select the third option.')
  );

  $options = array('0' => t('Disabled'), '1' => t('Template in theme'), '2' => 'Template only');
  $form['i18n_selection_page_redirect_type'] = array(
    '#title' => t('Select the way the Selection Page should work'),
    '#type' => 'select',
    '#multiple' => FALSE,
    '#default_value' => variable_get('i18n_selection_page_redirect_type', 0),
    '#options' => $options,
    '#description' => t('0: Does nothing.<br>1: Insert the content of the template in the current theme.<br>2: Display the template of the selection page only.')
  );

  $form['i18n_selection_page_blacklisted_paths'] = array(
    '#type' => 'textarea',
    '#title' => t('List of paths to blacklist'),
    '#default_value' => implode("\n", variable_get('i18n_selection_page_blacklisted_paths', array('admin', 'user'))),
    '#size' => 10,
    '#description' => t('Write on each line a path to blacklist from Language Selection Page processor')
  );

  $form['i18n_selection_page_cookie_lifetime'] = array(
    '#type' => 'textfield',
    '#title' => t('Cookie lifetime'),
    '#default_value' => variable_get('i18n_selection_page_cookie_lifetime', 2592000),
    '#size' => 10,
    '#description' => t('Cookie lifetime in seconds. (2592000 = 1 month)')
  );

  return system_settings_form($form);

}

function i18n_selection_page_admin_validate($form, &$form_state) {
  $form_state['values']['i18n_selection_page_blacklisted_paths'] = explode("\n", trim($form_state['values']['i18n_selection_page_blacklisted_paths']));
}

function i18n_selection_page_admin_submit($form, &$form_state) {

}