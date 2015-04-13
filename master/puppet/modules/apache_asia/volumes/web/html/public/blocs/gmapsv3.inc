<?php
/**
 * Guia de Barcelona - Agenda and Directory
 *
 * This file is part of Guia Barcelona v1.0.0
 * @author Elazos Software Factory
 **/

/**
 * Google map view
 * Returns html into var html_out
 * @package blocks_admin
 **/

global $response;
global $destacades;
global $result;
global $m;
global $from;
global $rows;

require_once("includes/search.class.inc");

$Lat = _GMAP_LAT;
$Lng = _GMAP_LNG;
$Level = _GMAP_LEVEL-2;
$addMarker = "";
$i=1;
$points=array();

if (isset($response)) {$result=$response->response->docs;}

if (isset($destacades)) {	
	
	$result=array_slice($destacades,$from,$rows);
}

$pos = 0;
foreach($result as $docKey=>$doc){
	
	
	if (is_object($doc))
			$doc = search::prepareRow(get_object_vars($doc));
	else
			$doc = search::prepareRow($doc);
	
  
	if (array_key_exists("gmapx",$doc)){
    $name = htmlspecialchars(strip_tags($doc["name"]));

	 $found = false;
	 foreach($points as $ptKey=>$pt){
	 	if ($pt["gmapx"]==$doc["gmapx"] && $pt["gmapy"]==$doc["gmapy"]){
	  	$pos = $ptKey+1;
	  	$found = true;
	 	}
	 }
	 
	 if (!$found) {
	 	$points[] = $doc;
	 	unset($points[count($points)-1]["name"]); 	
	 	$points[count($points)-1]["name"][] = str_replace("'","\'",$this->html_link("pg=detall&id_doc=".$doc["id"],$name));
	 	if (isset($destacades))$points[count($points)-1]["tp"]="AG";
	 	$pos = count($points);
	 }	else {
	 	$points[$pos-1]["name"][] = str_replace("'","\'",$this->html_link("pg=detall&id_doc=".$doc["id"],$name));
	 }
	 $result[$docKey]["pos"]=$pos;
	}
	$i++;
}

if (isset($response)) {$response->response->docs = $result;}

foreach($points as $ptKey=>$pt){

	
	$pos = $ptKey+1;
	
	if ($this->solr!=""){
		$image = "/tpl/escoles/images/icos/";
		if (array_key_exists("code_tit",$pt)){
		if($pt["code_tit"]=="0013201002") $image .= "concertats$pos.png";
		if($pt["code_tit"]=="0010201001") $image .= "publics$pos.png";
		if($pt["code_tit"]=="0010201002") $image .= "privats$pos.png";
		} 
		
	} else {
		$image = "/tpl/guiabcn/images/";
		if($pt["tp"]=="EQ") $image .= "eq$pos.png";
		else $image .= "ag$pos.png";
	}
	
	/********************globo***************************/

    $strName = "";
    $last = "";
	foreach($pt["name"] as $nm){
		//if ($strName!="<div>") $strName .=  "<br/>";
			$last =  $nm; 
		//break;			 
	}	
	//echo $last;
	$strName .=  $last;
	//$strName .= "";
	
	if (array_key_exists("begindate",$pt)){
		$pt["date"]=_BEGINDATE." ".$pt["begindate"]." "._ENDDATE." ".$pt["enddate"];
	}
	
	if($pt["tp"]=="EQ") {
		$tmp = "<dd><span class=\"notranslate\">".str_replace("'","\'",$pt["address"])."</span></dd>"
		."<dd><span class=\"notranslate\">".str_replace("'","\'",$pt["district"])."</span></dd>";		
	} else {
		if(array_key_exists("equipment_id",$pt))
			$pt["institutionname"] = $this->html_link("pg=detall&id_doc=".$pt["equipment_id"],htmlspecialchars($pt["institutionname"]));
		
		$tmp = "<dt>"._DATE."</dt><dd>".str_replace("'","\'",$pt["date"])."</dd>"
		."<dt>"._INSTITUTIONNAME."</dt><dd><span class=\"notranslate\">".str_replace("'","\'",$pt["institutionname"])."</span></dd>";
		
	}
	
	$Detalles = "<div id=\"globo\">"
		        //."<img  src=\"$image\" alt=\"\"/>"
		        .$strName
		   //     ."<dl>".$tmp."</dl>"
		        ."</div>";
	
	/******************* end globo **********************/

	$addMarker .= "var houseMarker = new google.maps.MarkerImage(\"$image\",markerSize);";
	//."markerOptions = { icon:blueIcon };\n"
	
	$addMarker .= "AddMarker(map, ".$pt["gmapx"].", ".$pt["gmapy"].",'$Detalles',houseMarker,houseMarkerShadow,latlngbounds);";
}


//$gmapkey = "<script src=\"http://maps.google.com/maps?file=api&amp;v=2&amp;key="._GMAP_KEY."\" type=\"text/javascript\"/>";
//$script = "$gmapkey

$script = "<script
src=\"/"._TPLDIR."/".$this->theme_dir."/"._DirSCRIPTS."/gmapv3.js\"
type=\"text/javascript\"> </script><script id=\"markers\" type=\"text/javascript\">function addPoints(map){var markerSize = new google.maps.Size(30,31);
var markerShadowSize = new google.maps.Size(42,30);
var markerShadowPoint = new google.maps.Point(0,0);
var markerShadowAnchor = new google.maps.Point(14,30);
var houseMarkerShadow = new google.maps.MarkerImage(\"/tpl/guiabcn/images/sombra-map.png\",markerShadowSize,markerShadowPoint,markerShadowAnchor);
var latlngbounds = new google.maps.LatLngBounds();
$addMarker
map.setCenter(latlngbounds.getCenter());
map.fitBounds(latlngbounds);}</script><div id=\"map\" class=\"map\"></div>";

$script = str_replace("\n","",$script);

if (!(isset($m) && $m=='n')) $this->html_out.="<gmap lat=\"$Lat\" lng=\"$Lng\" level=\"$Level\" url=\"".$_SERVER['HTTP_HOST'].$_SERVER["PHP_SELF"]."?\" label=\""._MAPLABELSEARCH."\">".$script."</gmap>";

?>
