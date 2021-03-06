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
class agrecom extends object {

	var $imageServer = "";
	var $tot;
	var $rejected_post_id;
	var $url;
	
	function agrecom(){
		$this->rejected_post_id = array();
		$this->url = "noticies.bcn.cat";
	}

	/**
	 * Devuelve de agenda recomendada, los campos begindate, endate, institutionname
	 *
	 * @param unknown_type $entity_id
	 * @return unknown
	 */
	public function getAgendaData($entity_id, $post_id = null){

		//echo "in getAgendaData $entity_id<br/>\n";
		$result = array();

		$result["begindate"] = "null";
		$result["enddate"] = "null";
		$result["institutionname"] = "null";
		$result["equipment_id"] = "null";
		$result["gmapx"]="null";
		$result["gmapy"]="null";


		if ($this->query("select equipment_id, begindate, enddate, placename from agenda where entity_id = ".$entity_id.";")){
			if ($this->num_rows()>0){

				$this->next_record();
				$result["begindate"] = $this->Record["begindate"];
				$result["enddate"] = $this->Record["enddate"];
				$result["institutionname"] = $this->Record["placename"];


				$equipment_id = $this->Record["equipment_id"];
				if ($equipment_id!="" && $this->query("select sectionname, institutionname from equipment where entity_id = ".$equipment_id.";")){
					if ($this->num_rows()>0){
						$this->next_record();
						$result["institutionname"] = $this->Record["institutionname"];
						if ($this->Record["sectionname"]!="" && $this->Record["sectionname"]!="#")
						$result["sectionname"] = $this->Record["sectionname"];
						$result["equipment_id"] = $equipment_id;
						$this->query("select coordaddressx, coordaddressy from addresses where entity_id = $equipment_id;");
						if ($this->num_rows()>0){
							$this->next_record();
							$gmaps=$this->CoordGmap($this->Record["coordaddressx"], $this->Record["coordaddressy"]);
							$result["gmapx"]=$gmaps["gmapx"];
							$result["gmapy"]=$gmaps["gmapy"];
						}
					}
				}
				// if no localization found 
				if ($result["gmapx"]=="null"){
					$this->query("select coordaddressx, coordaddressy from addresses where entity_id = $entity_id;");
					if ($this->num_rows()>0){
						$this->next_record();
						$gmaps=$this->CoordGmap($this->Record["coordaddressx"], $this->Record["coordaddressy"]);
						$result["gmapx"]=$gmaps["gmapx"];
						$result["gmapy"]=$gmaps["gmapy"];
					}

				}
			} else {
				if ($post_id!=null) $this->rejected_post_id[] = $post_id; 
				return null;
			}
		}
			return $result;
		}
		/**
		 * Devuelve true si el equipament existe, o null sino.
		 *
		 * @param unknown_type $entity_id
		 * @return unknown
		 */
		public function getEquipmentData($entity_id, $post_id = null){

			if ($this->query("select entity_id from equipment where entity_id = ".$entity_id.";")){
				if ($this->num_rows()>0){
					return true;					
				} else {
					if ($post_id!=null) $this->rejected_post_id[] = $post_id;
					return null;
				}
			}
			return null;
		}
		/**
		 * Devuelve una URL de youtube
		 *
		 * @param unknown_type $data
		 * @return unknown
		 */
		public function extract_urls($data){

			$links = array();
			$pos = (int) 0;
			$i = (int) 0;

			while (!(($pos = strpos($data,"<a",$pos)) === false)) {
				$startpos = strpos($data,"\"", $pos);
				$endpos = strpos($data,"\">",$pos);
				$tag = trim(substr($data,$startpos+1,($endpos-$startpos-1)));
				$tag = substr($tag, 0, strlen($tag));
				$end_tag_pos = strpos($data,'</a>',$endpos);
				$linked_text = strip_tags(substr($data, $endpos+2, ($end_tag_pos-$endpos-2)));
				$links[$i][0] = stripslashes($linked_text);
				$links[$i][1] = stripslashes($tag);
				$pos++;
				$i++;
			}
			return $links;
		}
		/**
		 * Enter description here...
		 *
		 * @return unknown
		 */
		public function GetXMLAgendaRecomenada($type = "agenda"){
			
			//$urlIdioma[1]="http://142.75.8.12/portal/site/Home/menuitem.14f90aeeb15793636d5d05f320348a0c/?vgnextoid=db0b7b75049fd310VgnVCM1000004947900aRCRD&appInstanceName=default&pageLayoutOnly=true";
			//$urlIdioma[2]="http://142.75.8.12/portal/site/Home/menuitem.14f90aeeb15793636d5d05f320348a0c/?vgnextoid=db0b7b75049fd310VgnVCM1000004947900aRCRD&appInstanceName=default&pageLayoutOnly=true&lang=es_ES";
			//$urlIdioma[3]="http://142.75.8.12/portal/site/Home/menuitem.14f90aeeb15793636d5d05f320348a0c/?vgnextoid=db0b7b75049fd310VgnVCM1000004947900aRCRD&appInstanceName=default&pageLayoutOnly=true&lang=en_GB";
			
			$urlIdioma[1]="http://".$this->url."/api/agrecom.php?type=$type&lg=ca";
			$urlIdioma[2]="http://".$this->url."/api/agrecom.php?type=$type&lg=es";
			$urlIdioma[3]="http://".$this->url."/api/agrecom.php?type=$type&lg=en";
			
			$date = date("Y-m-d",time());
			$idiomes = array(1,2,3);
			foreach($idiomes as $idioma) {
				$i = 0;

				
				$fileXml = file_get_contents($urlIdioma[$idioma]);
				//$fileXml = $this->getDataUrl($urlIdioma[$idioma]);		
			   
			    
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

				foreach($xml->element as $Element){
					$result = null;
					$AsiaIDExists = false;
					//$result["data"] = $Element->data;
					$result["data"] = $date;
					$result["titol"] = (string)$Element->titol;
					$result["resum"] = (string)$Element->resum;
					$result["isactive"] = false;

					$links=$this->extract_urls($result["resum"]);
					foreach($links as $linkItem){
						if (strpos($linkItem[1],"youtube")!==false){
							if (strpos($linkItem[1],"watch?v=")!==false) $result["urlvideo"] = str_replace("watch?v=","embed/",$linkItem[1]);
							else $result["urlvideo"] = "http://www.youtube.com/embed".strrchr($linkItem[1], '/');
						}
					}

					$result["imatge"] = (string)$this->imageServer.$Element->imatge->path;
					$result["imatgecos"] = (string)$this->imageServer.$Element->Detall->imatgeCos->path;
					//$result["texte"] = substr((string)$this->imageServer.$Element->Detall->texte,stripos((string)$this->imageServer.$Element->Detall->texte,"<p>"));
					$result["texte"] = (string)$Element->Detall->texte;
					$result["idioma"] =  $idioma;


					/* temas */
					$result["tema"]=null;
					$canals = array();
					if (count($Element->xpath("temas"))>0){
						if ( count($Element->temas->children())>=1){
							foreach($Element->temas->tema as $tema){
								//echo "Id Asia : ".$asia->id."<br/>";
								if (($tmp=$this->GetTema((string)$tema))!=null){
									$result["tema"]=$tmp;
									$canals[]=strtoupper((string)$tema);	
								}
							}
						}
					}
					$result["canals"]=$canals;
					//echo $result["tema"]." .... ".$result["titol"]."<br/>";
					/* end temas */
					
					/* start web target */
					
					$webtarget = array();
					$pos_webtarget = 0;
					if (count($Element->xpath("webtarget"))>0){
						if ( count($Element->webtarget->children())>=1){
							foreach($Element->webtarget->item as $wt){
								//echo "Id Asia : ".$asia->id."<br/>";								
									$webtarget[$pos_webtarget]["id"]=(string)$wt->id;
									$webtarget[$pos_webtarget]["order"]=(string)$wt->order;
									$pos_webtarget++;
							}
						}
						$result["webtargets"]=$webtarget;
					}
					
					
					/* end web target */
					 
					$result["post_id"] = (string)$Element->post_id;
					$result["original_post_id"] = (string)$Element->original_post_id;
					

					//echo "<img src=\"".$imageServer.$Element->Detall->imatgeCos->path."\" alt=\"\"/>";
					//echo "<img style=\"width: auto;height : 100px;\" src=\"".$imageServer.$Element->Detall->imatgeCos->path."\" alt=\"\"/>";
					//echo "<img src=\"".$imageServer.$Element->imatge->path."\" alt=\"\"/><br/>";
					//print_r($Element->xpath("asia"));
					if (count($Element->xpath("asia"))>0){
						if ( count($Element->asia->element->children())>1){
							foreach($Element->asia->element as $asia){
								//echo "Id Asia : ".$asia->id."<br/>";
								$result["agenda_id"][] = (string)$asia->id;
							}
							if ($type=="agenda")  {
								$tmp = $this->getAgendaData($result["agenda_id"][0], (string)$Element->post_id);
								$result = array_merge($tmp,$result);
							}
							if ($type=="equipament")  {
								$tmp = $this->getEquipmentData($result["agenda_id"][0], (string)$Element->post_id);
							}
							
							//$AsiaIDExists = true;
							if ($tmp!=null) $result["isactive"] = true;
							//echo "else 1<br/>\n";
						} else {
							//echo "Id Asia : ".$Element->asia->element->fitxa->body->id."<br/>";
							$result["agenda_id"][] = (string)$Element->asia->element->fitxa->body->id;
							$entity_id = (string)$Element->asia->element->fitxa->body->id;
							if ($type=="agenda")  {
								$tmp = $this->getAgendaData($entity_id, (string)$Element->post_id);
								$result = array_merge($tmp,$result);
							}
							if ($type=="equipament")  {
								$tmp = $this->getEquipmentData($entity_id, (string)$Element->post_id);
							}							
							
							if ($tmp!=null) $result["isactive"] = true;
							//$AsiaIDExists = true;
							
							//echo "else 2<br/>\n";
							//$attributes = $Element->asia->element->fitxa->body->attributes();
							//echo "idioma: ".$attributes["idioma"]."<br/>";
						}
					}
					//if ($i==5 && $AsiaIDExists == false) {
					//	echo "No hay ID ASIA en el idioma principal CATALAN.";
					//	return false; 
					//}
					$item[$idioma][$i] = $result;
					$i++;
				}
				$this->tot[$idioma]=$i-1;
			}
			
			foreach($idiomes as $idioma) if ($this->tot[$idioma]==-1) return false;
			return $item;
		}
		/**
		 * Borra el contenido de las tablas donde guardamos la agenda recomendada
		 *
		 */
		public function EmptyAllTables($type = "agenda"){
			if ($type=="agenda") {
				$this->query("delete from esf_post_webtarget where post_type = 'agenda';");
			
				$this->query("truncate table agrecomcanals;");
				$this->query("truncate table agrecomentity_id;");
				$this->query("truncate table agrecomtxt;");
				$this->query("truncate table agrecom;");
			}
			//$this->query("truncate table agcanaltxt;");			
		}
		/**
		 * Crea la principal información partiendo del catalan.
		 *
		 * @param unknown_type $item
		 */
		public function AddCatalan($item){
			// Catala is the main language
			//$this->Debug=1;
			//print_r($item[1]);
			$result = "";
			foreach($item[1] as $recom){
				if($recom["isactive"]==true) {
				if ($recom["tema"]!=null) $recom["tema"]="'".$this->str2SQL($recom["tema"])."'";else $recom["tema"]="NULL";
				if ($recom["begindate"]!="null") $recom["begindate"]="'".$recom["begindate"]."'";
				if ($recom["begindate"]=="''") $recom["begindate"]="null";
				if ($recom["enddate"]!="null") $recom["enddate"]="'".$recom["enddate"]."'";
				if ($recom["enddate"]=="''") $recom["enddate"]="null";
				if ($recom["institutionname"]!="null") {
					if (array_key_exists("sectionname",$recom)) $recom["institutionname"] = $recom["sectionname"]." - ".$recom["institutionname"];
					$recom["institutionname"]="'".$this->str2SQL($recom["institutionname"])."'";
				}
				if ($recom["institutionname"]=="''") $recom["institutionname"]="null";
				if ($recom["equipment_id"]!="null") $recom["equipment_id"]="'".$recom["equipment_id"]."'";
				if ($recom["equipment_id"]=="''") $recom["equipment_id"]="null";
				if ($recom["gmapx"]=="") $recom["gmapx"]="null";
				if ($recom["gmapy"]=="") $recom["gmapy"]="null";
				//$this->Debug=1;

				if ($this->query("insert into agrecom (data,imatge,imatgecos,begindate,enddate,institutionname,gmapx,gmapy,equipment_id) values ('".$recom["data"]."','".$recom["imatge"]."','".$recom["imatgecos"]."',".$recom["begindate"].",".$recom["enddate"].",".$recom["institutionname"].",".$recom["gmapx"].",".$recom["gmapy"].",".$recom["equipment_id"].") ;")){
					$recom_id=$this->last_insert_id();
					if (array_key_exists("agenda_id",$recom))
						foreach($recom["agenda_id"] as $agenda_id){
							if ($this->query("insert into agrecomentity_id (entity_id,recom_id,entity_type) values ($agenda_id,$recom_id,'AG') ;")){
							} else { $result .="error SQL AddCatalan : ".$recom["titol"];/*return $result;*/}
						} //foreach
					if (array_key_exists("canals",$recom))
						foreach($recom["canals"] as $canal){
							if ($this->query("insert into agrecomcanals (recom_id,canal) values ($recom_id,'$canal') ;")){
								//$this->query("insert ignore agcanaltxt (canal, language_id, txt_canal) values ('$canal','1','$canal')");
							} else { $result .="warning : SQL AddCatalan - Canal duplicated for same id<br/>\n";/*die;*/}
						} //foreach	
											
					// start webtarget 
						
					if (array_key_exists("webtargets",$recom))
						
						foreach($recom["webtargets"] as $wtitem){
						
						if ($this->query("insert into esf_post_webtarget (txt_webtarget, post_id, recom_id, numordre, post_type) values ('".$wtitem["id"]."',".$recom["original_post_id"].",$recom_id,".$wtitem["order"].",'agenda') ;")){
								//$this->query("insert ignore agcanaltxt (canal, language_id, txt_canal) values ('$canal','1','$canal')");
						} else { $result .="warning : SQL AddCatalan - adding esf_post_webtarget $recom_id<br/>\n";/*die;*/
						}
						
					} //foreach
						
					// end web target 

					// save post xml			
					
					$urlPost = "http://noticies.bcn.cat/api/detall.php?id_doc=".$recom["original_post_id"]."&media=n&lg=ca";
					file_put_contents("data/post_".$recom["original_post_id"]."_ca.xml",file_get_contents($urlPost));
					
					// end post xml
					
					if (array_key_exists("urlvideo",$recom)) $urlvideo = "'".$recom["urlvideo"]."'";else $urlvideo= "null";
					if ($this->query("insert into agrecomtxt (recom_id, language_id, titol, resum, texte,urlvideo,tema) values ($recom_id,1,'".$this->str2SQL($recom["titol"]) ."','".$this->str2SQL($recom["resum"])."','".$this->str2SQL($recom["texte"])."',$urlvideo,".$recom["tema"].") ;")){
					} else { $result .="error SQL AddCatalan 1";return $result;}

				} else { $result .="error SQL AddCatalan 2";return $result;}
				} // if			
				} // for each
				return $result;
		}
		/**
		 * Enter description here...
		 *
		 * @param unknown_type $item
		 */
		public function AddOtherLanguages($item){
			// Spanish and english depends on Catalan
			$result = "";
			for ($i=2;$i<4;$i++){
				foreach($item[$i] as $recom){
					if($recom["isactive"]==true) {
					if ($this->query("select recom_id from agrecomentity_id where entity_id = ".$recom["agenda_id"][0].";")){
						if ($this->num_rows()>0){
							$this->next_record();
							if (array_key_exists("urlvideo",$recom)) $urlvideo = "'".$recom["urlvideo"]."'";else $urlvideo= "null";
							if ($recom["tema"]!=null) $recom["tema"]="'".$this->str2SQL($recom["tema"])."'";else $recom["tema"]="NULL";
							$sqlTmp = "insert into agrecomtxt (recom_id, language_id, titol, resum,texte,urlvideo,tema) values (".$this->Record["recom_id"].",$i,'".$this->str2SQL($recom["titol"]) ."','".$this->str2SQL($recom["resum"])."','".$this->str2SQL($recom["texte"])."',$urlvideo,".$recom["tema"].");";
							if ($this->query($sqlTmp)){
							} else {
								if (stripos($this->Error,"primary")!==false){ 
								} else $result.= "<br/>Error : ".$this->Error." - SQL AddOtherLanguages Insert agrecomtxt ID ".$this->Record["recom_id"]." ".$recom["titol"]."<br/>\n$sqlTmp<br/>\n";
								
							}
							 
							// save post xml
							if($i==2) $lang="es";
							if($i==3) $lang="en";	
							$urlPost = "http://noticies.bcn.cat/api/detall.php?id_doc=".$recom["original_post_id"]."&media=n&lg=".$lang;
							file_put_contents("data/post_".$recom["original_post_id"]."_$lang.xml",file_get_contents($urlPost));
								
							// end post xml
						}
					} else { $result.= "error SQL AddOtherLanguages Agenda ID : ".$recom["agenda_id"][0];}
				}
			  } // for each
			}
			return $result;
		}
		/**
		 * Devuelve el id del tema
		 *
		 * @param unknown_type $txttema
		 * @return unknown
		 */
		private function GetTema($txtTema){
			$strExcluded = array("HOME","HOME_","CANAL BCN","AGENDA","DIARY","PàGINA PRINCIPAL");
			//strtoupper(iconv('UTF-8', 'US-ASCII//TRANSLIT', $txtTema));
			if (array_search(strtoupper($txtTema),$strExcluded)===FALSE) return $txtTema;

		 else return null;
		}
		/**
		 * Retorna agendes o equipaments per wtarget amb ordre
		 * @param String $wtarget
		 * @param String $canal es la categoria de wp. no es el canal ASIA.
		 * @param Integer $from
		 * @param Integer $rows
		 * @param String $classificacion Code de classifications
		 * @return Array Result
		 */
		function getAgendaByWtarget($wtarget, $canal,$from = 0, $rows = 10, $classificacion = null, $type="AG"){
			
			//ini_set("display_errors", true);
			//$this->Debug=true;
			
			
			$joinCanal = "";
			$joinWt = "";
			$strWhere = "";
			$strColumns = "";
			$orderBy = "order by recom_id";
			
			if ($classificacion!=null && $classificacion!="") {
				$classificacion = str_replace("?","_",$classificacion);
				$classificacion = str_replace("*","%",$classificacion);
				$operator = "=";
				if (strpos($classificacion, '%') !== FALSE || strpos($classificacion, '_') !== FALSE) $operator = "like"; 
				$joinWt .= " inner join properties p on p.entity_id = e.entity_id";			
				$strWhere .= " and p.code $operator '".$classificacion."'";				
			}
			// canal es la categoria de wp, no es el canal de ASIA
			if (isset($canal) && $canal!="") {
				$joinCanal .= " left join agrecomcanals c on c.recom_id = ag.recom_id
				left join agcanaltxt ct on c.canal = ct.canal and ct.language_id = '"._LANGUAGE."'";
				$strWhere .= " and c.canal = '".strtoupper($canal)."'";
			}
			
			if (isset($wtarget) && $wtarget!="") {
				if ($type=="AG") {
					$joinWt .= " left join esf_post_webtarget wt on ag.recom_id = wt.recom_id";
					$post_type = "agenda";
					$orderBy = "order by numordre, recom_id asc";
				}
				if ($type=="EQ") {
					$joinWt .= " left join esf_post_webtarget wt on eq.entity_id = wt.entity_id";
					$post_type = "equipament";
					$orderBy = "order by numordre asc";
				}
				$strWhere .= " and wt.txt_webtarget = '".$wtarget."' and post_type = '$post_type'";
				
				$strColumns = ", wt.post_id ";
			}
			$strSQL = "";
			if ($type=="AG"){				
				$strSQL = "select SQL_CALC_FOUND_ROWS  distinct id.entity_id id, ag.recom_id, imatgeCos, imatge, titol, resum, texte, urlvideo, begindate, enddate, institutionname, gmapx, gmapy, equipment_id, e.entity_type,e.entity_id noexist $strColumns
					from agrecom ag
					inner join agrecomtxt txt on ag.recom_id = txt.recom_id
					$joinCanal
					inner join agrecomentity_id id on id.recom_id = ag.recom_id
					inner join entity e on e.entity_id = id.entity_id
					$joinWt
					where txt.language_id = "._LANGUAGE." $strWhere $orderBy limit $from,$rows;";				
			}elseif($type=="EQ"){
				$strSQL = "select SQL_CALC_FOUND_ROWS  distinct eq.entity_id id, institutionname as titol, institutionname, sectionname, sigla, e.entity_type, 0 as gmapx, 0 as gmapy $strColumns
				from equipment eq				
				inner join entity e on eq.entity_id = e.entity_id
				$joinWt
				where eq.language_id = 1 $strWhere $orderBy limit $from,$rows;";
				
			} 		
			
			$this->query($strSQL);		
			
			$return["found"] = $this->found_rows();
			$return["list"] = $this->select_array();
			
			return $return;			
		}
		/**
		 * Añade los registro de WP a GUIA de equipaments en los idiomas definidos.
		 *
		 * @param unknown_type $item
		 */
		public function AddEquipments($item){
			// Catala is the main language
			//$this->Debug=1;
			//print_r($item[1]);
			$result = "";
			foreach($item as $lg=>$itemLang){
			foreach($itemLang as $recom){
				if($recom["isactive"]==true) {

					//$this->Debug=1;
					$entity_id = "null";
					if (array_key_exists("agenda_id",$recom))
						foreach($recom["agenda_id"] as $agenda_id){
					       $entity_id = $agenda_id;
						}
					//foreach
						
					// start webtarget

					if (array_key_exists("webtargets",$recom) && $lg==1)
						foreach($recom["webtargets"] as $wtitem){
						if ($this->query("insert into esf_post_webtarget (txt_webtarget, post_id, entity_id, numordre, post_type) values ('".$wtitem["id"]."',".$recom["original_post_id"].",$entity_id,".$wtitem["order"].",'equipament') on duplicate key update numordre = ".$wtitem["order"].",entity_id = $entity_id ;")){
							//$this->query("insert ignore agcanaltxt (canal, language_id, txt_canal) values ('$canal','1','$canal')");
						} else { $result .="warning : SQL AddCatalan - adding esf_post_webtarget $entity_id<br/>\n";/*die;*/
						}

					} //foreach

					// end web target

					// save post xml
					if($lg==1) $lang="ca";
					if($lg==2) $lang="es";
					if($lg==3) $lang="en";
					$urlPost = "http://noticies.bcn.cat/api/detall.php?id_doc=".$recom["original_post_id"]."&media=n&lg=".$lang;
					file_put_contents("data/post_".$recom["original_post_id"]."_$lang.xml",file_get_contents($urlPost));
						
					// end post xml
				} // if active
			

			} // for each
			} // for each
				
			return $result;
		}
		/***************************************END CLASS*****************************************************/
	}
	?>