<?php
/**
 * Guia de Barcelona - Agenda and Directory
 *
 * This file is part of Guia Barcelona v1.0.0
 * @author Elazos Software Factory
 **/

/**
 * Index doc to solr
 */

global $limit;

// http://10.254.162.15/:8080/solr/update?stream.body=<delete><id>99400268845</id></delete>&commit=true
//global $lang;
ini_set('display_errors', '1');
error_reporting(E_ALL);
set_time_limit(60*60*2);

require_once("includes/update.class.inc");

$ent = new ASIAupdate;
//$ent->Debug = true;
$path = "jobs/output/";

$init = time();

$ent->GetXMLASIA();

echo "\nExit Job : ".((time()-$init))." Seconds\n" ;
exit(0);
?>