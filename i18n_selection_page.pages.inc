<?php

/**
 * Menu callback to display the selection page.
**/
function i18n_selection_page_selection_page() {

  module_load_include('inc', 'i18n_selection_page', 'includes/i18n_selection_page.helpers');

  $url_parsed = _i18n_selection_page_parse_url_custom();
  $query = $url_parsed['query'];
  $from = $query['destination'];

  unset($query['q']);
  unset($query['destination']);

  $query_args = array();
  foreach ($query as $key => $value) {
    $query_args[] = $key . '=' . $value;
  }  
  $query_str = implode('&', $query_args);

  $nulllang = new stdClass;
  $link_text = url($from, array('query' => $query_str, 'language' => $nulllang));
  $data['from_link'] = l($link_text, $from, array('query' => $query_str, 'language' => $nulllang));

  foreach (language_list() as $prefix => $language) {
    $link_text = ucfirst(strtolower(t('Continue in ', array(), $language->language))) . $language->native;
    $items[$language->language] = l($link_text, $from, array('query' => $query_str, 'language' => $language));
  }

  $data['links'] = $items;

  $redirect_type = variable_get('i18n_selection_page_redirect_type', 0);
  switch ($redirect_type) {
    case 1:
      return theme('i18n_selection_page', $data);
      break;
    case 2:
      print theme('i18n_selection_page', $data);
      exit;
  }
}
