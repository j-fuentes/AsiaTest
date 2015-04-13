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

global $tree;

require_once("includes/classification.class.inc");

$class = new classification;

//$class->Debug=1;

//echo $class->getClassTreeXML("0040101",1);

if (!isset($tree)) $tree = "401";

if ($tree=="401") $label = _CATS_DIRECTORI;
if ($tree=="400") $label = _CATS_AGENDA;

if ($tmp=$this->mc->get("00".$tree."00_"._IDIOMA)) {
	//echo "Cached: 00".$tree."00_"._IDIOMA;
	$Directori = $tmp;
} else {
	$Directori = $class->getClassTreeArray("00".$tree."00",_LANGUAGE,2);
	$this->mc->set("00".$tree."00_"._IDIOMA,$Directori,(60*60));
}
//$Agenda = $class->getClassTreeArray("0040001",_LANGUAGE,1);
//print_r($Directori);
$this->html_out .="<classall label=\"$label\">";


foreach($Directori as $item){
	$this->html_out .="<item href=\"".LK_PAG."".$this->url_encrypt("pg=search&q=*:*&code0=".$item["code"])."\">";
	$this->html_out .="<name><![CDATA[".$item["desc"]."]]></name>\n";
	if (array_key_exists("ramas",$item) && is_array($item["ramas"])){
		foreach($item["ramas"] as $subitem){
			$this->html_out .="<subitem href=\"".LK_PAG."".$this->url_encrypt("pg=search&q=*:*&code1=".$subitem["code"])."\">";
			$this->html_out .="<name><![CDATA[".$subitem["desc"]."]]></name>\n";
			$this->html_out .="</subitem>";
		}
	}
	$this->html_out .="</item>";
}



$this->html_out .="</classall>";





?>