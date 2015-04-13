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

if ($outstring=$this->mc->get("mvoted_"._IDIOMA)){
	$this->html_out .= $outstring;
} else {

	global $nm;
	require_once("includes/entity.class.inc");
	$outstring = " ";
	$db = new entity;
	/*
    // More voted today 
	if ($entity = $db->mviewed(4)){
		// EL DETALLE SE AGARRA EN CATALAN PARA LUEGO TRADUCIRLO
		$outstring .="<mvotedtoday label=\""._MVOTEDTODAY."\">";
		foreach($entity as $item){
			$outstring .="<item href=\"".LK_PAG."".$this->url_encrypt("pg=detall&id_doc=".$item["entity_id"])."\">";
			foreach($item as $key=>$value)
			$outstring .="<$key><![CDATA[$value]]></$key>\n";
			$outstring .="</item>";
		}
		$outstring .="</mvotedtoday>";
	}
    // More voted 7 days 
	if ($entity = $db->mviewed(5)){
		// EL DETALLE SE AGARRA EN CATALAN PARA LUEGO TRADUCIRLO
		$outstring .="<mvoted7days label=\""._MVOTED7DAYS."\">";
		foreach($entity as $item){
			$outstring .="<item href=\"".LK_PAG."".$this->url_encrypt("pg=detall&id_doc=".$item["entity_id"])."\">";
			foreach($item as $key=>$value)
			$outstring .="<$key><![CDATA[$value]]></$key>\n";
			$outstring .="</item>";
		}
		$outstring .="</mvoted7days>";
	}*/
    // More voted 1 Month (depends on calcvisitsday interval) 
	if ($entity = $db->mviewed(6)){
		// EL DETALLE SE AGARRA EN CATALAN PARA LUEGO TRADUCIRLO
		$outstring .="<mvotedmonth label=\""._MVOTEDMONTH."\">";
		foreach($entity as $item){
			$outstring .="<item href=\"".$this->getPermalink($item["name"],"pg=detall&id_doc=".$item["entity_id"])."\">";
			//$outstring .="<item href=\"".LK_PAG."".$this->url_encrypt("pg=detall&id_doc=".$item["entity_id"])."\">";
		
			$outstring .= $db->RecordToXML($item);
			$outstring .="</item>";
		}
		$outstring .="</mvotedmonth>";
	}    
	$this->mc->set("mvoted_"._IDIOMA,$outstring,(60*60));
	$this->html_out.= $outstring;
}

?>