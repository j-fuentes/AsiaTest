<?php
global $id_doc;
global $from;

require_once("includes/search.class.inc");

if ($tmp=$this->mc->get($id_doc._IDIOMA)) {
	//echo "Cached:$id_doc";
	$entity = $tmp["entity"];	
} else {
	// deberia volver a cargar el Entity
	/**
     * @TODO deberia volver a cargar el Entity 
     * */	
}


//Registros relacionados
if (!$this->notfound && !$this->isMobile && array_key_exists("classification",$entity)){
	$outString = "";
	//print_r($entity);
	$classCodes = "";
	foreach($entity["classification"] as $branch){
		$tmp="";
		ksort($branch);
		foreach($branch as $code=>$value){
			$tmp = "code$code:".$value["code"];			
		}
		if ($classCodes=="") $classCodes = $tmp;else $classCodes.= " OR $tmp";
	}	
	$solr = new search(); 
	$rows = 4;
	if ($solr->client) {
		$filters = array($classCodes);
		$query_response = $solr->getRelated($filters,$from,$rows);
		$response = $query_response->getResponse();
		if (is_array($response->response->docs)){
			
			require_once("includes/lists/xmlist.php");
			$list = new xmllist;
			//$this->html_out .= "<bleft><leftfilter>".$list->facetlist($facet_data,$facet_queries, $SelectedFacets,"pg=search&q=$q$keywords" )."</leftfilter></bleft>";
			$outString .= "<related label=\""._RELATED."\">";
			$outString .= $list->xml_list($response->response->docs,$from,$rows,"pg=detall&id_doc=$id_doc","pg=detall&id_doc=",null,null, $response->response->numFound,$solr->query->getFields(), null);
			$outString .= "</related>";
		}
	}

	$this->html_out .= $outString;
}

?>