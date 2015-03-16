<?php
/**
 * Guia de Barcelona - Agenda and Directory
 *
 * This file is part of Guia Barcelona v1.0.0
 * @author Elazos Software Factory
 **/


require_once("db/mysql.class.inc");
/**
 *Backup Handling to XML file
 *@author Elazos Software Factory
 *@version 1.0
 *@package Database
 */
class ImpExp extends DB_Sql {

	var $filename;            // file name(sqldata.txt)
	var $structure_only;    // Output method : true/false
	var $fptr;              // Do Not change this.
	var $charset;
	var $TableColumns;
	var $reader;
	var $ImpDebug = false;
	var $table2Update = array();
	var $KeyBytable = array();
	var $IDtoInsert;


	/**
	 * Constructor function: This will Inisialize variables.
	 *
	 * @param unknown_type $filename
	 * @param unknown_type $structure_only
	 * @return mysql_backup
	 */
	function ImpExp(){
		set_time_limit (1200);
		$this->charset="UTF-8";
	}

	/**
	 * This will create the sqldata.txt file.
	 *
	 * @param unknown_type $filename
	 * @param unknown_type $structure_only
	 * @return unknown
	 */
	function MMysqlbackup($filename, $structure_only){
		if (strval($this->filename)!="") $this->fptr=fopen($this->filename,"w"); else $this->fptr=false;
		$data="<?xml version=\"1.0\" encoding=\"".$this->charset."\"?>\n<root>\n";
		if ($this->fptr!=false) fwrite($this->fptr,$data);
		$tables=$this->table_names();
		foreach($tables as $tb) {
			$data="";
			if ($this->query("select * from ".$tb["table_name"])){
				$nodeName = substr($tb["table_name"],strlen($this->prefix)+1,strlen($tb["table_name"]));
				$data.="<".$nodeName.">\n";
				$rows=$this->select_xml($this->table_columns($tb["table_name"]),false);
				$data.="$rows";
				$data.="</".$nodeName.">\n";
				if ($this->fptr!=false) fwrite($this->fptr,$data);
			}
		}
		$data="</root>";
		//echo $data;
		if ($this->fptr!=false) fwrite($this->fptr,$data);
		if ($this->fptr!=false) fclose($this->fptr);
		return 0;
	}
	/**
	 * Main method. Executes the backup.
	 *
	 * @param unknown_type $filename
	 * @param unknown_type $structure_only
	 * @return unknown
	 */
	function Backup($filename,$structure_only){
		$this->filename = $filename;
		$this->structure_only = $structure_only;
		$this->MMysqlbackup($this->filename,$this->structure_only);
		return 1;
	}

	/**
	 * Enter description here...
	 *
	 * @param unknown_type $type
	 */
	public function executeProcess($type,$filename){

		switch($type){
			case "total":
				$TableList = file_get_contents($filename);
				$tmp = explode("\n", $TableList);
				unset($TableList);
				foreach($tmp as $tmpItem){
					$tmpItem = explode("|", $tmpItem);
					$TableList[]=strtolower($tmpItem[0]);
					if (count($tmpItem)>1){
					$this->table2Update[]=strtolower($tmpItem[0]);
					$this->KeyBytable[strtolower($tmpItem[0])]=explode(",",$tmpItem[1]);
					}
				}
				$this->query("truncate table tmp_import;");
				$this->getEntity2Import();
				$this->query("update tmp_import set action = 'I' where entity_id not in (select entity_id from entity);");
				$this->query("update tmp_import set action = 'U' where entity_id in (select entity_id from entity);");
				$this->query("insert into tmp_import (entity_id, action) select entity_id, 'D' from entity where entity_id not in (select entity_id from tmp_import);");
   			    $this->deleteIDUpdateTable();
				$this->query("select entity_id from tmp_import where action = 'I';");
				$this->IDtoInsert = array();
				while($this->next_record_assoc()){
					$this->IDtoInsert[] = $this->Record["entity_id"];
				}
				$this->deleteValues("total");
				foreach($TableList as $table){
					$this->import($table.".xml");
				}
				$this->query("update variants set keywords = SUBSTRING(keywords,2) where code like '00106%' and keywords like 'M%';");
				$this->query("UPDATE tct_codes SET PARENT_CODE = IF(CHAR_LENGTH(CODE)>7,CONCAT(SUBSTRING(CODE,1,6),(SUBSTRING(CODE,7,1)-1),SUBSTRING(code,8,((CHAR_LENGTH(code)-3)-7))),NULL)");
				break;
			case "parcial":
				$TableList = file_get_contents("jobs/parcial.txt");
				break;
		}

	}

