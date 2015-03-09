<?php
/**
 * Guia de Barcelona - Agenda and Directory
 *
 * This file is part of Guia Barcelona v1.0.0
 * @author Elazos Software Factory
 **/

/**
 *Returns xml node for home page.
 *Gets content from a xml file defined in xml navigator file.
 *@package blocks_public
 **/
global $id_doc;
global $from;
global $nm;
global $lk;
global $wtarget;
global $tr;

//global $r; //if is set is a featured

if (!isset($from)) $from = 0;
if (!isset($lk)) $lk = false; else $lk = true;

require_once("includes/entity.class.inc");
require_once("includes/search.class.inc");
require_once("includes/engine.class.inc");

$this->SetXslFile($id_doc); //change XSL template file if exists in folder /tpl/theme/ids

$outString = "";


$db = new entity;
//$db->Debug = 1;
//if browser user agent is not IMI nimbus = PETE then make counts
if (array_key_exists("HTTP_USER_AGENT",$_SERVER) && strpos($_SERVER['HTTP_USER_AGENT'],"PETE")===FALSE) {
	if (isset($id_doc) && $id_doc!="" && $from==0) $db->SetCounter($id_doc,$this->vars["user_id"],$lk);
}
if (isset($wtarget) && $wtarget!="") $id_cache = $id_doc.$wtarget._IDIOMA; else $id_cache = $id_doc._IDIOMA;
// mira si esta en la cache
if ($tmp=$this->mc->get($id_cache)) {

	//echo "Cached:$id_doc";
	$outString = $tmp["outstring"];	
	
	if (isset($lk) && $lk=="y"){ 
		$s = explode('votes="',$outString);
		$t = explode('"',$s[1]);
		$votes_old = 'votes="'.$t[0].'"';
		$votes = 'votes="'.($t[0]+1).'"';
		$outString = str_replace($votes_old, $votes, $outString);
		//if (array_key_exists("debug", $_GET)) print $t[0];
	}
	
	$entity = $tmp["entity"];
	$this->html_out .= $outString;
	
} else {
	if ($entity = $db->dtl_entity($id_doc,1,false)){
		$engine = new engine;
		
		if ($this->solr=="") $ItemRecommended = $engine->ItemRecommended($id_doc,7);
		else $ItemRecommended = false;
		$db->prepare_fields_to_show($entity);	

	if ($entity["entity_type"]=="AG") $entity["name"] = preg_replace('/(")(.*?)(")/i', ' <span class="notranslate">"$2"</span> ',$entity["name"]);		
	//if (array_key_exists("comments",$entity)) $entity["comments"]=preg_replace('/("|&quot;)(.*?)("|&quot;)/i', ' <span class="notranslate">"$2"</span> ',$entity["comments"]);
	$recomanada = false;
	// Buscamos si es una recomendada, si no esta en la cache accedemos a BD
	
	if ($entity["entity_type"]=="AG" && $recomtxt = $db->GetRecomByEntityID($id_doc,_LANGUAGE)){	
		
		if (count($recomtxt)>0){			
			
			$entity["internetref"][0]["irefvalue"]=$recomtxt["imatgeCos"];
			$entity["resum"]="<p>".$recomtxt["resum"]."</p>";
			$entity["texte"]=$recomtxt["texte"];		
			$entity["nameasia"]=$entity["name"];
			$entity["name"]=preg_replace('/(")(.*?)(")/i', ' <span class="notranslate\">"$2"</span> ',$recomtxt["titol"]);
			
			$recomanada = true;
		} 
	}
	
	if (($tmpid = $db->getPost_id($id_doc, $wtarget,$entity["entity_type"]))!==false) { 
	        $recomtxt["post_id"] = $tmpid;
	        $recomanada = true;	
	}
	
	$outString .="<detall>\n";

	if (array_key_exists("sectionname",$entity)) {
	   $FullName = strip_tags($entity["sectionname"]." - ".$entity["name"]);
	} else {
	   $FullName = strip_tags($entity["name"]);
	}	
	
	$outString .= "<share href=\"".urlencode($this->url)."\" label=\"".htmlspecialchars($FullName)." \"/>\n";
	if ($entity["entity_type"]=="AG"){
		if (array_key_exists("votes",$entity)) $votes = $entity["votes"]; else $votes = 0;
		$outString .= "<likeit href=\"".LK_PAG.$this->url_encrypt("pg=detall&lk=y&id_doc=".$id_doc)."\" label=\""._LIKEIT." \" votes=\"".$votes."\" />\n";
	}
	
	$outString .= $db->RecordToXML($entity);
	
	// Links
	if (array_key_exists("gmapx",$entity)){
		//$outString .="<apikey>"._GMAP_KEY."</apikey>";
		//Lo comentado envia la direccion en lugar de Lat long
		//$outString .= $this->link("f=d&source=s_d&saddr=&daddr=".$entity["street"]." ".$entity["streetnum_i"].", ".$entity["postalcode"]." ".$entity["district"]."&hl="._IDIOMA."&ie=UTF8&z=12", _COMANAR, null,false,"http://maps.google.com/maps?");
		$outString .= $this->link("f=d&source=s_d&saddr=&daddr=".$entity["gmapx"].", ".$entity["gmapy"]."&hl="._IDIOMA."&ie=UTF8&z=12", _COMANAR, null,false,"http://maps.google.com/maps?");
	}
	// End Links

	if($ItemRecommended){
		$outString .="<recommend label=\""._RECOMMENDED."\">";
		foreach($ItemRecommended as $entity_id){
			$Recommended = false;
			if ($tmp=$this->mc->get($entity_id._IDIOMA)){
				$Recommended = $tmp["entity"];
		    } else {
		    	$Recommended = $db->dtl_SimpleEntity($entity_id,1);		    	
		    }	
		    if($Recommended){
		    	//print_r($Recommended);
		    	$outString .="<item href=\"".$this->getPermalink($Recommended["name"],"pg=detall&id_doc=".$entity_id)."\">";		    	//
		    	//$outString .="<item href=\"".LK_PAG.$this->url_encrypt("pg=detall&id_doc=".$entity_id)."\">";
		    	$outString .= $db->RecordToXML($Recommended);
		    	$outString .="</item>";
		    }
		}
		$outString .="</recommend>";
	}
	if ($recomanada) {
		//$urlPost = "http://noticies.bcn.cat/api/detall.php?id_doc=".$recomtxt["post_id"]."&media=n&lg="._LANGUAGE;
		//$xmlPost = simplexml_load_string(file_get_contents($urlPost));
		$wp_content = file_get_contents("data/post_".$recomtxt["post_id"]."_"._IDIOMA.".xml");
		$outString .= "<wp>$wp_content</wp>";
	}
	$outString .="</detall>\n";
	$this->html_out .= $outString;
	unset($tmp);
	$tmp["outstring"] = $outString;
	$tmp["entity"] = $entity;
	// guarda en cache
	$this->mc->set($id_cache,$tmp,(60*60));
	} else {		
		$this->html_out .= $this->exec_copy(array(array("VALUE"=>"notfound")));		
		$this->notfound=true;	
	}
}
// Page title, desc
if (!$this->notfound){
	if (array_key_exists("sectionname",$entity)) {
	   $FullName = strip_tags($entity["sectionname"]." - ".$entity["name"]);
	} else {
	   $FullName = strip_tags($entity["name"]);
	}
	$this->pagetitle = htmlspecialchars($FullName);
	$FullDesc = "";
	/**
	if (array_key_exists("classification",$entity)) {		
		foreach($entity["classification"] as $tmpClass){			
			foreach($tmpClass as $itemClass) if ($FullDesc=="") $FullDesc.=$itemClass["class"];else $FullDesc.=", ".$itemClass["class"];
		}
		$FullDesc = $FullDesc." - ";
	}*/		
	if (array_key_exists("street",$entity)) $this->pagedesc  = $this->pagetitle." ".htmlspecialchars($FullDesc.$entity["street"]." ".$entity["streetnum_i"].", ".$entity["district"]);
	else $this->pagedesc = $this->pagetitle;
} else $this->pagetitle = _NOTFOUND;

