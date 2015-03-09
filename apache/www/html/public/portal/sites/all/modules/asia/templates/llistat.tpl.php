<?php
/**
* @file llista-asia.tpl.php
* Renderiza una lista de items.
*
* - $items
*
* 
*/
//print '<pre>'. check_plain(print_r($dis->gmap->script[1]->div, 1)) .'</pre>';
$url_page="http://".$_SERVER['HTTP_HOST'].$_SERVER['REQUEST_URI'];
$url_page=substr($url_page,0,strpos($url_page, '?'));	


//Recollir variables
global $language;
$base_url = $GLOBALS['base_url'].'/'.$language->language;

// titGeolocalizació
if(isset($dis->gmap['label'])){
	$titGeo=$dis->gmap['label'];
}else{
	$titGeo=t('Geolocation results');
}



//Variable per definir i substituir el titol per un nou ex: "&titleseccio=Nou+Titol"
$titleSeccio = "";
$strVariablesUrl = "";
$etiquetes = "";

if(isset($_GET["titleseccio"])){
	$titleSeccio = $_GET["titleseccio"];
}
	
// Si esta activat els "filtres generics" de la pàgina de configuració asia.admin.inc
// recull per url la variable "&filters=disabled"
$filters = "";	
if(isset($config[2]) && $config[2]==2){
	
	if(isset($_GET["filters"])){
		$filters = $_GET["filters"];
	}
}
// Si esta activat per configuracio asia.admin.inc les etiquetes de categoria
// recull per url la variable 

if(isset($display[1]) && $display[1]==1){
	if(isset($_GET["etiquetes"])){
		$etiquetes = $_GET["etiquetes"];
	}
}


// Recull variable per url i les guarda en un string
if(hasValue($filters)){ $strVariablesUrl .= "&filters=".$filters;  }
if(hasValue($titleSeccio)){ $strVariablesUrl .= "&titleseccio=".$titleSeccio; }
if(hasValue($etiquetes)){ $strVariablesUrl .= "&etiquetes=".$etiquetes; }


$strVariablesUrl=parsejaUrl($strVariablesUrl);


//si el mapa esta activat a la pàgina de comfiguració asia.admin.inc.
$mostraMapa = "";
if(isset($config[1]) && $config[1]==0){
	$mostraMapa = 0;
}else{
	$mostraMapa = 1;
}

// numero de punts que tenen geolocalització
if(isset($dis->gmap->script[1]->div)){
	$puntsGeo=count($dis->gmap->script[1]->div);
}else{
	$puntsGeo=0;
}



