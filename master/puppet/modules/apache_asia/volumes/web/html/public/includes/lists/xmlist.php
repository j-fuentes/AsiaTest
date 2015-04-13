<?php
/**
 * Guia de Barcelona - Agenda and Directory
 *
 * This file is part of Guia Barcelona v1.0.0
 * @author Elazos Software Factory
 **/

/**
 * XML List class.
 * Returns a xml table list/grid from an array of columns.
 */
/**
 * Class Utils file.
 * Class Session extends class Utils.
 */
require_once("ctrl/utils.class.inc");
require_once("includes/search.class.inc");
require_once("includes/classification.class.inc");
/**
 * Returns a xml table list/grid from an array of columns.
 *
 */
class xmllist extends utils {

	var $html_out = "";
	//var $totRecords = 0;
	var $selFacets;
	var $rowsperpage = array("10","20","30","50","100");

	/**
	 * Returns a xml table list/grid from an array of columns.
	 * The array layout is list[row_num][fieldname]=fieldvalue and List[0][field_name]=fieldname.
	 * Includes page information like found items, current page number, next and previous links.
	 * Returns xml into the class var html_out.
	 * Node structure <list><found/><lst_info><pags><pag href=""><next href=""><prev href="">...
	 * @author Elazos Software Factory
	 * @access public
	 * @param array   array[row_num][fieldname]=fieldvalue
	 * @param integer initial row number within the sql query, needed to link with next & previous page
	 * @param integer Number of rows to show
	 * @param string current page name for links (Not used, Pending to delete)
	 * @param string edit page name & parameter for links Ex: "pg=edtpage&id="
	 * @param string Parameter to delete row Ex: "id_to_del="
	 * @param integer Variables to pass through Ex : "view=$view&id_account=$id_account"
	 */
	function xml_list( $list, $from, $num_rows, $pagina, $edt_pagina, $borrar, $vars,$found_rows = Null,$fields = Null, $sortField = Null) {

		$this->html_out = "";
		$next=$from+$num_rows;
		$previous=$from-$num_rows;
		$total=count($list)-1;
		$col_num=count($list[0])-1;
		if (isset($borrar)) $col_num++;
		//if (isset($this->vars["pg"])) $pagina="pg=".$this->vars["pg"]; else $pagina="";
		if($vars!=null && $vars!="") $vars = $vars."&nr=$num_rows";
		else $vars = "nr=$num_rows";

		$this->html_out .= "<list>";



		if (isset($found_rows)) {
			if ($from==0) $tmpFrom = 1; else $tmpFrom = $from;
			if ($num_rows>$found_rows) $tmpTo = $found_rows; else $tmpTo = ($from+$num_rows);
			$this->html_out .= "<found from=\"$tmpFrom\" to=\"$tmpTo\" total=\"$found_rows\" vis=\""._DISPLAYING."\" al=\""._TO."\" de=\""._OF."\" results=\""._RESULTS."\"/>";
		}

		$this->html_out .="<lst_info>";
		$pages_lnks="";
		$current=1;
		if($found_rows>$num_rows){
			$pages_lnks .= "<pags>";
			$z=0;
			for ($i=0;$i<$found_rows;$i=$i+$num_rows){
				if ($from>=($i-($num_rows*5)) && $from<=($i+($num_rows*5))){
					//if ($z>0) $pages_lnks .="-";
					if ($from==$i) {$current=($i/$num_rows+1);$pages_lnks .= "<pag>".($i/$num_rows+1)."</pag>";}
					else $pages_lnks .= "<pag href=\"".LK_PAG."".$this->url_encrypt("$pagina&from=$i&$vars")."\">".($i/$num_rows+1)."</pag> ";
					$z++;
				}
			}
			if ($from>0) $pages_lnks .= "<prev href=\"".LK_PAG."".$this->url_encrypt("$pagina&from=$previous&$vars")."\">"._PREVIOUS."</prev>";
			//if ($from>0 && $found_rows>$next) $pages_lnks .=" - ";
			if ($found_rows>$next) $pages_lnks .= "<next href=\"".LK_PAG."".$this->url_encrypt("$pagina&from=$next&$vars")."\">"._NEXT."</next>";
			$pages_lnks .= "</pags>";

			$this->html_out .= $pages_lnks;
		}
		//Sorting
		if ($sortField!=null) {
			if (is_array($sortField)) $SortFieldSelected = "selected=\"".$sortField[0]."\"";
			else $SortFieldSelected = "selected=\"none\"";
			$this->html_out .= "<sort $SortFieldSelected label=\""._SORTBY."\">"
			//."<lastupdatedate href=\"".LK_PAG."".$this->url_encrypt("$pagina&from=0&$vars&sort=lastupdatedate,desc")."\">"._LATEST."</lastupdatedate>\n"
			."<popularity href=\"".LK_PAG."".$this->url_encrypt("$pagina&from=0&$vars&sort=popularity,desc")."\">"._POPULARITY."</popularity>\n"
			."<namesort href=\"".LK_PAG."".$this->url_encrypt("$pagina&from=0&$vars&sort=namesort,asc")."\">"._ALPHA."</namesort>\n";
			$this->html_out .= "</sort>\n";
		}
		//end Sorting
		// numrows
		$tmpHref = $this->DropVarUrl("$pagina&$vars","nr");
		$this->html_out .= "<numrows href=\"".LK_PAG."".$this->url_encrypt($tmpHref)."\" name=\""._NUMROWS."\" selected=\"$num_rows\">";

		foreach($this->rowsperpage as $rpp){

			$selected = "";
			if ($rpp==$num_rows) $selected="selected=\"selected\"";

			$this->html_out .= "<option $selected value=\"$rpp\">$rpp "._NUMROWS."</option>\n";
		}
		$this->html_out .= "</numrows>\n";
		//Pages found, previous position next
		$this->html_out .= "<label>"._PAGS."</label><current>$current</current><total>"._OF." ".ceil($found_rows/$num_rows)."</total>";
		$this->html_out .="</lst_info>";
		//End Pages found, previous position next
		// Lista de nombres de campos en la pos 0
		$this->html_out .="<list_items>";
		if ($fields) {
			//$z=false; // sirve para controla que la 1a columna no se visualize
			$this->html_out .="<cols>";
			foreach($fields as $value){
				//if ($z) 
					$this->html_out .= "<$value>".constant(strtoupper("_$value"))."</$value>";
				//else $z=true;
			}
			$this->html_out .="</cols>";
		}
		// fin lista nombres de campos
		// Lista elementos
		$this->html_out .= $this->row2xml($list, $total,$edt_pagina);
		// end lista elementos
		$this->html_out .="</list_items>";
		$this->html_out .= "</list>";
		return $this->html_out;
	}
	/**
	 * Enter description here...
	 *
	 */
	public function row2xml($list,$total, $edt_pagina){

		$out = "";
		$i=0;
		while ($i<=$total){
			//print_r($list[$i]);
			if (is_object($list[$i]))
			$row = search::prepareRow(get_object_vars($list[$i]));
			else
			$row = search::prepareRow($list[$i]);			
			
			if (array_key_exists("pos",$row))
			$out .="<row pos=\"".$row["pos"]."\" num=\"".($i+1)."\">";
			else
			$out .="<row num=\"".($i+1)."\">";

			//$ln=$i % 2;
			$tmp="";
				
			foreach($row as $key=>$value){
				$strValue = "";
				//if ($key=="code_postwt") continue;
				if ($key=="stringnode") $strValue = $row[$key];
					else $strValue = "<![CDATA[".$row[$key]."]]>";
				$label2="";
				if($key=="begindate") $label2="label2=\""._DATE."\"";
				if ($key=="equipment_id") {
					$label2 = "href=\"".$this->getPermalink(strip_tags($row["institutionname"]),$edt_pagina.$value)."\"";
				}
				if ($key=="stringnode") $tmp.=$strValue;
				else {
					if (is_array($value)){
						$strValue = "";						
						foreach($value as $valueItem){
							if($key=="code_prop" || $key=="code0" || $key=="code1" || $key=="code2" || $key=="code3" || $key=="code4"){ 
								$itemAtt = 'code="'.$valueItem.'" tree_id="'.substr($valueItem,2,3).'"';
							} else $itemAtt = "";
							$strValue .= "<item $itemAtt><![CDATA[".$valueItem."]]></item>";						
						}
					} 
					$tmp .="<$key $label2 label=\"".constant("_".strtoupper($key))."\">$strValue</$key>\n";
				}

			}
			
			if (array_key_exists("sectionname",$row)) {
	   			$FullName = $row["sectionname"]." - ".$row["name"];
			} else {
	   			$FullName = $row["name"];
			}	

			if (array_key_exists("code_postwt",$row)) {
				global $wtarget;
				foreach($row["code_postwt"] as $post){
				   $wt = explode(",",$post);
				   if($wt[1]==$wtarget)	{
				   	  $wp_content =file_get_contents("data/post_".$wt[0]."_"._IDIOMA.".xml");
				   	  if ($wp_content!==false) $tmp.= $wp_content; 
				   }
				   
				}
				$tmp.= "<wt>$wtarget</wt>";
				
			}
				
			$href = $this->getPermalink(strip_tags($FullName),$edt_pagina.$row["id"]);
			$out .= "<item href=\"$href\">";
			$out .= "$tmp";
			$out .= "</item>";
			$i=++$i;
			$out .="</row>";
		}

		return $out;
	}


