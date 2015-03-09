<?php
/**
 * Guia de Barcelona - Agenda and Directory
 *
 * This file is part of Guia Barcelona v1.0.0
 * @author Elazos Software Factory
 **/
/**
 *Class entity file
 *@author Elazos Software Factory  - May 2004
 **/
/**
 * Class search file
 **/
//require_once("includes/object.class.inc");

class search {
	/**
	 * Message after execution of any method.
	 * Se almacenan el mensaje generado por la ejecución de un metodo.
	 * @var string
	 */
	var $txt_error;
	/**
	 * Solr connection options : host, login, pass and port
	 *
	 * @var array Solr connection options
	 */
	var $options = array
	(
    'hostname' => SOLR_SERVER_HOSTNAME,
    'login'    => SOLR_SERVER_USERNAME,
    'password' => SOLR_SERVER_PASSWORD,
    'port'     => SOLR_SERVER_PORT,
	);

	var $client;
	var $q;
	var $fq;
	private $preFilterWords = array("d_avui" => array("avui","today","hoy"),
	                      "d_dema" => array("demà","dema","tomorrow","mañana"),
	                      "d_cap" => array("cap de setmana","weekend","fin de semana"),
	                      "ticket_00060002" => array("gratuit","gratuits","gratuites","gratis","gratuitos","gratuito","gratuita","gratuitas","free"));

	var $pendingFilters = array();
	/**
	 * Constructor
	 *
	 * @return solr
	 */
	function search(){
		if (extension_loaded('solr')) {
			$this->client = new SolrClient($this->options);
			$this->q = new SolrQuery();
		} else {
			$this->client = false;
			$this->q = false;
		}
	}
	function queryReset(){
		$this->q = new SolrQuery();
	}
	/**
	 * Enter description here...
	 * $LatLongs["maxLat"]
	 * $LatLongs["minLat"]
	 * $LatLongs["maxLon"]
	 * $LatLongs["minLon"]
	 *
	 */
	public function getDistance($lat,$lon,$filter,$from,$rows,$meters = 300){
		
		$meters = $meters/1000;
		
		$LatLongs = $this->getLatLongDistance($lat, $lon, $meters);
		$maxLat = $LatLongs["maxLat"];
		$minLat = $LatLongs["minLat"];
		$maxLon = $LatLongs["maxLon"];
		$minLon = $LatLongs["minLon"];
		$this->query = new SolrQuery();
		$this->query->setQuery("*:*");
		$this->query->addFilterQuery("gmapx:[$minLat TO $maxLat]");
		$this->query->addFilterQuery("gmapy:[$minLon TO $maxLon]");
		foreach($filter as $flt) $this->query->addFilterQuery($flt);
		$this->query->setFacet(true);
		$this->query->addFacetField('class0_'._LANGUAGE)->setFacetMinCount(1);
		$this->query->setStart($from);
		$this->query->setRows($rows);
		$this->query->addField('id')->addField('name')->addField('sectionname')->addField('address')->addField('district')->addField('phonenumber');
		$query_response = $this->client->query($this->query);
		return $query_response;
	}
	/**
	 * Enter description here...
	 *
	 * @param unknown_type $filter
	 * @param unknown_type $from
	 * @param unknown_type $rows
	 * @return unknown
	 */
	public function getRelated($filter,$from,$rows){
		$this->query = new SolrQuery();
		$this->query->setQuery("*:*");
		foreach($filter as $flt) $this->query->addFilterQuery($flt);
		$this->query->setFacet(false);
		$this->query->setStart($from);
		$this->query->setRows($rows);
		//$this->query->addField('id')->addField('name')->addField('sectionname');
		$query_response = $this->client->query($this->query);
		return $query_response;
	}
	/**
	 * Enter description here...
	 *
	 * @param unknown_type $lat
	 * @param unknown_type $lon
	 * @param unknown_type $rad Radius of the circle or distance in KM
	 * @return unknown
	 */
	function getLatLongDistance($lat, $lon, $rad){

		$R=6371; // Earth Km

		// first-cut bounding box (in degrees)
		$maxLat = $lat + rad2deg($rad/$R);
		$minLat = $lat - rad2deg($rad/$R);
		// compensate for degrees longitude getting smaller with increasing latitude
		$maxLon = $lon + rad2deg($rad/$R/cos(deg2rad($lat)));
		$minLon = $lon - rad2deg($rad/$R/cos(deg2rad($lat)));

		$result["maxLat"]=$maxLat;
		$result["minLat"]=$minLat;
		$result["maxLon"]=$maxLon;
		$result["minLon"]=$minLon;
		return $result;
	}
	/**
	 * Enter description here...
	 *
	 */
	public function SetHighlight(){
		$this->q->setHighlight(true);
		$this->q->setHighlightHighlightMultiTerm(true);
		$this->q->setHighlightUsePhraseHighlighter(true);
		$this->q->setHighlightMaxAnalyzedChars(10000);
		$this->q->setHighlightFragsize(5000);
		$this->q->addHighlightField('name');
		$this->q->addHighlightField('sectionname');
		$this->q->addHighlightField('institutionname');
		$this->q->addHighlightField('district');
		$this->q->addHighlightField('sigla');
		$this->q->addHighlightField('address');
		$this->q->setHighlightSimplePre('<b>');
		$this->q->setHighlightSimplePost('</b>');
	}
	/**
	 * Enter description here...
	 *
	 * @param unknown_type $response
	 * @return unknown
	 */
	public function getHighlightResponse($response){
		// highlight
		foreach($response->highlighting as $hKey=>$hObject){
			foreach($response->response->docs as $kdoc=>$doc){
				if ($hKey==$doc["id"]){
					foreach ($hObject as $kfield=>$vfield){
						if (count($response->response->docs[$kdoc][$kfield])>1)
						$response->response->docs[$kdoc][$kfield] = array_merge($vfield,$response->response->docs[$kdoc][$kfield]);
						else {
							$response->response->docs[$kdoc][$kfield]=$vfield[0];
						}
					}
					break;
				}
			}
		}
		return $response;
	}
	/**
	 * Set fields to return on a search
	 *
	 */
	public function SetFields(){
		$this->q->addField('id')->addField('internetref')->addField('name')->addField('sectionname')->addField('sigla')->addField('institutionname')->addField('address')->addField('district')->addField('city')->addField('type')->addField('enddate')->addField('begindate')->addField('phonenumber')->addField('gmapx')->addField('gmapy')->addField('equipment_id')->addField('code_url');
	}
	/**
	 * Enter description here...
	 *
	 * @param unknown_type $q
	 */
	public function preQueryFilter($q){
		$intResultingQuery = array();
		$StrToRemove = array();
		//return $q;
		if (count($arWords = explode(" ",$q))>1){
			//print_r($arWords);
			foreach($this->preFilterWords as $key=>$words){
				foreach($words as $word){
					if (count(explode(" ",$word))>1){
					 if (stristr($q,$word)!==FALSE) {
					 	$this->pendingFilters[]=$key;
					 	$StrToRemove[]=$word;
						}
							
					} else {
						foreach($arWords as $pos=>$qWord){
							if (stristr($qWord,$word)!==FALSE) {
								$this->pendingFilters[]=$key;
								$intResultingQuery[]=(int)$pos;
							}
						}
					}

				}
			}
			//print_r($arWords);
			//print_r($intResultingQuery);
			$strResultingQuery = "";
			foreach($arWords as $pos=>$word)  if(array_search($pos,$intResultingQuery)===FALSE) {
				$strResultingQuery.=" ".$word;
			}
			foreach($StrToRemove as $word) $strResultingQuery = str_replace($word,"",$strResultingQuery);
			return trim($strResultingQuery);
		} else return $q;
	}
	/**
	 * Enter description here...
	 *
	 */
	public function ApplyPendingFilters(){
		//print_r($this->fq);
		//print_r($this->pendingFilters);
		$keywords ="";
		foreach($this->pendingFilters as $strFilter){
			$vars = explode("_",$strFilter);
			$keywords.="&".$vars[0]."=".$vars[1];
			if(array_key_exists($strFilter,$this->fq)) $this->q->addFilterQuery($this->fq[$strFilter]);
			else $this->q->addFilterQuery($vars[0].":\"".$vars[1]."\"");

		}
		//echo $keywords;
		return $keywords;
	}

