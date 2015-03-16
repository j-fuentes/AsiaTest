<?php
/**
 * Guia de Barcelona - Agenda and Directory
 *
 * This file is part of Guia Barcelona v1.0.0
 * @author Elazos Software Factory
 **/

/**
 *Returns xml node for search page.
 *Gets content from a xml file defined in xml navigator file.
 *@package blocks_public
 **/

//require_once("includes/forms/forms_xml.php");
require_once("includes/lists/xmlist.php");
require_once("includes/search.class.inc");

global $m;
global $from;
global $nr;
global $q; // words to search
global $p; // preu
global $d; // Quan
global $dt; // Dates
global $t; //1 all words, 2 any word, 3 phrase
global $canal; // Canal que es code_canal en SOLR
global $c; // Code classificacion no internet
global $pt; // lat;lng separated by ; 
global $pd; // only if pt is set - distance in meters ;
global $code_comarca; // comarca
global $wtarget; // webtarget
global $af;//addfield add new field to result
global $id;//entity_id comma separated 
global $pd;//proxdate

global $code0, $code1, $code2, $code3, $code4, $code5, $code_tit,$code_info,$cf;
global $mnj,$acll,$cuina,$extra;

global $cd; // contains codex:code
if (isset($cd)&& $cd!="") {$tmp=explode(":",$cd);eval("\$".$tmp[0]." = \"".$tmp[1]."\";");}


global $ad; //street name
global $ini; //numero de calle inicio
global $fi; //numero de calle fin
global $type;
global $ticket;
global $districtstr;
global $barristr;
global $sort;
global $response;
global $tr; //List of tree_ids to show on filter.

if(array_key_exists("debug",$_GET)){
	ini_set("display_errors", true);
	error_reporting(E_ALL);
}

$strQuery = "";

$outString = "";
if (isset($nr)) $rows = $nr; else$rows = 10;
$keywords = "";

if(!isset($from) || trim($from)=='' ) $from = 0;

//$form = new xmlform("f1","","GET",""._FIND."");
//$form->add_textbox("search","",80,80);
//$form->add_hidden("data");
//if (!$form->process()){
//if (isset($q) && $q != "" ) {
//$form->fields["search"]->value=$q;
//}

//} else {
//$q = $form->fields["search"]->value;
//}
//$form->fields["data"]->value="pg=search";

//$outString .= "<sbox>".$form->draw()."</sbox>";

if (!isset($q) || $q == "" ) $q="*:*";

$strQuery = $q;