	/**
	 * Enter description here...
	 *
	 * @param unknown_type $list
	 * @param unknown_type $href
	 */
	function facetlist($list,$queries,$href,$TotalRecords,$rows, $trees){
			
		$SelectedFacets = $this->selFacets;
		$order = array("type","code_comarca","code_tit", "d", "ticket", "p", "districtstr", "barristr","code_info","code0","code1","code2","code3","code4","code5");


		$list = array_merge(get_object_vars($list),$this->GetFacetQueries($queries));

		
		foreach($order as $sortkey){
			if (array_key_exists($sortkey,$list))
			$tmp[$sortkey] = $list[$sortkey];
		}
		$list = $tmp;
		//$this->selFacets=SelectedFacets;
		$href = $href."&nr=$rows";
		if ($SelectedFacets==null) $SelectedFacets = array(0);

		//$this->totRecords = $TotalRecords;
		$this->html_out = "";
		$this->html_out .="<facetlist label=\""._FILTERS."\">";

		
		foreach($list as $key=>$value){
			$strKey = $key;
			if (substr($key,0,strlen($key)-3)=="class") $strKey = "class";
			if (substr($key,0,strlen($key)-1)=="code") $strKey = "code";

			switch($strKey){
				case "barristr":
				case "districtstr":
				case "code_comarca":
					$this->getDefault($key, $value, $SelectedFacets,$href);
					break;
				case "code":
					//$this->getClass($value, $SelectedFacets,$href);									
					$this->getCode($key, $value, $SelectedFacets,$href,$trees);
					break;
				default:					
					$this->getDefault($key, $value, $SelectedFacets,$href,true);
					break;
			}
		}
		$this->html_out .="</facetlist>\n";
		return $this->html_out;
	}
	/**
	 * Transform facet queries as a facet list.
	 *
	 * @param unknown_type $queries
	 * @return array facetlist
	 */
	private function GetFacetQueries($queries){
		$vars = array();
		foreach($queries as $strFacet=>$intFacet){
			if ($intFacet>0) {
				$tmpvars = explode("_",$strFacet);
				$vars[$tmpvars[0]][$tmpvars[1]]=$intFacet;
			}
		}
		return $vars;
	}
	/**
	 * Enter description here...
	 *
	 * @param unknown_type $key
	 * @param unknown_type $value
	 * @param unknown_type $SelectedFacets
	 */
	private function getDefault($key, $value, $SelectedFacets,$href,$translate = false){
		
		if (is_a($value,"SolrObject")) {
			$value = get_object_vars($value);			 
			$num = count($value);			
		} else {
			$num = count($value);
		}
		$nameKey = $key;
		//echo $key;print_r($value);
		$isSelected = array_key_exists($key,$SelectedFacets);
		if ($isSelected) {
			$href = $this->DropVarUrl($href,$key);
			if ($translate) $name = constant(strtoupper("_".$SelectedFacets[$key]));
			else  $name = $SelectedFacets[$key];
		}
		
		if ($num>0) {
			
			$this->html_out .="<$key name=\"".constant(strtoupper("_$key"))."\">";

			if ($isSelected)
			$this->html_out .= "<back name=\"$name\" label=\""._DROPFILTER."\" href=\"".LK_PAG.$this->url_encrypt($href)."\"/>\n";
			else {
				
				if ($key == "districtstr") ksort($value);
				foreach($value as $strFacet=>$intFacet){
					$code = "code=\"$strFacet\"";
					if ($isSelected or $num == 1) $link = "";					
					else $link = "href=\"".LK_PAG.$this->url_encrypt($href."&$key=".$strFacet)."\"";
					if ($translate)   $strFacet =  constant(strtoupper("_$strFacet"));
					$this->html_out .= "<item $code name=\"$strFacet\" $link>";
					$this->html_out .= $intFacet;
					$this->html_out .= "</item>\n";

				}
			}
			$this->html_out .="</$key>\n";
		}
	}
	/**
	 * Enter description here...
	 *
	 * @param unknown_type $key
	 * @param unknown_type $value
	 * @param unknown_type $SelectedFacets
	 * @param unknown_type $href
	 */
	private function getCode($key, $value, $SelectedFacets,$href,$tree_id_list){
		//echo "$key\n";
		//print_r($SelectedFacets);
		//print_r($value);
		$tree = array();
		if($tree_id_list!=""){
			$tree = explode(",",$tree_id_list);			
		}		
		//$tree[0] = "400";
		//$tree[1] = "401";
		
		$class = new classification;
		$allTctCodes = $class->getAllClassDesc();
		$level =  substr($key,4,1)-1;
		
        
		if(array_key_exists("code$level",$SelectedFacets)){
			$tctcodes[0] = $class->getClassLevel($SelectedFacets["code$level"],_LANGUAGE);			
			$tree[0] = substr($SelectedFacets["code$level"],2,3);			
			if ($tree[0]=="401") $nameClass[0] = _EQ; 
			if ($tree[0]=="400") $nameClass[0] = _AG; 
			if ($tree[0]!="400" && $tree[0]!="401") $nameClass[0] = $allTctCodes["ROOT"][_LANGUAGE]["00".$tree[0]."00"];
		} else {
			foreach($tree as $tree_id){
				$tctcodes[]=$class->getClassLevel("00".$tree_id."00",_LANGUAGE);				
				$i=count($tctcodes)-1;				
				if($tree_id!="400" && $tree_id!="401") $nameClass[]=$allTctCodes["ROOT"][_LANGUAGE]["00".$tree_id."00"];
				if ($tree_id=="400") $nameClass[]=_AG;
				if ($tree_id=="401") $nameClass[]=_EQ;
			}
			/*
			$tctcodes[0] = $class->getClassLevel("0040000",_LANGUAGE);
			$tctcodes[1] = $class->getClassLevel("0040100",_LANGUAGE);
			$nameClass[0] = _AG;
			$nameClass[1] = _EQ;
			*/
		}
		$value = get_object_vars($value);

		if($level==-1) $count=count($tree);else $count=1;
		for($i=0;$i<$count;$i++){
			$isResult = false;
			$out = "<class treeid=\"".$tree[$i]."\" name=\"".$nameClass[$i]."\">";
			if ($level>=0) {
				$isResult = true;
				foreach($SelectedFacets as $selkey=>$selvalue){
					if (substr($selkey,0,strlen($selkey)-1)=="code"){
						$selLevel = substr($selkey,4,1);
						$href2 = $href;
						for($y=$selLevel;$y<=7;$y++)
						$href2 = $this->DropVarUrl($href2,"code".($y));
						$nameBack  = $this->getFilterName($selkey,$selvalue);
						$out  .= "<back code=\"$selvalue\" name=\"$nameBack\" label=\""._DROPFILTER."\" href=\"".LK_PAG.$this->url_encrypt($href2)."\"/>\n";
					}
				}
				
			}		
			
			// New order

			$ArrayOut = array();
			$ArraySort = array();
			
		    foreach($value as $code=>$item){		    	
				$tmp = "";				
				if(is_array($tctcodes[$i]) && array_key_exists($code,$tctcodes[$i]) ){					
					$tmp  .= "<item code=\"$code\" name=\"".$tctcodes[$i]["$code"]."\" href=\"".LK_PAG.$this->url_encrypt($href."&$key=".$code)."\">";
					$tmp  .= $item;
					$tmp  .= "</item>\n";
					$ArrayOut[] = $tmp;
					$ArraySort[] = $tctcodes[$i]["$code"];
					$isResult = true;
				}
		    }
		   
		    asort($ArraySort);
		    foreach($ArraySort as $SortKey=>$SortValue){
		    		$out.= $ArrayOut[$SortKey];
		    }
			// End New Order
			
			$out  .="</class>\n";
			if ($isResult) $this->html_out .= $out;
		}
	}
	/**
	 * Returns xml to show filter an disable them
	 *
	 * @param array $selectedFilters
	 */
	public function Filters($href){
		$class = new classification;
		 
		if (count($this->selFacets)){
			$xmlout = "<filters label=\""._YOURFILTERS."\">";
			if (array_key_exists("q",$this->selFacets)) {
				$xmlout .= "<query label=\""._QUERYFILTER."\">".$this->selFacets["q"]."</query>\n";
				unset($this->selFacets["q"]);
			}
			$this->AddAllCodes($href);
			// Getting names of filters
				
			foreach($this->selFacets as $key=>$value){
				$strCode = "";
				if (substr($key,0,strlen($key)-1)=="code") {
					$strCode = "code=\"$value\"";
					$level = substr($key,4,1);
					$strhref = $href;
					for($i=$level;$i<=7;$i++)
					$strhref = $this->DropVarUrl($strhref,"code".($i));
				} else 	$strhref = $this->DropVarUrl($href,$key);
				$strvalue = $this->getFilterName($key,$value);
				if ($strvalue!="" && $strvalue!=null)
				$xmlout .= "<item filter=\"$key\" $strCode href=\"".LK_PAG.$this->url_encrypt($strhref)."\">$strvalue</item>\n";
			}
			$xmlout .= "</filters>";
			return $xmlout;
		} else return "";
	}

