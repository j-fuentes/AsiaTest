<?php
/**
 * Guia de Barcelona - Agenda and Directory
 *
 * This file is part of Guia Barcelona v1.0.0
 * @author Elazos Software Factory
 **/
/**
 *Class index to solr file
 *@author Elazos Software Factory  - May 2004
 **/
/**
 * Class Object file
 **/
require_once("includes/object.class.inc");

class index extends object {
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
	/**
	 * Constructor
	 *
	 * @return solr
	 */
	function index(){
		if (extension_loaded('solr')) {
			$this->client = new SolrClient($this->options);
		} else $this->client = false;
	}
	/**
	 * Gets fields from database to index to solr
	 *
	 * @param integer $id Entity_id
	 * @param integer $languages id Languade : 1=ca, 2=es, 3=en
	 * @return boolean true on success or false if error
	 */
	function dtlEntitySolr($id,$languages){
		try {
			if ($this->query("select entity_id, entity_type, lastupdatedate from entity where entity_id = $id;")){
				if ($this->num_rows()>0){
					$this->next_record_assoc();
					$entity = $this->Record;
					$entity["keywords"] = $this->getKeywords($id);
					if ($entity["entity_type"]=="AG"){
						$this->query("select ag.actname, ag.tickettype_code ticket, ag.begindate, ag.enddate, ag.placename, ag.equipment_id, ag.closeddays "
						."from agenda ag "
						."where ag.language_id = 1 and ag.entity_id = $id ;");
						if ($this->num_rows()>0){
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
	
							if ($entity["closeddays"]!=null && $entity["closeddays"]!=""){
								$entity = array_merge($entity,$this->GetOpenDays($entity["closeddays"]));
							}
							
							$this->query("select dt_open from cronologia where entity_id = $id order by dt_open asc limit 1;");
							if ($this->num_rows()>0) {
								$this->next_record_assoc();
								$entity["proxdate"] = $this->Record["dt_open"];
							} else $entity["proxdate"]="";
							
						} else return false;

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
						$tmp = $this->getTitularitat($id);
						if ($tmp!="") {
							$entity = array_merge($entity,array("code_tit"=>$tmp));
						}
						$tmp = $this->getAdditionalInfo($id);
						if ($tmp!==false) $entity = array_merge($entity,array("code_info"=>$tmp));
						
						$this->query("select value as code_url from interestinfo where entity_id = ".$id." and interestinfo_code = '00100003' order by position asc;");
						if ($this->num_rows()>0) {
							$this->next_record_assoc();
							$entity = array_merge($entity,$this->Record);
						}					
						
					} // if entity type
					$this->query("select label as ireflabel, value as irefvalue from internetref where visual_id = 2 and internetref_code = '00040002' and language_id = 1 and entity_id = $id order by irefvalue, position asc limit 1;");
					if ($this->num_rows()>0) $entity = array_merge($entity,$this->select_array_onefield("internetref"));					
					// Classificacions
					$tree_id=explode(",","400,401,618,619,620");					
					for($lang=1;$lang<4;$lang++){						
						if ($cl=$this->getClassification($id,$tree_id,$lang,"classification_".$lang)){						
							$entity = array_merge($entity,$cl);
						}						
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
					//end popularity
					// Canal
					$tmp=$this->getCanals($id);
					if ($tmp!=null) {
						$entity = array_merge($entity,$tmp);
					}
					$tmp=$this->getProperties($id);
					if ($tmp!=null) {
						$entity = array_merge($entity,$tmp);
					}

					$tmp=$this->getPostWebTarget($id);
					if ($tmp!==false) {
						$entity["code_postwt"] = $tmp;
					}
					
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
	 * Sends doc to solr server to index it
	 *
	 * @param SolrInputDocument $doc
	 */
	public function addDoc($doc){
		$updateResponse = $this->client->addDocument($doc);
		if ($updateResponse){
			$status = $updateResponse->success();
		} else return false;
		return $status;
	}
	/**
	 * Create SolrInputDocument object
	 *
	 * @param integer $id entity_id
	 * @param integer $language_id id Languade : 1=ca, 2=es, 3=en
	 * @return boolean true on success or false if error
	 */
	public function getDocToAdd($id,$language_id){

		
		$entity = $this->dtlEntitySolr($id,$language_id);
		if (is_array($entity)){
				
			if ($recom = $this->GetRecomImage($id)){			
				  
					if (count($recom)>0) {
						$entity["internetref"]=$recom["img"];
						$entity["name"]=$recom["name"];
					}
			}
			
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
			if ($boost==0) $boost=5;
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
				case "proxdate":
				case "begindate":
				case "enddate":
					if($fields[$key]!="") {
						$ts = strtotime($fields[$key]);
						$solr_date = date('Y-m-d', $ts) . 'T' . date('H:i:s', $ts) . 'Z';
						$fields[$key]=$solr_date;
					}
					else {
						if ($key=="begindate") $fields[$key]="1900-01-01T00:00:00Z";
						if ($key=="enddate" || $key=="proxdate") $fields[$key]="2100-01-01T00:00:00Z";						
					}
					break;
				case "lastupdatedate":
					if($fields[$key]!="") {
						$ts = strtotime($fields[$key]);
						$solr_date = date('Y-m-d', $ts) . 'T' . date('H:i:s', $ts) . 'Z';
						$fields[$key]=$solr_date;
					}
					else $fields[$key]="1900-01-01T00:00:00Z" ;
					break;
				case "streetnum_i":
					if($fields[$key]!="") {
						$fields["streetnum"] = $fields[$key];
						unset($fields[$key]);
					}
					break;
				case "id":
				case "streetnum":
				case "keywords":
				case "equipment_id":
				case "name":
				case "phonenumber":
				case "phonedesc":
				case "address":
				case "type":
				case "preu_min":
				case "preu_max":
				case "popularity":
				case "type":
				case "popularity":
				case "d1":
				case "d2":
				case "d3":
				case "d4":
				case "d5":
				case "d6":
				case "d7":
				case "code_canal":
				case "code_tit":
				case "code_info":
				case "code_prop":
			    case "code_comarca":
			    case "code_postwt":
					break;
				case "code_url":
					if ($fields[$key]!="") $fields[$key] =  str_ireplace("http://", "", $value);
					else unset($fields[$key]);
					break;
				case "institutionname":
					if (substr($value,0,1)=="*") $fields[$key]=substr($value,1);
					break;
				case "ticket":
					if ($fields[$key]=="00060001") unset($fields[$key]);
					break;
				case "entity_type":
					$fields["type"]=$fields[$key];
					unset($fields[$key]);
					break;
				case "sectionname":
				case "sigla":
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
						elseif (strtolower($fields[$key])=="les corts") $fields[$key]= "Les Corts";  
					}
					break;
				case "city":
					if($fields[$key]=="")  unset($fields[$key]); else $fields[$key]=ucfirst(strtolower($fields[$key]));
					break;
				case "internetref":
					//if (array_key_exists("irefvalue",$fields[$key][0]) && $fields[$key][0]["irefvalue"]!="") $fields[$key] = $fields[$key][0]["irefvalue"];
					//else $fields[$key]=_URL_SERVER_IMG.$fields["id"];//unset($fields[$key]);
					$fields[$key]=_URL_SERVER_IMG.$fields["id"];
					break;
				case "classification_1":
				case "classification_2":
				case "classification_3":
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
					$strBranchTotal=array_merge($strBranchTotal,$strBranch);
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
		return true;
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
		$this->query("select phonenumber from phones where phone_code <> '00020027' and entity_id =  $id order by position asc limit 1;");
		if ($this->num_rows() > 0) {
			$this->next_record_assoc();
			return $this->Record;
		} else
		return false;
	}
	/**
	 * Enter description here...
	 *
	 * @param unknown_type $id
	 * @return unknown
	 */
	private function getCanals($id) {
		$this->query("select canal_id from canals where entity_id =  $id;");
		if ($this->num_rows() > 0) {
			while($this->next_record_assoc())
				$result["code_canal"][]=$this->Record["canal_id"];
			return $result;
		} else return null;
	}
	/**
	 * Devuelve los code de los arboles a los que pertenece el entity
	 * @param unknown_type $id
	 */
	private function getProperties($id) {
		$this->query("select code from properties where entity_id =  $id;");
		if ($this->num_rows() > 0) {
			while($this->next_record_assoc())
				$result["code_prop"][]=$this->Record["code"];
			return $result;
		} else return null;
	}
	/**
	 * Get all open days from string 0000011
	 *
	 * @param unknown_type $strBitWeekDays
	 * @return unknown
	 */
	private function GetOpenDays($strBitWeekDays){
		for($i=0;$i<7;$i++){
			if (!((boolean)((int)substr($strBitWeekDays,$i,1))))
			$d["d".($i+1)] = "true";
			else
			$d["d".($i+1)] = "false";
		}
		return $d;
	}
	/**
	 * Se lanza una consulta a SOLR que sirve para crear el indice del Spellcheck
	 *
	 */
	public function BuildSpellIndex(){
		echo "BuildSpellIndex...\n";
		$this->q = new SolrQuery();
		$this->q->setQuery('*:*');
		$this->q->addParam('spellcheck', "true");
		$this->q->addParam('spellcheck.build', "true"); // Sirve para crear el indice del Spellcheck
		$this->q->addParam('spellcheck.reload', "true");
		$this->q->setStart(0);
		$this->q->setRows(1);
		$resp = $this->client->query($this->q)->getResponse();
			
		echo "End BuildSpellIndex.\n";
	}
	/**
	 * Retorna la imagen si el Entity es una recomendada.
	 *
	 * @param unknown_type $entity_id
	 * @return unknown
	 */
	public function GetRecomImage($entity_id){
		$result = array();
				
		if ($this->query("select imatgeCos, titol from agrecom ag, agrecomentity_id id, agrecomtxt txt where id.recom_id = txt.recom_id  and id.recom_id = ag.recom_id and id.entity_id = $entity_id and txt.language_id = "._LANGUAGE." ;")){
				if ($this->num_rows()>0){
					$this->next_record_assoc();
					$result["img"] = $this->Record["imatgeCos"];
					$result["name"] = $this->Record["titol"];
				}
		}		
		return $result; 
	}
	/**
	 * Delete all entity_id from all tables that have deletedate.
	 * This function prevent having data not deleted in ASIA.
	 */
	public function deleteID2delete($OnlyIndex = false){
		if (!$OnlyIndex) {
			$TableList = array("AGENDA","EQUIPMENT","ADDRESSES","RELLEVANCIA_ACTES","RELLEVANCIA_ACTES_EQUIP",
					"CLASSIFICATION","NOM_ACTE","ALTRES_ADDRESSES_ACTE","INTERESTINFO","INTERNETREF","PHONES","VISUALITZACIONS_INFOEXTERNA",
					"TIMETABLE","RELATIONS","ENTITYVARIANTS","PROPERTIES","REL_ENTITY_VARIABLES","KEYWORDS","HORARI",
					"ATENCIO_EQ");
			foreach($TableList as $TableName){
				$TableName = strtolower($TableName);
				if ($TableName == "relations"){
					$this->query("delete a from $TableName a left join entity e on e.entity_id = a.target_id where e.deletedate <= date(now())");
					$this->query("delete a from $TableName a left join entity e on e.entity_id = a.source_id where e.deletedate <= date(now())");
				} else {
					$this->query("delete a from $TableName a left join entity e on e.entity_id = a.entity_id where e.deletedate <= date(now())");
				}
			}
			$this->query("insert into tmp_import (entity_id, action, processed) select entity_id, 'D',0  from entity where deletedate <= date(now()) on duplicate key UPDATE action = 'D', processed = 0;");
			$this->query("delete from entity where deletedate <= date(now());");
		} else {
			$this->query("insert into tmp_import (entity_id, action, processed) select entity_id, 'D',0  from entity where deletedate <= date(now()) on duplicate key UPDATE action = 'D', processed = 0;");
		}
	}

}
?>