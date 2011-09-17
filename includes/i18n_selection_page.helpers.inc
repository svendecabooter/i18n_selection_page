<?php

/**
 * Custom function to parse a URL.
 *
 * @return array
 **/
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
 **/
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
 **/
function _i18n_detect_lang_from_url() {
  $url_parsed = _i18n_selection_page_parse_url_custom();
  $path = explode('/', $url_parsed['path']);

  $lang_list = language_list('enabled');
  $lang_list = $lang_list[1];

  foreach ($lang_list as $lang) {
    if (!empty($lang->prefix) && $lang->prefix == $path[0]) {
      return $lang;
    }
  }

  return NULL;

}

/**
 * Custom function who detect the language from a cookie.
 *
 * @return object
 **/
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