if ($q){

	
	$sr = new search();
	//$q = strtolower($q);
	$fq = $sr->GetFacetQueriesDefinition();
    
	$q=$sr->preQueryFilter($q); 

	if (isset($t) && $t!=""){
		switch($t){
			case "1":
				$sr->q->setQuery(strtolower($q));
				if ($q!="*:*") $sr->q->addParam('qt', "dismax");
				break;
			case "2":
				$sr->q->setQuery(strtolower($q));
				$sr->q->addParam('qt', "standard");
				$sr->q->addParam('q.op', "OR");
				break;
			case "3":
				$sr->q->setQuery("\"".strtolower($q)."\"");
				$sr->q->addParam('qt', "standard");
				break;
			default:
				$sr->q->setQuery(strtolower($q));
				if ($q!="*:*") $sr->q->addParam('qt', "dismax");
				break;
		}
		$keywords.="&t=$t";
	} else {
		$sr->q->setQuery(strtolower($q));
		if ($q!="*:*") $sr->q->addParam('qt', "dismax");
		//$sr->q->addParam('bq', "name");
		//$sr->q->addParam('q.op', "AND");
	}

	if ($q=="*:*") $sr->q->addSortField ("rellevancy",SolrQuery::ORDER_DESC);

	if (!isset($tr)){
		$tr="400,401";
	} else {
		$keywords.="&tr=$tr";
	}
	
	//&spellcheck=true&spellcheck.collate=true
	$sr->q->addParam('spellcheck', "true");
	//$sr->q->addParam('spellcheck.count',3);

	if (isset($sort)) {
		$arrsort = $sr->SetSort($sort,$keywords);
	} else $arrsort[0]="";	

	if (isset($type)) {
		$sr->q->addFilterQuery("type:\"".$type."\"");
		$keywords.="&type=$type";
	}
	if (isset($d)) {
		$sr->q->addFilterQuery($fq["d_".$d]);
		$keywords.="&d=$d";
		$sr->q->addFacetQuery($fq["d_".$d]);
	}
	if (isset($p) && $p!="") {
		$sr->q->addFilterQuery($fq["p_".$p]);
		$keywords.="&p=$p";
		$sr->q->addFacetQuery($fq["p_".$p]);
	}
	if (isset($ticket)) {
		$sr->q->addFilterQuery("ticket:\"".$ticket."\"");
		$keywords.="&ticket=$ticket";
	}

	if (isset($ad) && trim($ad)!="") {
		$sr->q->addFilterQuery("address:\"".$ad."\"");
		$keywords.="&ad=$ad";
	}
	
	// add fields to result list
	if (isset($af) && $af!=""){
		$keywords.="&af=$af";
		$af=explode(",",$af);
		foreach($af as $afItem){
			$sr->q->addField($afItem);
		}
	}
	
	if (isset($pd) && $pd!=""){
		$tmp = explode(",",$pd);
		if (count($tmp)==2) $sr->q->addFilterQuery("proxdate:[".$tmp[0]."T00:00:00Z TO ".$tmp[1]."T23:59:59Z]");
		if (count($tmp)==1) $sr->q->addFilterQuery("proxdate:[".$tmp[0]."T00:00:00Z TO ".$tmp[0]."T23:59:59Z]");
		$tmp=null;
		$keywords.="&pd=$pd";
	}

	if (isset($ini)&& is_numeric($ini) && isset($fi)&& is_numeric($fi)) {		
		$sr->q->addFilterQuery("streetnum:[$ini TO $fi]");
		$keywords.="&ini=$ini&fi=$fi";
	} else {
		if (isset($ini)&& is_int($ini)) {
			$sr->q->addFilterQuery("streetnum:[$ini TO *]");
			$keywords.="&ini=$ini";
		}
		if (isset($fi)&& is_int($fi)) {
			$sr->q->addFilterQuery("streetnum:[* TO $fi]");
			$keywords.="&fi=$fi";
		}
	}

	if (isset($districtstr) && $districtstr!="" && substr($districtstr,0,1)!="*") {
			$tmp = explode (",",$districtstr);
			$strFilterQuery = "";
			foreach($tmp as $tmp_code){
				if ($strFilterQuery=="") $strFilterQuery = "\"$tmp_code\"";
				else $strFilterQuery.=" OR \"$tmp_code\"";
			}
			$sr->q->addFilterQuery("districtstr:(".$strFilterQuery.")");
			
		//$sr->q->addFilterQuery("districtstr:\"".$districtstr."\"");
		$keywords.="&districtstr=$districtstr";
		$sr->q->addFacetField('barristr');
	}
	
	
	
	
	if (isset($barristr) && $barristr!="" && substr($barristr,0,1)!="*") {
		$sr->q->addFilterQuery("barristr:\"".$barristr."\"");
		$keywords.="&barristr=$barristr";
	}
	
	$FacetField = "code0";
	
	if ($this->solr!="") {
		$sr->q->addFacetField('code_tit');
		$sr->q->addFacetField('code_info');
		$sr->q->addField('code_tit');
		$sr->q->addFilterQuery($this->solr);
		$FacetField = "code1";
		$keywords.="&code0=0040101006";
	} else {
		if (isset($canal) && trim($canal)!="") {
			$sr->q->addFilterQuery("code_canal:\"".$canal."\"");
			$keywords.="&canal=$canal";						
		}
		if (isset($code_tit)) $sr->q->addFacetField('code_tit');	
	}
	

	if (isset($code_comarca) && $code_comarca=="") $sr->q->addFacetField('code_comarca');
	
	if (isset($code_comarca) && $code_comarca!="") {
		
		$sr->q->addFacetField('code_comarca');
		$sr->q->addFilterQuery("code_comarca:\"$code_comarca\"");
		$keywords.="&code_comarca=$code_comarca";
	}
			
	if (isset($mnj)) {		
		$sr->q->addFilterQuery("code_info:002200400");
		$keywords.="&mnj=002200400";		
	}
	if (isset($acll)) {
		$sr->q->addFilterQuery("code_info:002200412");
		$keywords.="&acll=002200412";		
	}
	if (isset($cuina)) {
		$sr->q->addFilterQuery("code_info:002200410");
		$keywords.="&cuina=002200410";		
	}
	if (isset($extra)) {
		$sr->q->addFilterQuery("code_info:002200441");
		$keywords.="&extra=002200441";		
	}
	
	if (isset($code_tit) && $code_tit!="") {
		$sr->q->addFilterQuery("code_tit:".$code_tit."");
		$keywords.="&code_tit=$code_tit";		
	}
	
	if (isset($code_info) && $code_info!="") {
		$sr->q->addFilterQuery("code_info:".$code_info."");
		$keywords.="&code_info=$code_info";		
	}
	
	if (isset($wtarget) && $wtarget!="") {
		$sr->q->addField('code_postwt');
		$keywords.="&wtarget=$wtarget";
	}
	
	if (isset($id) && $id!="") {
		$strFilterQuery = "";
		$strFilterQuery = str_replace(","," OR id:","id:".$id);
		$strFilterQuery = str_replace(";"," AND id:",$strFilterQuery);
		$sr->q->addFilterQuery($strFilterQuery);
		$keywords.="&id=$id";
	}	
	
	if (isset($c) && $c!="") {		
		$strFilterQuery = "";
	    $strFilterQuery = str_replace(","," OR code_prop:","code_prop:".$c);
	    $strFilterQuery = str_replace(";"," AND code_prop:",$strFilterQuery);	    
		$sr->q->addFilterQuery($strFilterQuery);
		$keywords.="&c=$c";
	}

	if (isset($cf) && $cf!="") {
		$tmp = explode (",",$cf);		
		$strFilterQuery = "";		
		foreach($tmp as $tmp_code){
			$level = substr($tmp_code,6,1)-1;
			if ($strFilterQuery=="") $strFilterQuery = "code$level:$tmp_code";
			else $strFilterQuery.=" OR code$level:$tmp_code";
		}		
		$sr->q->addFilterQuery($strFilterQuery);
		$keywords.="&cf=$cf";		
	}
	
	if (isset($code0) && $code0!="") {
		$sr->q->addFilterQuery("code0:".$code0."");
		$keywords.="&code0=$code0";
		$FacetField = "code1";
	}
	if (isset($code1)) {
		$sr->q->addFilterQuery("code1:".$code1."");
		$keywords.="&code1=$code1";
		$FacetField = "code2";
	}
	if (isset($code2)) {
		$sr->q->addFilterQuery("code2:".$code2."");
		$keywords.="&code2=$code2";
		$FacetField = "code3";
	}
	if (isset($code3)) {
		$sr->q->addFilterQuery("code3:".$code3."");
		$keywords.="&code3=$code3";
		$FacetField = "code4";
	}
	if (isset($code4)) {
		$sr->q->addFilterQuery("code4:".$code4."");
		$keywords.="&code4=$code4";
		$FacetField = "code5";
	}
	
	if (isset($pt) && $pt!=""){
		$latlong = preg_split("/,/", $pt);
		if (!isset($pd)) $pd = 500; 
		
		$LatLongs = $sr->getLatLongDistance($latlong[0], $latlong[1], ($pd/1000));		
		$sr->q->addFilterQuery("gmapx:[".$LatLongs["minLat"]." TO ".$LatLongs["maxLat"]."]");
		$sr->q->addFilterQuery("gmapy:[".$LatLongs["minLon"]." TO ".$LatLongs["maxLon"]."]");
		$keywords.="&pt=$pt";
	}

	if (isset($dt) && $dt!="") {
		//2007-03-06T00:00:00Z format of solr dates
		$tmp = explode(",",$dt);
		if (count($tmp)==1){
			$dayweek = date("w",strtotime($tmp[0]));
			if ($dayweek==0) $dayweek = 7;			
			$sr->q->addFilterQuery("d$dayweek:true AND begindate:[* TO ".$dt."T23:59:59Z] AND enddate:[".$dt."T00:00:00Z TO *]");
		} else {
			$strTmp = "";
			if ($tmp[0]==$tmp[1]){
				$dayweek = date("w",strtotime($tmp[0]));
				if ($dayweek==0) $dayweek = 7;
				$strTmp = "d$dayweek:true";
			} else {
				$diff = round((strtotime($tmp[1]) - strtotime($tmp[0]))/86400);
				if ($diff<7){
					$dayweekstart = date("w",strtotime($tmp[0]));
					if ($dayweekstart==0) $dayweekstart = 7;
					$dayweekend = date("w",strtotime($tmp[1]));
					if ($dayweekend==0) $dayweekend = 7;
					for($i=$dayweekstart;$i<=$dayweekend;$i++)
					if ($strTmp=="") $strTmp .= "d$i:true"; else $strTmp .= " OR d$i:true";
				}
			}	
			if ($strTmp!="") $strTmp = "($strTmp) AND";
			//echo "$strTmp begindate:[* TO ".$tmp[1]."T23:59:59Z] AND enddate:[".$tmp[0]."T00:00:00Z TO *]";		
			$sr->q->addFilterQuery("$strTmp begindate:[* TO ".$tmp[1]."T23:59:59Z] AND enddate:[".$tmp[0]."T00:00:00Z TO *]");
		}
		$keywords.="&dt=$dt";
	} else {
		if (!isset($d)){
			$sr->q->addFacetQuery($fq["d_avui"]);
			$sr->q->addFacetQuery($fq["d_dema"]);

			if (array_key_exists("d_cap",$fq)) $sr->q->addFacetQuery($fq["d_cap"]);
			$sr->q->addFacetQuery($fq["d_caps"]);
			$sr->q->addFacetQuery($fq["d_setmana"]);
			$sr->q->addFacetQuery($fq["d_mes"]);
		}
	}

	$sr->q->setFacet(true);
	$sr->q->setFacetMinCount(1);
	//$sr->q->setFacetLimit(30);

	$sr->q->addFacetField('type')->addFacetField('ticket')->addFacetField('districtstr');

	if ($FacetField!="") $sr->q->addFacetField($FacetField);

	if (!isset($p)){
		$sr->q->addFacetQuery($fq["p_de1a30"]);
		$sr->q->addFacetQuery($fq["p_de30a60"]);
		$sr->q->addFacetQuery($fq["p_mes60"]);
		$sr->q->addFacetQuery($fq["p_nopreu"]);
	}

	$sr->q->setStart($from);
	$sr->q->setRows($rows);
	$sr->SetFields();

	$sr->SetHighlight();
	$keywords.=$sr->ApplyPendingFilters();
	//print_r($sr->q->getFilterQueries());
	//print_r($sr->q->getFacetQueries());
	try {
		$query_response = $sr->client->query($sr->q);
		$response = $query_response->getResponse();
	} catch(SolrException $e){
		//print_r($e);die;
	}

	$facet_data = $response->facet_counts->facet_fields;
	$tmp_queries = get_object_vars($response->facet_counts->facet_queries);

	foreach($tmp_queries as $fqkey=>$fqvalue){
		$newKey=array_search($fqkey,$fq);
		$facet_queries[$newKey]=$fqvalue;
	}
	//$facet_queries = $response->facet_counts->facet_queries;

	parse_str(substr($keywords,1,strlen($keywords)),$SelectedFacets);
	//print_r($facet_data);

	$SelectedFacets["q"]=$q;
	//print_r($SelectedFacets);
	$outString .= "<query>$q</query>";
	if (isset($pt) && $pt!="") $outString .= "<pt>$pt</pt>";
	
	if($strQuery=="*:*")
		$outString .= "<writtenquery></writtenquery>";
		else
		$outString .= "<writtenquery>$strQuery</writtenquery>";

	if (count($response->response->docs)<10 && isset($response->spellcheck) && count(get_object_vars($response->spellcheck->suggestions))>0){

		foreach($response->spellcheck->suggestions as $keySpell=>$objSpell){
			if($keySpell!="collation") foreach($objSpell->suggestion as $txtsuggestion) {
				$outString .= "<suggestions name=\""._VOLIEUDIR."\" href=\"".LK_PAG."".$this->url_encrypt("pg=search&q=".$txtsuggestion)."\">";
				$outString .= $txtsuggestion;
				$outString .= "</suggestions>\n";
			}
		}
		if ((substr_count($q," ")+1)>1) {
			$outString .= "<suggestions name=\""._VOLIEUDIR."\" href=\"".LK_PAG."".$this->url_encrypt("pg=search&q=".$response->spellcheck->suggestions->collation)."\">";
			$outString .= $response->spellcheck->suggestions->collation;
			$outString .= "</suggestions>\n";
		}
	} 

	if (is_array($response->response->docs)){		
		$response = $sr->getHighlightResponse($query_response->getResponse());
		
		//if (!array_key_exists("xout",$this->vars)) {
		$this->includeBlock("gmapsv3");
		
			//$this->includeBlock("gmaps");
		//}

				

		$list = new xmllist;
		$list->SetSelectedFacets($SelectedFacets);
		$outString .= $list->Filters("pg=search&nr=$rows&q=$strQuery$keywords");
		$outString .= "<bleft><leftfilter>".$list->facetlist($facet_data,$facet_queries, "pg=search&q=$strQuery$keywords",$response->response->numFound,$rows, $tr)."</leftfilter></bleft>";
		$outString .= "<queryresponse>";
		$outString .=  "<share href=\"".urlencode($this->url)."\" label=\""._SEARCH." : ".htmlspecialchars($strQuery)."\"/>\n";
		$outString .= $list->xml_list($response->response->docs, $from,$rows,"pg=search","pg=detall&id_doc=",null,"q=$strQuery$keywords", $response->response->numFound,$sr->q->getFields(), $arrsort);
		$outString .= "</queryresponse>";
	} else {
		//$outString .= $list->Filters("pg=search&nr=$rows&q=$q$keywords");
		if ($q!="*:*" && $q!="") $str = " \"".$strQuery."\""; else $str = ".";	
			$outString .= "<noresults>";
			$outString .= "<query>"._NOT_FOUND."$str</query>";
		    $FilterQueries = $sr->q->getFilterQueries();
		if (count($FilterQueries)){		
			
		    foreach($FilterQueries as $fq) {
		    	$tmp = explode(":",$fq);
		    	if(defined("_".strtoupper($tmp[0])))
		    	  $outString .= "<item>".constant("_".strtoupper($tmp[0]))." ".$tmp[1]."</item>";	
		    }
		   
		}
		 $outString .= "</noresults>";
		$outString .= $this->exec_copy(array(array("VALUE"=>"noresultscomments")));
	}
	//print_r($response);
}
//$this->pagetitle = _SEARCH." : ".htmlspecialchars($q);
// set pagetitle
$this->pagetitle = htmlspecialchars(str_replace("*:*",_FIND,$strQuery));
if (isset($d)) $this->pagetitle.= " ".strtolower(constant("_".strtoupper($d)));

$this->html_out .= "<search>$outString</search>";

?>