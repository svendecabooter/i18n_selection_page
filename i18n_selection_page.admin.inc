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

  $lang_list = language_list('enabled');
  $lang_list = $lang_list[1];
  if (count($lang_list) < 2) {
    drupal_set_message(t('You should have more than <a href="@setting_url">one language</a> enabled to get the Language Selection Page working.', array(
                                                                                                                                                       '@setting_url' => url('admin/settings/language'),
                                                                                                                                                  )), 'warning');
    $error = true;
  }

  if ($error) return $form;

  $options = array('0' => t('No but redirect if language is found from cookie.'), '1' => t('No'), '2' => t('Yes'),);
  $form['i18n_selection_page_enable'] = array(
    '#title' => t('Redirect to a language selection page if no language is detected from URL and/or Cookie ?'),
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
    '#description' => t('Select yes if you want to store the language in a cookie.<br>The cookie is <i>' . LANGUAGE_COOKIE_KEY . '</i>')
  );

  $options = array('0' => t('Template in theme'), '1' => 'Template only');
  $form['i18n_selection_page_redirect_type'] = array(
    '#title' => t('Select the way the Selection Page should work'),
    '#type' => 'select',
    '#multiple' => FALSE,
    '#default_value' => variable_get('i18n_selection_page_redirect_type', 1),
    '#options' => $options,
    '#description' => t('<b>Template in theme</b>: Insert the Language Selection Page in the template in the current theme.<br><b>Template only</b>: Display the Selection Page template only.<br>Create a file named <i>i18n_selection_page.tpl.php</i> in your theme directory if you want to override it.')
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

  $form['#submit'][] = 'i18n_selection_page_admin_submit';

  return system_settings_form($form);

}

function i18n_selection_page_admin_validate($form, &$form_state) {
  $form_state['values']['i18n_selection_page_blacklisted_paths'] = explode("\n", trim($form_state['values']['i18n_selection_page_blacklisted_paths']));
}

function i18n_selection_page_admin_submit($form, &$form_state) {
  if ($form_state['values']['i18n_selection_page_use_language_cookie'] == 0) {
    setcookie(LANGUAGE_COOKIE_KEY, NULL, 0, '/');
    drupal_set_message(t('I18N Selection Page Cookie removed.'));
  }
}
