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


    $outstring ="<classsearch>";
	$outstring .="<directoris label=\""._CATS_H_DIRECTORI."\">";
    $outstring .="<more href=\"".LK_PAG."".$this->url_encrypt("pg=classall&tree=401&nm="._CATS_H_DIRECTORI)."\" label=\""._VEURE_CATS_DIRECTORI."\"/>";
	$outstring .="</directoris>";
	$outstring .="<agenda label=\""._CATS_H_AGENDA."\">";
    $outstring .="<more href=\"".LK_PAG."".$this->url_encrypt("pg=classall&tree=400&nm="._CATS_H_AGENDA)."\" label=\""._VEURE_CATS_AGENDA."\"/>";
	$outstring .="</agenda>";
	$outstring .="</classsearch>";
	$this->html_out.= $outstring;

?>