<?php
/**
 * Guia de Barcelona - Agenda and Directory
 *
 * This file is part of Guia Barcelona v1.0.0
 * @author Elazos Software Factory
 **/
/**
 * Execute diferent jobs using table Jobs.
 **/
/**
 * Before any execution checks if script is executed from command line an gets parameters.
 **/
error_reporting(E_ALL); // Deshabilitar todo reporte de errores

if (isset($argv)) { //Note:  This variable is only available when register_argc_argv  is enabled.  
	parse_str($argv[1],$params);
	//print_r($argv);echo "\n";
	//print_r($params);echo "\n";
	foreach ($params as $name=>$value) {
		switch($name){
			case "host":
				$_SERVER["HTTP_HOST"]=$value;
				break;
			case "jobs":
				$_GET["jobs"]=$value;
				break;
		} //end switch
	} // end for
	extract($params);
} else {
	extract($_GET);
}

set_time_limit(60*10);

/**
 * Links of the public site.
 **/
require_once("ctrl/lks_1.inc");  // Lista de Hyperlinks
/**
 * Constants of the public site.
 **/
require_once("ctrl/constants.inc");
/**
 * Labels in default language or if lang is set in URL lang=code
 **/
if (isset($lang))
require_once(_DirLANGS."lang_".$lang.".inc");
else require_once(_DirLANGS."lang_"._DEFAULT_LANG.".inc");

/**
 * Global vars of public site.
 **/
require_once("ctrl/globals.inc");



if (!isset($jobs)) echo "Error parameters : host=Url of the site without http://, jobs=Job_Name separated by commas, Optional : Lang = Laguage Code (en, es, fr) if not set then default language <br/>You can create any other variable to send to the job.";
else {
	$jobs=explode(",",$jobs);
	foreach($jobs as $job){
		include("jobs/$job.inc");
	}
}
?>