// Si el mapa esta activat a la pàgina de configuració asia.admin.inc.
if($mostraMapa==1){
?>


<script id="markers" type="text/javascript">

var map;
var activeWindow = null;
var markers_arr = new Array();
var nIcon = 0;
var latlng_pos = [];
var latlngbounds;
function saveMarker(_posicio, _gmapx, _gmapy, _address, _type,  _nom, _href){
	
	_pos = Number(_posicio);
		
	if(markers_arr[_pos] != undefined) markers_arr[_pos].events += '<h3><a href="'+_href+'">'+_nom+'</a></h3>';
	else {
		
		var obj = new Object();
			obj.lat = _gmapx;
			obj.lng = _gmapy;
			obj.events = '<h3><a href="'+_href+'">'+_nom+'</a></h3>';
			obj.type = _type;
			obj.pos = _pos;
			obj.address = _address;
		
		markers_arr[_pos] = obj;
		
		latlng_pos[nIcon] = new google.maps.LatLng(obj.lat,obj.lng);
        nIcon++;

	}
}
/* Mostra */
function pushMarker(_marker){
	if(_marker.type=="eq"){
	var img = '<?php echo $GLOBALS['base_url'] . '/' . drupal_get_path('module', 'asia') ?>/img/equipament/' + _marker.type +'-'+ _marker.pos + '.png';	
	}
	if(_marker.type=="ag"){
	var img = '<?php echo $GLOBALS['base_url'] . '/' . drupal_get_path('module', 'asia') ?>/img/agenda/' + _marker.type +'-'+ _marker.pos + '.png';	
	
	

	}
	
	var html = "<div class='bubble'>"+ _marker.events + "<p>" + _marker.address + "</p></div>";
    var infowindow = new google.maps.InfoWindow({ content: html });	
   
    var marker = new google.maps.Marker({ position: new google.maps.LatLng(_marker.lat, _marker.lng), map: map, icon: img });   
	google.maps.event.addListener(marker, 'click', function() { 
		if(activeWindow != null) activeWindow.close(); 
		infowindow.open(map,marker);
		activeWindow = infowindow; 
	});
}

function initialize() {

	var myOptions = {
		zoom: 12,
		center: new google.maps.LatLng(41.398479, 2.184804),
		mapTypeId: google.maps.MapTypeId.ROADMAP,
		zoomControl: true,
		zoomControlOptions: {
		  style: google.maps.ZoomControlStyle.SMALL
		}
	}
	map = new google.maps.Map(document.getElementById("map_canvas"), myOptions);
	
	for (var marker in markers_arr) pushMarker(markers_arr[marker]);
	
	// Centrar el mapa segons els markers:
	latlngbounds = new google.maps.LatLngBounds();
	for ( var i = 0; i < latlng_pos.length; i++ ) {
		latlngbounds.extend( latlng_pos[ i ] );
	}
	map.fitBounds( latlngbounds );
}
(function ($){
$(document).ready(function(e) {
   <?php
   if(count($dis->search->noresults->query)==0){
	
	
	
	$result=$dis->search->queryresponse->list->list_items->row;

	foreach($result as $llistat) {
		$item = $llistat->item;
		$name = parsejaComilles($item->name);
		$pos = $item->pos;		
		$address = parsejaComilles($item->address);		
		$tp = strtolower($item->tp);
		$gmapx = $item->gmapx;
		$gmapy = $item->gmapy;		
		$id = $item['href'];
		$sectionname=parsejaComilles($item->sectionname);

		// comença a pintar un item del llistat
	
		if (hasValue($sectionname)){ $nom = $sectionname.' - '.$name; }
			else $nom = $name;
			$href = 'detall/'.$id;
			
		 if(hasValue($pos) && hasValue($address) && hasValue($gmapx) && hasValue($gmapx) ){
		
		
			?>
			
				saveMarker(<?php echo "$pos, $gmapx, $gmapy, '$address', '$tp', '$nom', '$href'"; ?>);	
            
			<?php
			 }	
		}	?>

	initialize();
	
	  <?php }	?>

	

	
});
})(jQuery);
</script>


<?php } ?>
<div id="wrapper-results">
<div id="results-asia">
<?php 


//Filtres generics

//Si els filtres estan activats en la pàgina de configuració 
//i el parametre de filters no esta desactivat per la url ("&filters=disabled")


