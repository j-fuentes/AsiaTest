<?php

/*************************************************************/
/* Funciones Genèriques***************************************/
/*************************************************************/


function hasValue($var){
	if ($var=='' || $var == 'null' || $var == 'undefined' || !isset($var)) return false;
	else return true;
}


function arrayhasValue($var){
	if (count($var)<=0) return false;
	else return true;
}
function verificar_url($url)
{
   //abrimos el archivo en lectura
   $id = @fopen($url,"r");
   //hacemos las comprobaciones
   if ($id) $abierto = true;
   else $abierto = false;
   //devolvemos el valor
   return $abierto;
   //cerramos el archivo
   fclose($id);
}

/* Parseig de url del llistat */
function retallaUrl($href){		
	$href=substr($href ,strpos($href, '?'));			
    $href=str_replace("q=", "cerca=", $href);					
	return parsejaUrl($href);
}

function parsejaUrl($str){		
	$str=str_replace(" ", "+", $str);		
	$str=str_replace("&", "&amp;", $str);		
	return $str;
}

function parsejaComilles($str){
	$str = htmlspecialchars($str, ENT_QUOTES);
	$str = htmlspecialchars_decode( $str, ENT_NOQUOTES );
	$str = urldecode($str);
	return $str;
}

/*****************************/
/* Detalls                   */
/*****************************/



function asia_detall($strhref) {
	
	try{
		global $language;
		$idma = $language->language;
		$addthis = variable_get('asia_addthis','');
		$config_detall = variable_get('asia_config_detall','');
		$display = variable_get('asia_display_detail','');
		$arrayfields=array();
		foreach($display as $field){
			if($field!==0){
				$arrayfields[] = $field;
			}			
		}
	
		// Treiem el id de la url
		$strhref=substr($strhref,(strpos($strhref,'_')+1));
		$id_detall=substr($strhref,0,(strpos($strhref,'.html')));

		$url = "http://guia.bcn.cat/?pg=detall&id_doc=".$id_detall."&xout=1&ajax=detall&idma=".$idma;
	
	
		if(isset($_GET["param"])){
			
			if($_GET["param"] == 1){
				print $url;
			}
		}
	
		//Si no encuentra información del detalle que no hay xml la variable arrXml és vacia.
		
		if (@file_get_contents($url) == false){ 
			$arrXml = "";
			
		}else{ 
			$str = file_get_contents($url);
			$arrXml = new SimpleXmlElement($str);
		} 

		
	
		$variables = array(
			'arrXml' => $arrXml,
			'addthis' => $addthis,		
			'config_detall' => $config_detall,
			'display' => $arrayfields,
		);	


		return theme('asia_detall', $variables);

	}catch (Exception $e) {		
	if(isset($_GET["param"])){
			
			if($_GET["param"] == 1){
				print $url;
			}
		}
		$variables = array(
    		'arrXml' => "",
			'addthis' => $addthis,	
			'config_detall' => $config_detall,
			'display' => $arrayfields,
		);		

		return theme('asia_detall', $variables);
	}

}


