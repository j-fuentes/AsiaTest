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
 * Class Object file
 **/
require_once("includes/object.class.inc");
/**
 *Handles entitys - using table prefix_entitys.
 *Gestiona clientes con la tabla prefix_entitys.
 *@author Elazos Software Factory
 *@version 1.0
 *@package BusObj
 */
class entity extends object {
	/**
	 * Message after execution of any method.
	 * Se almacenan el mensaje generado por la ejecuci�n de un metodo.
	 * @var string
	 */
	var $txt_error;

	/**
	 * Get entity details from the table prefix_entitys
	 * @author Elazos Software Factory
	 * @access public
	 * @param integer entity id
	 * @return boolean
	 */
	function dtl_entity($id, $language_id, $tree_id = array(400,401)){
		
		try {
			if ($this->query("select entity_id, entity_type, lastupdatedate from entity where entity_id = $id;")){
				if ($this->num_rows()>0){
					$this->next_record_assoc();
					$entity = $this->Record;
					if ($entity["entity_type"]=="AG"){
						// si es AGENDA
						$this->query("select ag.actname, ag.tickettype_code, ag.acttype, ag.begindate, ag.enddate, ag.placename, ag.warning, ag.equipment_id, ag.status_id, ag.comments "
						."from agenda ag "
						."where ag.language_id = $language_id and ag.entity_id = $id ;");

						$this->next_record_assoc();
						$entity = array_merge($entity,$this->Record);

						if(array_key_exists("equipment_id",$entity) && $entity["equipment_id"]!="") {
							$this->query("select eq.entity_id institution_id, eq.institutionname, eq.sectionname, eq.sigla from equipment eq where language_id = $language_id and entity_id = ".$entity["equipment_id"].";");
							if ($this->num_rows()>0) {unset($entity["placename"]);$this->next_record_assoc();$entity = array_merge($entity,$this->Record);}
							if ($tmp=$this->getAddresses($entity["equipment_id"]))
							$entity = array_merge($entity,$tmp);
							$this->query("select phone_code, phonenumber, description as phonedesc from phones where language_id = $language_id and entity_id = ".$entity["equipment_id"]." order by position asc;");
							if ($this->num_rows()>0) $entity = array_merge($entity,$this->select_array_onefield("phones"));
							$this->query("select value as interinfo, interestinfo_code as intercode from interestinfo where entity_id = $id order by position asc;");
							if ($this->num_rows()>0) 
								$entity = array_merge($entity,$this->select_array_onefield("interestinfo"));
							else {
								$this->query("select value as interinfo, interestinfo_code as intercode from interestinfo where entity_id = ".$entity["equipment_id"]." order by position asc;");
								if ($this->num_rows()>0) $entity = array_merge($entity,$this->select_array_onefield("interestinfo"));
							}
						} else {
							$entity["institutionname"]=$entity["placename"];
							unset($entity["placename"]);
							if ($ad=$this->getAddresses($id))
							$entity = array_merge($entity,$ad);
							$this->query("select phone_code, phonenumber, description as phonedesc from phones where language_id = $language_id and entity_id = $id order by position asc;");
							if ($this->num_rows()>0) $entity = array_merge($entity,$this->select_array_onefield("phones"));
							$this->query("select value as interinfo, interestinfo_code as intercode from interestinfo where entity_id = $id order by position asc;");
							if ($this->num_rows()>0) $entity = array_merge($entity,$this->select_array_onefield("interestinfo"));
						}
						if ($tmp=$this->getHorari($id))
						$entity = array_merge($entity,$tmp);
						elseif ($tmp=$this->getHorari($entity["equipment_id"]))
						$entity = array_merge($entity,$tmp);
						//votes
						$this->query("select counter as votes from entityvotes eq where eq.entity_id = $id;");
						if ($this->num_rows()>0) {
							$this->next_record_assoc();
							$entity["votes"] = $this->Record["votes"];
						}
						// end votes


					} else {
						// si es EQUIPMENT, no AGENDA
						$this->query("select institutionname, sectionname, sigla, internettext, comments from equipment eq where language_id = $language_id and eq.entity_id = $id;");
						$this->next_record_assoc();
						$entity = array_merge($entity,$this->Record);
						if ($tmp=$this->getAddresses($id))
						$entity = array_merge($entity,$tmp);
						if ($tmp=$this->getHorari($id))
						$entity = array_merge($entity,$tmp);
						$this->query("select phone_code, phonenumber, description as phonedesc from phones where language_id = $language_id and entity_id = $id order by position;");
						if ($this->num_rows()>0) $entity = array_merge($entity,$this->select_array_onefield("phones"));
						$this->query("select value as interinfo, interestinfo_code as intercode from interestinfo where entity_id = $id;");
						if ($this->num_rows()>0) $entity = array_merge($entity,$this->select_array_onefield("interestinfo"));
						// accessibilitat
						$this->query("select code from properties where code = '0010501001' and entity_id = $id;");
						if ($this->num_rows()>0) {
							$this->next_record_assoc();						
							$entity = array_merge($entity, array("accessibility"=>$this->Record["code"]));
						}
						
						$tmp = $this->getTitularitat($id);
						if ($tmp!="") {
							$entity["titularitat"] = $tmp;
						}						
						$tmp = $this->getAdditionalInfo($id);
						if ($tmp!==false) {
							$entity = array_merge($entity,array("code_info"=>$tmp));
						}
						$tmp = $this->getServeis($id, _LANGUAGE);
						if ($tmp!==false) {														
							$entity = array_merge($entity,array("serveis"=>$tmp));
						}
						$this->query("select atencio from atencio_eq where entity_id = $id;");
						if ($this->num_rows()>0) {
							$this->next_record_assoc();
							$entity = array_merge($entity, array("atencio_eq"=>$this->Record["atencio"]));
						}						

					} // if entity type
					$this->query("select distinct label as ireflabel, value as irefvalue from internetref where visual_id = 2 and internetref_code = '00040002' and language_id = $language_id and entity_id = $id order by irefvalue, position asc limit 1;");
					if ($this->num_rows()>0) $entity = array_merge($entity,$this->select_array_onefield("internetref"));
					// Classificacions
					//$tree_id[]=400;
					//$tree_id[]=401;
					//$tree_id[]=105;
					//$tree_id[]=119;
					//$tree_id = false;
					if ($cl=$this->getClassification($id,$tree_id,$language_id,"classification"))
					$entity = array_merge($entity,$cl);
					// End Classifications
					// Relations
					$this->query("select distinct eq.entity_id, reltype, tp.direct, sectionname, institutionname, sigla, rel.comments from relations rel, reltypes tp, equipment eq where rel.reltype = tp.reltype_id and rel.target_id = eq.entity_id and eq.language_id = $language_id and rel.language_id = $language_id and tp.language_id = $language_id and rel.source_id = $id;");
					if ($this->num_rows()>0) {							
						$entity = array_merge($entity,$this->select_array_onefield("relations"));
					}
					//End Relations

					$this->query("select * from timetable where language_id = $language_id and entity_id = $id;");
					if ($this->num_rows()>0) {
						$this->next_record_assoc();$entity = array_merge($entity,array("timetable"=>$this->Record));
					}

					if (array_key_exists("coordaddressx",$entity) && $entity["coordaddressx"]!="" && $entity["coordaddressx"]!="0"){

						$gmaps=$this->CoordGmap($entity["coordaddressx"], $entity["coordaddressy"]);
						$entity["gmapx"]=$gmaps["gmapx"];
						$entity["gmapy"]=$gmaps["gmapy"];
						$entity["coordaddressx"] = $entity["coordaddressx"]/1000;
						$entity["coordaddressy"] = $entity["coordaddressy"]/1000;

					}
					//if($tmp=$this->getWords($id))
					// $entity = array_merge($entity,$tmp)						
					return array_filter($entity);;
				} else return false;
			} else {$this->txt_error=""._ER_SELET_TBL." "._ENTITY; return false;}
		} catch(Exception $ex){
			//echo $id;
			//print_r($ex);
			return false;
		}
	}
	/**
	 * Enter description here...
	 *
	 * @param unknown_type $id
	 */
	function getHorari($id){
		$this->query("select periode_inici, periode_fi, dies, festius, vigilies, relatives, dia_exacte_inclos, dia_exacte_exclos, DATE_FORMAT(hora_inici, '%H:%i:%s') hora_inici, DATE_FORMAT(hora_fi, '%H:%i:%s') hora_fi, preu_min, preu_max from horari where entity_id = $id;");
		if ($this->num_rows()>0) {
			$preu_min = false;
			$preu_max = 0;
			while($this->next_record_assoc()){
				if (array_key_exists("preu_min",$this->Record) && $this->Record["preu_min"]!=""){
					if  ($preu_min==false) $preu_min = $this->Record["preu_min"];
					if ($this->Record["preu_min"] < $preu_min ) $preu_min = $this->Record["preu_min"];
				}
				if (array_key_exists("preu_max",$this->Record) && $this->Record["preu_max"]!=""){
					if  ($preu_max==false) $preu_max = $this->Record["preu_max"];
					if ($this->Record["preu_max"] < $preu_max ) $preu_max = $this->Record["preu_max"];
				}
				if ($preu_min) $result["preu_min"]=$preu_min;
				if ($preu_max>0) $result["preu_max"]=$preu_max;
				$result["horari"][] = array_filter($this->Record,'strlen');
			}

			return $result;
		} else return false;
	}

