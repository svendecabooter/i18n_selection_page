<?php

function i18n_selection_page_admin() {

  $form = array();
  $error = false;

  if (variable_get('language_negotiation', LANGUAGE_NEGOTIATION_NONE) != 2) {
    drupal_set_message(t('The Language Selection Page settings are not available until %setting_name setting is not set to required "%setting_value" value. You should either disable the module or <a href="@setting_url">change your configuration</a>.', array(
    	'%setting_name' => t('Language negotiation'),
      '%setting_value' => t('Path prefix with language fallback.'),
      '@setting_url' => url('admin/settings/language/configure'),
    )), 'warning');
  }
  
  $lang_list       = language_list('enabled');
  $lang_list       = $lang_list[1];
  if (count($lang_list) < 2) {
    drupal_set_message(t('You should have more than <a href="@setting_url">one language</a> enabled to get the Language Selection Page working.', array(
      '@setting_url' => url('admin/settings/language'),
    )), 'warning');
    $error = true;
  }

  if ($error) return $form;

  $options = array('0' => t('No when language is found from cookie.'), '1' => t('No'), '2' => t('Yes'), );
  $form['i18n_selection_page_enable'] = array(
    '#title' => t('Redirect user to a language selection page if no language is detected from URL ?'),
    '#type' => 'radios',
    '#default_value' => variable_get('i18n_selection_page_enable', 0),
    '#options' => $options,
    '#description' => t('Select yes if you want to enable the language selection page when no language is detected from URL and/or Cookie.')
  );

  $options = array('0' => t('No'), '1' => t('Yes'));
  $form['i18n_selection_page_use_language_cookie'] = array(
    '#title' => t('Use cookie to remember your language ?'),
    '#type' => 'radios',
    '#default_value' => variable_get('i18n_selection_page_use_language_cookie', 0),
    '#options' => $options,
    '#description' => t('Select yes if you want to store the language in a cookie.')
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