/*****************************/
/* Llistats                  */
/*                           */
/*****************************/
function llistat() {
 
// Creació de la url per cridar a Àsia.


$url = "http://guia.bcn.cat/?pg=search&xout=1&ajax=search";
$amplada = variable_get('asia_maplist_amplada','');
$alcada = variable_get('asia_maplist_alcada','');
$config = variable_get('asia_config_resultats','');
$display = variable_get('asia_display_list','');
$addthis = variable_get('asia_addthis','');



/* redefinir el canal */
//si en la configuracio hi ha canal, guarda canal
$canal = variable_get('asia_canal','');

// si hi ha en la url informació del canal redefineix el canal i pilla el de la url.
if(isset($_GET["canal"])){
	$canal = $_GET["canal"];
}
/**/

if($canal!=""){
	$url = $url."&canal=".$canal;	
}

if(isset($_GET["cerca"])){
	$cerca = str_replace( " " ,"+",$_GET["cerca"]);
	$url = $url."&q=".$cerca;
}

if(isset($_GET["districtstr"])){
	$districte =  str_replace( " " ,"+",$_GET["districtstr"]);
	$url = $url."&districtstr=".$districte;
}
if(isset($_GET["tipusact"])){
	$tipusact = $_GET["tipusact"];
	$url = $url."&code0=".$tipusact;
}
if(isset($_GET["especialitat"])){
	$especialitat = $_GET["especialitat"];	
	if(hasValue($especialitat)){
		$url = $url."&code1=".$especialitat;
	}
}

if(isset($_GET["code0"]) && hasValue($_GET["code0"])){
	$url = $url."&code0=".$_GET["code0"];
}
if(isset($_GET["code1"]) && hasValue($_GET["code1"])){
	$url = $url."&code1=".$_GET["code1"];
}
if(isset($_GET["code2"]) && hasValue($_GET["code2"])){
	$url = $url."&code2=".$_GET["code2"];
}
if(isset($_GET["code3"]) && hasValue($_GET["code3"])){
	$url = $url."&code3=".$_GET["code3"];
}
if(isset($_GET["code4"]) && hasValue($_GET["code4"])){
	$url = $url."&code4=".$_GET["code4"];
}
if(isset($_GET["code5"]) && hasValue($_GET["code5"])){
	$url = $url."&code5=".$_GET["code5"];
}
if(isset($_GET["d"])){
	$url = $url."&d=".$_GET["d"];
}
if(isset($_GET["dt"])){
	$url = $url."&dt=".$_GET["dt"];
}
if(isset($_GET["from"])){
	$url = $url."&from=".$_GET["from"];
}
if(isset($_GET["sort"])){
	$url = $url."&sort=".$_GET["sort"];
}else{
	$url = $url."&sort=popularity,desc";
}
if(isset($_GET["type"])){
	$url = $url."&type=".$_GET["type"];
}
if(isset($_GET["ticket"])){
	$url = $url."&ticket=".$_GET["ticket"];
}
if(isset($_GET["p"])){
	$url = $url."&p=".$_GET["p"];
}

if(isset($_GET["c"])){
	$url = $url."&c=".$_GET["c"];
}
if(isset($_GET["ad"])){
	$url = $url."&ad=".$_GET["ad"];
}

if(isset($_GET["ini"])){
	$url = $url."&ini=".$_GET["ini"];
}

if(isset($_GET["fi"])){
	$url = $url."&fi=".$_GET["fi"];
}

if(isset($_GET["t"])){
	$url = $url."&t=".$_GET["t"];
}
if(isset($_GET["barristr"])){
	$barri =str_replace(' ', '+',$_GET["barristr"]);
	$url = $url."&barristr=".$_GET["barristr"];
}

if(isset($_GET["nr"])){
	$url = $url."&nr=".$_GET["nr"];
}else{
$num_resultats = variable_get('asia_num_resultats', '');
if($num_resultats != ""){
	$url = $url."&nr=".$num_resultats;
}
}

global $language;
$idma = $language->language;

$url = $url."&idma=".$idma;

if(isset($_GET["param"])){
if ($_GET["param"] == 1) print $url;
}

$str = file_get_contents($url);

$arrXml = new SimpleXmlElement($str);




$variables = array(
    'dis' => $arrXml,
	'amplada' => $amplada,
	'alcada' => $alcada,
	'config' => $config,
	'display' => $display,	
	'addthis' => $addthis,	
	'codefilters' => getSelectedFilters(),
	'blockfilters' => getBlockFilters(),
	
  );

 return theme('asia_llistat', $variables);
}



//*****************************/
/*  Functions de blocks       */
/*                            */
/******************************/



function mostra_form_cerca_paraula(){

	$variables = array();
	//$variables["districte"] =  variable_get('districtes', 0);	
	$variables["cerca"] =  variable_get('cerca', 0);	
	
	$variables["settings_cercaavancada"] =  variable_get('settings_cercaavancada', 0);	
	$variables = array(
    'dis' => $variables,
	
  );
	return theme('asia_cercador', $variables);
}


function mostra_form_mapa_districtes(){

	$arraySelectMap =  variable_get('arraySelectMap', '');	
	$widthMap =  variable_get('widthMap', '');
	$codi0 = variable_get('code0Mapa', '');
	$codi1 = variable_get('code1Mapa', '');
	
	
	$variables = array(
    	'arraySelectMap' => $arraySelectMap,
		'widthMap' => $widthMap,
		'code0' => $codi0,
		'code1' => $codi1,		
  	);
	return theme('asia_mapa_districtes', $variables);
}

