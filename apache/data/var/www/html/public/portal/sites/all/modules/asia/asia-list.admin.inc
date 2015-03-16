<?php
// $Id: asia-list.admin.inc, v1.5 2014/03/25
/**
 * @file
 * Callbacks de administración del módulo Gestor Asia.
 */

/**
 * Definir el formulario de opciones de configuración
 */
function asia_pagelist_configuracion() {  

  
  $form['asia_num_resultats'] = array(
    '#title' => 'Número de resultats per pàgina en els llistats',  
    '#type' => 'textfield',
    '#default_value' => variable_get('asia_num_resultats', 10),  

  );
  
   $form['asia_config_resultats'] = array(
    '#type' => 'checkboxes', 
    '#title' => t('Results list'), 
    '#default_value' => variable_get('asia_config_resultats', array(1, 2, 3)),
    '#options' => array( 
      1 => t('Active map'),    
      2 => t('Active filters'),    
      3 => t('Active "Ajax"'),
     ),
   );
   $form['asia_display_list'] = array(
    '#type' => 'checkboxes', 
    '#title' => t('Fields to display the list'), 
    '#default_value' => variable_get('asia_display_list', array(1, 2, 3, 4, 5, 6, 7)),
    '#options' => array(     
      1 => t('Active labels category "Events / Entities"'),
      2 => t('Show picture'),
      3 => t('Show when'),
      4 => t('Show where'),        
      5 => t('Show address & district'),  
      6 => t('Show phones'),    
      7 => t('Show web'),
    ),
   );
  
  $form['asia_maplist_amplada'] = array(
    '#title' => t('Map width (in pixels)'),  
    '#type' => 'textfield',
    '#default_value' => variable_get('asia_maplist_amplada', 260), 
  );
 
  $form['asia_maplist_alcada'] = array(
    '#title' => t('Map height (in pixels)'),  
    '#type' => 'textfield',
    '#default_value' => variable_get('asia_maplist_alcada', 353), 
  );
  
  $form['asia_list_amplada'] = array(
    '#title' => t('Width of the list (in pixels)'),  
    '#type' => 'textfield',
    '#default_value' => variable_get('asia_list_amplada', 410), 
  );
  

 
 
  $form['submit'] = array(
      '#type' => 'submit',
      '#value' => 'Guardar configuración',
  );

  $form['#submit'][] = 'asia_pagelist_configuracion_submit';  
  return $form;
}

/**
 * Validar el formulario de opciones de configuración
 */
function asia_pagelist_configuracion_validate($form, &$form_state) {
 
  if (trim($form_state['values']['asia_num_resultats']) == '') {
    form_set_error('asia_num_resultats', 'El número de resultats no pot estar buit');
  }
  if (trim($form_state['values']['asia_maplist_amplada']) == '') {
    form_set_error('asia_maplist_amplada', 'L&rsquo;amplada del mapa del llistat no pot estar buida');
  }
   if (trim($form_state['values']['asia_maplist_alcada']) == '') {
    form_set_error('asia_maplist_alcada', 'L&rsquo;alçada del mapa del llistat no pot estar buida');
  }
}

/**
 * Procesar el envío del formulario de opciones de configuración
*/

function asia_pagelist_configuracion_submit($form, $form_state) {  

  variable_set('asia_num_resultats', $form_state['values']['asia_num_resultats']);
  variable_set('asia_maplist_amplada', $form_state['values']['asia_maplist_amplada']);
  variable_set('asia_list_amplada', $form_state['values']['asia_list_amplada']);
  variable_set('asia_maplist_alcada', $form_state['values']['asia_maplist_alcada']);
  variable_set('asia_config_resultats', $form_state['values']['asia_config_resultats']);
  variable_set('asia_display_list', $form_state['values']['asia_display_list']);
  drupal_set_message(t("Se han guardado las opciones de configuración."));
} 