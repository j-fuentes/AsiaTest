<?php
/**
 * Guia de Barcelona - Agenda and Directory
 *
 * This file is part of Guia Barcelona v1.0.0
 * @author Elazos Software Factory
 **/
/**
 * Class Object file
 * @author Elazos Software Factory
 **/
/**
 * Class Mysql file
 **/
require_once("includes/object.class.inc");
/**
 * Handles Database Objects
 *
 * @author Elazos Software Factory
 * @version 1.0
 * @package BusObj
 */
class ASIAupdate extends object {


	/**
	 * Enter description here...
	 *
	 * @return unknown
	 */
	public function GetXMLASIA(){
			
		$url="http://w10.bcn.es/APPS/asiasiacache/peticioXmlAsia?id=200";
	
		$date = date("Y-m-d",time());

		$fileXml = file_get_contents($url);
		 
		if(!$fileXml || trim($fileXml)=="") return false;
		$fileXml = str_replace(" & ","",$fileXml);

		try {
			//$xml = new SimpleXMLElement($fileXml);
			$xml = simplexml_load_string($fileXml, 'SimpleXMLElement', LIBXML_NOCDATA);
		} catch (Exception $e){
			Echo "error al cargar XML\n";
			return false;
		}
		//print_r($xml);die;

		$index = 5000000;
		$i = 0;
		$this->query("delete from properties where code = '0000102016000';");
		foreach($xml->body->resultat->equipaments->equipament as $Element){

			//print_r();
			//echo $Element->id."<br/>"; 
			//$this->Debug = true;
			$this->query("insert into properties (classification_id, entity_id, entity_type, code, tree_id, cgroup, generalflag) values (".($index+$i).", ".$Element->id.", 'EQ', '0000102016000', 102, 0, 1);");
			$i++;
				
				
		}
		$this->query("insert into tmp_entity (entity_id, action, processed) select entity_id, 'S',0 from properties where code = '0000102016000' on duplicate key UPDATE  action = 'S', processed = 0;");
		echo "Inserted $i rows from XML<br/>";	
		$this->query("SELECT p.entity_id FROM properties p left join entity e on e.entity_id = p.entity_id where p.code = '0000102016000' and e.entity_id is null;");
		$result = $this->select_array();
		foreach($result as $item){
			echo $item["entity_id"]."<br/>";
		}
		return true;
	}




	/***************************************END CLASS*****************************************************/
}
?>