<?php
/**
 * Guia de Barcelona - Agenda and Directory
 *
 * This file is part of Guia Barcelona v1.0.0
 * @author Elazos Software Factory
 **/
/**
 * Class Classification file
 * @author Elazos Software Factory
 **/
/**
 * Class Object file
 **/
require_once("includes/object.class.inc");
/**
 * Handles Classification Objects
 *
 * @author Elazos Software Factory
 * @version 1.0
 * @package BusObj
 */
class classification extends object {
	/**
	 * Enter description here...
	 *
	 * @param unknown_type $code
	 * @param unknown_type $language_id
	 * @return unknown
	 */
	function getClassTreeArray($code,$language_id,$levelDisplay){
		try {			
			//echo "code : ".$code."<br/>";
			$level = ((strlen($code)-7)/3)+1;
			//$nexLevel = substr($code,0,5)."0".$level.substr($code,7,substr($code,0,5));

			if ($this->query("select code, description from tct_codes where parent_code =  '$code' and language_id = $language_id and visible = 1 order by description;")){
				
				if ($this->num_rows()>0){
					$tmp = $this->select_array();					
					//$result[$desc]=$tmp;
					$i = 0;						
					foreach($tmp as $node){
						//$result[$node["description"]]=$this->getClassTree($node["code"],$node["description"],$language_id);
						$result[$i]["code"] = $node["code"];
						$result[$i]["desc"] = $node["description"];
						if ($level<$levelDisplay) {
							$result[$i]["ramas"]=$this->getClassTreeArray($node["code"],$language_id,$levelDisplay);						
						} else $result[$i]["ramas"]=null;
						$i++;
					}						
					return $result;
				} else return false;
					
			} else return false;
		} catch(Exception $ex){
			print_r($ex);
			return false;
		}
	}
	/**
	 * Enter description here...
	 *
	 * @param unknown_type $code
	 * @param unknown_type $language_id
	 * @return unknown
	 */
	function getClassTreeXML($code,$language_id){
		try {
			//echo "code : ".$code."<br/>";
			//$level = ((strlen($code)-7)/3)+1;
			//$nexLevel = substr($code,0,5)."0".$level.substr($code,7,substr($code,0,5));
			if ($this->query("select code, description from tct_codes where parent_code = '$code' and language_id = $language_id and visible = 1 order by description;")){
				if ($this->num_rows()>0){
					$tmp = $this->select_array();
					//$result[$desc]=$tmp;
					$result = "";
					foreach($tmp as $node){
						//$result[$node["description"]]=$this->getClassTree($node["code"],$node["description"],$language_id);

						$result.= "<".$node["code"]." desc=\"".$node["description"]."\">";
						$result.= $this->getClassTreeXML($node["code"],$language_id);
						$result.= "</".$node["code"].">";

							
					}
					return $result;
				} else return false;
					
			} else return false;
		} catch(Exception $ex){
			print_r($ex);
			return false;
		}
	}
	/**
	 * Enter description here...
	 *
	 * @param unknown_type $code
	 * @param unknown_type $language_id
	 * @return unknown
	 */
	/*
	function getClassLevel($code,$language_id){
		try {
			if ($tmp=$this->mc->get("$code$language_id")) {
            	return $tmp;            
            }	 
			if ($this->query("select code, description from tct_codes where parent_code = '$code' and language_id = $language_id and visible = 1 order by description;")){
				if ($this->num_rows()>0){
				    $tmp = $this->select_array();
					foreach($tmp as $item){
						$result[$item["code"]]= $item["description"];
					}
					$this->mc->set("$code$language_id",$result,(60*60));
					//$result[$desc]=$tmp;
					return $result;
				} else return false;
					
			} else return false;
		} catch(Exception $ex){
			print_r($ex);
			return false;
		}
	}*/
	function getClassLevel($code,$language_id){
		try {
			if ($tmp=$this->getAllClassDesc()){
				if (array_key_exists($code,$tmp)) 
				return $tmp[$code][$language_id];
				else return false;
			} else return false;
		} catch(Exception $ex){
			print_r($ex);
			return false;
		}
	}
	/**
	 * Enter description here...
	 *
	 * @param unknown_type $language_id
	 * @return unknown
	 */
	function getAllClassDesc(){
	    try {		
            if ($tmp=$this->mc->get("tctcodes")) {
            	//echo "Cached alltctcodes";
            	return $tmp;            
            }	    	
			if ($this->query("select parent_code, code, description, language_id from tct_codes where visible = 1;")){
				if ($this->num_rows()>0){
					$tmp = $this->select_array();
					foreach($tmp as $item){
						if($item["parent_code"]=="") $item["parent_code"] = "ROOT";
						$result[$item["parent_code"]][$item["language_id"]][$item["code"]]= $item["description"];
					}
					$this->mc->set("tctcodes",$result,(60*60));
					return $result;
				} else return false;					
			} else return false;
		} catch(Exception $ex){
			print_r($ex);
			return false;
		}		
	}
	/**
	 * Return parent code for a given code
	 *
	 * @param String $code Classification Code
	 * @return String Parent Classification Code
	 */
	public function GetParentCode($code){
		$level = $this->GetLevel($code)-1;
		return substr($code,0,5)."0".$level.substr($code,7,(3*$level));		
	}
	/**
	 * Enter description here...
	 *
	 * @param unknown_type $code
	 * @return unknown
	 */
	public function GetLevel($code){
		return substr($code,6,1);
	}
	/***************************************END CLASS*****************************************************/
}
?>
