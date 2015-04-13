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

require_once("includes/agrecom.class.inc");
require_once("includes/lists/xmlist.php");

$outString = "";
global $rows;
global $nr;
global $node;
global $cs;
global $id_tema;
global $ctg;
global $districtstr;
global $wtarget;
global $c;

if (!isset($nr)) {
	if (!isset($rows)) {
		$rows = 11;
	}
	$nr = $rows;
} else {
	$rows = $nr;
}


if (!isset($node)) $node = "homebcn";
if (!isset($cs))
	$this->outputcharset="ISO-8859-1";
else
	$this->outputcharset=$cs;

$db = new agrecom;
$list = new xmllist;

$canal = "";
if (!isset($wtarget)) $wtarget = "home-bcn";
 
if(isset($ctg) && $ctg!="") {
	$canal = $ctg;
}
if(isset($id_tema) && $id_tema!="") {
	$canal = $id_tema;
}
if(isset($districtstr) && $districtstr!="") {
	$canal = $districtstr;
}

if(!isset($c)) {
	$c = "";
}

$agendes = $db->getAgendaByWtarget($wtarget, $canal, 0, $rows, $c);

$result = $agendes["list"];
$found_rows = $agendes["found"]; 

if (count($result)>0){
	
	$outString .="<$node lang=\""._IDIOMA."\" label=\""._HOMEBCNTITOL."\" label2=\""._HOMEBCNTOTS."\">\n";
	$outString .="<label1><![CDATA["._HOMEBCNTITOL2."]]></label1>";
	$outString .="<label2><![CDATA["._HOMEBCNTOTS2."]]></label2>";
	
	foreach($result as $tmpKey=>$tmpItem){
		//$tmp = str_replace("225x170","343x193",$tmpItem["imatgeCos"]);
		$tmp = str_replace("225x170","570x321",$tmpItem["imatgeCos"]);
		$result[$tmpKey]["post-image-col1"]=$tmp;
	}
	$fields = array_keys($result[0]);
	if(count($result)>0)		
		$outString .= $list->xml_list($result, 0,$rows,null,"pg=detall&idma=1&id_doc=",null,null, $rows,$fields, null);
	$outString .="</$node>\n";
	$this->html_out .= $outString;
}

?>