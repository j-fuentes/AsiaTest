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

ini_set('display_errors', '1');
error_reporting(E_ALL);

if ($tmp=$this->mc->get("dades_merce_"._IDIOMA)){
	
	$this->html_out .= $tmp;
	
} else {

require_once("includes/entity.class.inc");
$db = new entity;


$url = "http://212.15.224.54/APPS/asiw/XmlController?xml=";

$fileXml = file_get_contents("http://10.254.160.13/?pg=search&q=*:*&nr=600&type=AG&xout=1&ajax=search&code1=0040002023025");

try {
	$xml = new SimpleXMLElement($fileXml);
} catch (Exception $e){
	echo "error al cargar XML\n";
}

//$this->html_out .="<merce>\n";
$result = "";
foreach($xml->search->queryresponse->list->list_items->row as $row){
	$id_doc = $row->item->id;	
	// mira si esta en la cache
			 
		if ($entity = $db->dtl_entity($id_doc,1)){
			$db->prepare_fields_to_show($entity);	
			// Buscamos si es una recomendada, si no esta en la cache accedemos a BD
			if ($entity["entity_type"]=="AG" && $recomtxt = $db->GetRecomByEntityID($id_doc,_LANGUAGE)){
				if (count($recomtxt)>0){
					$entity["internetref"][0]["irefvalue"]=$recomtxt["imatgeCos"];
					$entity["resum"]=$recomtxt["resum"];
					$entity["texte"]=$recomtxt["texte"];
					$entity["nameasia"]=$entity["name"];
					$entity["name"]=$recomtxt["titol"];
				}			
			}			
			$request="<request>
			<header module=\"QueryModule\" operation=\"getDetallAgenda\" identity=\"PROVES\"/>
			<body>
			<id>$id_doc</id>
			<idioma>CA</idioma>
			<dependencia></dependencia>
			<format_horari>V</format_horari>
			</body>
			</request>";
			$horariHTML = "";
			if ($ASIAxml = file_get_contents($url.urlencode($request))){				
				try {					
					$ASIAxml = new SimpleXMLElement($ASIAxml);					
					$horariHTML="<horari_html><![CDATA[".$ASIAxml->body->resultat->horari."]]></horari_html>";					
				} catch (Exception $e){
					echo "error al cargar XML ASIA\n";
				}
			} else {
				echo "error al cargar XML ASIA\n";
			}		
			$result .= "<detall>\n".$db->RecordToXML($entity).$horariHTML."</detall>";						
		}		

}
$this->html_out .= $result;
$this->mc->set("dades_merce_"._IDIOMA,$result,(60*60));
}



?>