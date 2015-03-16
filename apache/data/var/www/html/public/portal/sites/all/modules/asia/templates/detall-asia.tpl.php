
<?php
/**
* @file llista-asia.tpl.php
* Renderiza una lista de items.
*
* - $arrXml
*
* 
*/






global $language;
$base_url=$GLOBALS['base_url'].'/'.$language->language;



////////////////////////////////////////////////////////////
//print '<pre>'. check_plain(print_r($config_detall, 1)) .'</pre>';

// Google translate
// Si esta activada la variable en el config del detall i no és català
if(isset($config_detall[2]) && $config_detall[2]==2 && $language->language!="ca"){
?>

<script>
function googleSectionalElementInit() {
		  new google.translate.SectionalElement({
		    sectionalNodeClassName: 'goog-trans-section',
		    controlNodeClassName: 'goog-trans-control',
		    pageLanguage: 'ca',
		    background: 'transparent'
		  }, 'google_sectional_element');
}		
</script>
	<?php 
	
	switch($language->language){
		case 'es':
		
		?>	
		<script type="text/javascript" src="http://translate.google.com/translate_a/element.js?cb=googleSectionalElementInit&amp;ug=section&amp;hl=es"></script>
		<?php
		break;
		case 'en':
		?>
		<script type="text/javascript" src="http://translate.google.com/translate_a/element.js?cb=googleSectionalElementInit&amp;ug=section&amp;hl=en"></script>
		<?php
		break;
    }// end switch

?>
<script>
(function ($){
   google_initialized = false;

    function google_auto_translate(){
        if(google_initialized){           
            
            $('a.goog-te-gadget-link')[0].click();    
            
        }
        else if(google.translate)
        {
            google_initialized = true;
            setTimeout(google_auto_translate, 2500);
        }
        else
            setTimeout(google_auto_translate, 750);
    }
	window.onload = google_auto_translate;
})(jQuery);

</script>

<?php

}// end if google translate