function mostra_form_cerca_avancada(){
 global $language;
 $idma = $language->language;
 $canal = variable_get('asia_canal','');
 $code0=variable_get('code0Cerca', '');
 $code1=variable_get('code1Cerca', '');
 
 $url = "http://guia.bcn.cat/index.php?pg=search&xout=1&ajax=search&idma=".$idma;
 $settings_cercaavancada = variable_get('settings_cercaavancada','');
	if($canal != ''){
		$url = $url."&canal=".$canal;
	}
	if($code0 != ''){
		$url = $url."&code0=".$code0;
	}
	if($code1 != ''){
		$url = $url."&code1=".$code1;
	}

 $str = file_get_contents($url);
 $arrXml = new SimpleXmlElement($str);
 
 	$variables = array(
    'dis' => $arrXml,
	'settings_cercaavancada' => $settings_cercaavancada,
	'canal' => $canal,
	'code0' => $code0,
	'code1' => $code1,
  );
  return theme('asia_cercador_avancat', $variables);
}

function mostra_form_cerca_avancada_prefixada(){
 global $language;
 $idma = $language->language;
 $canal = variable_get('asia_canal','');
 $code0=variable_get('code0Cerca_prefixada', '');
 $code1=variable_get('code1Cerca_prefixada', '');
 
 $url = "http://guia.bcn.cat/index.php?pg=search&xout=1&ajax=search&idma=".$idma;
 $settings_cercaavancada_prefixada = variable_get('settings_cercaavancada_prefixada','');
	if($canal != ''){
		$url = $url."&canal=".$canal;
	}
	if($code0 != ''){
		$url = $url."&code0=".$code0;
	}
	if($code1 != ''){
		$url = $url."&code1=".$code1;
	}

 $str = file_get_contents($url);
 $arrXml = new SimpleXmlElement($str);
 
 	$variables = array(
    'dis' => $arrXml,
	'settings_cercaavancada_prefixada' => $settings_cercaavancada_prefixada,
	'canal' => $canal,
	'code0' => $code0,
	'code1' => $code1,
  );
  return theme('asia_cercador_avancat_prefixat', $variables);

}

function especialitat($id_especialitat){
  global $language;
  $idma = $language->language;
  echo "dins".$id_especialitat;
  
  $canal = variable_get('asia_canal','');
  $url = "http://guia.bcn.cat/index.php?pg=search&&xout=1&ajax=search&code0=".$id_especialitat."&idma=".$idma;
  
  if($canal != ''){
		$url = $url."&canal=".$canal;
	}

   print $url;
  $str = file_get_contents($url);
 
  $arrXml = new SimpleXmlElement($str);
  
  	$variables = array(
    'arrXml' => $arrXml,
	
  );
    return theme('especialitat',  $variables);

}

/***********************************/
/*         Mapa districtes         */
/***********************************/


function changeCoordsRatio($arr, $ratio_W, $ratio_H){
	$cad = "";
	$isX = true; // la 1a coord és una X
	foreach ($arr as &$value) {
		
		if($isX) $cad .= round($value*$ratio_W, 1).","; // es una X, multipliquem pel ratio WIDTH
		else  $cad .= round($value*$ratio_H, 1).",";    // es una Y, multipliquem pel ratio HEIGHT
		
		$isX = !$isX;
	}
	return $cad;
}


/******************************************/
/*   Configuració de la selecció filtres  */
/******************************************/


function getBlockFilters(){ //per block
	$blockfilters = variable_get('asia_block_filters', '');
	$array_bfilters=array();
	foreach ($blockfilters as $bloc){
		if($bloc!==0){
			$array_bfilters[]=$bloc;	
		}
	}
	return $array_bfilters;
	
}

function getSelectedFilters(){ //per codi tematic

	$cadena =variable_get('asia_codes_filters','');
	$codefilters=array();
	if(isset($cadena['@codes'])){
		$codefilters = array_filter(explode(", ", $cadena['@codes']));
	}
	return $codefilters;
}


/*******************************************/
/*   Càrrega de filtres per l'administarió  */
/*******************************************/

function getFilters(){
	 global $language;
	 $idma = $language->language;
 	 $canal = variable_get('asia_canal','');
	 $url = "http://guia.bcn.cat/index.php?pg=search&xout=1&ajax=search&idma=".$idma;
	
	 if($canal != ''){
	 	$url = $url."&canal=".$canal;
	 }
	
	$str = file_get_contents($url);
 	$arrXml = new SimpleXmlElement($str);
  	
	if(isset($arrXml->search->bleft->leftfilter->facetlist)){

	  $array_filtres=$arrXml->search->bleft->leftfilter->facetlist;
	  $titleFilters=array();	  
	  foreach($array_filtres->children() as $itype){		  
	
		  if($itype -> getName()!="class"){			  
			  $titleFilters[$itype -> getName()] = (string)$itype['name'];
		  }else{
			  
			  $titleFilters[(string)$itype['treeid']] = (string)$itype['name'];
			
		  }

	  } 
	
  }
  

	
	return $titleFilters;
}


