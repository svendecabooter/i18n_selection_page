<?php
/**
 * @file
 * The page containing the modules pages.
 */
/**
 * Menu callback to display the selection page.
 */
function i18n_selection_page_selection_page() {
  $query      = drupal_get_query_parameters();
  $from       = $query['destination'];
  unset($query['q']);
  unset($query['destination']);

  $nulllang  = new stdClass;
  $link_text = url($from, array('query' => $query, 'language' => $nulllang));

  $data['from_link']['from_text'] = $from;
  $data['from_link']['from_query'] = $query;
  $data['from_link']['link_text'] = url($from, array('query' => $query, 'language' => $nulllang));
  $data['from_link']['html'] = l($link_text, $from, array('query' => $query, 'language' => $nulllang));

  $rrr = translation_path_get_translations($from);

  foreach (language_list() as $prefix => $language) {
    if (!$language->prefix) continue;
    $link_text = drupal_ucfirst(drupal_strtolower(t('Continue in', array(), array('langcode'=>$language->language)))) . ' ' . $language->native;
    $data['links']['items'][$prefix] = l($link_text, $rrr[$language->language], array('query' => $query, 'language' => $language));
  }

  $data['links']['html']  = theme('item_list', $data['links']);

  $data['content'] = theme('i18n_selection_page_body', $data);

  $html = theme('i18n_selection_page_body', $data);

  //dpm($html, 'html');

  return $html;
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
  $vars['from_link_html'] = $vars['from_link']['html'];
  $vars['to_links_html']  = $vars['links']['html'];
}