/****************************** FIN PRINCIPAL **************************************************************/
// Cerca de aqui
if (!$this->notfound && !$this->isMobile && array_key_exists("gmapx",$entity)){	
	$solr = new search();
	if ($this->solr==""){
	$filters[0]["filters"] = array("class:Aparcaments");
	$filters[0]["label"] = _APARCS;
	$filters[0]["node"] = "aparcs";
	$filters[1]["filters"] = array("class:Restaurants");
	$filters[1]["label"] = _RESTAURANTS;
	$filters[1]["node"] = "restaurants";
	} else {
    $filters[0]["filters"] = array("code1:0040102004033 OR code1:0040102004035");
	$filters[0]["label"] = "Biblioteques i sales d'estudi";
	$filters[0]["node"] = "biblioteques";
	
	$filters[1]["filters"] = array("code2:0040103004020002");
	$filters[1]["label"] = "Parc i Jardins";
	$filters[1]["node"] = "parcsijardins";	
	
	$filters[2]["filters"] = array("code2:0040103004015003 OR code1:0040102004013 OR code2:0040103004015004");
	$filters[2]["label"] = "Espais de joc i Casals";
	$filters[2]["node"] = "espaisjoc";	
	}
	
	$outString = $solr->CloseTo($entity["gmapx"],$entity["gmapy"],$filters);	
	if($outString!="")
	     $this->html_out .= "<aprop label=\""._APROPDAQUI."\">".$outString."</aprop>";
}
// Esdeveniments
$this->includeBlock('agendaeq');

?>