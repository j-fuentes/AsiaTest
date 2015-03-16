<?php
/**
 * Guia de Barcelona - Agenda and Directory
 *
 * This file is part of Guia Barcelona v1.0.0
 * @author Elazos Software Factory
 **/

/**
 *Returns xml node with the content from xml file.
 *Content file is defined on navigator file attribute xml.
 *@package blocks_public
 **/

global $nm;

require_once("includes/entity.class.inc");
require_once("includes/lists/xmlist.php");

$outString = "";
global $rows;
global $nr;
global $ctg;
global $districtstr;
if (!isset($nr)) {$rows = 5; } else {$rows = $nr;}
 
global $from;
global $destacades;
global $result;
global $id_tema;
global $m;

if(!isset($from) || trim($from)=='') $from = 0;
if(!isset($id_tema)) $id_tema = "n";
if(isset($ctg) && $ctg!="") $id_tema = $ctg;

$db = new entity;

$list = new xmllist;

if (count($destacades=$db->getActDestacades(_LANGUAGE))>0){
	
	$ids = array(0);
	$fields = null;
	//print_r($destacades);
	foreach($destacades as $key=>$row){
		if (!array_key_exists("noexist",$row)) $row["noexist"]="";
		
		//print_r($row);
		
		if ($fields==null) $fields = array_keys($row);
		
				
		/*
		   if(array_key_exists("institutionname",$row)) {
		   	    $pos = strpos($row["institutionname"], "-");
		   	    if ($pos!==false) $destacades[$key]["institutionname"] = substr($row["institutionname"],0,$pos);		   	    
		   }*/
        if ($row["noexist"]=="") {
        	unset($destacades[$key]);
        	continue;
        } else     
	    if (!array_search($row["recom_id"],$ids)) $ids[]=$row["recom_id"]; else {
            unset($destacades[$key]);
            continue;
        }
         
        
        //if(array_key_exists("id_tema",$row)) $temas[$row["id_tema"]]=$row["tema"]; else $row["id_tema"]="";
        //if(array_key_exists("id_tema",$row)) $temas[utils::getTxtPermalink($row["tema"])]=$row["tema"]; else $row["id_tema"]="";

        if(array_key_exists("cc",$row)){
        	foreach($row["cc"] as $cc){
        		if ($cc["tema"]!="") $temas[$cc["id_tema"]]=$cc["tema"];
        	}
        }
        
        if (isset($districtstr) && $districtstr!=""){
        	$trobat_dist = false;
        	if(array_key_exists("cc",$row)){
         		foreach($row["cc"] as $cc){
         			if ( utils::getTxtPermalink($districtstr)==$cc["id_tema"]) {
         				$trobat_dist = true;
         			}         			
         		}
         	}         	
         	if ($trobat_dist==false) { unset($destacades[$key]); continue; }        	
        }
        
         if ($id_tema!="n"){
         	$trobat = false;
         	if(array_key_exists("cc",$row)){
         		foreach($row["cc"] as $cc){
         			if ( $id_tema==$cc["id_tema"]) {
         				$trobat = true;
         			}         			
         		}
         	}         	
         	if ($trobat==false) unset($destacades[$key]);
         	//continue;         	
         }
    
	}
	
	$this->includeBlock("gmapsv3");
	$outString .="<hrecom label=\""._ACTDESTACADES."\">\n";	
	$outString .= "<temas>\n";	
	foreach($temas as $keyTema=>$nameTema){
		$selected = "";			
		if((string)$keyTema==(string)$id_tema) $selected= "selected=\"selected\"";		 	
		//$outString .= "<item $selected href=\"?pg=home&amp;from=0&amp;id_tema=$keyTema\">$nameTema</item>\n";
		$outString .= "<item $selected href=\"".LK_PAG."".$this->url_encrypt("pg=home&from=0&id_tema=$keyTema")."\">$nameTema</item>\n";
	}
	if((string)$id_tema==(string)"n") $selected="selected=\"selected\"";else $selected="";	
	$outString .= "<item $selected href=\"".LK_PAG."".$this->url_encrypt("pg=home&from=0&id_tema=n")."\">"._TEMA_TOTS."</item>\n";
	//$outString .= "<item $selected href=\"?pg=home&amp;from=0&amp;id_tema=n\">"._TEMA_TOTS."</item>\n";
	$outString .= "</temas>\n";	
	if(count($result)>0)		
		$outString .= $list->xml_list($result, $from,$rows,"pg=home&id_tema=$id_tema","pg=detall&r=1&id_doc=",null,null, count($destacades),$fields, null);
	$outString .="</hrecom>\n";
	$this->html_out .= $outString;
}

?>