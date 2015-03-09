<?php
/**
 * Guia de Barcelona - Agenda and Directory
 *
 * This file is part of Guia Barcelona v1.0.0
 * @author Elazos Software Factory
 **/
global $id_doc;
global $pass;

if (isset($id_doc) && isset($pass) && $pass="jkhgoihqe23rfalvl67kdvnsjvb"){

	require_once("includes/index.class.inc");

	//global $lang;
	error_reporting(E_ALL);
	ini_set("display_errors",true);
	set_time_limit(60*60);

	$solr = new index;

	$SolrUpdateResponse  = $solr->client->deleteById($id_doc);
	//print_r($SolrUpdateResponse->getResponse());
	$SolrUpdateResponse  = $solr->client->commit();
	//print_r($SolrUpdateResponse->getResponse());

	$solr->query("delete from agenda where entity_id = $id_doc");
	$solr->query("delete from equipment where entity_id = $id_doc");
	$solr->query("delete from entity where entity_id = $id_doc");
	
	$mc = new Memcached();
	$mc->addServer("localhost", 11211);
	
	$mc->delete($id_doc.'ca');
	$mc->delete($id_doc.'es');
	$mc->delete($id_doc.'en');

	echo "<br/>id_doc deleted from DB, index and Cache.";	
	
} else echo "Id not set or error password. Nothing to do."
?>