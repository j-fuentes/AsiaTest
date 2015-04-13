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


if ($outstring=$this->mc->get("mviewed_"._IDIOMA)){
	$this->html_out .= $outstring;
} else {
	global $nm;

	require_once("includes/entity.class.inc");	

	$outstring = " ";

	$db = new entity;

	/*
    // More viewed today 
	if ($entity = $db->mviewed(1)){

		// EL DETALLE SE AGARRA EN CATALAN PARA LUEGO TRADUCIRLO
		$outstring .="<mviewedtoday label=\""._MVIEWEDTODAY."\">";
		foreach($entity as $item){
			$outstring .="<item href=\"".LK_PAG."".$this->url_encrypt("pg=detall&id_doc=".$item["entity_id"])."\">";
			foreach($item as $key=>$value)
			$outstring .="<$key><![CDATA[$value]]></$key>\n";
			$outstring .="</item>";
		}
		$outstring .="</mviewedtoday>";
	}
     // More viewed 7 days 
	if ($entity = $db->mviewed(2)){
		// EL DETALLE SE AGARRA EN CATALAN PARA LUEGO TRADUCIRLO
		$outstring .="<mviewed7days label=\""._MVIEWED7DAYS."\">";
		foreach($entity as $item){
			$outstring .="<item href=\"".LK_PAG."".$this->url_encrypt("pg=detall&id_doc=".$item["entity_id"])."\">";
			foreach($item as $key=>$value)
			$outstring .="<$key><![CDATA[$value]]></$key>\n";
			$outstring .="</item>";
		}
		$outstring .="</mviewed7days>";
	}*/
     // More viewed 1 Month (depends on calcvisitsday interval)
	if ($entity = $db->mviewed(3)){
		// EL DETALLE SE AGARRA EN CATALAN PARA LUEGO TRADUCIRLO
		$outstring .="<mviewedmonth label=\""._MVIEWEDMONTH."\">";
		foreach($entity as $item){
			$outstring .="<item href=\"".$this->getPermalink($item["name"],"pg=detall&id_doc=".$item["entity_id"])."\">";
			//$outstring .="<item href=\"".LK_PAG."".$this->url_encrypt("pg=detall&id_doc=".$item["entity_id"])."\">";
			//foreach($item as $key=>$value)
				//$outstring .="<$key><![CDATA[$value]]></$key>\n";
			$outstring .= $db->RecordToXML($item);
			$outstring .="</item>";
		}
		$outstring .="</mviewedmonth>";
	}
	$this->mc->set("mviewed_"._IDIOMA,$outstring,(60*60));
	$this->html_out.= $outstring;
}


?>