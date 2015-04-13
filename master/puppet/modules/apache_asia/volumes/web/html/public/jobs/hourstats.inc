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
set_time_limit(60*30);
ini_set("display_errors",1);
error_reporting(E_ALL);
//global $data;
require_once("includes/engine.class.inc");
$result = "";
$dbi= new engine;

$init = time();

//if (!isset($data)) $data = date("Y-m-d",time());

//$dbi->Debug = 1;
$dbi->CalcMViewed(1); //more viewed today
$dbi->CalcMViewed(4); //more voted today

$result .= "<br/>\nExit Job 1 : ".((time()-$init))." Seconds\n" ;

$init = time();

require_once("includes/agrecom.class.inc");

$agrecom = new agrecom;

$item = $agrecom->GetXMLAgendaRecomenada();
if (!$item) { 
	$result .= "ERROR : No se ha podido obtener la Agenda destacada de la URL http://noticies.bcn.cat/api/agrecom.php?lg=ca";
} else {
	
	$agrecom->EmptyAllTables();
	$result .= $agrecom->AddCatalan($item);
	$result .= $agrecom->AddOtherLanguages($item);
	
	$result .= "<br/>Importados ".$agrecom->tot[1]." Catalan, ".$agrecom->tot[2]." Castellano, ".$agrecom->tot[3]." Ingles.\n";
	$result .= "<br/>\nExit Job : ".((time()-$init))." Seconds.<br/>\n" ;
	
	$mc = new Memcached();
	$mc->addServer("localhost", 11211);
	if ($mc->delete("actdest_ca")) $result .= "Deleted cache Recomanada ca ".date('d/m/y H:i')."<br/>\n";
	if ($mc->delete("actdest_es")) $result .= "Deleted cache Recomanada es ".date('d/m/y H:i')."<br/>\n";
	if ($mc->delete("actdest_en")) $result .= "Deleted cache Recomanada en ".date('d/m/y H:i')."<br/>\n";
	
	
	$url = "http://noticies.bcn.cat/api/updentity.php";
	$fields_string = "p=".implode(",",$agrecom->rejected_post_id);
	$fields["p"]=implode(",",$agrecom->rejected_post_id);
	
	
	//open connection
	$ch = curl_init();
	
	//set the url, number of POST vars, POST data
	curl_setopt($ch,CURLOPT_URL, $url);
	curl_setopt($ch,CURLOPT_POST, count($fields));
	curl_setopt($ch,CURLOPT_POSTFIELDS, $fields_string);
	curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
	curl_setopt($ch, CURLOPT_HEADER, false);
	
	//execute post
	
	$result .= curl_exec($ch);
	
	//close connection
	curl_close($ch);
}

$result .= "<br/>\nExit total Job : ".((time()-$init))." Seconds.<br/>\n" ;

echo $result;

if (stripos($result,"error")===false) {
	echo "<br/>\nNo errors. Any email sent.";
	} else {
	echo "<br/>\nSending alert email....";
	require_once("includes/smtp.inc");
	$smtp=new smtp_class;
	//$smtp->debug=1;               /* Set to 1 to output the communication with the SMTP server */
	//$smtp->html_debug=1;
	$smtp->type=0;   // set to 1 to use php mail function, set to 0 to uses smtp
	
	$item["from"]="info@elazos.com";
	$item["from_name"]="Jobs execution";
	$item["to"][0]["email"]="info@elazos.com";
	$item["to"][0]["name"]="Elazos Software Factory";
	
	$item["to"][1]["email"]="mcomaposada@bcn.cat";
	$item["to"][1]["name"]="COMAPOSADA MARTI,  MONTSERRAT";
	$item["to"][2]["email"]="opalau@bcn.cat";
	$item["to"][2]["name"]="Palau Tarrades, Octavi";
	
	$item["subject"]="Process - hourstats executed with errors at ".date("d/m/Y H:i:s");
	//$item["msg"]="Executed from guia<br/>\n".$result;
	$result = "\n<html><body><p>Nom : hourstats<br/>Execució: cada 15mins<br/>Descripció : Aquest procés descarrega les agendes de wp i les carrega a GUIA. Despublica a wp les agendes caducades a ASIA i publica els post/agenda previstos.<br/>"
	.$result."</p></body></html>";
	$item["msg"] = utf8_decode($result);
	$item["html"]=true;
	
	$smtp->sendemail($item["from"],$item["from_name"],$item["to"],$item["subject"],$item["msg"],$item["html"]);
	echo "<br/>\nAlert email sent!";	
}
?>