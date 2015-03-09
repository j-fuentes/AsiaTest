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
global $all;
global $canal;
global $id_doc;
// http://10.254.162.15/:8080/solr/update?stream.body=<delete><id>99400268845</id></delete>&commit=true
//global $lang;
ini_set('display_errors', '1');
error_reporting(E_ALL);
set_time_limit(60*60*2);

require_once("includes/index.class.inc");

$ent = new index;
//$ent->Debug = true;
$path = "jobs/output/";

$init = time();

if (isset($all) && $all=="y") $ent->query("insert into tmp_entity (entity_id, action, processed) select entity_id, 'S',0 from entity on duplicate key UPDATE  action = 'S', processed = 0;");
if (isset($all) && $all=="agenda") $ent->query("insert into tmp_entity (entity_id, action, processed) select entity_id, 'S',0 from entity where entity_type = 'AG' on duplicate key UPDATE  action = 'S', processed = 0;");
if (isset($canal) && $canal!="") $ent->query("insert into tmp_entity (entity_id, action, processed) select entity_id, 'S',0 from canals where canal_id = '$canal' on duplicate key UPDATE  action = 'S', processed = 0;");
if (isset($id_doc) && $id_doc!="") $ent->query("insert into tmp_entity (entity_id, action, processed) select entity_id, 'S',0 from entity where entity_id = $id_doc on duplicate key UPDATE  action = 'S', processed = 0;");

$ent->query("delete from addresses where entity_type is null;");

$hora = date("H");
if ($hora < 7) {
	$ent->deleteID2delete(true);
	// borrar registros solo de solr
}

if (isset($limit)) $limit = "limit $limit"; else $limit="";
$processed = 0;
if ($ent->query("select entity_id from tmp_import where action = 'D' or action = 'd';")){
	$IDstoDelete = array();
	while($ent->next_record_assoc()){
		$IDstoDelete[] = $ent->Record["entity_id"];
	}
	if (count($IDstoDelete)>0) {
		$response = $ent->client->deleteByIds($IDstoDelete);
		if ($response->success()) {
			$ent->client->commit();
			echo count($IDstoDelete)." docs deleted from index.\n";
		} else {
			echo "Error trying to delete from index.\n";
		}
	} else {
		echo "No docs to delete from index.\n";
	}
}
$ent->query("delete from tmp_import where action = 'D' or action = 'd';");
$ent->query("select entity_id from tmp_import where (action = 'I' or action = 'i' or action = 's' or action = 'S') and processed = false;");
$result = $ent->select_array();
$ent->query("select entity_id from tmp_entity where processed = false;");
if ($result) {
    if ($tmp =  $ent->select_array()) {    
        $result = array_merge($result,$tmp);        
    }    
} else {
    $result=$ent->select_array();
}
  
$errors=array();
if ($result) {
	$total = array();
	foreach($result as $item){
		$total[]=$item["entity_id"];
	}
	$result = array_unique($total);
	unset($total);
	$i = 0;
	echo count($result)." docs to index to solr.\n";
	foreach($result as $entity_id){
		$doc = $ent->getDocToAdd($entity_id,1);
		
		if ($doc){			
			if ($ent->addDoc($doc)!=true) echo "Solr returned error for doc ".$entity_id." \n";				
			if (($i % 1000)==0) {
				$ent->client->commit();
				echo "Indexed $i docs...".(number_format(((time()-$init)/60),2))." Seconds\n"; //print_r($ent->addDoc($doc));
			}
			$i++;
		} else {
			echo "Error getting doc ".$item." no data from DB.\n";
			$errors[]=$entity_id;
		}		
	}	
	$ent->client->commit();
	$ent->query("update tmp_import set processed = true where (action = 'I' or action = 'i' or action = 's' or action = 'S') and processed = false;");
	$ent->query("update tmp_entity set processed = true where processed = false;");
	foreach($errors as $entity_id){
		$ent->query("update tmp_import set processed = false where entity_id = $entity_id;");
	    $ent->query("update tmp_entity set processed = false where entity_id = $entity_id;");
	}
	$ent->query("delete from tmp_entity where processed = true;");
	$ent->query("delete tmp_entity FROM tmp_entity left join entity e on e.entity_id = tmp_entity.entity_id where e.entity_id is null;");	
} else echo "No docs to index.\n";
$ent->BuildSpellIndex();
echo "\nExit Job : ".((time()-$init))." Seconds\n" ;
exit(0);
?>