//  Fi Google translate
// Comprovar si ve informació de l'acte, sinó hi ha res el missatge és "pàgina no trobada"
if($arrXml!=""){


// Variables generiques
$detall=$arrXml->detall;
$tp=strtolower($detall->entity_type);

//print $detall->entity_type;


if($tp=='eq'){
	$name = $detall->share['label'];
}else{
	$name = $detall->name;
}

//Status
if(isset($detall->status->item->name)){
	$out_status = $detall->status->item->name;
}

// Crea i Recull variables de sortida si esta activat en la configuració del detall asia-detail.admin.inc

foreach ($display as $field){	
	switch($field){
		case 'picture':
			$picture = $detall->internetref->item; // Array	
			if (arrayhasValue($picture)){
				foreach($picture as $ipicture => $field){
					$out_picture='<img alt="" src="'.$field->irefvalue.'" />';
				}
			}
		break;
		case 'when':
			$on = $detall->institutionname;
			if (hasValue($on)){
					$out_where= '<dt class="notranslate">'.$on['label'].'</dt>';
					if(hasValue($on['href'])){				
						$out_where.= '<dd class="notranslate"><a href="'.$on['href'].'">'.$on.'</a></dd>';
					}else{
						$out_where.= '<dd class="notranslate">'.$on.'</dd>';
					}
			}
		break;
		case 'where':
			$date = $detall->date;
			$out_when ='';
			if (hasValue($date)){
				$out_when .= '<dt class="notranslate">'.$date['label'].'</dt>';
				$out_when .= '<dd class="notranslate">'.$date.'</dd>';
			}else if (hasValue($detall->begindate) || hasValue($detall->enddate)){
				$out_when .=  '<dt class="notranslate">'.$detall->begindate['label2'].'</dt>';
				$out_when .= '<dd class="notranslate">'.$detall->begindate['label'].' '.$detall->begindate.' '.$detall->enddate['label'].' '.$detall->enddate.'.</dd>';
			}
		break;
		case 'street':
			$street = $detall->street;
			$num_street = $detall->streetnum_i;
			if (hasValue($street)){
				$out_street = '<dt class="notranslate">'.$street['label'].':</dt>';
				$out_street .= '<dd class="notranslate">'.$street.', '.$num_street.'</dd>';
			}		 
		break;
		case 'district':
			$district = $detall->district;
			if (hasValue($district)){
				$out_district = '<dt class="notranslate">'.$district['label'].':</dt>';
				$out_district .= '<dd class="notranslate">'.$district.'</dd>';
			}
		break;
		case 'area':
			$barri = $detall->barri;	
			if (hasValue($barri)){
				$out_area = '<dt class="notranslate">'.$barri['label'].':</dt>';
				$out_area .= '<dd class="notranslate">'.$barri.'</dd>';
			}
		break;			
		case 'cp':
			$cp = $detall->postalcode;
		 	if (hasValue($cp)){
				$out_cp = '<dt class="notranslate">'.$cp['label'].':</dt>';
				$out_cp .= '<dd class="notranslate">'.$cp.'</dd>';
			}
		break;
		case 'city':
			$city = $detall->city; 	
			if (hasValue($city)){
				$out_city =  '<dt class="notranslate">'.$city['label'].':</dt>';
				$out_city .=  '<dd class="notranslate">'.$city.'</dd>';
			}
		
		 
		break;
		case 'phone':
			$tel = $detall->phones->item; //Array tel + fax 
			if (arrayhasValue($tel)){	
				$out_phone="";		
				foreach($tel as $itel => $field){
					
					if($field->label!="Fax"){						
						$out_phone .= '<dt class="notranslate">'.$field->label.': </dt>';				
						$out_phone .= '<dd>'.$field->phonenumber.' '.$field->phonedesc.'</dd>';
					}
				}			 
			}
		break;
		case 'fax':
			$tel = $detall->phones->item; //Array tel + fax 
			if (arrayhasValue($tel)){	
				$out_fax="";		
				foreach($tel as $itel => $field){
						
					if($field->label=="Fax"){						
						$out_fax .= '<dt class="notranslate">'.$field->label.': </dt>';				
						$out_fax .= '<dd>'.$field->phonenumber.' '.$field->phonedesc.'</dd>';
					}
				}			 
			}
		 	
		break;
		case 'web':
			$interestinfo = $detall->interestinfo->item; // array email + web
			if (arrayhasValue($interestinfo)){
				$out_web="";
				foreach($interestinfo as $iint => $field){					
					if($field->label=='Web'){
						if($field->label!=''){
							$out_web .= '<dt class="notranslate">'.$field->label.': </dt>';
						}
						$out_web .= '<dd><a href="http://'.$field->interinfo.'">'.$field->interinfo.'</a></dd>';
					}				
				}
			}
		break;
		case 'email':
		 	$interestinfo = $detall->interestinfo->item; // array email + web
			if (arrayhasValue($interestinfo)){
				$out_email = "";
				foreach($interestinfo as $iint => $field){					
						if($field->label!='Web'){
						if($field->label=='Email' || $field->label=='Adreça electrònica' || $field->label=='Correo electrónico'){			
							if($field->label!=''){
								$out_email .= '<dt class="notranslate">'.$field->label.': </dt>';
							}	
							$out_email .= '<dd class="notranslate"><a href="mailto:'.$field->interinfo.'">'.$field->interinfo.'</a></dd>';
						}else{
							if($field->label!=''){
								$out_email .= '<dt class="notranslate">'.$field->label.': </dt>';
							}	
							$out_email .= '<dd class="notranslate">'.$field->interinfo.'</dd>';
						}
					}
					
				}
			}
		break;
		case 'accessibility':
			$accessibility = $detall->accessibility;
			if (hasValue($accessibility)){ 
				$out_accessibility = '<p class="accessibility">'.$accessibility.'</p>';
			}
		 
		break;
		case 'ownership':
			$titularitat = $detall->titularitat;
			if (hasValue($titularitat)){
				$out_ownership = '<dl class="titularitat">';
					$out_ownership .= '<dt>'.$titularitat['label'].': </dt>';
					$out_ownership .= '<dd>'.$titularitat.'</dd>';
				$out_ownership .= '</dl>';
			}
		break;						
		case 'description':
			$desc = $detall->texte;				
			if (hasValue($desc)){ 
				$out_description = $desc;
			}		 
		break;
		case 'abstract':
			$resum = $detall->resum;
			if (hasValue($resum)){ 
				$out_abstract = $resum;
			}
		 
		break;
		case 'comments':
			$comments = $detall->comments; 
			if (hasValue($comments)){
				$out_comments = '<p>'.$comments.'</p>';
			}			
		break;
		case 'maps':
			//coordenades
			$gmapx = $detall->gmapx;
			$gmapy = $detall->gmapy;
			$coordaddressx = $detall->coordaddressx;
			$coordaddressy = $detall->coordaddressy;
			drupal_add_css(drupal_get_path('module', 'asia') .'/css/jquery.map-guia-1.0.css');
			drupal_add_js(drupal_get_path('module', 'asia') .'/js/jquery-gmapis-ui.min.js');
			drupal_add_js(drupal_get_path('module', 'asia') .'/js/jquery.fancybox-1.3.0.js');
			drupal_add_js(drupal_get_path('module', 'asia') .'/js/jquery.mousewheel.js');
			drupal_add_js(drupal_get_path('module', 'asia') .'/js/planol.js');
			drupal_add_js(drupal_get_path('module', 'asia') .'/js/gmaps.js');
			
			if(isset($gmapx)&& isset($coordaddressx)){
			$out_maps = '<div id="mapes">';
				$out_maps .= '<div id="mapadetall" ><div id="detallmap"></div></div>';
				$out_maps .= '<div id="mapaplanol" class="mapa_guia"></div>';
				$out_maps .= '<div id="mapastreet" ><div id="streetview" ></div></div>';
				$out_maps .= '<div id="changemap" style="display: block;"><a href="#mapaplanol" class="active">Plànol BCN</a> | <a href="#mapadetall">Google Maps</a> | <a href="#mapastreet">Street view</a></div>';
			$out_maps .= '</div>';
			
			?>

				
		                        
                               
                                                       
                            <script language="javascript" type="text/javascript">
							
							(function ($){
							//gmap
							$(document).bind('ready', function() {loadmapdetall(<?php echo $gmapx?>,<?php echo $gmapy?>,'','<?php echo $tp?>');});		
							//Planol
                            $(window).load(function () {
                                MapObject = $('.mapa_guia').map_guia({UseHistory : false, Width : 265, Height : 265, x : "<?php echo $coordaddressx?>", y : "<?php echo $coordaddressy?>", z: "5", capas : "P001K001K006K014",plot : "<?php echo $coordaddressx?>,<?php echo $coordaddressy?>" });
                            });
							
							})(jQuery);
                            </script>   
                            

 <?php 
}
			
			
		break;
		case 'howtogo':
		$comanar=$detall->link;
		if(isset($comanar)){
			$out_howtogo = '<div id="banners" class="notranslate">'; 
				$out_howtogo .= '<a href="'.$comanar['href'].'" class="com-anar">'.$comanar.'<span>'.t('Find the best way to go where you want.').'</span></a>';
			$out_howtogo .= '</div>';
		}
		 
		break;
		case 'tabinfomation':
		// Pestanya Informació
		$info = $detall->timetable->horari; //Array		
		$id_on = $detall->institution_id;
		
		if ($tp=="eq"){
			$info_rel = $detall->relations->section;
			$tit_info_rel = $detall->relations['labelsection']; 
			$info_relOtros = $detall->relations->item; //Array
			$tit_info_relOtros = $detall->relations['label']; 
		}else{
			$info_rel = $detall->relations->item; //Array
			$tit_info_rel = $detall->relations['label']; 
		}
		
		
		if (arrayhasValue($info) || arrayhasValue($info_rel) || arrayhasValue($info_relOtros)){
			$out_tabinfomation = '<div class="tabdetall" id="div-informacio">';

			if ($tp=='eq'){ 
				if (arrayhasValue($info)){
					
					$out_tabinfomation .= '<div id="horari">';// inici horaris
					$out_tabinfomation .= '<h3>'.t('Schedule').'</h3>';
					if(count($info)>1){
					$out_tabinfomation .= '<table>';
					$out_tabinfomation .= '<tbody>';
						$txt="";
						/*foreach($info as $iinfo => $field){
							if($txt==""){
								$out_tabinfomation .= '<h3>'.$field['label'].'</h3>';
							}
							$txt=$field['label'];
							if($txt!="Time tables" && $txt!="Horaris" && $txt!="Horarios" ){
								$out_tabinfomation .= '<h3>'.$txt.'</h3>';
							}
							$out_tabinfomation .= '<p>'.$field->periode.' '.$field->dies.' '.$field->hores.' '.$field->observacions.'</p>';
						}*/
						foreach($info as $iinfo => $field){
							$out_tabinfomation .= '<tr>';
						
							
							//periode
							if (hasValue($field->periode)){
								$out_tabinfomation .= '<td class="content-info">'.$field->periode.'</td>';
							}else{
								$out_tabinfomation .= '<td>'.$field->periode.'</td>';
							}
							
							//dies
							if (hasValue($field->dies)){
								$out_tabinfomation .= '<td class="content-info">'.$field->dies.'</td>';
							}else{
								$out_tabinfomation .= '<td>'.$field->dies.'</td>';
							}
							//hores
							if (hasValue($field->hores)){
								$out_tabinfomation .= '<td class="content-info">'.$field->hores.'</td>';
							}else{
								$out_tabinfomation .= '<td>'.$field->hores.'</td>';
							}				
							//preu
							if (hasValue($field->observacions)){
								$out_tabinfomation .= '<td class="content-info">'.$field->observacions.'</td>';
							}else{
								$out_tabinfomation .= '<td>'.$field->observacions.'</td>';
							}
							
							
							$out_tabinfomation .= '</tr>';
						}
					$out_tabinfomation .= '</tbody>';
					$out_tabinfomation .= '</table>';
					$out_tabinfomation .= '</div>'; // fi horari
					}else{
							$txt="";
						foreach($info as $iinfo => $field){
							$out_tabinfomation .= '<p>'.$field->periode.' '.$field->dies.' '.$field->hores.'. '.$field->observacions.'</p>';
							$out_tabinfomation .= '</div>'; // fi horari			
							if(hasValue($field->preu)){		
								$out_tabinfomation .= '<div class="preu"><h3>'.$field->preu['label'].'</h3>';
								$out_tabinfomation .= '<p>'.$field->preu.'</p></div>';
							}
							
						}
					}
					
				}
			}else{
				// Horari d'agenda
				if (arrayhasValue($info)){
					
					$out_tabinfomation .= '<div id="horari">';// inici horaris
					$out_tabinfomation .= '<h3>'.t('Schedule').'</h3>';
					if(count($info)>1){
					$out_tabinfomation .= '<table>';
					$out_tabinfomation .= '<tbody>';
						foreach($info as $iinfo => $field){
							$out_tabinfomation .= '<tr>';
						
							
							//periode
							if (hasValue($field->periode)){
								$out_tabinfomation .= '<td class="content-info">'.$field->periode.'</td>';
							}else{
								$out_tabinfomation .= '<td>'.$field->periode.'</td>';
							}
							
							//dies
							if (hasValue($field->dies)){
								$out_tabinfomation .= '<td class="content-info">'.$field->dies.'</td>';
							}else{
								$out_tabinfomation .= '<td>'.$field->dies.'</td>';
							}
							//hores
							if (hasValue($field->hores)){
								$out_tabinfomation .= '<td class="content-info">'.$field->hores.'</td>';
							}else{
								$out_tabinfomation .= '<td>'.$field->hores.'</td>';
							}
							//preu
							if (hasValue($field->preu)){
								$out_tabinfomation .= '<td class="content-info">'.$field->preu.'</td>';
							}else{
								$out_tabinfomation .= '<td>'.$field->preu.'</td>';
							}
							//preu
							if (hasValue($field->observacions)){
								$out_tabinfomation .= '<td class="content-info">'.$field->observacions.'</td>';
							}else{
								$out_tabinfomation .= '<td>'.$field->observacions.'</td>';
							}
							
							
							$out_tabinfomation .= '</tr>';
						}
					$out_tabinfomation .= '</tbody>';
					$out_tabinfomation .= '</table>';
					$out_tabinfomation .= '</div>'; // fi horari
					}else{
							$txt="";
						foreach($info as $iinfo => $field){
							$out_tabinfomation .= '<p>'.$field->periode.' '.$field->dies.' '.$field->hores.'. '.$field->observacions.'</p>';
							$out_tabinfomation .= '</div>'; // fi horari			
							if(hasValue($field->preu)){		
								$out_tabinfomation .= '<div class="preu"><h3>'.$field->preu['label'].'</h3>';
								$out_tabinfomation .= '<p>'.$field->preu.'</p></div>';
							}
							
						}
					}
					

				}
			}


			// Otros o informacio relacionada
	 
			if (arrayhasValue($info_rel)){
				$out_tabinfomation .= '<div>';
					$out_tabinfomation .= '<h3>'.$tit_info_rel.'</h3>';
					if($tp=='eq'){ 
						$out_tabinfomation .= '<ul class="notranslate">';
							foreach($info_rel as $irel => $field){
								if(hasValue($field->sectionname)){
									$out_tabinfomation .= '<li><a href="'.$base_url.'/detall/'.$field['href'].'">'.$field->sectionname.'</a></li>';
								}elseif(hasValue($field->institutionname)){
									$out_tabinfomation .= '<li><a href="'.$base_url.'/detall/'.$field['href'].'">'.$field->institutionname.'</a></li>';
								}
								
							}
						$out_tabinfomation .= '</ul>';
					}else{
						$out_tabinfomation .= '<dl>';
							foreach($info_rel as $irel => $field){
								$out_tabinfomation .= '<dt>'.$field->direct.': </dt><dd class="notranslate"><a href="'.$base_url.'/detall/'.$field['href'].'">'.$field->institutionname.'</a>. '.$field->comments.'</dd>';
							}
						$out_tabinfomation .= '</dl>';
					}	
				$out_tabinfomation .= '</div>';
			}
		if (isset($info_relOtros) && arrayhasValue($info_relOtros)){
				$out_tabinfomation .= '<div>';
					$out_tabinfomation .= '<h3>'.$tit_info_relOtros.'</h3>';
			
						$out_tabinfomation .= '<dl>';
							foreach($info_relOtros as $irel => $field){
								$out_tabinfomation .= '<dt>'.$field->direct.': </dt><dd class="notranslate"><a href="'.$base_url.'/detall/'.$field['href'].'">'.$field->institutionname.'</a>. '.$field->comments.'</dd>';
							}
						$out_tabinfomation .= '</dl>';
						
				$out_tabinfomation .= '</div>';
		}

			$out_tabinfomation .= '</div>'; //fi div-info

		}




		
		
		
		 
		break;				
		case 'tabactivities':
		 $ageq=$arrXml->ageq;
		 if (arrayhasValue($ageq)){
			$out_tabactivities = '<div class="tabdetall" id="div-ageq">';
				$out_tabactivities .= '<ul>';
					foreach($ageq->item as $iageq){
						$out_tabactivities .= '<li><a href="'.$base_url.'/detall/'.$iageq['href'].'">'.$iageq->actname.'</a>';
							$out_tabactivities .= '<dl>';
								if (hasValue($iageq->date)){
									$out_tabactivities .= '<dt class="notranslate">'.$iageq->date['label'].'</dt><dd>'.$iageq->date.'</dd>';
								}else{
									$out_tabactivities .= '<dt>'.$iageq->begindate['label2'].'</dt><dd>'.$iageq->begindate['label'].' '.$iageq->begindate.' '.$iageq->enddate['label'].' '.$iageq->enddate.'</dd>';
								}
							$out_tabactivities .= '</dl>';
						$out_tabactivities .= '</li>';
					}
				$out_tabactivities .= '</ul>';
			$out_tabactivities .= '</div>';
		}
		 
		 
		 
		break;	
		case 'tabneavy':
			$aprop=$arrXml->aprop;
			
		 	// Pestanya Aprop d'aqui
			if(isset($aprop->aparcs)){
			$aprop_aparcs = $aprop->aparcs->list->list_items->row; //Array
			}
			if(isset($aprop->restaurants)){
			$aprop_restau = $aprop->restaurants->list->list_items->row; //Array
			}
			
			if (isset($aprop_aparcs) || isset($aprop_restau)){
			$out_tabneavy = '<div class="tabdetall" id="div-aprop">';
				if (isset($aprop_aparcs)){
					$out_tabneavy .= '<h3>'.$aprop->aparcs['label'].'</h3>';
					foreach($aprop_aparcs as $iapracs =>$field){
						$out_tabneavy .= '<h4><a href="'.$base_url.'/detall/'.$field->item['href'].'" class="notranslate">'.$field->item->name.'</a></h4>';
						$out_tabneavy .= '<div class="dades">';
							$out_tabneavy .= '<p class="notranslate">'.$field->item->address.'</p>';
							$out_tabneavy .= '<p>'.$field->item->phonenumber.'</p>';
						$out_tabneavy .= '</div>';
		
					}
				}
				if (isset($aprop_restau)){
					$out_tabneavy .= '<h3>'.$aprop->restaurants['label'].'</h3>';	
					foreach($aprop_restau as $irestau =>$field){
						$out_tabneavy .= '<h4><a href="'.$base_url.'/detall/'.$field->item['href'].'" class="notranslate">'.$field->item->name.'</a></h4>';
						$out_tabneavy .= '<div class="dades">';
							$out_tabneavy .= '<p class="notranslate">'.$field->item->address.'</p>';
							$out_tabneavy .= '<p>'.$field->item->phonenumber.'</p>';
						$out_tabneavy .= '</div>';
					}
				}
			$out_tabneavy .= '</div>';
		}
    
			
		break;	
	}

}





?>

				
		                        
    
                            

 <?php 


/*****************************************************************/
/*                       PRESENTACIÓ                             */ 
/*****************************************************************/



?>

<div id="contenidor-detall" class="goog-trans-section">

<?php
if($tp=='eq'){
	print '<h1 class="notranslate">'.$name.'</h1>';
}else{	
	print '<h1>'.$name.'</h1>';
}

// Si esta activat el enllaç de tornar enrera a asia.admin.inc
if (isset($config_detall[1]) && $config_detall[1]==1){
?>
<p class="torna"><a href="<?php print $_SERVER['HTTP_REFERER']; ?>"><?php print t('Back') ?></a></p>
<?php
}
if(isset($config_detall[2]) && $config_detall[2]==2 && $language->language!="ca"){ ?>
        <div id="box-translate">
        <span class="info-translate">Traductor de Google:</span>
         <div class="goog-trans-control"></div>
         </div>
        <?php
		}
	print '<div id="fitxa">';
	print '<div class="detall">';//Inici de fitxa
			//Addthis
		
		if(isset($addthis['detall']) && $addthis['detall']==='detall'){
		?>
        <div id="addthis">
            <!-- AddThis Button BEGIN -->
            <div class="addthis_toolbox addthis_default_style ">
            <a class="addthis_button_preferred_1"></a>
            <a class="addthis_button_preferred_2"></a>
            <a class="addthis_button_preferred_3"></a>
            <a class="addthis_button_preferred_4"></a>
            <a class="addthis_button_compact"></a>
            <a class="addthis_counter addthis_bubble_style"></a>
            </div>
            <script type="text/javascript">var addthis_config = {"data_track_addressbar":false};</script>
            <script type="text/javascript" src="http://s7.addthis.com/js/300/addthis_widget.js#pubid=ra-5089049b7e37f4d5"></script>
            <!-- AddThis Button END -->    
        </div>
       <?php
		
	}
	
	//$name = '<span class="goog-trans-section">'.$name.'</span>';
	
	 if (hasValue($name)){ 
	 
	
	 $tags = array(
	  'title' => array(
		'#tag' => 'title',
		'#value' => strip_tags($name),
	  )
		);

	foreach ($tags as $key => $val) {
	  drupal_add_html_head($val, $key);
	}
	 
	 //drupal_set_title($name, $output = PASS_THROUGH);
	 }
		
			
		
		if (isset($out_picture)){print $out_picture;}

		// quan-on
		if ( isset($out_when) || isset($out_where)){
		print '<dl class="quan-on">';
			
			if (isset($out_when)){
				print $out_when;
			}
			if (isset($out_where)){
				print $out_where;
			}
			
		print '</dl>';
		}

		//direcció
		if(isset($out_street) || isset($out_district) || isset($out_area) || isset($out_cp) || isset($out_city)){
		print '<dl class="adreca">';
			if(isset($out_street)){
				print $out_street;
			}
			
			if(isset($out_district)){
				print $out_district;
			}
			
			if(isset($out_area)){
				print $out_area;
			}
			
			if(isset($out_cp)){
				print $out_cp;
			}
			if(isset($out_city)){
				print $out_city;
			}
			
			
			
		print '</dl>';
		}

		//telefons
		if (isset($out_phone) || isset($out_fax)){
			print '<dl class="phones">';
			if(isset($out_phone)){
				print $out_phone;
			}
			if(isset($out_fax)){
				print $out_fax;
			}
			print '</dl>';  
		}

		// informacíó email + web  
		if (isset($out_web) || isset($out_email)){
			print '<dl class="interestinfo">';
			if(isset($out_web)){
				print $out_web;
			}
			if(isset($out_email)){
				print $out_email;
			}
			print '</dl>';
		}
		
		//Status
		if (isset($out_status)){ 
			print '<p class="status notranslate">'.$out_status.'</p>';
		}
 
		// Accessibilitat
		if (isset($out_accessibility)){
			print $out_accessibility;	
		}

		// Titularitat
		if (isset($out_ownership)){
			print $out_ownership;			
		}

		// resum, descripció i comentaris
		if (isset($out_abstract) || isset($out_description) || isset($out_comments)){
			print '<div class="resum">';
			if (isset($out_abstract)){ 
				print $out_abstract;
			}
				
			if (isset($out_description)){ 
				print $out_description;
			}
			
			if (isset($out_comments)){
				print $out_comments;
			}			
			print '</div>';
		}
			
	print '</div>'; // Fi de detall

// Columna adicional amb el mapa i el  banner de com anar 
if(isset($out_maps) || isset($out_howtogo)){
?>

<div id="contingut-addicional">

	<?php 
		if(isset($out_maps)){
			print $out_maps; 
		}
		if(isset($out_howtogo)){
			print $out_howtogo; 
		}
	?>
 
</div>


<?php
}

print '</div>'; // fi div fitxa
// Menu de pestanyes

if(isset($out_tabinfomation) || isset($out_tabactivities) || isset($out_tabneavy)){

	print '<div id="contenidor-pestanes">'; 
	
		// Menú pestanyes
		print '<ul id="menu-pestanes" class="notranslate">';
			if(isset($out_tabinfomation)){
				print '<li id="informacio"><a href="#div-informacio">'.t('Information').'</a></li>';
			}
			if(isset($out_tabactivities)){
				print '<li id="ageq"><a href="#div-ageq">'.t('Events').'</a></li>';
			}
			if (isset($out_tabneavy)){
				print '<li id="aprop"><a href="#div-aprop">'.$aprop['label'].'</a></li>'; 
			}
		print '</ul>';

		//Pestanya informació pinta-la
		if(isset($out_tabinfomation)){
			print $out_tabinfomation;
		}
		// Pestanya Agenda d'un equipament
		if(isset($out_tabactivities)){
			 print $out_tabactivities;
		}
		// Pestanya Aprop d'aquí
		if (isset($out_tabneavy)){
			print $out_tabneavy;
		}
	print '</div>';  //fi pestañes
}
?>
</div><!-- contenidor -->
   
<?php }else{ // Si el xml ve buit

print '<div id="contenidor-detall">';
print '<p class="torna"><a href="'.$base_url.'">'.t('Back').'</a></p>';

	print '<div class="detall">';//Inici de fitxa
		print '<p>'.t('Page not found').'</p>';	
	print '</div>';
print '</div>';

}

?>
