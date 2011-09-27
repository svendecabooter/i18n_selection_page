<?php
/**
 * @file
 * The page containing the modules pages.
 */
/**
 * Menu callback to display the selection page.
 */
function i18n_selection_page_selection_page() {
  module_load_include('inc', 'i18n_selection_page', 'includes/i18n_selection_page.helpers');
  drupal_init_language();

  $url_parsed = _i18n_selection_page_parse_url_custom();
  $query      = $url_parsed['query'];
  $from       = $query['destination'];
  unset($query['q']);
  unset($query['destination']);
  $query_args = array();

  foreach ($query as $key => $value) {
    $query_args[] = $key . '=' . $value;
  }

  $query_str = implode('&', $query_args);
  $nulllang  = new stdClass;
  $link_text = url($from, array('query' => $query_str, 'language' => $nulllang));
//  $data['from_link'] = l($link_text, $from, array('query' => $query_str, 'language' => $nulllang));

  $data['from_link']['from_text'] = $from;
  $data['from_link']['from_query_str'] = $query_str;
  $data['from_link']['link_text'] = url($from, array('query' => $query_str, 'language' => $nulllang));
  $data['from_link']['html'] = l($link_text, $from, array('query' => $query_str, 'language' => $nulllang));

  foreach (language_list() as $prefix => $language) {
    if (!$language->prefix) continue;
    $link_text = drupal_ucfirst(drupal_strtolower(t('Continue in', array(), $language->language))) . ' ' . $language->native;
    $data['links']['items'][$prefix] = l($link_text, $from, array('query' => $query_str, 'language' => $language));
  }

  $data['links']['html']  = theme('item_list', $data['links']['items']);
  $data['content'] = theme('i18n_selection_page_body', $data);

  $redirect_type = variable_get('i18n_selection_page_redirect_type', 64);

  switch ($redirect_type) {
    case 32:
      return theme('i18n_selection_page_body', $data);
      break;
    case 64:
      print theme('i18n_selection_page', $data);
      exit;
  }
}

function i18n_selection_page_preprocess_i18n_selection_page(&$vars) {
  drupal_add_css(drupal_get_path('module', 'i18n_selection_page').'/themes/css/i18n_selection_page.css');

  $vars['head']    = drupal_get_html_head();
  $vars['css']     = drupal_add_css();
  $vars['styles']  = drupal_get_css();
  $vars['scripts'] = drupal_get_js();
  $vars['title']   = "Language selection";
  $vars['content'] = $vars['data']['content'];
}

function i18n_selection_page_preprocess_i18n_selection_page_body(&$vars) {
  $vars['from_link_html'] = $vars['data']['from_link']['html'];
  $vars['to_links_html']  = $vars['data']['links']['html'];
}
