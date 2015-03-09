<?php
/**
 * Guia de Barcelona - Agenda and Directory
 *
 * This file is part of Guia Barcelona v1.0.0
 * @author Elazos Software Factory
 **/
global $id;

if (isset($id)){

	require_once("includes/index.class.inc");

	//global $lang;
	error_reporting(E_ALL);
	set_time_limit(60*60);

	$solr = new index;

	$SolrUpdateResponse  = $solr->client->deleteById($id);
	print_r($SolrUpdateResponse->getResponse());
	$SolrUpdateResponse  = $solr->client->commit();
	print_r($SolrUpdateResponse->getResponse());

} else echo "Id not set. Nothing to do."
?>