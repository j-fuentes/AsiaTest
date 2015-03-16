<?php
/**
* @file especialitat.tpl.php
* 
*
* - $arrXml
*
* 
*/

/* Variables */
global $language;
$base_url=$GLOBALS['base_url'].'/'.$language->language;
?>

<?php  
//print '<pre>'. check_plain(print_r($fieldsshow, 1)) .'</pre>'; 

//Si esta activat en el settings el enllaç de mes activitats $settings_asia_list[1] valida la url.
if(isset($settings_asia_list[1])){
	if(hasvalue($urlmoreinfo) && $settings_asia_list[1]==1){		
		$urlmoreinfo='?'.substr($urlmoreinfo,1);
		$urlmoreinfo=str_replace("&", "&amp;", $urlmoreinfo);
		
	}
}



// Si hi han resultats
if(count($arrXml->search->noresults->query)==0){


print '<div id="properes-activitats">';

$result=$arrXml->search->queryresponse->list->list_items->row;

	foreach($result as $llistat) {
		$item = $llistat->item;
		$name = parsejaComilles($item->name);		
		$id = $item['href'];
		$pos = $item->pos;
		$address = parsejaComilles($item->address);
		$district = $item->district;
		$web = $item->code_url;		
		$tit_address = $item->address['label'];
		$picture = $item->internetref;
		$phone = $item->phonenumber;
		$tp = strtolower($item->tp);
		$type = $item->type;				
		$sectionname = parsejaComilles($item->sectionname);
		$city = $item->city;
		
		//Si es tipus agenda agafa el on i el quan
		if($tp=='ag'){
			$on = $item->institutionname;
			$tit_on = $item->institutionname['label'];
			$id_on = $item->equipment_id['href'];
			$quan = $item->date;
			$tit_quan = $item->date['label'];
		}
		
		// comença a pintar un item del llistat
		print '<div>';
		
			$href = $base_url.'/detall/'.$id;
			
			if (hasValue($sectionname)){ $nom = $sectionname.' - '.$name; }
			else $nom = $name;
			
			print '<h3 class="properes"><a href="'.$href.'">'.$nom.'</a></h3>';
			// Si esta activat el camp picture en asia_list.module
				if(isset($fieldsshow) && $fieldsshow[1]==1){
					if (verificar_url($picture)){ 
						print '<img alt="" src="'.$picture.'"/>';	
					}
				}
			// Si esta configurat asia_list.module algun dels camps asia_list.module	
			if(isset($fieldsshow) && $fieldsshow[2]==2 || $fieldsshow[3]==3 || $fieldsshow[4]==4 || $fieldsshow[5]==5){	
			print '<div class="dades">';				
				print '<dl>';
				// Si esta activat el camp when en asia_list.module
				if(isset($fieldsshow) && $fieldsshow[2]==2){
					if (hasValue($quan)){
						print '<dt>'.$tit_quan.'</dt>';
						print '<dd>'.$quan.'</dd>';
					}else if (hasValue($item->begindate) || hasValue($item->enddate)){
						print '<dt>'.$item->begindate['label2'].'</dt>';
						print '<dd>'.$item->begindate['label'].' '.$item->begindate.' '.$item->enddate['label'].' '.$item->enddate.'.</dd>';
					}		
				}
				// Si esta activat el camp where en asia_list.module
				if (hasValue($on) && isset($fieldsshow) && $fieldsshow[3]==3){
					print '<dt>'.$tit_on.'</dt>';
					print '<dd><a href="'.$base_url.'/detall/'.$id_on.'">'.$on.'</a></dd>';
				}
				
				// Si esta activat el camp address en asia_list.module
				if (hasValue($address) && isset($fieldsshow) && $fieldsshow[4]==4){
					print '<dd>'.$address;
					if(hasValue($district)){
						print ' ('.$district.')</dd>';
					}else{
						print ' ('.$city.')</dd>';
					}
				}
				if (hasValue($phone) && isset($fieldsshow) && $fieldsshow[5]==5){
					print '<dd>'.$phone.'</dd>';
				}
				print '</dl>';		
			
			
		
			print '</div>';
			} // fi caixa dades
		
		print '</div>'; // final del item d'un llistat
		

	  
		
				
		}
//si esta activat el check de mes info en el settings del block		
	if(isset($settings_asia_list[1]) && $settings_asia_list[1]==1){	
		if($urlmoreinfo!=""){	
			print '<p><a href="'.$base_url.'/llistat'.$urlmoreinfo.'&type=AG">'.t('More activities').'</a></p>';	
		}else{
			print '<p><a href="'.$base_url.'/llistat?type=AG">'.t('More activities').'</a></p>';	
		}
	}
 print '</div>';
 
}else{ //Si la cerca no te resultats
	print '<p class="noresults">'.$arrXml->search->noresults->query.'</p>';
} 

?>