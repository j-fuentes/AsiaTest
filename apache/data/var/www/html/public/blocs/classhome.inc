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


if ($outstring=$this->mc->get("classhome_"._IDIOMA)){
	$this->html_out .= $outstring;	
} else {
	global $nm;

	require_once("includes/classification.class.inc");

	$class = new classification;
	
	$ag_home = array("0040001001","0040001002","0040001006","0040001008","0040001009","0040001023","0040001010","0040001019","0040001014","0040001012");
	$eq_home = array("0040101001","0040101003","0040101002","0040101004","0040101006","0040101008","0040101000","0040101012","0040101013","0040101015");
                     
	//$class->Debug=0;
	//echo $class->getClassTreeXML("0040101",1);

	$Directori = $class->getClassTreeArray("0040100",_LANGUAGE,1);
	$Agenda = $class->getClassTreeArray("0040000",_LANGUAGE,1);

	$outstring .="<classhome>";
	$outstring .="<direchome label=\""._CATS_H_DIRECTORI."\">";
	$col="1";
	$i=1;
	
	
	foreach($Directori as $item){
		if (array_search($item["code"],$eq_home)!==false){
			$outstring .="<item$col href=\"".LK_PAG."".$this->url_encrypt("pg=search&q=*:*&code0=".$item["code"])."\">";
			$outstring .="<name><![CDATA[".$item["desc"]."]]></name>\n";
			$outstring .="</item$col>";
			if ($i==5) $col=2;
			$i++;
		}
	}
	
	$outstring .="<more href=\"".LK_PAG."".$this->url_encrypt("pg=classall&tree=401&nm="._CATS_H_DIRECTORI)."\" label=\""._VEURE_CATS_DIRECTORI."\"/>";
	$outstring .="</direchome>";

	$outstring .="<agendahome label=\""._CATS_H_AGENDA."\">";
    $col="1";
	$i=1;
	foreach($Agenda as $item){
		if (array_search($item["code"],$ag_home)!==false){
		$outstring .="<item$col href=\"".LK_PAG."".$this->url_encrypt("pg=search&q=*:*&code0=".$item["code"])."\">";
		$outstring .="<name><![CDATA[".$item["desc"]."]]></name>\n";
		$outstring .="</item$col>";
		if ($i==5) $col=2;
		$i++;
		}
	}
	$outstring .="<more href=\"".LK_PAG."".$this->url_encrypt("pg=classall&tree=400&nm="._CATS_H_AGENDA)."\" label=\""._VEURE_CATS_AGENDA."\"/>";
	$outstring .="</agendahome>";
	$outstring .="</classhome>";
	
		
	$this->mc->set("classhome_"._IDIOMA,$outstring,(60*60));
	
	$this->html_out.= $outstring;
}


?>