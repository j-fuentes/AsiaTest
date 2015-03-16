<?php
/**
 * Guia de Barcelona - Agenda and Directory
 *
 * This file is part of Guia Barcelona v1.0.0
 * @author Elazos Software Factory
 **/
/**
 * Class Site definition file
 * See class site documentation
 * @author Elazos Software Factory
 **/
/**
 * Class page definition file
 * Incluye el fichero de declaración de la clase page
 **/
require_once("ctrl/page.class.inc");
/**
 * Classe site extends classe page
 * Contiene la definición de la clase site que extiende la clase page. La clase site es la clase principal de la web publica.
 * Las funciones que realiza son:
 * 1. Modifica la clase page en el sentido que añade metodos especificos para la web pública.
 * 2. Basa su salida en XML a diferencia de page que basa su salida en HTML
 * 3. Debido al punto 2 realiza la transformaci�n XSL
 * @author Elazos Software Factory
 * @version 1.0
 */
class site extends page {
	/**
	 * XML output
	 *
	 * @var unknown_type
	 */
	private $xmlOutput = "";
	protected $accept;
	protected $userAgent;
	public $isMobile     = false;
	
	/**
	 * Memcached Object
	 *
	 * @var Memcached
	 */
	public $mc;

	protected $devices = array(
        "android"       => "android",
        "blackberry"    => "blackberry",
        "iphone"        => "(iphone|ipod)",
        "opera"         => "opera mini",
        "palm"          => "(avantgo|blazer|elaine|hiptop|palm|plucker|xiino)",
        "windows"       => "windows ce; (iemobile|ppc|smartphone)",
        "generic"       => "(kindle|mobile|mmp|midp|o2|pda|pocket|psp|symbian|smartphone|treo|up.browser|up.link|vodafone|wap)",
	    "exclude"       => "(ipad)"
	
        );
        /**
         * Contructor.
         * Checks device type and init memcached connection.
         * @return site
         */
        public function site(){
        	$this->DeviceCheck();
        	$this->mc = new Memcached();
        	$this->mc->addServer("localhost", 11211);
        }
        /**
         * Returns the xml output of the application
         * Is the main method called from index file. Create the xml nodes headers, footers, bleft, bright
         * and executes php files defined in navigator file
         * @author Elazos Software Factory
         * @access public
         */
        function out(){       	
        	
        	
        	if (array_key_exists("xout",$this->vars)) $xout = $this->vars["xout"];else $xout = 0;
        	if (array_key_exists("ajax",$this->vars)) $ajax=$this->vars["ajax"];else $ajax=0;

        	// html Cached - only for home
        	if (!$ajax && !$xout && $this->vars["pg"]=="home" && !array_key_exists("from",$this->vars) && ($home=$this->mc->get($this->file_xslt."_"._IDIOMA))){
        		$this->send_headers();
        		echo $home;
        		exit;
        	}
        	// end html cached

        	$path=substr($_SERVER['SCRIPT_NAME'],0,strrpos($_SERVER['SCRIPT_NAME'],"/"));

        	// create XML String to send to XSLT


        	if (!$ajax) {
        		$this->execOutput($this->block);
        		$out_string  =  $this->head();
        		if ($this->onload!="") $this->onload="onload=\"".$this->onload."\"";
        		$out_string .= "<page ".$this->onload." lang=\""._IDIOMA."\" path=\"".$path."\">\n";
         		if ($this->show_msg) $out_string.=$this->messages();
        		$out_string .=  $this->xmlOutput;
        		$out_string .= "</page>\n</html>\n";
        	} else {
        		if ($this->vars["ajax"]=="1") {        			    			
        			$this->execOutput($this->block["CENTRAL"][0]);
        		} else {        			
        			$this->execOutput(array("BLOCK" => array(array("VALUE"=>$this->vars["ajax"]))));        			
        		}
        		$out_string = "<ajax>$this->xmlOutput</ajax>";
        		 		
        		
        	}
        	// End creation of XML String to send to XSLT

        	// if we want to sent xml output
        	if ($xout) {
        		$this->charset=_CHARSET;
        		$this->send_headers();       		
        		
        		if ($xout=='json'){
        			//$array_xml = simplexml_load_string($out_string);
        			$array_xml = simplexml_load_string($out_string, 'SimpleXMLElement', LIBXML_NOCDATA);
        			header("Content-type: application/json");
        			echo json_encode($array_xml);
        			exit;
        		}
        		header("Content-Type: text/xml");
        		
        		echo $out_string;
        	} else {
        		// Starts XSLT Transformation
        		$xp = new XsltProcessor();
        		// create a DOM document and load the XSL stylesheet
        		$xsl = new DomDocument;
        		$xsl->load(_TPLDIR.$this->theme_dir.'/'.$this->file_xslt.'.xsl');
        		eval("\$xsl->getElementsByTagName('output')->item(0)->setAttribute('encoding','".$this->outputcharset."');");
        	      	
        		if (!$ajax) {
        			$xsl->documentElement->setAttribute('xmlns:fb','http://www.facebook.com/2008/fbml');
        			$xsl->documentElement->setAttribute('xmlns','http://www.w3.org/1999/xhtml');
        			
        		} 
        		// import the XSL styelsheet into the XSLT process
        		$xp->importStylesheet($xsl);
        		$xml_doc = new DomDocument;
        		
        		/* 
        		 * To check error line code on XML 
        		if (!$xml_doc->loadXML($out_string)) {
        		    $i = 1;
        			foreach(explode("\n", $out_string) as $line) {
        				if ($i==245) echo $line;
        				$i++;
        			}        			
        		}*/
       		
        		$xml_doc->loadXML($out_string);
        		$result = $xp->transformToXML($xml_doc);
        		// ends XSLT transformation

        		// Sends result to browser
        		$this->send_headers();
        		if ($result) {
        			if (!$ajax && !$xout && !array_key_exists("from",$this->vars) && array_key_exists("pg",$this->vars) && $this->vars["pg"]=="home") {
        				$this->mc->set($this->file_xslt."_"._IDIOMA,$result,(60*60));
        			}
        			if ($ajax) $result= trim(substr($result, strpos($result,">")+1));
        			echo $result;
        		}else echo $msg_error;
        		// end send results to browser
        	}

        	// For develpopment or Debugging purpose send XML output to file
        	if (defined("_XMLOUTPUT2FILE") && _XMLOUTPUT2FILE==true) {
        		$handle = fopen(realpath(_TPLDIR)."/".$this->theme_dir."output.xml", "wb");
        		fwrite($handle,$out_string);
        		fclose($handle);
        	}
        }
        /**
         * Returns a html table with all messages saved during execution.
         * This method is the same of class page but returning xml.
         * To add a message you have to use method add_message of page class.
         * Returns xml into the class var html_out.
         * @author Elazos Software Factory
         * @access private
         */
        function messages(){
        	$out_string="";
        	$out_string .= "<msg>";
        	if (is_array($this->vars_ste) && $this->vars_ste && count($this->vars_ste)>1) {
        		reset($this->vars_ste);
        		$out_string .= "<position>";
        		while (list($key,$msg)=each($this->vars_ste)){
        			if (isset($msg["nm"])) $name=$msg["nm"];else $name=constant(strtoupper("_".$msg["pg"]));
        			if ($msg["pg"]!=$this->vars["pg"] && isset($msg["url"]))
        			{if ($msg["url"]!="") $out_string .= "<pos href=\"".LK_PAG.htmlspecialchars($this->DropVarUrl($msg["url"],"ajax"))."\">$name</pos>";
        			else $out_string .= "<pos href=\"".LK_HOME."\">$name</pos>";}
        			else $out_string .= "<pos>".$name."</pos>";
        		}
        		$out_string .= "</position>";
        	}

        	reset($this->page_msg);
        	if ($this->page_msg){
        		$out_string .= "<alerts>";
        		while (list($key,$msg)=each($this->page_msg))
        		$out_string .= "<msg>"._MSG." : $msg</msg>";
        		$out_string .= "</alerts>";
        	}
        	$out_string .= "</msg>";
        	return $out_string;
        }
        /**
         * Returns xml that represents page title with menu options.
         * @author Elazos Software Factory
         * @access public
         * @param string Title of the page
         * @param bool Enables back button. True is enabled, false no.
         * @param array Menu options in the following format array[#option][action]. Option is numeric sequence.
         * Action can be "href"(page vars non encripted), "confirm"(creates a popup when clic),"print"(create a hp for printing page),
         * and "popup"(includes a target blank on anchor).
         */
        function pgtitle($title,$back=True, $links=NULL){
        	if ($this->pg_title) {
        		$out  = "<pgtitle>";
        		$out .= "<title>$title</title>";
        		$out .= "<options>";
        		if ($back) {
        			if (isset($this->vars_ste)) $state=$this->vars_ste; else $state=Null;
        			$num=count($state);
        			//print_r($state);
        			if (is_array($state) && array_key_exists($num-2,$state))
        			{ if ($state[$num-2]["url"]!="")  $go=LK_PAG.htmlspecialchars($state[$num-2]["url"]);else $go=LK_HOME;}
        			else $go="javascript:history.go(-1)";
        			$out .= "<back href=\"$go\">"._BACK."</back>";
        		}
        		if (is_array($links))
        		foreach ($links as $lnk) {
        			$onclick=false;$target=false;$link_pag="".LK_PAG."";$url="";
        			if (array_key_exists("popup",$lnk)) {$target="target=\"_blank\"";$link_pag=$lnk["popup"];}
        			if (array_key_exists("confirm",$lnk)) $onclick="onclick=\"return confirm('".$lnk["confirm"]."')\"";
        			if (array_key_exists("print",$lnk)) {$lnk["href"]=$this->rev_parse_str($this->vars)."&prt="._NAVPRT;$target="target=\"_blank\"";
        			$link_pag=LK_PAG;}
        			if (array_key_exists("href",$lnk)) $url=$this->url_encrypt("".$lnk["href"]."");
        			$out .= "<item href=\"$link_pag$url\"";
        			if ($target)$out .= " $target";else $out .= " target=\"_self\"";
        			if ($onclick) $out .= " $onclick"; else  $out .= " onclick=\"\"";
        			$out .= ">".$lnk["txt"]."</item>";
        		}
        		$out .= "</options></pgtitle>";
        		return $out;
        	} else return "";
        }
        /**
         * Returns xml that represents an hyperlink (html link)
         * @author Elazos Software Factory
         * @access public
         * @param string href or Link
         * @param string label of the hyperlink
         * @param string CSS class name
         * @param boolean if true encrypts link
         */
        function link($link, $txt, $class=null,$enc=true, $externa = false){
        	if (isset($class)) $class="class=\"$class\""; else $class="";
        	if (!$externa) {
        		if ($enc) $enc="".$this->url_encrypt("".$link."&nm=$txt")."";else $enc=$link;
        		if ($enc=="") $enc="".LK_HOME."";else $enc="".LK_PAG."".$enc."";
        	} $enc = $externa.htmlspecialchars($link);

        	return "<link $class href=\"".$enc."\">".$txt."</link>\n";
        }
        /**
         * Return the header section of the xml output.
         * returns also the html header of the page within the xml. This is because does affect to XSL transformation.
         * It uses many class vars, like charset, etc...
         * @author Elazos Software Factory
         * @access private
         * @return string xml generated by this method
         */
        function head(){
        	//$out_string = "";
        	$this->charset=_CHARSET;
        	$out_string  = "<?xml version=\"1.0\" encoding=\"".$this->charset."\"?>\n";
        	$out_string .= "<html>\n";
        	$out_string .= "<head>\n";
        	
        	if ($this->pagedesc=="") $this->pagedesc = _SITEDESC;
        	
        	if (strlen($this->pagetitle)==0){
        		$out_string .= "<title>"._SITENAME." - "._SITEOWNER."</title>\n";
        		$out_string .= "<meta name=\"title\" content=\""._SITENAME." - "._SITEOWNER."\"/>";        		
        	} else {
        		$out_string .= "<title>".$this->pagetitle." - "._SITENAME."</title>\n";
        		$out_string .= "<meta name=\"title\" content=\"".$this->pagetitle." - "._SITENAME."\"/>";
        	}
        	//$out_string .= "<meta http-equiv=\"content-type\" content=\"text/html; charset=".$this->charset."\"/>\n";

        	$out_string .= "<meta http-equiv=\"CONTENT-LANGUAGE\" content=\""._IDIOMA."\"/>";
        	$out_string .= "<meta http-equiv=\"EXPIRES\" content=\"0\"/>\n";
        	$out_string.=  "<meta name=\"RESOURCE-TYPE\" content=\"DOCUMENT\"/>\n";
        	$out_string .= "<meta name=\"DISTRIBUTION\" content=\"GLOBAL\"/>\n";
        	$out_string .= "<meta name=\"AUTHOR\" content=\""._SITEOWNER."\"/>\n";
        	$out_string .= "<meta name=\"COPYRIGHT\" content=\"Copyright (c) ".date("Y")." by "._SITEOWNER."\"/>\n";
        	$out_string .= "<meta name=\"KEYWORDS\" content=\"".$this->keywords._KEYWORDS."\"/>\n";
        	$out_string .= "<meta name=\"DESCRIPTION\" content=\"".$this->pagedesc."\"/>\n";
        	$out_string .= "<meta name=\"ROBOTS\" content=\"INDEX, FOLLOW\"/>\n";
        	$out_string .= "<meta name=\"REVISIT-AFTER\" content=\"1 DAYS\"/>\n";
        	$out_string .= "<meta name=\"RATING\" content=\"GENERAL\"/>\n";
        	$out_string .= "<meta name=\"GENERATOR\" content=\"Copyright ".date("Y")." by "._SITEOWNER."\"/>\n";

        	$out_string .= "</head>\n";
        	return $out_string;
        }
        /**
         * Execute php files depending on nav2.xml structure and return a xml text content
         *
         * @param unknown_type $tree
         */
        function execOutput($tree){
        	if (is_array($tree)) {
        		foreach($tree as $key=>$value){
        			switch($key){
        				case "BLOCK":
        					$this->xmlOutput .= $this->exec_blocks($value);
        					break;
        				case "COPY":
        					$this->xmlOutput .= $this->exec_copy($value);
        					break;
        				case "MNU":
        					$this->xmlOutput .= $this->mnuOutut($value);
        					break;
        				case "HOME_CENTRAL":
        					$this->xmlOutput .= $this->exec_blocks($value);
        					break;
        				default:
        					if (is_array($value)) {
        						$this->xmlOutput .= "<".strtolower($key).">";
        						$this->execOutput($value[0]);
        						$this->xmlOutput .= "</".strtolower($key).">";
        					} else $this->xmlOutput .= $value;
        					break;
        			}

        		}//for
        	}
        }
        /**
         * Return a XML structure for mnu node in nav2.xml file
         *
         * @param unknown_type $mnus
         */
        function mnuOutut($mnus){
        	$output = "";
        	foreach ($mnus as $items) {
        		if (array_key_exists("ITEM",$items)) {
        			foreach ($items["ITEM"] as $item) {

        				if (array_key_exists("HREF",$item["ATTRIBUTES"])) $href ="href=\"".$item["ATTRIBUTES"]["HREF"]."\""; else $href="";
        				if (array_key_exists("LINK",$item["ATTRIBUTES"])) $link ="link=\"".$item["ATTRIBUTES"]["LINK"]."\""; else $link="";
        				if (array_key_exists("NAME",$item["ATTRIBUTES"])) $name ="name=\"".$item["ATTRIBUTES"]["NAME"]."\""; else $name="";

        				$output.="<item $href $link $name>".$item["VALUE"]."</item>";
        			}
        			if (array_key_exists("ATTRIBUTES",$items)){
        				if (array_key_exists("TITLE",$items["ATTRIBUTES"])) $title="title=\"".$items["ATTRIBUTES"]["TITLE"]."\"";else $title="";

        				if (array_key_exists("NAME",$items["ATTRIBUTES"])) {
        					$mnuname="name=\"".$items["ATTRIBUTES"]["NAME"]."\"";
        					$output ="<$mnuname $title>".$output."</$mnuname>\n";
        				} else {$output="<mnu $title>".$output."</mnu>\n";}
        			}
        		}
        	}
        	return $output;
        }
        /**
         * Checks if device is mobile
         * See class variable IsMobile
         */
        public function DeviceCheck() {
        	if (!$this->isMobile) {
        		$this->userAgent = $_SERVER['HTTP_USER_AGENT'];
        		$this->accept    = $_SERVER['HTTP_ACCEPT'];

        		if (isset($_SERVER['HTTP_X_WAP_PROFILE'])|| isset($_SERVER['HTTP_PROFILE'])) {
        			$this->isMobile = true;
        		} elseif (strpos($this->accept,'text/vnd.wap.wml') > 0 || strpos($this->accept,'application/vnd.wap.xhtml+xml') > 0) {
        			$this->isMobile = true;
        		} else {
        			foreach ($this->devices as $device => $regexp) {
        				if (preg_match("/" . $this->devices[$device] . "/i", $this->userAgent) && !preg_match("/" . $this->devices["exclude"] . "/i", $this->userAgent)) {
        					$this->isMobile = true;
        					break;
        				}
        			}
        		}
        	}
        }
        /**
         * Set user session
         *
         */
        public function SetSession(){
        	if ($session = $this->get_cookie_state("session")) {
        		if (array_key_exists("mob",$session))
        		$this->isMobile = $session["mob"];
        		if (array_key_exists("user_id",$session))
        		$this->vars["user_id"]=$session["user_id"];
        	} else {
        		$session["user_id"]= "usr".uniqid(true);
        		$this->vars["user_id"]=$session["user_id"];
        	}
        	 
        	if (array_key_exists("mob",$this->vars)) {
        		if ($this->vars["mob"]=="y"){
        			$session["mob"] = true;
        			$this->isMobile = true;
        		} else {
        			$session["mob"] = false;
        			$this->isMobile = false;
        		}
        	}
        	$this->set_cookie_state("session",$session);
        	if (array_key_exists("prt",$this->vars))
        		$this->file_nav=_TPLDIR."/".$this->theme_dir."/".$this->vars["prt"];
        		elseif (!$this->isMobile)
        			$this->file_nav=_TPLDIR."/".$this->theme_dir."/"._NAVFILE;
        			else
        			$this->file_nav=_TPLDIR."/".$this->theme_dir."/"._NAVMOBILE;
        }
        /**
         * Gets XSL template files from folder ids.
         *
         * @author Elazos Software Factory
         * @access public
         */
        function SetXslFile($id_doc){
        	if($listofxslt_ids=$this->mc->get("xsltids")){
        		
        		if (in_array($id_doc, $listofxslt_ids)){
        			$this->file_xslt = "ids/".$id_doc;
        		}        		
        	} else {
        		$listofxslt_ids = array();
        		
        		if ($handle = opendir(_TPLDIR.$this->theme_dir.'ids')) {
        			while (false !== ($entry = readdir($handle))) {
        				
        				if ($entry!="." && $entry!="..") $listofxslt_ids[]=current(explode(".", $entry, 2));
        			}
					
        			$this->mc->set("xsltids",$listofxslt_ids,(60*10));

        			closedir($handle);
        		}
        		if (in_array($id_doc, $listofxslt_ids)){
        			$this->file_xslt = "ids/".$id_doc;
        		}        		
        	
        	}
        }
         
} //end class
?>