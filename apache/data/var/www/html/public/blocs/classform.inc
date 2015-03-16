<?php
/**
 * Guia de Barcelona - Agenda and Directory
 *
 * This file is part of Guia Barcelona v1.0.0
 * @author Elazos Software Factory
 **/

if ($outstring=$this->mc->get("classform_"._IDIOMA)){
	$this->html_out .= $outstring;	
} else {
	global $nm;
	require_once("includes/classification.class.inc");
	$class = new classification;
	$Directori = $class->getClassTreeArray("0040100",_LANGUAGE,1);
	$Agenda = $class->getClassTreeArray("0040000",_LANGUAGE,1);
	$outstring .="<classform>";
    $outstring .="<directori>";
	foreach($Directori as $item){
		$outstring .="<item>";
		$outstring .="<code><![CDATA[".$item["code"]."]]></code>\n";
		$outstring .="<name><![CDATA[".$item["desc"]."]]></name>\n";		
		$outstring .="</item>\n";
	}	
	$outstring .="</directori>";
	$outstring .="<agenda>";  
	foreach($Agenda as $item){
		$outstring .="<item>";
		$outstring .="<code><![CDATA[".$item["code"]."]]></code>\n";
		$outstring .="<name><![CDATA[".$item["desc"]."]]></name>\n";
		$outstring .="</item>\n";
	}
	$outstring .="</agenda>";
	$outstring .="</classform>";
	$this->mc->set("classform_"._IDIOMA,$outstring,(60*60));	
	$this->html_out.= $outstring;
}
?>