<?php
/**
 * Guia de Barcelona - Agenda and Directory
 *
 * This file is part of Guia Barcelona v1.0.0
 * @author Elazos Software Factory
 **/
/*
//global $lang;
set_time_limit(60*30);

$init = time();

require_once("includes/agrecom.class.inc");

$agrecom = new agrecom;
//$agrecom->Debug = true;
$item = $agrecom->GetXMLAgendaRecomenada();
if (!$item) {echo "ERROR : No se ha podido obtener la Agenda destacada de la URL bcn.cat";exit(1);}
$agrecom->EmptyAllTables();
$agrecom->AddCatalan($item);
$agrecom->AddOtherLanguages($item);
// ReIndexo en solr el contenido
$agrecom->query("insert into tmp_entity (entity_id, action, processed) SELECT entity_id, 'S',0 FROM agrecomentity_id a ON DUPLICATE KEY UPDATE action='S', processed=0;");

echo "Importados ".$agrecom->tot[1]." Catalan, ".$agrecom->tot[2]." Castellano, ".$agrecom->tot[3]." Ingles.\n";
echo "\nExit Job : ".((time()-$init))." Seconds.<br/>\n" ;
//print_r($item);
$mc = new Memcached();
$mc->addServer("localhost", 11211);
if ($mc->delete("actdest_ca")) echo "Deleted cache Recomanada ca ".date('d/m/y H:i')."<br/>\n";
if ($mc->delete("actdest_es")) echo "Deleted cache Recomanada es ".date('d/m/y H:i')."<br/>\n";
if ($mc->delete("actdest_en")) echo "Deleted cache Recomanada en ".date('d/m/y H:i')."<br/>\n";

ini_set("display_errors",true);
error_reporting(E_ALL);

$url = "http://noticies.bcn.cat/api/updentity.php";
$fields_string = "p=".implode(",",$agrecom->rejected_post_id);
$fields["p"]=implode(",",$agrecom->rejected_post_id);


//open connection
$ch = curl_init();

//set the url, number of POST vars, POST data
curl_setopt($ch,CURLOPT_URL, $url);
curl_setopt($ch,CURLOPT_POST, count($fields));
curl_setopt($ch,CURLOPT_POSTFIELDS, $fields_string);

//execute post
$result = curl_exec($ch);

//close connection
curl_close($ch);

echo $result;
*/
require_once("jobs/hourstats.inc");
?>