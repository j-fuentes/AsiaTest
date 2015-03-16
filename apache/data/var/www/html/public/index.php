<?php
/**
 * Guia de Barcelona - Agenda and Directory
 *
 * This file is part of Guia Barcelona v1.0.0
 * @author Elazos Software Factory
 **/
define("FILE_EXT","");
require_once("ctrl/lks_1.inc");  // Lista de Hyperlinks
require_once("ctrl/constants.inc");
require_once("ctrl/sitexml.class.inc");
require_once("ctrl/globals.inc");	

$page = new site;

if ($page->get_page_params()) extract($page->vars);
$page->getLanguage();
$page->SetSession();
$page->vars_ste=$page->get_cookie_state(""._CkSTATE."");

if (array_key_exists("pg",$page->vars)) {	
	$page->central=NULL;
	$pg=explode(" ",$page->vars["pg"]);
	foreach($pg as $value) {
		$page->central["CENTRAL"][0]["BLOCK"][]=array("VALUE"=>$value);
	}
	unset($pg);
}
$page->state();
$page->out();
?>