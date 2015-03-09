<?php
date_default_timezone_set('Europe/Madrid');
ini_set('display_errors', '1');
error_reporting(E_ALL);

$ip = gethostbyname("eldigital.bcn.cat");
echo "La Ip de eldigital.bcn.cat es : ".$ip."<br/>";

if ($ip=="eldigital.bcn.cat")
	echo "Error resolving eldigital.bcn.cat<br/>";
else
	echo "Great !!! eldigital.bcn.cat is resolved<br/><br/>";

if (false === file_get_contents("http://eldigital.bcn.cat/api/search.php?type=post&lg=ca&nr=20&from=0")) {
	echo "<br/>Error file_get_contents http://eldigital.bcn.cat/api/search.php?type=post&lg=ca&nr=20&from=0<br/>";
	
} else echo "Great !!! file get contents to eldigital.bcn.cat works!<br/>";


?>