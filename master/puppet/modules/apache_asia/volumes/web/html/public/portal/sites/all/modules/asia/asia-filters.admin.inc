<?php
// $Id: asia-filters.admin.inc, v1.5 2014/03/25
/**
 * @file
 * Callbacks de administración del módulo Gestor Asia.
 */

/**
 * Definir el formulario de opciones de configuración
 */
 
 
function asia_pagefilters_configuracion($form, &$form_state, $no_js_use = FALSE) {
  //print_r(getFilters());

  $var_codes = variable_get('asia_codes_filters');
if (isset($var_codes['@codes'])) {  
  $codes=explode(', ', $var_codes['@codes']);
}
else {
   $codes=0;
}
  $form['asia_block_filters'] = array(
  '#type' => 'checkboxes', 
  '#title' => t('Block to display the filters'), 
  '#default_value' => variable_get('asia_block_filters'),
  '#options' => getFilters(),
   );  


  

  // Because we have many fields with the same values, we have to set
  // #tree to be able to access them.
  $form['#tree'] = TRUE;
  $form['codes_fieldset'] = array(
    '#type' => 'fieldset',
    '#title' => t('Hide thematic codes'),
    // Set up the wrapper so that AJAX will be able to replace the fieldset.
    '#prefix' => '<div id="codes-fieldset-wrapper">',
    '#suffix' => '</div>',
  );

  // Build the fieldset with the proper number of names. We'll use
  // $form_state['num_names'] to determine the number of textfields to build.
  if (empty($form_state['num_codes'])) {
      if (count($codes)!=0) {
        $form_state['num_codes'] = count($codes);
      } 
      else  {
        $form_state['num_codes'] = 1;
    }
  }
  //carga tots els camps guardats
  for ($i = 0; $i < $form_state['num_codes']; $i++) {
    $form['codes_fieldset']['code'][$i] = array(
      '#type' => 'textfield',
      '#title' => t('Code'),
    '#default_value' => $codes[$i],
    );
  
  }
  //boto d'afegiu un code més
  $form['codes_fieldset']['add_code'] = array(
    '#type' => 'submit',
    '#value' => t('Add one more'),
    '#submit' => array('ajax_example_add_more_add_one'),
    // See the examples in ajax_example.module for more details on the
    // properties of #ajax.
    '#ajax' => array(
      'callback' => 'ajax_example_add_more_callback',
      'wrapper' => 'codes-fieldset-wrapper',
    ),
  );
  if ($form_state['num_codes'] > 1) {
    $form['codes_fieldset']['remove_code'] = array(
      '#type' => 'submit',
      '#value' => t('Remove one'),
      '#submit' => array('ajax_example_add_more_remove_one'),
      '#ajax' => array(
        'callback' => 'ajax_example_add_more_callback',
        'wrapper' => 'codes-fieldset-wrapper',
      ),
    );
  }
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit'),
  );

  // This simply allows us to demonstrate no-javascript use without
  // actually turning off javascript in the browser. Removing the #ajax
  // element turns off AJAX behaviors on that element and as a result
  // ajax.js doesn't get loaded.
  // For demonstration only! You don't need this.
  if ($no_js_use) {
    // Remove the #ajax from the above, so ajax.js won't be loaded.
    if (!empty($form['codes_fieldset']['remove_code']['#ajax'])) {
      unset($form['codes_fieldset']['remove_code']['#ajax']);
    }
    unset($form['codes_fieldset']['add_code']['#ajax']);
  }
$form['#submit'][] = 'ajax_example_add_more_submit';  
  return $form;
}

/**
 * Callback for both ajax-enabled buttons.
 *
 * Selects and returns the fieldset with the names in it.
 */
function ajax_example_add_more_callback($form, $form_state) {
  return $form['codes_fieldset'];
}

/**
 * Submit handler for the "add-one-more" button.
 *
 * Increments the max counter and causes a rebuild.
 */
function ajax_example_add_more_add_one($form, &$form_state) {
  
  $form_state['num_codes']++;
  $form_state['rebuild'] = TRUE;
}

/**
 * Submit handler for the "remove one" button.
 *
 * Decrements the max counter and causes a form rebuild.
 */
function ajax_example_add_more_remove_one($form, &$form_state) {
  if ($form_state['num_codes'] > 1) {
    $form_state['num_codes']--;
  }
  $form_state['rebuild'] = TRUE;
}

/**
 * Final submit handler.
 *
 * Reports what values were finally set.
 */
function ajax_example_add_more_submit($form, &$form_state) {
  
 $var_codes="";
  for ($i=0; $i < count($form_state['values']['codes_fieldset']['code']); $i++) {
    if ($form_state['values']['codes_fieldset']['code'][$i]!='') {            
      $var_codes .= $form_state['values']['codes_fieldset']['code'][$i] . ', ';        
    }

   }  
  variable_set('asia_codes_filters', array('@codes' => $var_codes) );  
  variable_set('asia_block_filters', $form_state['values']['asia_block_filters']);  
  drupal_set_message(t("Se han guardado las opciones de configuración."));
  
}
/**
 * @} End of "defgroup ajax_degradation_example".
 */