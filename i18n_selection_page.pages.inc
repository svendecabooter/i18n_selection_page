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

  //$tpaths = translation_path_get_translations($from);

  //echo "<pre>" . print_r($GLOBALS, 1) . "</pre>";

  foreach (language_list() as $prefix => $language) {
    if (!$language->prefix) continue;
    $link_text = drupal_ucfirst(drupal_strtolower(t('Continue in', array(), array('langcode'=>$language->language)))) . ' ' . $language->native;
    $link_text = url($to, array('query' => $query, 'language' => $language));

    //$to = array_key_exists($language->language, $tpaths) ? $tpaths[$language->language] : $from;
    $to = $from;
    $data['links']['items'][$prefix] = l($link_text, $to, array('query' => $query, 'language' => $language));
  }

  $data['links']['html']  = theme('item_list', $data['links']);
  $data['content'] = theme('i18n_selection_page_body', $data);

  switch (variable_get('i18n_selection_page_redirect_type', 64)) {
    case 32:
      return $data['content'];
      break;
    case 64:
      drupal_add_css(drupal_get_path('module', 'i18n_selection_page') . '/themes/css/i18n_selection_page.css');

      $data['head'] = drupal_get_html_head();
      $data['css'] = drupal_add_css();
      $data['styles'] = drupal_get_css();
      $data['scripts'] = drupal_get_js();
      $data['title'] = "Language selection";

      print theme('i18n_selection_page', $data);
      exit;
  }
}