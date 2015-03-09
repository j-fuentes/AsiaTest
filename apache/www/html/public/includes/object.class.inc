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
require_once("db/mysql.class.inc");
/**
 * Handles Database Objects
 *
 * @author Elazos Software Factory
 * @version 1.0
 * @package BusObj
 */
class object extends DB_Sql {

	var $mc;

	function object(){
		$this->mc = new Memcached();
		$this->mc->addServer("localhost", 11211);
	}

	/**
	 * Enter description here...
	 *
	 * @param unknown_type $id
	 * @return unknown
	 */
	public function getKeywords($id) {

		$stopwords = array("sacces","sacceso","sauto","sss","Sespectacles","Sespectacle","Swc","Swater","Stenda","Stienda","Sbotigueta","Sbotiga","Smedic", "Smedico", "Smedicos", "Smedics","scon ","samb ", "srestaurant", "srestaurante",  "svestidors", "svestidores", "svestuari", "svestuario", "senfermeria", "sinfermeria", "sbar", "ssauna");

		$this->query("select txtword from words w, wordsentity e where w.id_word = e.id_word and entity_id =  $id;");

		//$this->query("(select distinct keywords from keywords where entity_id =  $id)"
		//." UNION DISTINCT (select distinct keywords from variants v, entityvariants e where v.code = e.code and entity_id = $id)"
		//.";");

		if ($this->num_rows() > 0) {
			$keywords = $this->select_array();
			$result = array();
			foreach($keywords as $item){
				$Notfound = true;
				foreach($stopwords as $stop){
					//echo "Stop $stop - ".$item["txtword"]."";
					if(stripos($item["txtword"],$stop)!==false) {$Notfound = false; /*echo " Si <br/>";*/break;} //else echo " No <br/>";
				}
				if ($Notfound) $result[] = ucfirst(strtolower($item["txtword"]));
			}
			return array_unique(array_filter($result));
		} else
		return null;
	}
	/**
	 * Enter description here...
	 *
	 * @param unknown_type $id
	 */
	function getAddresses($id){
		$this->query("select ad.street, ad.streetnum_i,ad.streetnum_s, ad.district, ad.barri, ad.stair, ad.floor, ad.door, ad.postalcode, ad.city, ad.coordaddressx, ad.coordaddressy, c.nm_comarca as code_comarca from addresses ad " 
				."left join comarca_cp cp on ad.postalcode = cp.cpostal "
				."left join comarca c on c.id_comarca = cp.id_comarca "
				."where entity_id = $id order by address_id desc ;");
		if ($this->num_rows()>0) {
			$this->next_record_assoc();
			//$this->Record["streetnum_i"] = str_replace("*","-",$this->Record["streetnum_i"]);
			return $this->Record;
		} else return false;
	}
	/**
	 * Enter description here...
	 *
	 * @param unknown_type $id
	 * @return unknown
	 */
	function getClassification($id, $arrayTree_id, $language_id, $name){
		$strTreeIDs = "";
		if ($arrayTree_id){
			foreach($arrayTree_id as $tree_id){
				if ($strTreeIDs == "") $strTreeIDs = "c.tree_id = ".$tree_id;
				else $strTreeIDs .= " or c.tree_id = ".$tree_id;
			}
			$strTreeIDs = "(".$strTreeIDs.") and ";
		}
		$this->query("select c.code, description as class from classification c, tct_codes t where $strTreeIDs c.code = t.code and language_id = $language_id and entity_id = $id
				 union 
				select c.code, description as class from properties c, tct_codes t where $strTreeIDs c.code = t.code and language_id = $language_id and entity_id = $id;");
		if ($this->num_rows()>0) {
			$class=$this->select_array_onefield($name);
			$x = 0;
			foreach($class[$name] as $item){
				$faltan = (strlen(substr($item["code"],7,strlen($item["code"])))/3)-1;
				$result[$name][$x][$faltan]["code"]=$item["code"];
				$result[$name][$x][$faltan]["class"]=$item["class"];
				$code_ant = "";
				for($i=1;$i<=$faltan;$i++){
					if ($code_ant=="") $code = substr($item["code"],0,5)."0".$i.substr($item["code"],7+(($i-1)*3),3);
					else               $code = substr($item["code"],0,5)."0".$i.substr($code_ant,7,strlen($code_ant)).substr($item["code"],7+(($i-1)*3),3);
					$code_ant = $code;
					$this->query("select code, description as class from tct_codes where language_id = $language_id and code = $code;");
					$this->next_record_assoc();
					$result[$name][$x][$i-1]["code"]=$this->Record["code"];
					$result[$name][$x][$i-1]["class"]=$this->Record["class"];
				}
				$x++;
			}
			return $result;
		} else return false;
		// End classifications
	}
	/**
	 * Transformation from BCN Planol position to Latitud Longitud = google.
	 *
	 * @param integer $coordx
	 * @param integer $coordy
	 */
	function CoordGmap($coordx, $coordy){

		$_Tx = -131.250417839;
		$_Ty = -206.9696618318;
		$_Exy = 1.3219081270;
		$_Ang = -1.6446198;
		$_E47 = 31;
		$coordx = ($coordx+400000000)/1000;
		$coordy = ($coordy+4500000000)/1000;

		$Exy = $_Exy/1000000;
		$ang = $_Ang/3600;
		$ang = $ang*pi()/180;
		//Conversió de les coordenades a UTM ETRS89}

		$seno = sin($ang);
		$coseno = cos($ang);

		$UTMS89X = $_Tx+((1+$Exy)*($coordx*$coseno- $coordy*$seno));
		$UTMS89Y = $_Ty+((1+$Exy)*($coordx*$seno  + $coordy*$coseno));

		//Conversió de les coordenades a Geográficas ETRS89
		$a = 6378137.00000000;     //GRS80
		$b = $a*(1-0.0033528106811823189354341461261285);
		$z = $_E47;
		$x = $UTMS89X;
		$y = $UTMS89Y;

		$ep = pow((pow($a,2)-pow($b,2)),0.5)/($b);       // segunda excentricidad
		$ep2 = pow($ep,2);                                    // cuadrado de la segunda excentricidad
		$c = pow($a,2)/$b;     // ratio polar de curvatura

		$XX = $x-500000;      // eliminar retranqueo de x
		$YY = $y;

		$lon_decimal = $z*6 -183;    // meridiano central del huso
		$lat_decimal = $YY /(6366197.724 * 0.9996);
		$ni = $c * 0.9996 / pow( (1+$ep2*pow(cos($lat_decimal),2)),0.5);

		$a = $XX/$ni;
		$A1 = sin(2* $lat_decimal);
		$A2 =  $A1* pow(cos($lat_decimal),2);
		$J2 =   $lat_decimal + ($A1/2);
		$J4 =  ((3*$J2)+$A2)/4;
		$J6 =  ((5*$J4)+$A2* pow(cos($lat_decimal),2))/3;
		$alfa =  3*$ep2/4;
		$beta =  5* pow($alfa,2) /3;
		$gamma =  35 * pow($alfa,3) /27;
		$BsubZeta =  0.9996 * $c *($lat_decimal - $alfa*$J2 + $beta*$J4-$gamma*$J6);
		$b = ($YY- $BsubZeta) /$ni;
		$dseta = ($ep2*pow($a,2) * pow(cos($lat_decimal),2))/2;
		$xi =  $a*(1-($dseta/3));
		$ene =  $b*(1-$dseta)+$lat_decimal;
		$ee  =  exp(1.0);
		$sen_h_xi =  (pow($ee,$xi)-pow($ee,-$xi))/2;
		$inc_lon =  atan($sen_h_xi/cos($ene));
		$tau =  atan(cos($inc_lon)*tan($ene));
		// longitud
		$lon_sexa =    ($inc_lon/pi()*180)+ $lon_decimal;
		// latitud
		$latitud = $lat_decimal+(((1+($ep2*pow(cos($lat_decimal),2))-(3/2*$ep2*sin($lat_decimal)*cos($lat_decimal)*($tau-$lat_decimal))))*($tau-$lat_decimal));
		$lat_sexa = $latitud/pi()*180;

		$return["gmapx"]=$lat_sexa;
		$return["gmapy"]=$lon_sexa;

		return $return;

	}
	/**
	 * Return text of a URL.
	 *
	 * @param string $url
	 * @return string text of a URL
	 */
	public function getDataUrl($url)	{
		$ch = curl_init();
		$timeout = 10;
		curl_setopt($ch,CURLOPT_URL,$url);
		curl_setopt($ch,CURLOPT_RETURNTRANSFER,1);
		curl_setopt($ch,CURLOPT_CONNECTTIMEOUT,$timeout);
		$data = curl_exec($ch);
		curl_close($ch);
		return $data;
	}
	/**
	 * Devuelve la titularitat : Publica, Privada, concertada. 
	 *
	 * @param unknown_type $entity_id
	 * @return unknown
	 */
	public function getTitularitat($entity_id){
		$titularitat = "";
		$this->query("select CONCAT('0010201',SUBSTRING(CODE,8,3)) as code from properties where entity_id = $entity_id and tree_id = 102;");
		if ($this->num_rows()>0) {
			$this->next_record_assoc();
			$titularitat = $this->Record["code"];
		}
		// Si es una escuela puede ser concertada.
		$this->query("select code FROM properties where entity_id = $entity_id and tree_id = 132");
		if ($this->num_rows()>0) {
			$this->next_record_assoc();
			//$titularitat = $this->Record["code"];
			$titularitat = "0013201002";
		} 	
		return $titularitat;		
	}
	/**
	 * Enter description here...
	 *
	 * @param unknown_type $id
	 * @return unknown
	 */
	function getAdditionalInfo($id){
		$this->query("select variable_id from rel_entity_variables where entity_id = $id;");
		if ($this->num_rows()>0) {						
			while($this->next_record()) $result[]="002200".$this->Record["variable_id"];
			return $result;
		} else return false;
	}
	/**
	 * 
	 * @param unknown_type $id
	 * @return string|boolean
	 */	
	function getServeis($id,$language_id){		
		$this->query("select p.code, description from properties p left join tct_codes t on p.code = t.code where t.language_id = $language_id and p.tree_id = 110 and entity_id = $id;");
		if ($this->num_rows()>0) {
			$i=0;						
			while($this->next_record()){
				$result[$i]["code"]=$this->Record["code"];
				$result[$i]["value"]=$this->Record["description"];
				$i++;
			}
			return $result;
		} else return false;
	}
	/**
	 * Return post_id + target
	 * @param unknown_type $id
	 * @return string|boolean
	 */
	function getPostWebTarget($id){
		$this->query("select * from esf_post_webtarget wt where wt.entity_id = $id");
		if ($this->num_rows()>0) {
			$i=0;
			while($this->next_record()){
				$result[$i]=$this->Record["post_id"].",".$this->Record["txt_webtarget"];			
				$i++;
			}
			return $result;
		} else return false;
	}
	/***************************************END CLASS*****************************************************/
}


?>
