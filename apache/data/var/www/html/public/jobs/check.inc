<?php
/**
 * Guia de Barcelona - Agenda and Directory
 *
 * This file is part of Guia Barcelona v1.0.0
 * @author Elazos Software Factory
 **/

/**
 * Check if all data between Mysql and SOLR is consistent
 */


//global $lang;
error_reporting(E_ALL);
set_time_limit(60*60*2);

require_once("includes/index.class.inc");
require_once("includes/search.class.inc");
// Comprueba que en SOLR sobren docs y los borrar
$index = new index;
$sr = new search;
$sr->q->setQuery("*:*");
//$sr->q->addFilterQuery("type:AG");
$sr->q->addField('id');
$sr->q->setStart(0);
$sr->q->setRows(50000);
try {
	$query_response = $sr->client->query($sr->q);
	$response = $query_response->getResponse();
} catch(SolrException $e){
	print_r($e);die;
}

echo "Se han encontrado ".count($response->response->docs)." documentos<br/>\n";
$processedIDs = array();
$IDinSOLR = array();

$index->query("select entity_id from entity");
$allEntity_ids = $index->select_array();

foreach($allEntity_ids as $record){
	$IDinDB[]=$record["entity_id"];
}
unset($allEntity_ids);
foreach($response->response->docs as $item){
	
	if (array_search($item->id, $IDinDB)===FALSE) {
			$processedIDs[] = $item->id;
	}
	
	$IDinSOLR[] = $item->id;

}
/*
foreach($response->response->docs as $item){
	if ($index->query("select entity_id from entity where entity_id = ".$item->id)){
		if ($index->num_rows()==0) {
			$processedIDs[] = $item->id;
		}
	}
	$IDinSOLR[] = $item->id;
	 
}*/
echo "Docs no contenidos en la BD ".count($processedIDs)."<br/>\n";
if (count($processedIDs)>0){
	foreach($processedIDs as $item){
		$SolrUpdateResponse  = $index->client->deleteById($item);
		//print_r($SolrUpdateResponse->getResponse());
	}
	$SolrUpdateResponse  = $index->client->commit();
	print_r($SolrUpdateResponse->getResponse());
}
// fin : Comprueba que en SOLR sobren docs y los borrar
// Comprueba que todos los registros de Mysql estan en SOLR y sino los añade para insertar
$processedIDs = array();
//if ($index->query("select entity_id from entity")){
//	$total = $index->select_array();
	foreach($IDinDB as $item) {
       if (!array_search($item,$IDinSOLR)) { 
       	   $processedIDs[] =    $item;     
           $fields["processed"] = 0;
           $fields["action"] = "'s'";
           $fields["entity_id"] = $item;          
           $index->insert($fields,"tmp_entity",true);         
       }
	}
//}
echo "Docs no contenidos en SOLR ".count($processedIDs)."<br/>\n";

$init = time();
echo "\nExit Job : ".((time()-$init))." Seconds\n" ;
exit(0);
?>