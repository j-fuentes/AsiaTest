<?php
//error_reporting(E_ALL);

$id_doc = $_GET["id_doc"];

$out_string = file_get_contents("http://10.10.10.5/?pg=detall&id_doc=$id_doc&xout=1");

//echo $out_string;
$xp = new XsltProcessor();
// create a DOM document and load the XSL stylesheet
$xsl = new DomDocument;
$xsl->load('tpl/ids/'.$id_doc.'.xsl');

eval("\$xsl->getElementsByTagName('output')->item(0)->setAttribute('encoding',UTF-8);");
// import the XSL styelsheet into the XSLT process
$xp->importStylesheet($xsl);
$xml_doc = new DomDocument;
$xml_doc->loadXML($out_string);
$result = $xp->transformToXML($xml_doc);
// TODO !! echo headers http
echo $result;

?>