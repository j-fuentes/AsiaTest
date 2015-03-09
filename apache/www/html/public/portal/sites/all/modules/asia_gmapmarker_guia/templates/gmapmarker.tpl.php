<?php

/**
* @file gmapmarker.tpl.php
* 
*	parametres de url
*		&q=(paraula cerca)
*		&type= (AG | EQ)
*		&code0=(codi de primer nivell de guia)
*   	&code1=(codi de segon nivell de guia)
*		...
*		&c= (codi o varis codis combinats a arbre asia)
*   	&canal= (Canal guia) Hauria de venir <none> en la configuració del block.
*
*   Hi han 2 maneres de montar el formulari 
*   una manera és per idioma
*   switch ($language->language =="ca"){
*		case 'ca':
*			print '<li><input id="circ" type="checkbox" value="&q=*:*&code0=0040001027&nr=3" /><label for="circ">Circ</label></li>';
*			
*		break;
*		case 'es':
*		...
*		break;
*		...
*   }
*   o traduir per interficie
*	<li><input id="circ" type="checkbox" value="&q=*:*&code0=0040001027&nr=3" /><label for="circ"><?php echo t('Circ') ?></label></li>
*/


/* Variables */
global $language;
$base_url=$GLOBALS['base_url'].'/'.$language->language;

if(!empty($itemlist)){ 
?>


<div id="bcn-map-actions">
  <form action="<?php echo $urljson?>">
    <ul>
    <?php
	  if($activeList[2]==2){ 
	   echo '<li><input id="tots" type="checkbox" value="tots" /><label for="tots">' . t('All') . '</label></li>';	
	  }
	?>
    
      <?php 
	  // for ($i = 0; $i < count($itemlist); $i++) {
		  foreach($itemlist as $i=>$item){
			if(!empty($item[0]) && !empty($item[1])){	
			   echo '<li><input id="' . sanear_text($item[0]). '" type="checkbox" value="' .$item[1] . '" /><label for="' . sanear_text($item[0]) . '">' . t($item[0]) . '</label></li>';
			}
	   }
	  ?>
     
    </ul>
  </form>
</div>
<?php } ?>
<div id="bcn-map-view">
  <div id="map-canvasGM"></div>
  <?php 
  //Si llistat esta activat per configuració
  if($activeList[1]==1){ ?>
  	<div id="llistat-text"></div>
  <?php } ?>
</div>
