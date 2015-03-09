<?php
/**
 * Guia de Barcelona - Agenda and Directory
 *
 * This file is part of Guia Barcelona v1.0.0
 * @author Elazos Software Factory
 **/
/**
 * Shows words/keywords by entity_id
 */

global $id;

//global $lang;
error_reporting(E_ALL);

require_once("includes/object.class.inc");
header('Content-Type: text/html; charset=utf-8'); 
$dbi = new object;
if(isset($id)){
  

  $dbi->query("SELECT description as txtword FROM classification c, tct_codes t where c.code = t.code and entity_id = $id");
  $result = $dbi->select_array();  
  
  foreach($result as $row){
  	  $tmp[] =strtolower($row["txtword"]);  
  }
  $tmp = array_unique($tmp);
  $i=1;
   foreach($tmp as $word){
  	echo "$i : ".$word."<br/>";
  	$i++;
  }
  $keywords = $dbi->getKeywords($id);
  echo "KEYWORDS : <br/>";
   foreach($keywords as $word){
  	echo "$i : ".$word."<br/>";
  	$i++;
  }
  
  } else  echo "id is not set";
  


?>