	/**
	 * Checks entity fields before any add or update to the table prefix_entity
	 * @author Elazos Software Factory
	 * @access private
	 * @param array Assoc array[fieldname]=value
	 * @return boolean
	 */
	function prepare_fields_to_show(&$fields){
		
       
		if ($fields["entity_type"]=="AG") {
			$fields["type"]=_AG;			
			$fields["name"]= $fields["actname"];			
			if ($fields["acttype"]!="E"){
				if ($fields["begindate"]==$fields["enddate"]) {
				    $fields["date"]=$fields["begindate"];
					unset($fields["enddate"]);
					unset($fields["begindate"]);
				} 
				
			} else {
				$fields["date"] = _PERMANENT;
				unset($fields["enddate"]);
				unset($fields["begindate"]);
			}
			if (!array_key_exists("institutionname",$fields))
			    $fields["institutionname"]=_NODISPONIBLE;

		} else {
			$fields["type"]=_EQ;
			$fields["name"]=$fields["institutionname"];
			unset($fields["institutionname"]);
		}

       
		reset($fields);
	   
		while (list($key,$value)=each($fields)){
			switch($key){
				case "internetref":					
					foreach($fields[$key] as $itemK=>$item){
						//if(!array_key_exists("irefvalue",$item)) $fields[$key][$itemK]["irefvalue"]=_URL_SERVER_IMG.$fields["entity_id"];//unset($fields[$key][$itemK]);
						$fields[$key][$itemK]["irefvalue"]=_URL_SERVER_IMG.$fields["entity_id"];
					}
					break;
				case "sectionname":
					if ($fields[$key]=="#")  unset($fields[$key]);
					break;
				case "date":	
				if ($fields[$key]!=_PERMANENT) $fields[$key] = date('d/m/Y',strtotime($fields[$key]));
				break;
				case "begindate":
				case "enddate":
					if ($fields[$key]!="") $fields[$key] = date('d/m/Y',strtotime($fields[$key]));
					else unset($fields[$key]);
					break;
				case "status_id":					
					if($fields[$key]!="3") {
						$fields["status"][0]["code"]=$value;
						$fields["status"][0]["name"]=constant("_AG_STATUS_ID_".strtoupper($value));						
						unset($fields[$key]);
					}
					 else
					 	unset($fields[$key]);
					break;	
				case "status";	
				case "name";
				case "acttype":
					//case "horari":
				case "entity_id":				
				case "institution_id":
				case "sigla":
				case "actname":
				case "language_id":
				case "period":
				case "days":
				case "hours":
				case "price":
				case "remarks":
				case "street":
				case "stair":
				case "floor":
				case "door":
				case "postalcode":				
				case "classification":
				case "relations":
				case "entity_type":
				case "timetable":
				case "tipus":
				case "type":
				case "votes":
				case "serveis":				
					break;
				case "streetnum_i":
					$fields[$key]=$fields["streetnum_s"];
					break;
				case "titularitat":	
					if($fields[$key]!="") {					    
						$fields[$key]=constant("_N".strtoupper($fields[$key]));					
					} else unset($fields[$key]);
					break;
				case "institutionname":	
				    if (substr($value,0,1)=="*") $fields[$key]=substr($value,1);
				    break;
				case "district":
					if($fields[$key]=="") unset($fields[$key]);
					else {
						if(strpos($fields[$key],"0")!== false) unset($fields[$key]);
					}
					break;
				case "barri":
					if($fields[$key]=="")  unset($fields[$key]);
					break;
				case "city":
					if($fields[$key]=="")  unset($fields[$key]); else $fields[$key]=ucfirst(strtolower($fields[$key]));
					break;
				case "tickettype_code":
				case "accessibility":	
					if($fields[$key]!="") {
						$fields[$key]=constant("_".strtoupper($value));
					} else unset($fields[$key]);
					break;
				case "internettext":
				case "gmapx":
				case "gmapy":
					if(strlen($fields[$key])<=1) unset($fields[$key]);
					break;
				case "interestinfo":
					foreach($fields[$key] as $itemK=>$item){
						if(stripos($item["interinfo"],"http://")!==FALSE) $fields[$key][$itemK]["interinfo"] = str_ireplace("http://", "", $item["interinfo"]);
						if ($item["intercode"]!="") $fields[$key][$itemK]["label"]=constant("_".strtoupper($item["intercode"]));
					}
					break;
				case "code_info":					
					foreach($fields[$key] as $itemK=>$item){						
						if ($item!="") {							
							$fields["serveis"][$itemK]["label"]=constant("_".strtoupper($item));
							$fields["serveis"][$itemK]["code"]=$item;
						} 
					}
					unset($fields[$key]);	
					break;	
				case "comments":
				case "warning":
				case "atencio_eq":
					if ($fields[$key]!="" && $fields[$key][0]=="1") {
						$fields[$key]=substr($fields[$key],1,strlen($fields[$key]));						
					} else unset($fields[$key]);
					break;
				case "phones":
					foreach($fields[$key] as $itemK=>$item)
					if ($item["phone_code"]!="")
					if (defined("_".strtoupper($item["phone_code"]))) $fields[$key][$itemK]["label"]=constant("_".strtoupper($item["phone_code"]));
					else $fields[$key][$itemK]["label"]=_00020001;
					break;	
				case "coordaddressx":
				case "coordaddressy":
					if ($fields[$key]=="" or $fields[$key]=="0") unset($fields[$key]);
					break;
				default:
					unset($fields[$key]);
					break;
			}
		}
		//print_r($fields);
		return true;
	}
	/**
	 * Updates visit and vote counter
	 *
	 * @param unknown_type $entity_id
	 */
	public function SetCounter($entity_id,$user_id, $vote = false){

		if (strpos(_IP_EXCLUDED,$_SERVER["REMOTE_ADDR"])===FALSE) {
		
			if ($vote) $strVote = "1"; else  $strVote = "0";
	
			if ($this->query("select entity_id from counters where user_id = '$user_id' and entity_id = $entity_id and dtDay = CURDATE();")){
				if ($this->num_rows()>0)
				$this->query("update counters set counter = (counter + 1), vote = $strVote where user_id = '$user_id' and entity_id = $entity_id and dtDay = CURDATE();");
				else
				$this->query("insert into counters (entity_id,counter,dtDay,user_id,vote) values ($entity_id,1,CURDATE(),'$user_id',$strVote);");
			}
			if ($vote){
				if ($this->query("select entity_id from entityvotes where entity_id = $entity_id;")){
					if ($this->num_rows()>0)
					$this->query("update entityvotes set counter = (counter + 1) where entity_id = $entity_id;");
					else
					$this->query("insert into entityvotes (entity_id,counter) values ($entity_id,1);");
				}
			}
		} else {
			 $this->query("insert into browseragent (entity_id, txt_useragent) values ($entity_id,'".print_r($_SERVER,true)."');");
		}
			
	}
	/**
	 * More viewed for today, last 7 days, month  *
	 *
	 * @param unknown_type $type
	 */
	public function mviewed($type){
		if ($this->query("select c.entity_id from mviewedvoted c, entity e where c.entity_id = e.entity_id and c.itype = $type order by counter desc limit 5;")){
			if ($counter = $this->select_array()) {
				//print_r($counter);
				foreach($counter as $entity){
					//$this->query();
					$fields = $this->dtl_SimpleEntity($entity["entity_id"],1);
					$result[]= array_filter($fields);
				}
			}
		}
		if (isset($result)) return $result; else return null;
	}
	/**
	 * Get Simple entity details from the table prefix_entitys
	 * @author Elazos Software Factory
	 * @access public
	 * @param integer entity id
	 * @return boolean
	 */
	function dtl_SimpleEntity($id, $language_id){
		try {
			if ($this->query("select entity_id, entity_type, lastupdatedate from entity where entity_id = $id;")){
				if ($this->num_rows()>0){
					$this->next_record_assoc();
					$entity = $this->Record;
					if ($entity["entity_type"]=="AG"){
						$this->query("select ag.actname, ag.tickettype_code, ag.acttype, ag.begindate, ag.enddate, ag.placename, ag.equipment_id, ag.status_id "
						."from agenda ag "
						."where ag.language_id = $language_id and ag.entity_id = $id ;");

						$this->next_record_assoc();
						$entity = array_merge($entity,$this->Record);

						if(array_key_exists("equipment_id",$entity) && $entity["equipment_id"]!="") {
							$this->query("select eq.entity_id institution_id, eq.institutionname, eq.sectionname, eq.sigla from equipment eq where language_id = $language_id and entity_id = ".$entity["equipment_id"].";");
							if ($this->num_rows()>0) {unset($entity["placename"]);$this->next_record_assoc();$entity = array_merge($entity,$this->Record);}
							if ($tmp=$this->getAddresses($entity["equipment_id"]))
							$entity = array_merge($entity,$tmp);
							$this->query("select phone_code, phonenumber, description as phonedesc from phones where language_id = $language_id and entity_id = ".$entity["equipment_id"]." order by position asc;");
							if ($this->num_rows()>0) $entity = array_merge($entity,$this->select_array_onefield("phones"));
							$this->query("select value as interinfo, interestinfo_code as intercode from interestinfo where entity_id = $id order by position asc;");
							//if ($this->num_rows()>0) $entity = array_merge($entity,$this->select_array_onefield("interestinfo"));
							if ($this->num_rows()>0)
								$entity = array_merge($entity,$this->select_array_onefield("interestinfo"));
							else {
								$this->query("select value as interinfo, interestinfo_code as intercode from interestinfo where entity_id = ".$entity["equipment_id"]." order by position asc;");
								if ($this->num_rows()>0) $entity = array_merge($entity,$this->select_array_onefield("interestinfo"));
							}
						} else {
							$entity["institutionname"]=$entity["placename"];
							unset($entity["placename"]);
							if ($ad=$this->getAddresses($id))
							$entity = array_merge($entity,$ad);
							$this->query("select phone_code, phonenumber, description as phonedesc from phones where language_id = $language_id and entity_id = $id order by position asc;");
							if ($this->num_rows()>0) $entity = array_merge($entity,$this->select_array_onefield("phones"));
							$this->query("select value as interinfo, interestinfo_code as intercode from interestinfo where entity_id = $id;");
							if ($this->num_rows()>0) $entity = array_merge($entity,$this->select_array_onefield("interestinfo"));
						}

						//popularity
						//$this->query("select popularity from popularity where entity_id = $id;");
						//if ($this->num_rows()>0) {
						//	$this->next_record_assoc();
						//	$entity["popularity"] = $this->Record["popularity"];
						//}
						// end popularity

					} else {
						$this->query("select institutionname, sectionname, sigla, internettext from equipment eq where language_id = $language_id and eq.entity_id = $id;");
						$this->next_record_assoc();
						$entity = array_merge($entity,$this->Record);
						if ($tmp=$this->getAddresses($id))
						$entity = array_merge($entity,$tmp);
						$this->query("select phone_code, phonenumber, description as phonedesc from phones where language_id = $language_id and entity_id = $id order by position asc;");
						if ($this->num_rows()>0) $entity = array_merge($entity,$this->select_array_onefield("phones"));
						$this->query("select value as interinfo, interestinfo_code as intercode from interestinfo where entity_id = $id;");
						if ($this->num_rows()>0) $entity = array_merge($entity,$this->select_array_onefield("interestinfo"));

					} // if entity type
					$this->query("select distinct label as ireflabel, value as irefvalue from internetref where visual_id = 2 and internetref_code = '00040002' and language_id = $language_id and entity_id = $id;");
					if ($this->num_rows()>0) $entity = array_merge($entity,$this->select_array_onefield("internetref"));

					if (array_key_exists("coordaddressx",$entity) && $entity["coordaddressx"]!="" && $entity["coordaddressx"]!="0"){

						$gmaps=$this->CoordGmap($entity["coordaddressx"], $entity["coordaddressy"]);
						$entity["gmapx"]=$gmaps["gmapx"];
						$entity["gmapy"]=$gmaps["gmapy"];
						$entity["coordaddressx"] = $entity["coordaddressx"]/1000;
						$entity["coordaddressy"] = $entity["coordaddressy"]/1000;

					}
					//if($tmp=$this->getWords($id))
					// $entity = array_merge($entity,$tmp);
					
					$this->prepare_fields_to_show($entity);
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
	 * @param integer $id_doc
	 */
	public function GetAgendEq($id_doc){
		if ($this->query("select a.entity_id from agenda a,entity e where a.entity_id = e.entity_id and a.equipment_id = $id_doc order by begindate asc;")){
			if ($rows = $this->select_array()){
				foreach($rows as $entity){
					//$this->query();
					$fields = $this->dtl_SimpleEntity($entity["entity_id"],1);
					$result[]= array_filter($fields);
				}
				return $result;
			} else false;
		}
		return false;
	}
    /**
     * Enter description here...
     *
     * @return unknown
     */
	public function getActDestacades($language_id, $wtarget = "home-bcn"){
		
		$sqlWTarget = "";
		
		if ($wtarget!="") $sqlWTarget = "and txt_webtarget = '$wtarget'"; 
		
		// si no esta en la cache accedemos a BD		
		if ($destacades=$this->mc->get("actdest_"._IDIOMA)){			
			return $destacades;
		} else {			
			$result = array(0);
			if ($this->query("select distinct id.entity_id id, ag.recom_id, imatgeCos, imatge, titol, resum, texte, urlvideo, tema, begindate, enddate, institutionname, gmapx, gmapy, equipment_id,e.entity_id noexist
, c.canal,ct.txt_canal, wt.post_id from agrecom ag
inner join agrecomentity_id id on id.recom_id = ag.recom_id
inner join agrecomtxt txt on ag.recom_id = txt.recom_id
left join agrecomcanals c on c.recom_id = ag.recom_id
left join agcanaltxt ct on c.canal = ct.canal and ct.language_id = '$language_id'
left join entity e on e.entity_id = id.entity_id
inner join esf_post_webtarget wt on wt.recom_id = ag.recom_id $sqlWTarget 					
where txt.language_id = $language_id order by wt.numordre, ag.recom_id asc;")){
				if ($this->num_rows()>0){
					$result = $this->select_array();
					// quitando valores vacios
					$i = 0;
					$ids = array();
					foreach($result as $row){				   
					   //$i = $row["recom_id"];
					   $pos=array_search($row["recom_id"], $ids);
					   if ($pos===false) {
					   	$result[$i] = array_filter($row);
					   	$ids[$i]=$row["recom_id"];
					   	$pos = $i;	
					   	$i++;				   	
					   } 
					   
					   if (array_key_exists("canal",$row)) {
					      //$temas[]=$result[$i]["tema"];
					      //$temas = array_unique($temas);
					      //if (array_search($result[$i]["tema"],$temas)!==false) 
					      	
					      	//$result[$pos]["canal"][] = $tema; 
					      	if ($row["canal"]!=""){
					      		$temas["tema"]= strtolower($row["txt_canal"]);
					      		$temas["id_tema"] = utils::getTxtPermalink($row["canal"]);
					      		$result[$pos]["cc"][]=$temas;
					   	    $result[$pos]["tema"] = strtolower($row["txt_canal"]);
					      	$result[$pos]["id_tema"] = utils::getTxtPermalink($row["canal"]);
					      	} 
					      //$result[$i]["id_tema"]= array_search($result[$i]["tema"],$temas);					     
					   }					  				   
					   //$i++;
					}
					//return $result;
				}
			}			
			if (count($result)>0){		
				//print_r($result);
				$this->mc->set("actdest_"._IDIOMA,$result,(60*30));
				return $result;
			} else return array(0);			
		}
	}
	/**
	 * Returna la agenda recomendada asociada a un entity_id 
	 *
	 * @param unknown_type $entity_id
	 */
	public function GetRecomByEntityID($entity_id, $language_id){
		$AllRecom = $this->getActDestacades($language_id);
		$tmp = false;		
		foreach($AllRecom as $row){
			if ($row["id"]==$entity_id) {
			   if ($row["noexist"]!="") return $row;
			   else $tmp = $row;				
			}
		}
		return $tmp; 
	}
	/**
	 * Enter description here...
	 *
	 */
	public function RecordToXML($entity){
      
		$outString = "";

		foreach($entity as $key=>$value){

			switch($key){
				case "institutionname":				
					$href="";
					if (array_key_exists("institution_id",$entity)){
						//$href="href=\"".LK_PAG."".utils::url_encrypt("pg=detall&id_doc=".$entity["institution_id"])."\"";
						if(array_key_exists("sectionname",$entity)) $name =  strip_tags($entity["sectionname"])." - ". strip_tags($entity["institutionname"]);
					       else $name = strip_tags($entity["institutionname"]);	
						
						$href="href=\"".utils::getPermalink($name,"pg=detall&id_doc=".$entity["institution_id"])."\"";
					}
					$outString .="<$key $href label=\"".constant("_".strtoupper($key))."\"><![CDATA[".$value."]]></$key>\n";
					break;
				
				
				case "timetable":
					
					$this->cleanTimetable($value);
					$period = explode("|",$value["period"]);
					$days = explode("|",$value["days"]);
					$hours =explode("|",$value["hours"]);
					$price = explode("|",$value["price"]);
					$remarks = explode("|",$value["remarks"]);				
					
					//print_r($days);
					$outString .="<timetable>";
					
					//$outString .="<td>"._PERIOD."</td><td>"._DAYS."</td><td>"._HOURS."</td><td>"._PRICE."</td><td>"._REMARKS."</td>";
					
					if(count($remarks)>1){
						
						for($i=0;$i<count($remarks);$i++){
							$tmp = "";							
							if (trim($period[$i])!="") $tmp .="<periode><![CDATA[".ucfirst($period[$i])."]]></periode>";
							if (trim($days[$i])!="") $tmp .="<dies><![CDATA[".ucfirst($days[$i])."]]></dies>";
							if (trim($hours[$i])!="") $tmp .="<hores><![CDATA[".$hours[$i]."]]></hores>";
							if (trim($price[$i])!="") $tmp .="<preu label=\""._PREUS."\"><![CDATA[".str_replace("<br>","<br/>",$price[$i]).".]]></preu>";
							if (trim($remarks[$i])!="") $tmp .="<observacions><![CDATA[".$remarks[$i]."]]></observacions>";
								
							if ($tmp!="") $outString .="<horari label=\""._HORARIS."\">$tmp</horari>";
                            /*$tmp = "";	
                            if (trim($price[$i])!="") $tmp .="<![CDATA[".$price[$i].".]]>";						
							if ($tmp!="") $outString .="<preu label=\""._PREUS."\">".$tmp."</preu>";						
							*/
						}
						
					}
					//$outString .="<td><![CDATA[".$price[$i]."]]></td>";
					//	$outString .="<td><![CDATA[".$remarks[$i]."]]></td>";
					$outString .="</timetable>";

					break;
				case "classification":					
					foreach($value as $branch){
						$tree_id = false;
						$strBranch = "";						
						for($i=0;$i<count($branch);$i++){
							$strBranch .= "<item>";
							if (!$tree_id) $tree_id = substr($branch[$i]["code"],2,3);
							if ($tree_id=="401" || $tree_id=="400" ) $strBranch .= "<code key=\"code$i\" href=\"".LK_PAG."".utils::url_encrypt("pg=search&q=*:*&code$i=".$branch[$i]["code"])."\">".$branch[$i]["code"]."</code>";
								else $strBranch .= "<code>".$branch[$i]["code"]."</code>"; 
							$strBranch .= "<name><![CDATA[".$branch[$i]["class"]."]]></name>";
							$strBranch .= "</item>";
						}
						if ($tree_id=="401" || $tree_id=="400" ) $nameNode = "classification";else $nameNode = "otherclassification"; 
						$outString .="<$nameNode label=\""._CLASSLABEL."\" tree_id=\"$tree_id\">$strBranch</$nameNode>\n";
						//echo $strBranch."<br/>";
					}
					break;
				case "relations":
					$outString .="<relations labelsection=\""._SECTION."\" label=\""._RELATIONS."\">";					
					foreach($value as $item){	
						$name = $item["institutionname"]; 										
						if (array_key_exists("sectionname",$item) && $item["sectionname"]=="#") unset($item["sectionname"]);
						else $name = $item["sectionname"]." - ".$item["institutionname"];
						$item["direct"]=ucfirst($item["direct"]);
						$nameNode="item";						
						if ($item["reltype"]==1) $nameNode="section";
						//$outString .="<$nameNode href=\"".LK_PAG."".utils::url_encrypt("pg=detall&id_doc=".$item["entity_id"])."\">";
						$outString .="<$nameNode href=\"".utils::getPermalink($name,"pg=detall&id_doc=".$item["entity_id"])."\">";
						foreach($item as $subkey=>$subvalue) $outString .="<$subkey><![CDATA[".strip_tags($subvalue)."]]></$subkey>\n";
						$outString .="</$nameNode>";
					}
					$outString .="</relations>";
					break;					
				default:
					if (is_array($value)) {
						$outString .="<$key>";
						foreach($value as $subarray) {
							$outString .="<item>";
							foreach($subarray as $subkey=>$subvalue)$outString .="<$subkey><![CDATA[".$subvalue."]]></$subkey>\n";
							$outString .="</item>";
						}
						$outString .="</$key>";
					} else {
						$label2="";
						if ($key=="begindate") $label2 = "label2=\""._DATE."\"";
						$outString .="<$key $label2 label=\"".constant("_".strtoupper($key))."\"><![CDATA[".ucfirst($value)."]]></$key>\n";
						
					}
					break;
			}
		}
		return $outString;
       
	}
	/**
	 * Clean html tags timetable 
	 *
	 */
	private function cleanTimetable(&$timetable){
		
		foreach($timetable as $key=>$line){
				//$timetable[$key]=preg_replace("/(<\/?)(\w+)([^>]*>)/e","'\\1'.strtoupper('\\2').'\\3'",$line);
				if ($key!="price" && $key!="remarks") $timetable[$key]=preg_replace("/(<\/?)(\w+)([^>]*>)/e","', '",$line);
				if ($key=="price") $timetable[$key]=preg_replace("/([0-9]) e/","\\1 €",$line);				

		}
		
	}
	/**
	 * Devuelve el post_id del equipamiento recomendado
	 *
	 * @param unknown_type $entity_id
	 * @return unknown
	 */
	public function getPost_id($entity_id, $wtarget, $type = "AG"){	
		
		if ($type=="AG"){
			$sql = "select post_id from esf_post_webtarget wt inner join agrecomentity_id ag on ag.recom_id = wt.recom_id where  ag.entity_id = ".$entity_id." and txt_webtarget = '".$wtarget."'";	
		}
		if ($type=="EQ"){
			$sql = "select post_id from esf_post_webtarget where txt_webtarget = '$wtarget' and entity_id = ".$entity_id.";";
		}
				
		if ($this->query($sql)){
			if ($this->num_rows()>0){
				$this->next_record_assoc();
				return $this->Record["post_id"];
			} else return false;	
		}
		return false;
	}
	/***************************************END CLASS*****************************************************/
}
?>
