<?php
/**
 * Guia de Barcelona - Agenda and Directory
 *
 * This file is part of Guia Barcelona v1.0.0
 * @author Elazos Software Factory
 **/
/**
 * Page views by code classifications
 */



//global $lang;
error_reporting(E_ALL);

require_once("includes/object.class.inc");
header('Content-Type: text/html; charset=utf-8'); 

PageViewsByClass();


function  PageViewsByClass(){
   $dbi = new object;

   $total = 0;
  $dbi->query("SELECT * FROM stats_x_class");
  $result = $dbi->select_array();  
 
  foreach($result as $row){
  	  //echo "for1<br/>";
  	  $vars = parse_url($row["Page"]); 	  

  	  
  	  if (array_key_exists("query",$vars) && $vars["query"]!=""){  	  	
  	  	parse_str($vars["query"],$vars);
  	  }
  	  
  	  $key = array_keys($vars);
  	 
  	  
  	  foreach($key as $keyName){  
  	  
  	  	switch($keyName){
  	  		case "code0":
  	  		case "code1":
  	  		case "code2":
  	  		case "code3":
  	  		case "code4":
  	  		case "code5":  	  		
  	  		if (!array_key_exists($vars[$keyName],$pv)) $pv[$vars[$keyName]] = $pv[$vars[$keyName]] + $row["Pageviews"];
  	  		else $pv[$vars[$keyName]] = $pv[$vars[$$keyName]] + $row["Pageviews"];  

  	  		$total = $total + $row["Pageviews"]; 
  	  		break;  	  		
  	  	}	
  	  	
  	  }
  }
 
  echo "total Pageviews $total<br/>";
  arsort($pv);
  return $pv;

}  


?>