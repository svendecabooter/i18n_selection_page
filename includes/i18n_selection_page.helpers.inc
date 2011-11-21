<?php
/**
 * @file
 * This file contains all the custom functions needed for the module.
 */
/**
 * Custom function to parse a URL.
 *
 * @return array
 */
function _i18n_selection_page_parse_url_custom() {


  $array_url = parse_url($_REQUEST['q'] . '?' . $_SERVER['QUERY_STRING']);
  if (isset($array_url['query'])) {
    parse_str($array_url['query'], $array_url['query']);
  }
  return $array_url;
}

/**
 * Custom function who return the first argument which is not null.
 * If all arguments are null, it returns the default lang.
 *
 * @return object
 */
function _i18n_resolve_lang() {
  foreach (func_get_args() as $arg) {
    if (!is_null($arg)) {
      return $arg;
    }
  }
  return language_default();
}

/**
 * Custom function who detect the language from URL.
 *
 * @return object
 */
function _i18n_detect_lang_from_url($languages) {
    $language_url = FALSE;

    switch (variable_get('locale_language_negotiation_url_part', LOCALE_LANGUAGE_NEGOTIATION_URL_PREFIX)) {
      case LOCALE_LANGUAGE_NEGOTIATION_URL_PREFIX:

        $path = str_replace(base_path(), '', $_SERVER['REQUEST_URI']);

        list($language, $path) = language_url_split_prefix(isset($path) ? $path : NULL, $languages);
        if ($language !== FALSE) {
          $language_url = $language->language;
        }
        break;

      case LOCALE_LANGUAGE_NEGOTIATION_URL_DOMAIN:
        foreach ($languages as $language) {
          $host = parse_url($language->domain, PHP_URL_HOST);
          if ($host && ($_SERVER['HTTP_HOST'] == $host)) {
            $language_url = $language->language;
            break;
          }
        }
        break;
    }

    return $language_url;
  }

/**
 * Custom function who detect the language from a cookie.
 *
 * @return object
 */
function _i18n_detect_lang_from_cookie() {
  $lang_list = language_list('enabled');
  $lang_list = $lang_list[1];
  foreach ($lang_list as $lang) {
    if (!empty($lang->prefix) && $lang->prefix == $_COOKIE[LANGUAGE_COOKIE_KEY]) {
      return $lang;
    }
  }
  return NULL;
}

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
 * All the error messages are saved in this function so they are the same in the requirements page
 * and/or the settings page.
 *
 * @return array
 */
function _i18n_selection_page_error_messages() {
  $messages = array();
  $messages['language_count'] = 'There is a problem with the <b>language_count</b> variable.<br/>There are @language_count_db languages enabled in the database and @language_count_vars in the variable table (or from Features/Strongarm).<br/>This can lead to problems in your Drupal website.<br/>Please fix this problem before going further.';
  $messages['language_negotiation'] = 'The I18N Selection Page will be available when %setting_name setting is set to required "%setting_value" value. You should either disable the module or <a href="@setting_url">change your configuration</a>.';
  $messages['language_enabled'] = 'You should have more than <a href="@setting_url">one language</a> enabled to get the <b>I18N Selection Page</b> working.';
  $messages['language_prefix'] = 'You should add a path prefix to <a href="@language_url">language @language_name</a> if you want to have it enabled in the <b>I18N Selection Page</b>.';
  $messages['language_only_one'] = 'There is only <a href="@link">one language enabled</a>.';
  $messages['language_all_good'] = 'All your enabled languages have language prefix, all good.';
  return $messages;
}