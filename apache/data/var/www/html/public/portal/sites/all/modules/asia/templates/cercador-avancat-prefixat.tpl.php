<?php 
/**
* @file cercador-avansat.tpl.php
* Renderiza una lista de items.
*
*
*<script type="text/javascript" src="sites/all/modules/asia/js/datepicker.js"></script> 
<link rel="stylesheet" href="sites/all/modules/asia/css/datepicker.css" type="text/css" />
*/

$disabled="";
global $language;

/* Recull variables generiques */
$base_url = $GLOBALS['base_url'];
/*$canal = variable_get('asia_canal','');
$code0 = variable_get('code0Cerca','');
$code1 = variable_get('code1Cerca','');*/

//Recollim variables "calendari" de  function asia
$showSearchCalendarPrefix = 0;



if(hasValue($settings_cercaavancada_prefixada)){
	//si calendari esta activat en el config de block
	if(isset($settings_cercaavancada_prefixada[1]) && $settings_cercaavancada_prefixada[1]==1){
		$showSearchCalendarPrefix=$settings_cercaavancada_prefixada[1];
	}	
}	


// Si viene parametro districte url i aquest esta activat en el config del block
if(isset($_GET["districtstr"]) && $settings_cercaavancada_prefixada[2]==2){
	$districte =  str_replace( " " ,"+",$_GET["districtstr"]);	
	
	switch($districte){
    case 'Ciutat+Vella':
        $disabled=1;
        break;
    case 'Eixample':
        $disabled=1;		
        break;
    case 'Sants-Montjuïc':
        $disabled=1;
        break;
	case 'Les+Corts':
        $disabled=1;
        break;	
	case 'Sarrià-Sant+Gervasi':
        $disabled=1;
        break;	
	case 'Gràcia':
        $disabled=1;
        break;	
	case 'Horta-Guinardó':
        $disabled=1;
        break;	
	case 'Nou+Barris':
        $disabled=1;
        break;	
	case 'Sant+Andreu':
        $disabled=1;
        break;	
	case 'Sant+Martí':
        $disabled=1;
        break;		
	}
}


// Si $showSearchCalendar -->  0 = NO MOSTREM RES  //  1 = CALENDARI
// Pasem parametres de iniciacio en el formulari.
?>
<script type="text/javascript">
  
    (function ($){
     
	   $(document).ready(function(){
	 	
			var showSearchCalendarPrefix = <?php echo $showSearchCalendarPrefix;?>;
			// Si $showSearchCalendar -->  0 = NO MOSTREM RES  //  1 = CALENDARI
			var canal = "<?php echo $canal; ?>";
			var base_url = "<?php echo $base_url; ?>";
			var idioma = "<?php echo $language->language; ?>";
			var code0 = "";
			var code1 = "";
			var element = '#date-prefixat';			
			init(showSearchCalendarPrefix,canal,base_url,code0,code1,element,idioma);			
	   });
		
   })(jQuery);
	
</script>

