<?php

function language_selection_page_admin() {

  $form = array();

  $options = array('0'=>t('Disabled'), '1'=>t('Template in theme'), '2'=>'Template only');
  $form['language_selection_page_redirect_type'] = array(
    '#title' => t('Select the way the Selection Page should work'),
    '#type' => 'select',
    '#multiple' => FALSE,
    '#default_value' => variable_get('language_selection_page_redirect_type', 0),
    '#options' => $options,
    '#description' => t('Description')
  );
  
  return system_settings_form($form);

}

function language_selection_page_admin_validate($form, &$form_state) {

}

function language_selection_page_admin_submit($form, &$form_state) {

}