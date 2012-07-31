<?php
/**
 * @file
 * This file contains all the custom functions needed for the module.
 */

/**
 * Return an array with the real language count from DB and the one from vars.
 *
 * @return array
 */
function _i18n_selection_page_check_language_count() {
  // We cannot rely on the variables from Features or system.
  $language_count = language_list('enabled');
  return array('db' => count($language_count[1]), 'vars' => variable_get('language_count', 1));
}

/**
 * All the error messages are saved in this function so they are the same
 * in the requirements page and/or the settings page.
 *
 * @return array
 */
function _i18n_selection_page_get_error_messages() {

  $args = func_get_args();
  $t = get_t();

  $messages['language_count'] = $t('There is a problem with the <b>language_count</b> variable.<br/>There are @language_count_db languages enabled in the database and @language_count_vars in the variable table (or from Features/Strongarm).<br/>This can lead to problems in your Drupal website.<br/>Please fix this problem before going further.', array('@language_count_db' => $args[1], '@language_count_vars' => $args[2]));
  $messages['language_enabled'] = $t('You should have more than <a href="@setting_url">one language</a> enabled to get the <b>Language Selection Page</b> working.', array('@setting_url' => $args[1]));
  $messages['language_prefix'] = $t('You should add a path prefix to <a href="@language_url">language @language_name</a> if you want to have it enabled in the <b>Language Selection Page</b>.', array('@language_url' => $args[1], '@language_name' => $args[2]));
  $messages['language_only_one'] = $t('There is only <a href="@link">one language enabled</a>.', array('@link' => $args[1]));
  $messages['language_all_good'] = $t('All your enabled languages have language prefix, all good.');

  return $args[0] ? $messages[$args[0]]: $messages;
}