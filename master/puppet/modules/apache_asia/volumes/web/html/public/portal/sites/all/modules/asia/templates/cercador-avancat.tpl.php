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
$showSearchCalendar = 0;

if(hasValue($settings_cercaavancada)){
	//si calendari esta activat en el config de block
	if(isset($settings_cercaavancada[1]) && $settings_cercaavancada[1]==1){
		$showSearchCalendar=$settings_cercaavancada[1];
	}	
}	


// Si viene parametro districte url i aquest esta activat en el config del block
if(isset($_GET["districtstr"]) && $settings_cercaavancada[2]==2){
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
	 	
			var showSearchCalendar = <?php echo $showSearchCalendar;?>;
			// Si $showSearchCalendar -->  0 = NO MOSTREM RES  //  1 = CALENDARI
			var canal = "<?php echo $canal; ?>";
			var base_url = "<?php echo $base_url; ?>";
			var idioma = "<?php echo $language->language; ?>";
			var code0 = "<?php echo $code0; ?>";
			var code1 = "<?php echo $code1; ?>";
			var element = "#date";
			
			init(showSearchCalendar,canal,base_url,code0,code1,element,idioma);
			
	   });
		
   })(jQuery);
	
  	</script>

<form id="asia" action="<?php echo $base_url.'/'.$language->language ?>/llistat" method="get">
     <div>
     <input type="hidden" value="" name="dt" id="inputDate" />

		<p><label for="cerca-av"><?php print t('By word') ?></label><input type="text" name="cerca" id="cerca-av" value="" /></p>
		
		<?php 
		// Com que no ve disabled=1, és a dir, no ve districte 
		// mostra el select de districtes
		if($disabled!=1){
		?>
			<p>	<label><?php print t('Choose a district') ?></label>
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
			</select></p>
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
                <select id="tipusact" name="tipusact">
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
            // Si només esta configurat el code0
            // guardes en un camp ocult el code0
            } else {
                 print '<input id="tipusact" name="tipusact" type="hidden" value="'.$code0.'" />';
            }
            
            // Si code1 no esta configurat	
            // Mostram les especialitats per javascript
            if(!hasValue($code1)){ ?>
    
                <label><?php print t('Choose a speciality') ?></label>
                <select id="especialitat" name="especialitat">
                <?php  ?>
            </select>
            <?php 
            // si esta configurat code1
            // guardam el code1 en un camp ocult
            } else{
                 print '<input id="code1" name="code1" type="hidden" value="'.$code1.'" />';
            }?>
		</p>
    </div>

   
	<?php 	
	// Si esta configurat el calendari
	if($showSearchCalendar == 1){  ?>        
        <div id="date" class="date"> </div>
	<?php 	 } 	?>

<p class="enviar"><input type="submit" value="<?php print t('Search') ?>" /></p>
</form>