if(isset($config[2]) && $config[2]==2 && $filters!=="disabled"){

//Si hi han filtres

if(isset($dis->search->bleft->leftfilter->facetlist)){
	
	$filtres = $dis->search->bleft->leftfilter->facetlist;
		
	print '<div id="filtres-generics">';
	print '<h2>'.$filtres['label'].'</h2>';	
	print '<div id="llistat-filtres">';
	//type
	
	
	foreach($filtres->children() as $itype){
		
			$name = $itype->getName();	
			
			if($name=='class'){
				$name=$itype['treeid'];
			}
			
			if (in_array($name, $blockfilters)) {					
				$estatAG=false;
				$estatEQ=false;			
				if ($name==400){
								
					foreach($itype->back as $back) {  
						if (!in_array($back['code'], $codefilters)) {
							$estatAG=true;
							break;
						}
						
					}
					foreach($itype->item as $item) { 					
						if (!in_array($item['code'], $codefilters)) {	
							$estatAG=true;
							break;
						}
					}					
				}
				
				if ($name==401){
										
					foreach($itype->back as $back) {  
						if (!in_array($back['code'], $codefilters)) {
							$estatEQ=true;
							break;
						}
						
					}
					foreach($itype->item as $item) { 					
						if (!in_array($item['code'], $codefilters)) {	
							$estatEQ=true;
							break;
						}
					}					
				}
				
				    if($estatEQ || $estatAG || ($name!=401 && $name!=400)){
									
						print '<div class="caixa">';			
						if($name != "type"){
							print '<h3>'.$itype['name'].'</h3>';
						}
						print '<ul>';
						
						foreach($itype->back as $back) {  
							if (!in_array($back['code'], $codefilters)) {
								print '<li>';
								if (isset($back['href'])){							
									print '<a href="'.retallaUrl($back['href']).$strVariablesUrl.'">'.$back['name'].' (X)</a>';
								}else{
									print $back['name'];
								}
								print '</li>';
							}
						}
						foreach($itype->item as $item) { 
							
							
								if (!in_array($item['code'], $codefilters)) {
									print '<li>';
									if (isset($item['href'])){											
										print '<a href="'.retallaUrl($item['href']).$strVariablesUrl.'">'.$item['name'].' ('.$item.')</a>';
									}else{
										print $item['name'];
										if(isset($item)){ 
											print ' ('.$item.')';
										}
									}
									print '</li>';		
								}
							
						}	
						print '</ul></div>';
				  }
			}
			
	}
	
	
	print '</div>';
	print '</div>';
}
}
//fi filtres generics






?>





<div id="contingut-asia" class="llistat-cerca">

<?php
	//Si ver per url un nou titol "$titleseccio=Nou+Títol"
	//canvia el <title> de la pàgina
	//canvia el h2 i el fil-ariadna

	  if(hasValue($titleSeccio)){ 
		  drupal_set_title($titleSeccio) ;
		  //print "<h2 class='seccio'>".$titleSeccio."</h2>";
		  
		  $breadcrumb = array();
		  $breadcrumb[] = l(t('Home'), '<front>');
		  $breadcrumb[] = drupal_get_title(); // Link to current URL
		  // Set Breadcrumbs
		  drupal_set_breadcrumb($breadcrumb);
		 // print theme ( 'breadcrumb' , array( 'breadcrumb' => drupal_get_breadcrumb ())); 
		  
		  
	  }
// Si la cerca te resultats

