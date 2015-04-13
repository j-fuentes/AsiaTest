<?php
/**
 * Guia de Barcelona - Agenda and Directory
 *
 * This file is part of Guia Barcelona v1.0.0
 * @author Elazos Software Factory
 **/

/**
 * Exports tables needed for installation to install/tmp folder
 */

//global $lang;
error_reporting(E_ALL);
global $data;
require_once("includes/engine.class.inc");

$dbi= new engine;

$init = time();

//$dbi->Debug = 1;
if (isset($data))
    $dbi->CalculateItemRelation($data);
    else 
    $dbi->CalculateItemRelation();
    
    
//$dbi->Debug = 0;

echo "\nExit Job : ".((time()-$init))." Seconds\n" ;
?>