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
global $ctg;
global $districtstr;
global $id_tema;
global $from;
global $wtarget;
global $c;
global $type;
global $debug;

if (!isset($nr)) {
	if (!isset($rows)) {
		$rows = 5;
	}
	$nr = $rows;
} else {
	$rows = $nr;
}

if(!isset($from) || trim($from)=='') $from = 0;

$fieldName = "";
// ctg, id_tema i districstr se correcponden con categoria de wp.
// Son parametros equivalentes
if(isset($ctg) && $ctg!="") {
	$canal = $ctg;
	$fieldName = "&ctg=".$canal;	
}
if(isset($id_tema) && $id_tema!="") {
	$canal = $id_tema;
	$fieldName = "&id_tema=".$canal;
}
if(isset($districtstr) && $districtstr!="") {
	$canal = $districtstr;
	$fieldName = "&districtstr=".$canal;
}

if(!isset($c)) {
	$c = "";
}

$db = new agrecom;
if (isset($debug)) $db->Debug = true;
$list = new xmllist;

if (!isset($type) || $type==""){
	$type = "AG";
}
$fieldName .="&type=$type";
// canal es la categoria de wp. No es el canal d'ASIA.
$agendes = $db->getAgendaByWtarget($wtarget, $canal, $from, $rows, $c, $type);

$found_rows = $agendes["found"];

$destacades = $agendes["list"];
 
if (count($destacades)>0){
	//$this->includeBlock("gmapsv3");
	if ($type=="AG") $titleHrecom = _ACTDESTACADES;
	else $titleHrecom = "Registres per WebTarget";
	$outString .="<hrecom label=\"".$titleHrecom."\">\n";
	if (isset($wtarget) && $wtarget!=""){
		foreach($destacades as $key=>$item){
			$destacades[$key]["stringnode"] = file_get_contents("data/post_".$item["post_id"]."_"._IDIOMA.".xml");
		}
	}
	if (isset($wtarget) && $wtarget!="") $paramWt = "&wtarget=$wtarget";else $paramWt="";
	
	$outString .= $list->xml_list($destacades, $from,$rows,"pg=agrecom$fieldName","pg=detall$paramWt&id_doc=",null,null, $found_rows,null, null);
	$outString .="</hrecom>\n";
	$this->html_out .= $outString;
} //end if

?>