if(count($dis->search->noresults->query)==0){
	
	
	
	$result=$dis->search->queryresponse->list->list_items->row;
	$tpage=$dis->search->queryresponse->list->found;
	// Títol "Resultats de la cerca".
		
    	print '<h2>'.$tpage['vis'].'<span> '.$tpage['from'].'</span> '.$tpage['al'].' <span>'.$tpage['to'].'</span> '.$tpage['de'].' <span>'.$tpage['total'].'</span>';
	
		if ( $dis->search->writtenquery != ""){
  			print ' '.$tpage['results'].' <span>'.$dis->search->writtenquery.'</span>';
		}	
		print ".</h2>";

	?>
	
	<?php
	 
	

// Filtres de capçalera per popilaritat o alfabeticament + select de numero de resultats

if (isset($dis->search->queryresponse->list->lst_info->numrows )){
	print '<div id="accions">';
	
		$action = retallaUrl($dis->search->queryresponse->list->lst_info->numrows['href']).$strVariablesUrl;
		$sinsort = $action.'&amp;nr='.$dis->search->queryresponse->list->lst_info->numrows['selected'];
		$sinsort = explode('&amp;',$sinsort);	
		
		foreach ($sinsort as $i => $value) {
		  
		  if(!strstr($value, 'sort=')){
		  	if($i==0){
				$actionsinsort = $value;
		  	}else{
		  		$actionsinsort .= '&amp;'.$value;		  	
		  	}		    
			}
		}	
		
		
		
	print '<dl>';
	print '<dt>'.$dis->search->queryresponse->list->lst_info->sort['label'].'</dt>';
	if ($dis->search->queryresponse->list->lst_info->sort['selected']=="popularity" ){
		print '<dd>'.$dis->search->queryresponse->list->lst_info->sort->popularity.'</dd>';		
	}else{
		print '<dd><a href="'.$actionsinsort.'&amp;sort=popularity,desc">'.$dis->search->queryresponse->list->lst_info->sort->popularity.'</a></dd>';
	}
	if ($dis->search->queryresponse->list->lst_info->sort['selected']=="namesort"){
		print '<dd>'.$dis->search->queryresponse->list->lst_info->sort->namesort.'</dd>';		
	}else{
		print '<dd><a href="'.$actionsinsort.'&amp;sort=namesort,asc">'.$dis->search->queryresponse->list->lst_info->sort->namesort.'</a></dd>';		
	}
	
	print '</dl>';
	
	// numero de items 10,20,30,40,50
	$options=$dis->search->queryresponse->list->lst_info->numrows->option;
	if(arrayhasValue($options)){
	
		
		print '<select id="nr" href="'.$base_url.'/llistat'.$action.'" name="nr">';
		foreach($options as $ioption) {   
			if (hasValue($ioption['selected'])){
				print '<option selected="selected" value="'.$ioption['value'].'">'.$ioption.'</option>';
			}else{
				print '<option value="'.$ioption['value'].'">'.$ioption.'</option>';
			}	
		}
		print '</select>';
	}
	print '</div>';
}


	 
	 
	 print '<div class="info-llistat">';
	 //Si mapa esta activat
	 if($mostraMapa==1 && $puntsGeo!=0){
	 ?>
	 
	  <div id="mapa">
         <div id="content-mapa">
            <h3 class="mapa"><span><?php echo $titGeo ?></span></h3>
       		<div id="map_canvas" style="width:<?php echo $amplada.'px'?>; height:<?php echo $alcada.'px'?>;"></div>
         </div>
        </div>
        
           
 	 <?php  
	  print '<div id="llistat-resultats"  class="amb-mapa">';
	 }else{
	  print '<div id="llistat-resultats">';
	 }
	 
	 
   
	if (count($dis->search->filters->item)!=0 && $filters!="disabled"){
		$estatFiltre=false;
		// Si existeixen filtres i aquests no estan ocults
		 foreach($dis->search->filters->item as $ifiltre) {    		
                    if (!in_array($ifiltre['code'], $codefilters)) {
						$estatFiltre=true;
						break;  	
					}
		 }
		if($estatFiltre==true){
		
	 ?>
        <div class="filtres">
            <?php    
            print '<h3>'.$dis->search->filters['label'].'</h3>';            
            print '<ul>';		
            // Si el camp de la url districte no existeix mostram els filtres
            
            /*if(isset($mapadistrictes)){ 
                print '<li>'.$districte.'</li>';
            }else{*/ // si existeix camp districte mostram districte com a filtre                       	
				 foreach($dis->search->filters->item as $ifiltre) {    		
                    if (!in_array($ifiltre['code'], $codefilters)) {
						if(strpos($ifiltre['href'], '?')!==false){                      				
							print '<li>'.$ifiltre.' <a href="'.retallaUrl($ifiltre['href']).$strVariablesUrl.'">[x]</a></li>';
						}else{
							print '<li>'.$ifiltre.' <a href="'. $url_page.'">[x]</a></li>';
						}
					
					}
                }// fi del foreach
				
			
			
            /*}*/
            print '</ul>';
			
            ?>
        </div>
    
    <?php 

	}// fi de $estatFiltre
	} ?>
    
    
    
    
    
    
	<?php
	
	$markers_array = array();
	// Recull informacio de cada item del llistat
	foreach($result as $llistat) {
		$item = $llistat->item;
		$name = parsejaComilles($item->name);				
		$id=$item['href'];
		$pos=$item->pos;
		
		$district = $item->district;
		$web = $item->code_url;	
		$address = parsejaComilles($item->address);		
		$tit_address = $item->address['label'];
		$picture = $item->internetref;
		$phone = $item->phonenumber;
		$tp = strtolower($item->tp);
		$type = $item->type;
		$gmapx = $item->gmapx;
		$gmapy = $item->gmapy;		
		$sectionname = parsejaComilles($item->sectionname);
		$city = $item->city;		
		
		if($tp=='ag'){
			$on = $item->institutionname;
			$tit_on = $item->institutionname['label'];
			$id_on = $item->equipment_id['href'];
			$quan = $item->date;
			$tit_quan = $item->date['label'];
		}
		// comença a pintar un item del llistat
		print '<div>';
		
			$href = 'detall/'.$id;
			
			if (hasValue($sectionname)){ $nom = $sectionname.' - '.$name; }
			else $nom = $name;
			
			print '<h3><a href="'.$href.'">'.$nom.'</a></h3>';
			
			if($mostraMapa==1){
			?>
			<!--<script type="text/javascript">
			(function($){
				saveMarker(<?php //echo "$pos, $gmapx, $gmapy, '$address', '$tp', '$nom', '$href'"; ?>);	
			})(jQuery);
			</script>-->
			<?php
			}
			// si esta activat el camp de "imatge" en el asia-list.admin.inc
			if(isset($display) && $display[2]==2){
				if (verificar_url($picture)){ 
					$picture=str_replace("&", "&amp;", $picture);
					print '<img alt="" src="'.$picture.'"/>';	
				}
			}
			// Si esta configurat asia_list.module algun dels camps asia-list.admin.inc
			if(isset($display) && $display[3]==3 || $display[4]==4 || $display[5]==5 || $display[6]==6){	
			print '<div class="dades">';
			
			if($tp=='eq'){	
				
				if (hasValue($address) && isset($display) && $display[5]==5){
					print '<p>'.$address;
					if(hasValue($district)){
						print ' ('.$district.')</p>';
					}else{
						print ' ('.$city.')</p>';
					}
				}
				
				
				if (hasValue($phone) && isset($display) && $display[6]==6){
					print '<p>'.$phone.'</p>';
				}
				if (hasValue($web) && isset($display) && $display[7]==7){ 
					print '<a href="http://'.$web.'">'.$web.'</a>';
				}
				
			}else{
				
				print '<dl>';
				// Si esta activat el camp when en asia-list.admin.inc
				if(isset($display) && $display[3]==3){
					if (hasValue($quan)){
						print '<dt>'.$tit_quan.'</dt>';
						print '<dd>'.$quan.'</dd>';
					}else if (hasValue($item->begindate) || hasValue($item->enddate)){
						print '<dt>'.$item->begindate['label2'].'</dt>';
						print '<dd>'.$item->begindate['label'].' '.$item->begindate.' '.$item->enddate['label'].' '.$item->enddate.'.</dd>';
					}		
				}
				
				
				
				// Si esta activat el camp where en asia-list.admin.inc
				if (hasValue($on) && isset($display) && $display[4]==4){
				print '<dt>'.$tit_on.'</dt>';
				print '<dd>';
				if(hasValue($id_on)){
					print '<a href="detall/'.$id_on.'">'.$on.'</a>';				
				}else{
					print $on;				
				}
				print '</dd>';
				
				//print '<dd><a href="detall/'.$id_on.'">'.$on.'</a></dd>';
				}
				// Si esta activat el camp address en asia-list.admin.inc
				if (hasValue($address) && isset($display) && $display[5]==5){
					print '<dd>'.$address;
					if(hasValue($district)){
						print ' ('.$district.')</dd>';
					}elseif(hasValue($city)){
						print ' ('.$city.')</dd>';
					}
				}
				if (hasValue($phone) && isset($display) && $display[6]==6){
					print '<dd>'.$phone.'</dd>';
				}
				print '</dl>';
				
			}	
			// si esta activades les etiquetes per configuració i per parametres de la url "&etiquetes=disabled" no ve desactivat
			// Pintam l'etiqueta (Agenda / Entitats i equipaments)
			if (hasValue($type) && isset($display[1]) && $display[1]==1 && $etiquetes!="disabled"){ print '<p class="cat-'.$tp.'"><span>'.$type.'</span></p>';}
			print '</div>';
			} // fi div dades
			// Si mapa esta activat en asia.admin.inc i te posició el item amb cordenades
			// pintam el icona segons la categoria si es agenda o equipament
			if($pos != "" && $mostraMapa==1) {
				if($tp=='eq'){
				
					
					print '<img src="'.$GLOBALS['base_url'] . '/' . drupal_get_path('module', 'asia') . '/img/equipament/'.$tp.'-li-'.$pos.'.png" alt="" class="icona" />';
				}else if($tp=='ag'){
					print '<img src="'.$GLOBALS['base_url'] . '/' . drupal_get_path('module', 'asia') . '/img/agenda/'.$tp.'-li-'.$pos.'.png" alt="" class="icona nadal" />';
				}
			}
		print '</div>'; // final del item d'un llistat
		
				
		}
		
		// PAGINADOR
		// Si  te pagines pinta pàgina actual
		if (arrayhasValue($dis->search->queryresponse->list->lst_info->pags)){
		print '<div class="paginador">';
		
			// Pinta l'enllaç "anterior" si existeix		
			if(hasValue($dis->search->queryresponse->list->lst_info->pags->prev)){				
				print '<p class="prev"><a href="'.retallaUrl($dis->search->queryresponse->list->lst_info->pags->prev['href']).$strVariablesUrl.'">'.$dis->search->queryresponse->list->lst_info->pags->prev.'</a></p>';
				
			}
			// Pinta llistat de pagines		
			print '<ul>';	
		
			foreach($dis->search->queryresponse->list->lst_info->pags->pag as $pag) {  
				
				if(strpos($pag['href'], '?')!==false){
					print '<li><a href="'.retallaUrl($pag['href']).$strVariablesUrl.'">'.$pag.'</a></li>';
				}else{
					print '<li>'.$pag.'</li>';
				}
			}
		
			print '</ul>';
			// Pinta l'enllaç "seguent" si existeix
			if(hasValue($dis->search->queryresponse->list->lst_info->pags->next)){						
				print '<p class="next"><a href="'.retallaUrl($dis->search->queryresponse->list->lst_info->pags->next['href']).$strVariablesUrl.'">'.$dis->search->queryresponse->list->lst_info->pags->next.'</a></p>';				
			}
		
		print '</div>'; // fi paginador;
		}
		
	
		?>
		
		
		</div>
        <?php
        
		?>
       
<?php 
		print '</div>';// fi info-llistat
		
	
		
	
		
}else{ // Si la cerca no te resultats
	print '<p class="noresults">'.$dis->search->noresults->query.'</p>';
}    
    ?>
    
	 
</div>
</div>
</div>
<?php
	// Si l'addthis esta activat a la pàgina de configuració asia.admin.inc
		if(isset($addthis['llistat']) && $addthis['llistat']==='llistat'){
		?>
         <div id="addthis">
            <!-- AddThis Button BEGIN -->
            <div class="addthis_toolbox addthis_default_style">
            <a class="addthis_button_preferred_1"></a>
            <a class="addthis_button_preferred_2"></a>
            <a class="addthis_button_preferred_3"></a>
            <a class="addthis_button_preferred_4"></a>
            <a class="addthis_button_compact"></a>
            <a class="addthis_counter addthis_bubble_style"></a>
            </div>
            <script type="text/javascript">var addthis_config = {"data_track_addressbar":false};</script>
            <script type="text/javascript" src="http://s7.addthis.com/js/300/addthis_widget.js#pubid=ra-5089049b7e37f4d5?domready=1"></script>
            <!-- AddThis Button END -->    
        
        </div>
            <?php
		
	} ?>