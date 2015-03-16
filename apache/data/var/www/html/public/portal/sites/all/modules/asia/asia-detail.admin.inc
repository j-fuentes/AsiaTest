<?php
// $Id: asia-detail.admin.inc, v1.5 2014/03/25
/**
 * @file
 * Callbacks de administración del módulo Gestor Asia.
 */

/**
 * Definir el formulario de opciones de configuración
 */
function asia_pagedetail_configuracion() {  
  
  
$form['asia_config_detall'] = array(
  '#type' => 'checkboxes', 
  '#title' => t('Results list'), 
  '#default_value' => variable_get('asia_config_detall', array(1, 2)),
  '#options' => array( 
    1 => t('Back link'),  
    2 => t('Google translate'),  
  ),
);  
$form['asia_display_detail'] = array(
  '#type' => 'checkboxes', 
  '#title' => t('Fields to display the detail'), 
  '#default_value' => variable_get('asia_display_detail'),
  '#options' => array(     
    'picture' => t('Show picture'),
    'when' => t('Show when'),
    'where' => t('Show where'),    
    'street' => t('Show street'),  
    'district' => t('Show district'),    
    'area' => t('Show area'),
    'cp' => t('Show post code'),
    'city' => t('Show city'),
    'phone' => t('Show phone'),
    'fax' => t('Show fax'),
    'web' => t('Show web'),
    'email' => t('Show email'),
    'accessibility' => t('Show accessibility'),
    'ownership' => t('Show ownership'),
    'description' => t('Show description'),
    'abstract' => t('Show abstract'),
    'comments' => t('Show comments'),
    'maps' => t('Show maps'),
    'howtogo' => t('Show how to go'),
    'tabinfomation' => t('Show tab information'),
    'tabactivities' => t('Show tab activities'),
    'tabneavy' => t('Show tab neavy'),
  ),
   );  
  
  $form['submit'] = array(
      '#type' => 'submit',
      '#value' => 'Guardar configuración',
  );

  $form['#submit'][] = 'asia_pagedetail_configuracion_submit';  
  return $form;
}

/**
 * Validar el formulario de opciones de configuración
 */


/**
 * Procesar el envío del formulario de opciones de configuración
*/

function asia_pagedetail_configuracion_submit($form, $form_state) {  
  variable_set('asia_config_detall', $form_state['values']['asia_config_detall']);
  variable_set('asia_display_detail', $form_state['values']['asia_display_detail']);  
  drupal_set_message(t("Se han guardado las opciones de configuración."));
} 