<form id="asia-prefixat" action="<?php echo $base_url.'/'.$language->language ?>/llistat" method="get">
  <div>
    <input type="hidden" value="" name="dt" id="inputDate" />
    <p>
      <label for="cerca-av"><?php print t('By word') ?></label>
      <input type="text" name="cerca" id="cerca-av" value="" />
    </p>
    <?php 
		// Com que no ve disabled=1, és a dir, no ve districte 
		// mostra el select de districtes
		if($disabled!=1){
		?>
    <p>
      <label><?php print t('Choose a district') ?></label>
      <select id="districtstr" name="districtstr">
        <option value=""><?php print t('All districts') ?></option>
        <option value="Ciutat+Vella">Ciutat Vella</option>
        <option value="Eixample">Eixample</option>
        <option value="Sants-Montjuïc">Sants-Montjuïc</option>
        <option value="Les+Corts">Les Corts</option>
        <option value="Sarrià-Sant+Gervasi">Sarrià-Sant Gervasi</option>
        <option value="Gràcia">Gràcia</option>
        <option value="Horta-Guinardó">Horta-Guinardó</option>
        <option value="Nou+Barris">Nou barris</option>
        <option value="Sant+Andreu">Sant Andreu</option>
        <option value="Sant+Martí">Sant Martí</option>
      </select>
    </p>
    <?php 
		// Si que hi ha parametre districte i ademés "disabled=1". Per comprovar que és correcte.
		// Pinta camp ocult amb la informacio del districte		
		}elseif(hasvalue($districte) && $disabled==1){
			print '<input name="districtstr"  id="districtstr" value="'.$districte.'" type="hidden"  />';
		}
		
		?>
    <p>
      <?php 
            // Si code0 i code1 no estan configurats 
            // Pintam el tipus d'activitat
			
            if(!hasValue($code0) && !hasValue($code1)){ ?>
				<label><?php print t('Choose a type of activity') ?></label>
				<select id="code0" name="code0">
					<option value="">...</option>
       				<?php	
		            //Pintam tots els tipus d'activitats (code0) que venen al XML
					if(isset($dis->search->bleft->leftfilter->facetlist->class->item)){
		                foreach($dis->search->bleft->leftfilter->facetlist->class->item as $activitat) { 
        		            $name =  $activitat['name'];
                		    $value = str_replace('code0=', "", strrchr($activitat['href'], 'code0=')); 
                		?>
				        <option value="<?php print $value;?>"> <?php print $name;?></option>
        			<?php	} 
					}?>
      			</select>
      		<?php                     
		    // Si code0 o code1 tenen valor configurar
            }else{
				//si code0 te valor i code1 no
				// mostram en el selects els code1
				if(hasValue($code0) && !hasValue($code1)){					
					print '<input type="hidden" value="'.$code0.'" id="code0" name="code0"/>';
					?>
				      <label><?php print t('Choose a type of activity') ?></label>
				      <select id="code1" name="code1">
				      	<option value="">...</option>
				        <?php	
                		//Pintam tots els tipus d'activitats (code0) que venen al XML
						if(isset($dis->search->bleft->leftfilter->facetlist->class->item)){
            			    foreach($dis->search->bleft->leftfilter->facetlist->class->item as $activitat) { 
			                    $name =  $activitat['name'];
            			        $value = str_replace('code1=', "", strrchr($activitat['href'], 'code1=')); 
			                ?>
        					<option value="<?php print $value;?>"> <?php print $name;?></option>
        					<?php	} 
				
						}?>
      				  </select>
      			<?php
				}
				
				// si hi ha configurat el code0 i el code 1 o nomes el code 1
				// guardam les variables
				// mostram en el select el code2
				if(hasValue($code1) && hasValue($code0) || hasValue($code1) && !hasValue($code0)){
					if(hasValue($code0)	){				
						print '<input type="hidden" value="'.$code0.'" id="code0" name="code0"/>';
					}
					print '<input type="hidden" value="'.$code1.'" id="code1" name="code1"/>';
				
				
					?>
				      <label><?php print t('Choose a type of activity') ?></label>
					  <select id="code2" name="code2">
				        <option value="">...</option>
       					 <?php	
		                //Pintam tots els tipus d'activitats (code2) que venen al XML
						if(isset($dis->search->bleft->leftfilter->facetlist->class->item)){
        			        foreach($dis->search->bleft->leftfilter->facetlist->class->item as $activitat) { 
                    			$name =  $activitat['name'];
			                    $value = str_replace('code2=', "", strrchr($activitat['href'], 'code2=')); 
            				    ?>
						        <option value="<?php print $value;?>"> <?php print $name;?></option>
        					<?php	} 
				
						}?>
      				  </select>
      			<?php
				}
			}     
           
            
            ?>
    </p>
  </div>
  <?php 	
	// Si esta configurat el calendari
	if($showSearchCalendarPrefix == 1){  ?>
  <div id="date-prefixat" class="date"> </div>
  <?php 	 } 	?>
  <p class="enviar">
    <input type="submit" value="<?php print t('Search') ?>" />
  </p>
</form>
