<?php
date_default_timezone_set('Europe/Madrid');
ini_set('display_errors', '1');
error_reporting(E_ALL);

$ip = gethostbyname("guia.bcn.cat");
echo "La Ip de guia.bcn.cat es : ".$ip."<br/>";

if ($ip=="guia.bcn.cat")
	echo "Error resolving guia.bcn.cat<br/>";
else
	echo "Great !!! guia.bcn.cat is resolved<br/><br/>";

if (false === file_get_contents("http://guia.bcn.cat/?pg=search&q=nr=10&from=0&xout=xml")) {
	echo "<br/>Error file_get_contents http://guia.bcn.cat/?pg=search&q=nr=10&from=0&xout=xml<br/>";
	
} else echo "Great !!! file get contents to guia.bcn.cat works!<br/>";


if (false === fopen("http://w10.bcn.cat/APPS/asiw/ObtenerImagen?vId=2&eId=99400292072","r")) {
	echo "<br/>Error fopen http://w10.bcn.cat/APPS/asiw/ObtenerImagen?vId=2&eId=99400292072<br/>";

} else echo "Great !!! fopen to w10.bcn.cat works!<br/>";





?>