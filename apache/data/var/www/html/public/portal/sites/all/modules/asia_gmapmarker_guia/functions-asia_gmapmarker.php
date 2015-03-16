<?php

//*****************************/
/* Functions de blocks       */
/*                           */
/*****************************/


function mostra_gmapmarker(){
	global $language;
	$idma = $language->language;  	
	
	
	$gmcanal =  variable_get('gmcanal','');  
	$activeList = variable_get('gmactivelist', '');	
	$nr = variable_get('gmnr', '');	
	$typelist = variable_get('gmtipus', '');
	$items = variable_get('listcriteris', '');
	
	
	
	$urlJson = "http://guia.bcn.cat/index.php?pg=search&xout=json";

	if($gmcanal != "" && $gmcanal != "<none>" ){
		$canal = $gmcanal;
	}elseif($gmcanal == "<none>"){
		$canal = '';  
	}else{
		$canal = variable_get('asia_canal','');  
	}
	
	if($canal !=""){
		$urlJson = $urlJson."&canal=".$canal;
	}	

	if($nr != ""){
		$urlJson = $urlJson."&nr=".$nr;
	}
	
	if($typelist[1]==1 && $typelist[2]==2){
		$urlJson = $urlJson;
	}elseif($typelist[1]==1){
		$urlJson = $urlJson."&type=AG";
	}elseif($typelist[2]==2){
		$urlJson = $urlJson."&type=EQ";
		
	}
	
	$urlJson = $urlJson."&idma=".$idma;

	
	$variables = array(
    	'urljson' => $urlJson,		
		'activeList' => $activeList,			
		'nr' => $nr,	
		'itemlist' => $items,
	);
  
  	//mostra tpl mapa	
	return theme('gmapmarker', $variables);
}

function sanear_text($string) {
	utf8_encode($string);
	$a = array('á','é','í','ó','ú','à','è','ì','ò','ù','ä','ë','ï','ö','ü','â','ê','î','ô','û','ñ','ç',' ');
	$b = array('a','e','i','o','u','a','e','i','o','u','a','e','i','o','u','a','e','i','o','u','n','c','-');
	$string = str_replace($a, $b, $string);
	$string = strtolower($string);
	$string = str_replace('[^A-Za-z0-9-]', '', $string);
	return $string;
}