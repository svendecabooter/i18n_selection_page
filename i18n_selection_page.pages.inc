<?php
/**
 * @file
 * Contains menu callback functions for pages defined in this module
 */
/**
 * Menu callback to display the selection page.
 */
function i18n_selection_page_selection_page() {
  $query = drupal_get_query_parameters();
  $from = array_key_exists('destination', $query) ? $query['destination'] : '<front>';
  unset($query['q']);
  unset($query['destination']);

  // prepare information about the link the user is coming from
  $link_text = url($from, array('query' => $query, 'language' => LANGUAGE_NONE));
  $data['from_link']['from_text'] = $from;
  $data['from_link']['from_query'] = $query;
  $data['from_link']['link_text'] = url($from, array('query' => $query, 'language' => LANGUAGE_NONE));
  $data['from_link']['html'] = l($link_text, $from, array('query' => $query, 'language' => LANGUAGE_NONE));

  // prepare the links per language
  foreach (language_list() as $prefix => $language) {
    // @TODO: is prefix check necessary?
    if (!$language->prefix) continue;
    // format a human-readable link to let a user continue in this language
    $link_text = drupal_ucfirst(drupal_strtolower(t('Continue in', array(), array('langcode' => $language->language)))) . ' ' . $language->native;
    // add this link to the data list
    $data['links']['items'][$prefix] = l($link_text, $from, array('query' => $query, 'language' => $language));
  }

  $data['links']['html']  = theme('item_list', $data['links']);

  // before we start processing the gathered data, we let other modules alter it
  // by letting them implement hook_i18n_selection_page_data_alter(&$data)
  drupal_alter('i18n_selection_page_data', $data);

  $data['content'] = theme('i18n_selection_page_body', $data);

  switch (variable_get('i18n_selection_page_redirect_type', I18N_SELECTION_PAGE_TEMPLATE_ONLY)) {
    case I18N_SELECTION_PAGE_TEMPLATE_IN_THEME:
      return $data['content'];
      break;
    case I18N_SELECTION_PAGE_TEMPLATE_ONLY:
      drupal_add_css(drupal_get_path('module', 'i18n_selection_page') . '/themes/css/i18n_selection_page.css');

      $data['head'] = drupal_get_html_head();
      $data['css'] = drupal_add_css();
      $data['styles'] = drupal_get_css();
      $data['scripts'] = drupal_get_js();
      $data['title'] = t("Language selection");

      print theme('i18n_selection_page', $data);
      exit;
  }
}