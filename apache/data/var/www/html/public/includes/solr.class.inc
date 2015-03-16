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
 * Class Entity file
 **/
require_once("includes/entity.class.inc");

class solr extends entity {
	/**
	 *Message after execution of any method.
	 *Se almacenan el mensaje generado por la ejecución de un metodo.
	 *@var string
	 */
	var $txt_error;

	var $options = array
	(
    'hostname' => SOLR_SERVER_HOSTNAME,
    'login'    => SOLR_SERVER_USERNAME,
    'password' => SOLR_SERVER_PASSWORD,
    'port'     => SOLR_SERVER_PORT,
	);

	var $client;
	var $query;
	/**
	 * Constructor
	 *
	 * @return solr
	 */
	function solr(){
		if (extension_loaded('solr')) {
			$this->client = new SolrClient($this->options);
		} else $this->client = false;
	}
	/**
	 * Enter description here...
	 *
	 * @param unknown_type $id
	 */
	function dtlEntitySolr($id,$languages){
		try {
			if ($this->query("select entity_id, entity_type, lastupdatedate from entity where entity_id = $id;")){
				if ($this->num_rows()>0){
					$this->next_record_assoc();
					$entity = $this->Record;

					$entity["keywords"] = $this->getKeywords($id);

					if ($entity["entity_type"]=="AG"){
						$this->query("select ag.actname, ag.tickettype_code ticket, ag.begindate, ag.enddate, ag.placename, ag.equipment_id "
						."from agenda ag "
						."where ag.language_id = 1 and ag.entity_id = $id ;");

						$this->next_record_assoc();
						$entity = array_merge($entity,$this->Record);

						if(array_key_exists("equipment_id",$entity) && $entity["equipment_id"]!="") {
							$this->query("select eq.institutionname, eq.sectionname, eq.sigla from equipment eq where language_id = 1 and entity_id = ".$entity["equipment_id"].";");
							if ($this->num_rows()>0) {
								unset($entity["placename"]);$this->next_record_assoc();
								$entity = array_merge($entity,$this->Record);
							}
							if ($tmp=$this->getAddresses($entity["equipment_id"]))
							$entity = array_merge($entity,$tmp);
							if ($tmp=$this->getPhones($entity["equipment_id"]))
							$entity = array_merge($entity,$tmp);

						} else {
							$entity["institutionname"]=$entity["placename"];
							unset($entity["placename"]);
							if ($ad=$this->getAddresses($id))
							$entity = array_merge($entity,$ad);
						}
						if ($this->isToday($id)) $entity["when1"]="_TODAY";
						if ($this->isTomorrow($id)) $entity["when2"]="_TOMORROW";
						if ($this->isThisNDays($id,7)) $entity["when3"]="_7DAYS";
						if ($this->isThisNDays($id,30)) $entity["when4"]="_MONTH";

					} else {
						$this->query("select institutionname, sectionname, sigla from equipment eq where language_id = 1 and eq.entity_id = $id;");
						if ($this->num_rows()>0) {
							$this->next_record_assoc();
							$entity = array_merge($entity,$this->Record);
							if ($tmp=$this->getAddresses($id))
							$entity = array_merge($entity,$tmp);
							if ($tmp=$this->getPhones($id))
							$entity = array_merge($entity,$tmp);
						}
					} // if entity type

					$this->query("select label as ireflabel, value as irefvalue from internetref where internetref_code = '00040002' and language_id = 1 and entity_id = $id order by position asc limit 1;");
					if ($this->num_rows()>0) $entity = array_merge($entity,$this->select_array_onefield("internetref"));
					// Classificacions
					$tree_id[]=400;
					$tree_id[]=401;
					for($lang=1;$lang<4;$lang++){
						if ($cl=$this->getClassification($id,$tree_id,$lang,"classification_".$lang))
						$entity = array_merge($entity,$cl);
					}
					// End Classifications

					//prices

					$prices = $this->getPrices($id);
					if ($prices[0] > 0)
					$entity["preu_min"]=$prices[0];

					if ($prices[1] > 0)
					$entity["preu_max"]=$prices[1];
					//end prices

					// coordenades
					if (array_key_exists("coordaddressx",$entity) && $entity["coordaddressx"]!="" && $entity["coordaddressx"]!="0"){

						$gmaps=$this->CoordGmap($entity["coordaddressx"], $entity["coordaddressy"]);
						$entity["gmapx"]=$gmaps["gmapx"];
						$entity["gmapy"]=$gmaps["gmapy"];
						$entity["coordaddressx"] = $entity["coordaddressx"]/1000;
						$entity["coordaddressy"] = $entity["coordaddressy"]/1000;

					}
					// end coordenades
						
					//popularity
					$this->query("select popularity from popularity where entity_id = $id;");
					if ($this->num_rows()>0) {
						$this->next_record_assoc();
						$entity["popularity"] = (int)($this->Record["popularity"]*100);
					}
					// end popularity
					//if($tmp=$this->getWords($id))
					// $entity = array_merge($entity,$tmp);

					$this->prepare_fields_to_solr($entity);
					return $entity;
				} else return false;
			} else {$this->txt_error=""._ER_SELET_TBL." "._ENTITY; return false;}
		} catch(Exception $ex){
			echo $id;
			print_r($ex);
			return false;
		}
	}
	/**
	 * Enter description here...
	 *
	 * @param unknown_type $doc
	 */
	public function addDoc($doc){
		$updateResponse = $this->client->addDocument($doc);
		if ($updateResponse){
			//$updateResponse = $updateResponse->getResponse();
			$status = $updateResponse->success();
		} else return false;
		//if ($updateResponse->responseHeader->status==0)
		//	$this->client->commit();
		return $status;
	}
	/**
	 * Enter description here...
	 *
	 * @param unknown_type $id
	 * @param unknown_type $language_id
	 * @return unknown
	 */
	public function getDocToAdd($id,$language_id){

		$entity = $this->dtlEntitySolr($id,$language_id);
		
		if (is_array($entity)){
			$doc = new SolrInputDocument();
			foreach($entity as $key=>$value){
				if (is_array($value)) {
					foreach($value as $subarray) {
						$doc->addField($key, $subarray);
					}
				} else {
					$doc->addField($key, $value);
				}
			}
			$boost = $this->getBoostDoc($id,$entity);
			if ($boost>0) {
				$doc->setBoost($boost);
				$doc->addField("rellevancy",$boost);
			}			
			return $doc;
		}
		return false;
	}
	/**
	 * Enter description here...
	 *
	 * @param unknown_type $day
	 * @param unknown_type $limit
	 * @return unknown
	 */
	public function getBoostDoc($id, $entity){
		//$this->Debug = 1;
		$boost = 0;
		$type = $entity["type"];
		
		if (array_key_exists("popularity",$entity)) $boost = ($entity["popularity"]/100) * 70;
		
		if ($type=='EQ'){
			$this->query("select entity_id from rellevancia_actes_equip where entity_id = $id;");
			if ($this->num_rows() > 0) {
				$boost += 10;
			}
		}
		if ($type=='AG'){
		    $this->query("select entity_id from agrecom where entity_id = $id;");
			if ($this->num_rows() > 0) {
				$boost += 10;
			}
			$this->query("select entity_id from rellevancia_actes where entity_id = $id;");
			if ($this->num_rows() > 0) {
				$boost = 100;
			}
		}
		return (int)round($boost,0);

	}
	/**
	 * Enter description here...
	 * $LatLongs["maxLat"]
	 * $LatLongs["minLat"]
	 * $LatLongs["maxLon"]
	 * $LatLongs["minLon"]
	 *
	 */
	public function getDistance($lat,$lon,$filter,$from,$rows){


		$LatLongs = $this->getLatLongDistance($lat, $lon, 0.300);

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
		$this->query->addField('id')->addField('name')->addField('sectionname');

		$query_response = $this->client->query($this->query);

		return $query_response;
			
	}
	/**
	 * Enter description here...
	 *
	 * @param unknown_type $fields
	 * @return unknown
	 */
	function prepare_fields_to_solr(&$fields){
		//if (array_key_exists("internetref",$fields)) print_r($fields);
		$strBranch = "";
		$strBranchTotal = array();
		reset($fields);
		if (array_key_exists("street",$fields))
		$fields["address"] = $fields["street"]." ".$fields["streetnum_i"];
		$fields["id"] = $fields["entity_id"];
		if ($fields["entity_type"]=="AG") {
			$fields["name"]=$fields["actname"];
		} else {
			if (array_key_exists("institutionname",$fields)) {
			$fields["name"]=$fields["institutionname"];
			unset($fields["institutionname"]);
			} else {
				echo "No institutionname in EQ : ". $fields["entity_id"]."\n";
				$fields["name"]="NONAME";
			}
			
		}
		while (list($key,$value)=each($fields)){
			switch($key){

				case "begindate":
				case "enddate":
					if($fields[$key]!="") {
						$ts = strtotime($fields[$key]);
						$solr_date = date('Y-m-d', $ts) . 'T' . date('H:i:s', $ts) . 'Z';
						$fields[$key]=$solr_date;
					}
					else unset($fields[$key]);
					break;
				case "lastupdatedate":
					if($fields[$key]!="") {
						$ts = strtotime($fields[$key]);
						$solr_date = date('Y-m-d', $ts) . 'T' . date('H:i:s', $ts) . 'Z';
						$fields[$key]=$solr_date;
					}
					else $fields[$key]="1900-01-01T00:00:00Z" ;
					break;
				case "id":

				case "keywords":
				case "equipment_id":
				case "name":
				case "institutionname":
				case "phonenumber":
				case "phonedesc":
				case "address":
				case "type":				
				case "preu_min":
				case "preu_max":
				case "popularity":
				case "type":				
				case "popularity":
				case "when1":
				case "when2":
				case "when3":
				case "when4":	
					break;
				case "ticket":
					if ($fields[$key]=="00060001") unset($fields[$key]);	
					break;				
					//case "words":
				case "entity_type":
					$fields["type"]=$fields[$key];
					unset($fields[$key]);
				break;
   				    //case "internettext":
					//case "warning":
				case "sectionname":
				case "sigla":
					//case "comments":
				case "coordaddressx":
				case "coordaddressy":
				case "gmapx":
				case "gmapy":
					if(strlen($fields[$key])<=1) unset($fields[$key]);
					break;
				case "district":	
                    if($fields[$key]=="") unset($fields[$key]); 
                    else {
                    if (strtolower($fields["city"])!="barcelona") unset($fields[$key]);	
                        elseif(strpos($fields[$key],"0")!== false) unset($fields[$key]);
                    }
					break;
				case "barri":
					if($fields[$key]=="")  unset($fields[$key]); else {
						if (strtolower($fields["city"])!="barcelona") unset($fields[$key]);
					}
					break;
				case "city":
					if($fields[$key]=="")  unset($fields[$key]); else $fields[$key]=ucfirst(strtolower($fields[$key]));
					break;
				case "internetref":
					if (array_key_exists("irefvalue",$fields[$key][0]) && $fields[$key][0]["irefvalue"]!="") $fields[$key] = $fields[$key][0]["irefvalue"];
					else unset($fields[$key]);
					break;
				case "classification_1":
				case "classification_2":
				case "classification_3":

					/*************/
					//$langs = substr($key, strpos($key,"_")+1,1);
					//$strBranch = "";
					foreach($fields[$key] as $branch){
						for($i=0;$i<count($branch);$i++){
							if (!is_array($strBranch)){
								$strBranch["class"][] = $branch[$i]["class"];
								$strBranch["code$i"][] = $branch[$i]["code"];
							} else {
								if ($branch[$i]["class"]!=""){
									$strBranch["class"][] = $branch[$i]["class"];
									$strBranch["code$i"][] = $branch[$i]["code"];
								}
							}
						}
					}
					//foreach($strBranch as $bkey=>$arrayValues) {
					//	$strBranch[$bkey]=array_merge(array_unique($arrayValues));
					//}
					$strBranchTotal=array_merge($strBranchTotal,$strBranch);
					//print_r($strBranch);
					unset($fields[$key]);
					break;
				default;
				unset($fields[$key]);
				break;
			}
		}
		foreach($strBranchTotal as $key=>$array)
		$strBranchTotal[$key]=array_unique($array);
		$fields=array_merge($fields,$strBranchTotal);
		$fields=array_filter($fields);
		//if (array_key_exists("internetref",$fields)) print_r($fields);
		return true;
	}
	/**
	 * If entity is today.
	 * @param id
	 * @return
	 */
	private function isToday($id){
		$today = date('Y-m-d');
		if ($this->query("select entity_id from dayopen where entity_id = $id and dateopen = '$today';")) {
			if ($this->num_rows() > 0)
			return true;
			else
			return false;
		} else return false;
	}
	/**
	 *
	 * @param id
	 * @return
	 */
	private function isTomorrow($id){
		$tomorrow = date('Y-m-d',mktime(0, 0, 0, date("m"), date("d")+1, date("y")));
		if ($this->query("select entity_id from dayopen where entity_id = $id and dateopen = '$tomorrow';")) {
			if ($this->num_rows() > 0)
			return true;
			else
			return false;
		} else
		return false;
	}
	/**
	 *
	 */
	private function isThisNDays($id, $num){
		$today = date('Y-m-d');
		$nextDay = date('Y-m-d',mktime(0, 0, 0, date("m"), date("d")+$num, date("y")));
		if ($this->query("select entity_id from dayopen where entity_id = $id and dateopen >= '$today'"
		." and dateopen <= '$nextDay';")) {
			if ($this->num_rows() > 0)
			return true;
			else
			return false;
		} else
		return false;
	}
	/**
	 *
	 * @param id
	 * @return
	 */
	private function getPrices($id) {
		$result = array(0);
		$preu_min = -1;
		$preu_max = -1;

		$this->query("select preu_min, preu_max from horari where entity_id = $id;");

		if ($this->num_rows() > 0) {

			while ($this->next_record_assoc()) {
				if ($this->Record["preu_min"]!="") {
					if ($preu_min == -1)
					$preu_min = $this->Record["preu_min"];
					if ($this->Record["preu_min"] < $preu_min)
					$preu_min = $this->Record["preu_min"];
				}
				if ($this->Record["preu_max"]!="") {
					if ($preu_max == -1)
					$preu_max = $this->Record["preu_max"];
					if ($this->Record["preu_max"] > $preu_max)
					$preu_max = $this->Record["preu_max"];
				}
			}
		}
		$result[0] = $preu_min;
		$result[1] = $preu_max;
		return $result;
	}
	/**
	 * Enter description here...
	 *
	 * @param unknown_type
	 *            $id
	 */
	private function getPhones($id) {
		$this->query("select phonenumber from phones where phone_code <> '00020027' and entity_id =  $id limit 1;");
		if ($this->num_rows() > 0) {
			$this->next_record_assoc();
			return $this->Record;
		} else
		return false;
	}
	/**
	 * Enter description here...
	 *
	 * @param unknown_type $language_id
	 * @param unknown_type $dateEvent
	 * @return unknown
	 */
	public function getDayEvents($language_id, $dateEvent = null){
		//$this->Debug = 1;
		if ($dateEvent==null) {
			$dateEvent = date("Y-m-d");
			$datePeriode = date("1900-m-d");
		} else {
			$datePeriode = date("1900-m-d",strtotime($dateEvent));
		}
		if ($this->query("select h.*, e.entity_type from entity e "
		."left join agenda ag on ag.entity_id = e.entity_id  and ag.language_id = $language_id "
		."left join horari h on e.entity_id = h.entity_id "
		."where h.entity_id = e.entity_id and e.language_id = $language_id "
		."and ((begindate <= '$dateEvent' and ('$dateEvent' <= enddate or enddate is null)) or (begindate is null)) "
		."and ((periode_inici <= '$datePeriode' and  ('$datePeriode' <= periode_fi or periode_inici >= periode_fi)) or periode_inici is null) "
		."and ag.internetflag = 2 ;")){
			if ($this->num_rows()>0) {
				return true;
			} else return false;
		} else return false;
	}
}
?>