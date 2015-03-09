<?php
// $Id: asia.admin.inc, v1.5 2014/03/25
/**
 * @file
 * Callbacks de administración del módulo Gestor Asia.
 */

/**
 * Definir el formulario de opciones de configuración
 */
function asia_configuracion() {  

  $form['asia_canal'] = array(
    '#title' => t('Channel Asia query (Example ccivics, escoles..)'),  
    '#type' => 'textfield',
    '#default_value' => variable_get('asia_canal', ''),  

  );
  
   $form['asia_addthis'] = array(
    '#type' => 'checkboxes', 
    '#title' => t('Add Addthis:'), 
    '#default_value' => variable_get('asia_addthis', array('llistat', 'detall')),
    '#options' => array( 
      'llistat' => t('List'),
      'detall' => t('Detail'),          
    ),
   );
 
  $form['submit'] = array(
      '#type' => 'submit',
      '#value' => 'Guardar configuración',
  );

  $form['#submit'][] = 'asia_configuracion_submit';  
  return $form;
}

/**
 * Validar el formulario de opciones de configuración
 
function asia_configuracion_validate($form, &$form_state) {
 

}*/

/**
 * Procesar el envío del formulario de opciones de configuración
*/

function asia_configuracion_submit($form, $form_state) {  
  variable_set('asia_canal', $form_state['values']['asia_canal']);  
  variable_set('asia_addthis', $form_state['values']['asia_addthis']);
  drupal_set_message(t("Se han guardado las opciones de configuración."));
} 