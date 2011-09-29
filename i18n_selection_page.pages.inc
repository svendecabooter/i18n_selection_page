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
  $from       = array_key_exists('destination', $query) ? $query['destination'] : '<front>';
  unset($query['q']);
  unset($query['destination']);

  $link_text = url($from, array('query' => $query, 'language' => LANGUAGE_NONE));

  $data['from_link']['from_text'] = $from;
  $data['from_link']['from_query'] = $query;
  $data['from_link']['link_text'] = url($from, array('query' => $query, 'language' => LANGUAGE_NONE));
  $data['from_link']['html'] = l($link_text, $from, array('query' => $query, 'language' => LANGUAGE_NONE));

  $tpaths = translation_path_get_translations($from);

  foreach (language_list() as $prefix => $language) {
    if (!$language->prefix) continue;
    $link_text = drupal_ucfirst(drupal_strtolower(t('Continue in', array(), array('langcode'=>$language->language)))) . ' ' . $language->native;
    $to = array_key_exists($language->language, $tpaths) ? $tpaths[$language->language] : $from;
    $data['links']['items'][$prefix] = l($link_text, $to, array('query' => $query, 'language' => $language));
  }

  $data['links']['html']  = theme('item_list', $data['links']);
  $data['content'] = theme('i18n_selection_page_body', $data);

  switch (variable_get('i18n_selection_page_redirect_type', 64)) {
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
}

function i18n_selection_page_preprocess_i18n_selection_page_body(&$vars) {
  
}
