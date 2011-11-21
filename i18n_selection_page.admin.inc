<?php
/**
 * @file
 * The admin page of the language selection page module.
 */
/**
 * The admin page form.
 *
 * @return array
 */
function i18n_selection_page_admin() {
  module_load_include('inc', 'i18n_selection_page', 'includes/i18n_selection_page.helpers');

  $options = array('1' => t('Yes but redirect to the correct page with language found from cookie if it exists'), '2' => t('No'), '4' => t('Yes'));
  $form['i18n_selection_page_enable'] = array(
    '#title' => t('Redirect to a language selection page if no language is detected from URL and/or Cookie ?'),
    '#type' => 'radios',
    '#default_value' => variable_get('i18n_selection_page_enable', 2),
    '#options' => $options,
    '#description' => t('Select yes if you want to enable the I18N Selection Page when no language is detected from URL and/or Cookie.')
  );

  $options = array('32' => t('Template in theme'), '64' => 'Template only');
  $form['i18n_selection_page_redirect_type'] = array(
    '#title' => t('Select the way the Selection Page should work'),
    '#type' => 'select',
    '#multiple' => FALSE,
    '#default_value' => variable_get('i18n_selection_page_redirect_type', 64),
    '#options' => $options,
    '#description' => t('<b>Template in theme</b>: Insert the I18N Selection Page body as <i>$content</i> in the current theme.
                         <br/><b>Template only</b>: Display the I18N Selection Page template only.
                         <br/>Create a file named <i>i18n_selection_page.tpl.php</i> in your theme directory if you want to override the full page.
                         <br/>Create a file named <i>i18n_selection_page_body.tpl.php</i> in your theme directory if you want to override the body only.')
  );

  $form['i18n_selection_page_blacklisted_paths'] = array(
    '#type' => 'textarea',
    '#title' => t('List of paths to blacklist'),
    '#default_value' => implode("\n", variable_get('i18n_selection_page_blacklisted_paths', array('admin', 'user', 'admin/*', 'admin*', 'node/add/*', 'node/*/edit'))),
    '#size' => 10,
    '#description' => t('Write on each line a path to blacklist from Language Selection Page processor')
  );

  $form['#submit'][] = 'i18n_selection_page_admin_submit';

  drupal_flush_all_caches();

  return system_settings_form($form);
}

function i18n_selection_page_admin_validate($form, &$form_state) {
  $form_state['values']['i18n_selection_page_blacklisted_paths'] = explode("\n", trim($form_state['values']['i18n_selection_page_blacklisted_paths']));
}

function i18n_selection_page_admin_submit($form, &$form_state) {

}
