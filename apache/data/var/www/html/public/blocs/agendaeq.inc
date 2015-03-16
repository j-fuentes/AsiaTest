<?php
/**
 * Guia de Barcelona - Agenda and Directory
 *
 * This file is part of Guia Barcelona v1.0.0
 * @author Elazos Software Factory
 **/

/**
 * Returns xml node with the content from xml file.
 * Content file is defined on navigator file attribute xml.
 * @package blocks_public
 **/

global $id_doc;

require_once("includes/entity.class.inc");

$type = true; 

if ($tmp=$this->mc->get($id_doc._IDIOMA)) {
	//echo "Cached:$id_doc";
	$entity = $tmp["entity"];
	if ($entity["entity_type"]=="AG") $type = false; 	
} else {
	// deberia volver a cargar el Entity
	/**
     * @TODO deberia volver a cargar el Entity 
     * */	
}

$db = new entity;

//$entity->Debug=1;
if (!$this->notfound) {
	if ($GetAgendEq=$this->mc->get("ageq_".$id_doc._IDIOMA)){
		$this->html_out .=$GetAgendEq;
	} else {
		$outstring = "";
		if ($type && ($result = $db->GetAgendEq($id_doc))){
			//print_r($result);			
			$outstring .="<ageq label=\""._AGEQ."\">";
			foreach($result as $row){
				$tmpHref = $this->getPermalink(strip_tags($row["name"]),"pg=detall&id_doc=".$row["entity_id"]);
				$outstring .= "<item href=\"$tmpHref\">";
				$outstring .= $db->RecordToXML($row);
				$outstring .= "</item>";
			}
			$outstring .="</ageq>";
		}
		if ($outstring!="") {
			$this->mc->set("ageq_".$id_doc._IDIOMA,$outstring,(60*60));
			$this->html_out .= $outstring;
		}		
	}	
}
//$entity->Debug=0;

?>