	/**
	 * Tiene la definición de las queries facets(filtros).
	 * Hace los intervalos de precios y segun el dia de la semana hace los intervalos de fechas
	 * para que salgan los filtros de Hoy, Mañana, 7 dias, 30 dias
	 *
	 * @return array Intervals queries facets(filtros)
	 */
	public function GetFacetQueriesDefinition(){

		// intervalos para FacetQueries
		$fq["p_de1a30"]="preu_min:[1 TO 30] OR preu_max:[1 TO 30]";
		$fq["p_de30a60"]="preu_min:[30 TO 60] OR preu_max:[30 TO 60]";
		$fq["p_mes60"]="preu_min:[60 TO *] OR preu_max:[60 TO *]";
		$fq["p_nopreu"]="-preu_min:[* TO *] AND -preu_max:[* TO *] AND ticket:00060003";

		$dayweek = date("w");
		if ($dayweek==0) $dayweek = 7;

		$fq["d_avui"] = "d$dayweek:true AND (begindate:[* TO NOW] AND enddate:[NOW TO *])";
		if ($dayweek==7) $dema=1; else $dema=($dayweek+1);
		$fq["d_dema"] = "d".($dema).":true AND (begindate:[* TO NOW+1DAYS] AND enddate:[NOW+1DAYS TO *])";

		if ($dayweek!=6 && $dayweek!= 7) {
			$days_to_weekend = 7 - $dayweek;
			$fq["d_cap"] = "(d6:true AND begindate:[* TO NOW+".($days_to_weekend-1)."DAYS] AND enddate:[NOW+".($days_to_weekend-1)."DAYS TO *])"
			." OR (d7:true AND begindate:[* TO NOW+".($days_to_weekend)."DAYS] AND enddate:[NOW+".($days_to_weekend-1)."DAYS TO *])";

		}

		$fq["d_caps"] = "(d6:true AND begindate:[* TO NOW]) OR (d7:true AND begindate:[* TO NOW])";
		$fq["d_setmana"] = "begindate:[* TO NOW+7DAYS] AND enddate:[NOW+1DAYS TO *]";
		$fq["d_mes"] = "begindate:[* TO NOW+30DAYS] AND enddate:[NOW+1DAYS TO *]";

		$this->fq = $fq;
		return $fq;
	}
	/**
	 * Set query sort
	 *
	 * @param unknown_type $sort
	 * @return unknown
	 */
	public function SetSort($sort,&$keywords){
		$arrsort = explode(",",$sort);
		if (count($arrsort)==2) {
			if(strtolower($arrsort[1])=="asc")
			$this->q->addSortField ($arrsort[0],SolrQuery::ORDER_ASC);
			if(strtolower($arrsort[1])=="desc")
			$this->q->addSortField ($arrsort[0],SolrQuery::ORDER_DESC);
			$keywords.="&sort=".$arrsort[0].",".$arrsort[1];
			$this->q->addField($arrsort[0]);
		} else $arrsort[0]="";
		return $arrsort;
	}
	/**
	 * Enter description here...
	 *
	 * @param unknown_type $row
	 */
	public function prepareRow($row){
			
		if (array_key_exists("type",$row) && $row["type"]=='AG' && !array_key_exists("enddate",$row)) $row["enddate"]="2100-12-31 00:00:00";
		if (array_key_exists("begindate",$row) && $row["begindate"]==$row["enddate"]) {
			$date = new DateTime(substr($row["begindate"],0,10));
			$row["date"] = $date->format(_DATEFORMAT);
			unset($row["begindate"]);
			unset($row["enddate"]);
		}
			
		if(array_key_exists("type",$row) && $row["type"]=='AG') {
			if (array_key_exists("sectionname",$row)) {
				$row["institutionname"] =  strip_tags($row["sectionname"])." - ". strip_tags($row["institutionname"]);
				unset($row["sectionname"]);
			}
		}

		foreach($row as $fieldName=>$fieldValue){
			switch($fieldName){
				case "institutionname":
					$row[$fieldName] = str_replace("*","",$fieldValue);
					break;
				case "enddate":
					if (substr($fieldValue,0,4)=="2100") {
						unset($row[$fieldName]);
						unset($row["begindate"]);
						$row["date"]=_ACTEPERMANENT;
					} else {
						$date = new DateTime(substr($fieldValue,0,10));
						$row[$fieldName] = $date->format(_DATEFORMAT);
					}
					break;
				case "begindate":
					if (substr($fieldValue,0,4)=="1900") unset($row[$fieldName]);
					else {
						$date = new DateTime(substr($fieldValue,0,10));
						$row[$fieldName] = $date->format(_DATEFORMAT);
					}
					break;
				case "proxdate":
					if ($fieldValue!="") {
						if (array_key_exists("debug",$_GET)) echo $fieldValue."<br/>";
						//$date = new DateTime(substr($fieldValue,0,10));
						$date = new DateTime($fieldValue);
						$row[$fieldName] = $date->format(_DATEFORMAT);
						$row["proxhour"] = $date->format("H:i");
					} 
					break;
				case "type":
					$row[$fieldName] = constant("_".strtoupper($fieldValue));
					$row["tp"] = $fieldValue;
					break;
				case "titol":
					$row["name"]=$row["titol"];
					break;
				case "code_tit":
					$row["code_tit"]=$row["code_tit"][0];
					break;
				case "code_url":
					$row["code_url"]=$row["code_url"][0];
					break;
				case "code_postwt":
					$row["code_postwt"]=$row["code_postwt"];
					break;
				default:
					break;

			}


		}
		return $row;
	}
	/**
	 * Enter description here...
	 *
	 * @param unknown_type $gmapx
	 * @param unknown_type $gmapy
	 * @param unknown_type $filters
	 * @return unknown
	 */
	public function CloseTo($gmapx,$gmapy,$filters){
		if ($this->client) {
			$outString = "";
			$from = 0;
			$rows = 5;
			require_once("includes/lists/xmlist.php");
			$list = new xmllist;
			foreach($filters as $fltItem){
				$query_response = $this->getDistance($gmapx,$gmapy,$fltItem["filters"],$from,$rows);
				$response = $query_response->getResponse();
				if (is_array($response->response->docs)){
					$outString .= "<".$fltItem["node"]." label=\"".$fltItem["label"]."\">";
					$outString .= $list->xml_list($response->response->docs,0,$rows,"","pg=detall&id_doc=",null,null, $rows,$this->query->getFields(), null);
					$outString .= "</".$fltItem["node"].">";
				}
			}
			return $outString;
		} else return "";
	}
}
?>