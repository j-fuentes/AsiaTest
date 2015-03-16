<?php
/**
 * Guia de Barcelona - Agenda and Directory
 *
 * This file is part of Guia Barcelona v1.0.0
 * @author Elazos Software Factory
 **/

/**
 *Returns xml node for home page.
 *Gets content from a xml file defined in xml navigator file.
 *@package blocks_public
 **/

require_once("includes/lists/xmlist.php");

	$options = array
	(
    'hostname' => SOLR_SERVER_HOSTNAME,
    'login'    => SOLR_SERVER_USERNAME,
    'password' => SOLR_SERVER_PASSWORD,
    'port'     => SOLR_SERVER_PORT,
	);

	$client = new SolrClient($options);
	$query = new SolrQuery();

	$query->setQuery("*:*");

	//&spellcheck=true&spellcheck.collate=true
	//$query->addParam('spellcheck', "true");
	//$query->addParam('qt', "dismax");

	$query->setFacet(true);
	$query->addFacetField('type')->addFacetField('strwhen')->addFacetField('ticket')->addFacetField('districtstr')->addFacetField("strclass0")->setFacetMinCount(50);

	$query->addFacetQuery ("-preu_min:[* TO *]");
	$query->addFacetQuery ("preu_min:[1 TO 30]");
	$query->addFacetQuery ("preu_min:[30 TO 60]");
	$query->addFacetQuery ("preu_min:[60 TO *]");
	
	$query->setStart(0);
	$query->setRows(1);
	$query->addField('id');
	//->addField('name')->addField('sectionname')->addField('classic')->addField('district')->addField('type')->addField('address');

	$query_response = $client->query($query);

	$response = $query_response->getResponse();

	//print_r($response);
	//echo "Object vars : ".count(get_object_vars($response->spellcheck->suggestions));

	$facet_data = $response->facet_counts->facet_fields;
	$facet_queries = $response->facet_counts->facet_queries;

	//print_r($response);
	
	if (is_array($response->response->docs)){
		$this->html_out .= "<leftfilter>";
		$list = new xmllist;
		$this->html_out .= $list->facetlist($facet_data,$facet_queries, null,"pg=search&q=*:*" );
		//$this->html_out .= $list->xml_list($response->response->docs, $from,$rows,"","pg=detall&id_doc=",null,"pg=home&q=$q$keywords", $response->response->numFound,$query->getFields());
		$this->html_out .= "</leftfilter>";
	} 
	//print_r($response);

?>