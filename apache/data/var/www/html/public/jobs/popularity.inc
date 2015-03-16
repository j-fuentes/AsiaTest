<?php
/**
 * Guia de Barcelona - Agenda and Directory
 *
 * This file is part of Guia Barcelona v1.0.0
 * @author Elazos Software Factory
 **/
/**
 * Calculates popularity
 */
//global $lang;
error_reporting(E_ALL);
//global $data;
require_once("includes/engine.class.inc");

$dbi= new engine;

$init = time();

//if (!isset($data)) $data = date("Y-m-d",time());

//$dbi->Debug = 1;
$dbi->CalcPopularity(15);


echo "\nExit Job : ".((time()-$init))." Seconds\n" ;
?>