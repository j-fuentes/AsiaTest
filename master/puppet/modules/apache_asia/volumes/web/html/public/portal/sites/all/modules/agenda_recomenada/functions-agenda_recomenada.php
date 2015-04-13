<?php

//*****************************/
/* Functions de blocks       */
/*                           */
/*****************************/



function mostra_agenda_recomenada($tipus){
 global $language;
 $idma = $language->language;
  
 

		 try {


		 

		 $url = "http://guia.bcn.cat/index.php?pg=agrecom&xout=xml&ajax=agrecom&nr=6&wtarget=agenda500-tots&idma=".$idma;
	
		 if(isset($_GET['c'])){
			$tema = $_GET['c'];
			$url = $url."&c=".$tema;
		 }
		 
		 if(isset($_GET['wtarget'])){
			$wtarget = $_GET['wtarget'];
			$url = $url."&wtarget=".$wtarget;
		 }else{
			$url = $url."&wtarget=agenda500-tots";
		 }
		 
	
		

    $str = file_get_contents($url);
	$arrXml = new SimpleXmlElement($str);
	
	$variables = array(
	   'arrXml' => $arrXml,	
	);
  
  }
  catch (Exception $e) {
	drupal_set_message(t('error ag recom  = %message',
	array('%message' => $e->getMessage())), 'error');
 }
	
	return theme('agenda_recomenada', $variables);
	
}




function mostra_agenda_recomenada_page($wtarget){
 global $language;
 $idma = $language->language;
  
 $url = "http://guia.bcn.cat/index.php?pg=agrecom&wtarget=".$wtarget."&xout=xml&ajax=agrecom&idma=".$idma;


 if(isset($_GET['nr'])){
	$nr = $_GET['nr'];
	$url = $url."&nr=".$nr;
 }else{$url = $url."&nr=6";}
 
 if(isset($_GET['from'])){
	$from = $_GET['from'];
	$url = $url."&from=".$from;
 } 
  

 if(isset($_GET['c'])){
	$tema = $_GET['c'];
	$url = $url."&c=".$tema;
 }

	$str = file_get_contents($url);
	$arrXml = new SimpleXmlElement($str);
	
	$variables = array(
	   'arrXml' => $arrXml,	
	);
  
  	return theme('agenda_recomenada', $variables);
	
}

function mostra_agenda_recomenada_especials($desti){
 
 // $desti: Path de la pagina, en principi no s'utilitza per generar xml.
 
 global $language;
 $idma = $language->language;
 
 
  
 $url = "http://guia.bcn.cat/index.php?pg=agrecom&xout=xml&ajax=agrecom&idma=".$idma;


 if(isset($_GET['nr'])){
	$nr = $_GET['nr'];
	$url = $url."&nr=".$nr;
 }else{$url = $url."&nr=6";}
 
 if(isset($_GET['from'])){
	$from = $_GET['from'];
	$url = $url."&from=".$from;
 } 
 
 if(isset($_GET['wtarget'])){
	$wtarget = $_GET['wtarget'];
	$url = $url."&wtarget=".$wtarget;
 } 
   

 if(isset($_GET['c'])){
	$tema = $_GET['c'];
	$url = $url."&c=".$tema;
 }

	$str = file_get_contents($url);
	$arrXml = new SimpleXmlElement($str);
	
	$variables = array(
	   'arrXml' => $arrXml,	
	);
  
  	return theme('agenda_recomenada', $variables);
	
}