	/**
	 * Gets labels of the filters
	 *
	 * @param unknown_type $key
	 * @param unknown_type $value
	 * @return String Label
	 */
	private function getFilterName($key,$value){
		$class = new classification;
		$level = -1;
		if (substr($key,0,strlen($key)-1)=="code") {
			$level = substr($key,4,1);
			$key = "code";
		}

		switch($key){
			case "districtstr":
			case "code_comarca":
			case "barristr":
			case "ad":
				return $value;
				break;
			case "code":
				$class = new classification;
				$tree_id = substr($value,2,3);
				if ($level==0){
					$tctcodes = $class->getClassLevel("00".$tree_id."00",_LANGUAGE);
					return $tctcodes[$value];
				} else {
					if(array_key_exists("code".($level-1),$this->selFacets)){
						$tctcodes = $class->getClassLevel($this->selFacets["code".($level-1)],_LANGUAGE);
					} else {
						//never executes this because AddAllCodes method avoid it
						$tctcodes = $class->getClassLevel($class->GetParentCode($value),_LANGUAGE);
					}
					return $tctcodes[$value];
				}
				return $value;
				break;
			case "dt":
				$tmp = explode(",",$value);
				if (count($tmp)==1){
					$dt = new DateTime($tmp[0]);
					return $dt->format(_DATEFORMAT);
				}else{
					if ($tmp[0]==$tmp[1]){
						$dt = new DateTime($tmp[0]);
						return $dt->format(_DATEFORMAT);
					} else {
						$dt1 = new DateTime($tmp[0]);
						$dt2 = new DateTime($tmp[1]);
						return $dt1->format(_DATEFORMAT)." - ".$dt2->format(_DATEFORMAT);
					}
				}
				break;
			default:
				return constant(strtoupper("_$value"));;
				break;
		}
	}
	/**
	 * Enter description here...
	 *
	 * @param unknown_type $selectedFilters
	 * @return unknown
	 */
	private function  AddAllCodes(&$href){
		$class = new classification;
		// Add parent classifications where not found
		$maxLevel = -1;
		$countClass = 0;
		$maxCode = "";

		foreach($this->selFacets as $key=>$value){
			if (substr($key,0,strlen($key)-1)=="code") {
				$countClass++;
				$level = $class->GetLevel($value);
				if ($maxLevel<$level) {
					$maxLevel = $level;
					$maxCode = $value;
				}
			}
		}
		if ($maxLevel>$countClass) {
			for($i=($maxLevel-1);$i>0;$i--){
				$maxCode = $class->GetParentCode($maxCode);
				$this->selFacets["code".($i-1)]=$maxCode;
				$href.="&code".($i-1)."=$maxCode";
			}
		}
		ksort($this->selFacets);
	}
	/**
	 * Initialize Selected Facets/filters
	 *
	 * @param array $selectedFilters
	 */
	public function SetSelectedFacets($selectedFilters){
		$this->selFacets = $selectedFilters;
		if (array_key_exists("sort",$this->selFacets))
		unset($this->selFacets["sort"]);
	}

}
?>