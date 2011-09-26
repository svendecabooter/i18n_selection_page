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
    if (!$language->prefix) continue;
    $link_text = drupal_ucfirst(drupal_strtolower(t('Continue in', array(), $language->language))) . ' ' . $language->native;
    $data['links'][] = l($link_text, $from, array('query' => $query_str, 'language' => $language));
  }
  $data['links_html'] = theme('item_list', $data['links'], NULL, 'ul');
  $html = theme('i18n_selection_page', $data);
  $redirect_type = variable_get('i18n_selection_page_redirect_type', 64);
  switch ($redirect_type) {
    case 32:
      return $html;
      break;
    case 64:
      print $html;
      exit;
  }
}