	/**
	 * Enter description here...
	 *
	 * @param unknown_type $FileName File Name with path
	 */
	function Import($FileName){
		//$this->Debug = 1;
		$FileName = "jobs/input/".$FileName;

		$TableNames = $this->table_names();

		foreach($TableNames as $name){
			$this->TableColumns[$name["table_name"]] = $this->table_columns($name["table_name"]);
		}

		$this->reader = new XMLReader();
		if ($this->ImpDebug) echo "Loading File...\n";
		if ($this->reader->open($FileName)){
			$this->reader->read();
			$this->getRow(strtolower($this->reader->name));
		} else echo "Error Loading File...\n";

		//return $NoError;
	}
	/**
	 * Enter description here...
	 *
	 * @param unknown_type $xml
	 */
	private function getRow($table){

		if ($this->ImpDebug) echo "Importing table : ".$table." ...\n";
		//$this->deleteValues($table);
		$rowsProcessed = 0;
		$RowsReaded = 0;
		$entitiesCleared = array();
		// Deletes all table where if is not to update
		if (array_search($table,$this->table2Update)===false)
			$this->query("truncate table $table;");
		$this->reader->read();
		while ($this->reader->next()){
			if (strtoupper($this->reader->name)=="ROW"){
				if ($row = simplexml_load_string($this->reader->readOuterXML())){

					$RowFields = false;
					foreach($row->children() as $field) {
						$childs = $field->children();
						if ($childs){
							$this->getRowSimpleXML(strtolower($field->getName()),$field);
							//echo "getRow ".strtolower($field->getName())."\n";
						} else {
							//echo "RowFields ".strtolower($field->getName())."\n";
							$RowFields[strtolower($field->getName())] = (string)$field;
						}
					}
					if ($RowFields) {
						//if (array_search($table,$this->table2Update)===false && array_key_exists("entity_id",$RowFields) && array_search($RowFields["entity_id"],$entitiesCleared)===false) {
						//	$this->clearEntityID($RowFields["entity_id"],$table);
						//	$entitiesCleared[]=$RowFields["entity_id"];
						//}
						if ($this->executeSQL($table,$RowFields)) $rowsProcessed++;
						$RowsReaded++;
					}
				}

			}
		}
		echo "Imported $rowsProcessed of $RowsReaded. Errors = ".($RowsReaded-$rowsProcessed)." : ".$table." ...\n";

	}
	/**
	 * Enter description here...
	 *
	 * @param unknown_type $xml
	 */
	private function getRowSimpleXML($table,$xml){
		if ($this->ImpDebug) echo "Importing table : ".$table." ...\n";
		$this->deleteValues($table);
		$rowsProcessed = 0;
		$RowsReaded = 0;
		foreach($xml->ROW as $row){

			$RowFields = false;
			foreach($row->children() as $field) {

				$childs = $field->children();
				if ($childs){

					$this->getRowSimpleXML(strtolower($field->getName()),$field);

				} else {

					$RowFields[strtolower($field->getName())] = (string)$field;
				}
			}
			if ($RowFields) {
				if ($this->executeSQL($table,$RowFields)) $rowsProcessed++;
				$RowsReaded++;
			}
		}
		echo "Imported $rowsProcessed of $RowsReaded. Errors = ".($RowsReaded-$rowsProcessed)." : ".$table." ...\n";
			
	}
	/**
	 * Enter description here...
	 *
	 * @param unknown_type $table
	 * @param unknown_type $fields
	 */
	private function executeSQL($table,$fields){

		foreach($fields as $fieldName=>$fieldValue){
			$type = $this->TableColumns["$table"]["$fieldName"];
			switch($type){
				case "date":
				case "datetime":
					if ($fields[$fieldName]=="null")
					$fields[$fieldName]="null";
					else
					$fields[$fieldName]="'$fieldValue'";
					break;
				case "string":
				case "varchar":
					if ($fields[$fieldName]=="null" || strlen($fields[$fieldName])<2){
						$fields[$fieldName]="null";
					} else {
						$fields[$fieldName]="'".$this->str2SQL($fieldValue)."'";
					}
					break;
				case "decimal":
				case "int":
				case "bigint":
				case "tinyint":
					break;
				default:
					break;
			}
		}

		if (in_array($table,$this->table2Update)===false) {
			if (!$this->insert($fields,$table)) {
				if ($this->ImpDebug) echo "ERROR $table: ".$this->Errno." ".$this->Error."\n";
				return false;
			} else return true;
		} else {
			$id = false;
			if (array_key_exists("entity_id",$fields)) $id = $fields["entity_id"];
			if (array_key_exists("agenda_id",$fields)) $id = $fields["agenda_id"];			
			if ($id && in_array($id,$this->IDtoInsert)) {
				if (!$this->insert($fields,$table)) {
					if ($this->ImpDebug) echo "ERROR $table: ".$this->Errno." ".$this->Error."\n";
					return false;
				} else return true;

			} else {
				//$strWhere="";
				//foreach($this->KeyBytable[$table] as $keyName){
					//if ($strWhere!="") $strWhere.=" and $keyName = ".$fields[$keyName];
					//else $strWhere.="$keyName = ".$fields[$keyName];
				//}			
				//if (!$this->update($fields,$table,"where $strWhere")) {
				if (!$this->insert($fields,$table,true)) {
					if ($this->ImpDebug) echo "ERROR $table: ".$this->Errno." ".$this->Error."\n";
					return false;
				} else {				   	
				    if (($tmp=$this->affected_rows())>0) {
				    	foreach($this->KeyBytable[$table] as $keyName){
				    		echo " $keyName = ".$fields[$keyName];
				    	}
				    	echo "\n";
				       if ($id) $this->query("update tmp_import set action = 'S' where entity_id = $id;");
				    }					
					return true;
				}
			}
		}

	}
	/**
	 * Enter description here...
	 *
	 * @param unknown_type $table
	 */
	private function deleteValues($table){

		$TablesToDelete = array("ADDRESSES","INTERESTINFO","INTERNETREF"
		,"PHONES","VISUALITZACIONS_INFOEXTERNA","TIMETABLE","HORARI"
		);

		switch($table){
			case "agenda":
				foreach($TablesToDelete as $strTable){
					$this->query("delete from ".strtolower($strTable)." where entity_id in (select entity_id from entity where entity_type = 'AG');");
				}
				$this->query("delete from entity where entity_type = 'AG';");
				$this->query("truncate table altres_addresses_acte;");
				$this->query("truncate table nom_acte;");
				$this->query("truncate table agenda;");
				$this->query("delete from relations where target_type = 'AG' or source_type = 'AG';");

				break;
			case "equipment":
				foreach($TablesToDelete as $strTable){
					$this->query("delete from ".strtolower($strTable)." where entity_id in (select entity_id from entity where entity_type = 'EQ');");
				}
				$this->query("truncate table equipment;");
				$this->query("delete from entity where entity_type = 'EQ';");
				$this->query("delete from relations where target_type = 'EQ' or source_type = 'EQ';");
				break;
			case "classification":
				$this->query("truncate table classification;");
				break;
			case "tct_codes":
				$this->query("truncate table tct_codes;");
				break;
			case "reltypes":
				$this->query("truncate table reltypes;");
				break;
			case "keywords":
				$this->query("truncate table keywords;");
				break;
			case "total":
				$this->query("select entity_id from tmp_import where action  = 'D';");
				if ($this->num_rows()>0){
					$entityList = $this->select_array();
					foreach($entityList as $row){
						//foreach($TablesToDelete as $strTable){
						//$this->query("delete from table ".strtolower($strTable)." where entity_id =".$row["entity_id"].";");
						//}
						$this->query("delete from table equipment where entity_id =".$row["entity_id"].";");
						$this->query("delete from table agenda where entity_id =".$row["entity_id"].";");
						$this->query("delete from table entity where entity_id =".$row["entity_id"].";");
						$this->query("delete from table addresses where entity_id =".$row["entity_id"].";");
						$this->query("delete from table altres_addresses_acte where agenda_id =".$row["entity_id"].";");
						$this->query("delete from table nom_acte where entity_id =".$row["entity_id"].";");
						$this->query("delete from table rellevancia_actes where entity_id =".$row["entity_id"].";");
						$this->query("delete from table rellevancia_actes_equip where entity_id =".$row["entity_id"].";");
						$this->query("delete from table classification where entity_id =".$row["entity_id"].";");
						$this->query("delete from table counters where entity_id =".$row["entity_id"].";");
						$this->query("delete from table recommend where entityid1 =".$row["entity_id"]." or entityid2 =".$row["entity_id"].";");
						$this->query("delete from table entityvotes where entity_id =".$row["entity_id"].";");
						$this->query("delete from table interestinfo where entity_id =".$row["entity_id"].";");
						$this->query("delete from table internetref where entity_id =".$row["entity_id"].";");
						$this->query("delete from table keywords where entity_id =".$row["entity_id"].";");
						$this->query("delete from table mviewedvoted where entity_id =".$row["entity_id"].";");
						$this->query("delete from table phones where entity_id =".$row["entity_id"].";");
						$this->query("delete from table popularity where entity_id =".$row["entity_id"].";");
						$this->query("delete from table relations where target_id =".$row["entity_id"]." or source_id =".$row["entity_id"].";");
						$this->query("delete from table timetable where entity_id =".$row["entity_id"].";");
						$this->query("delete from table visualitzacions_infoexterna where entity_id =".$row["entity_id"].";");
						//$this->query("delete from table keywords where entity_id =".$row["entity_id"].";");
					}
				}
				//$this->query("truncate table tct_codes;");
				//$this->query("truncate table variants;");
				//$this->query("truncate table reltypes;");
				break;
			default:
				break;
		}
	}
	/**
	 * Enter description here...
	 *
	 */
	private function getEntity2Import(){
		$this->reader = new XMLReader();
		if ($this->ImpDebug) echo "Checking Entities to Import...\n";
		if ($this->reader->open("jobs/input/entity.xml")){
			$this->reader->read();
			$rowsProcessed = 0;
			$RowsReaded = 0;
			$this->reader->read();
			while ($this->reader->next()){
				if (strtoupper($this->reader->name)=="ROW"){
					if ($row = simplexml_load_string($this->reader->readOuterXML())){
						$RowFields = false;
						$RowFields["entity_id"] = (string)$row->ENTITY_ID;
						//$this->Debug = 1;
						if ($RowFields) {
							if ($this->executeSQL("tmp_import",$RowFields)) $rowsProcessed++;
							$RowsReaded++;
						}
					}
				}
			}
		} else echo "Error Loading File...\n";
	}
	/**
	 * Enter description here...
	 *
	 * @param unknown_type $entity_id
	 * @param unknown_type $table
	 */
	private function clearEntityID($entity_id, $table){
		switch($table){
			case "altres_addresses_acte":
				$this->query("delete from $table where agenda_id = $entity_id;");
				break;
			default:
				$this->query("delete from $table where entity_id = $entity_id;");
				break;
		}

	}
	/**
	 * Enter description here...
	 *
	 */
	private function deleteIDUpdateTable(){
		foreach($this->table2Update as $table){
			$this->query("delete from $table where entity_id in (select entity_id from tmp_import where action = 'D');");
		}		
	}
}
?>
