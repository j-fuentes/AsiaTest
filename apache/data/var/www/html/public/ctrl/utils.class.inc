<?php
/**
 * Guia de Barcelona - Agenda and Directory
 *
 * This file is part of Guia Barcelona v1.0.0
 * @author Elazos Software Factory
 **/

/**
 *Class Utils file
 *@author Elazos Software Factory
 **/
/**
 *Class Database file
 *Utils extends DB_Sql class.
 **/
//require_once(_DirINCLUDES."class_mysql.php");
/**
 *Adds somes utilities like encryptation, image resize, save image to folder, delete folder, check date format, etc...
 *@author Elazos Software Factory
 *@version 1.0
 *@package Site
 */
class utils { //extends DB_Sql  {
	/**
	 * Crypt.
	 * If 1 = yes All Url "GET" are crypted, 0 =  No
	 *@var Integer
	 */
	var $cryptar = _CRYPT_LINKS;
	/**
	 * Random.
	 * Si 1 = encrypta con un numero final random rand(1,100) para que sean siempre diferentes, 0 =  Se encripta sin Rand
	 * @var boolean
	 */
	var $Random = False;
	var $iv64="cx0DjR012c0PACRAvpm01LojVUjvUL0cH9Yyp5/WMYc=";
	var $ekey = "a7bc27daf59679de9db7b68b1ef92785";

	/**
	 * Encryptar una url.
	 * Recoge todas variables de una URL y las encrypta. Devuelve una variable URL=texto emcriptado.
	 *@param string Vars de una URL para encriptar
	 **/
	function url_encrypt($text){

		if (isset($this->cryptar) && $this->cryptar) {
			$text="url".$text;
			if ($this->Random) $text.="#".rand(1,100);else $text.="#00";

			$text=$this->ecrypt($text);
			$text="url=".base64_encode($text);
		} else $text = htmlspecialchars($text);// = urlencode($text); //$text = htmlentities($text);

		return $text;
	}
	/**
	 * Used when no class utils is defined.
	 *
	 * @param unknown_type $text
	 * @return unknown
	 */
	public static function surl_encrypt($text){
		return $this->url_encrypt($text);
	}
	/**
	 * Desencrypta una url.
	 *@param string Texto a encriptar.
	 **/
	function url_decrypt($text){
		if ($this->cryptar){
			$text=$this->txt_decrypt($text);
			if (substr($text, 0, 3)=="url") {

				$text=rtrim($text);
				$text=substr($text, 3, (strrpos($text,"#")-3));

				if ($pos=strpos($text,"&ref=")){
					$url=substr($text, 0, $pos);
					$referer=substr($text,(strpos($text,"http://")), strlen($text));
				} else $url=$text;
				//echo $referer."................";
				parse_str($url,$result);
				if (isset($referer)) $result["referer"]=$referer;

				return $result;
			} else return FALSE;
		} else {
			parse_str($text,$result);
			return $result;
		}
	}
	/**
	 * Encrypts to be used in forms
	 *
	 *@param string URL para  desencriptar
	 **/
	function txt_encrypt($text){
		if ($this->cryptar) {
			$text="url".$text;
			if ($this->Random) $text.="#".rand(1,100);else $text.="#00";
			$text=$this->ecrypt($text);
			$text=base64_encode($text);
		}
		return str_replace("&",",",$text);
	}
	/**
	 * Decrypts text
	 *@param string Texto a desencriptar.
	 **/
	function txt_decrypt($text){
		if ($this->cryptar){
			$text=base64_decode($text);
			$text=$this->dcrypt($text);
		}
		return $text;
	}
	/**
	 * Encripta un texto.
	 *@param string texto a encryptar.
	 **/
	function ecrypt($text) {
		$td = mcrypt_module_open('rijndael-256', '', 'ofb', '');
		$iv=base64_decode($this->iv64);
		mcrypt_generic_init($td, $this->ekey, $iv);
		$encrypted = mcrypt_generic($td, $text);
		mcrypt_generic_deinit($td);
		mcrypt_module_close($td);
		return urlencode($encrypted); //Poner si hay problemas con el servidor http
		//return $encrypted;
	}
	/**
	 * Decripta un texto.
	 *@param string texto a desencryptar
	 **/
	function dcrypt($encrypted){
		$encrypted=urldecode($encrypted); //poner si hay problemas con el servidor http
		$td = mcrypt_module_open('rijndael-256', '', 'ofb', '');
		$iv=base64_decode($this->iv64);
		mcrypt_generic_init($td, $this->ekey, $iv);
		$decrypted = mdecrypt_generic($td, $encrypted);
		mcrypt_generic_deinit($td);
		mcrypt_module_close($td);
		//echo trim($decrypted)."<br/>";
		return trim($decrypted);
	}
	/**
	 *Change image size used by another method save_image
	 *@author Elazos Software Factory
	 *@access private
	 **/
	function img_resize($imagen, $destino, $max_pixels, $SelectSide=true){
		/* TIPOS DE IMAGENES
		 1 = GIF, 2 = JPG, 3 = PNG, 4 = SWF, 5 = PSD, 6 = BMP, 7 = TIFF(orden de bytes intel),
		 8 = TIFF(orden de bytes motorola), 9 = JPC, 10 = JP2, 11 = JPX, 12 = JB2, 13 = SWC,
		 14 = IFF, 15 = WBMP, 16 = XBM.
		 */

		if (file_exists($imagen)) {

			if (!$tam = getimagesize($imagen)) return false ; //Devuelve una array con varios datos

			if ($tam[2]!=2) return false; // no es jpg

			if (!$img_origen = imagecreatefromjpeg($imagen)) return false;

			//$x=imagesx($img_origen);
			//$y=imagesy($img_origen);

			$x=$tam[0];
			$y=$tam[1];
			if ($SelectSide){
				if ($x>$y)
				{ $nova_largura = $max_pixels; $nova_altura = $max_pixels * $y / $x;}
				else
				{ $nova_altura = $max_pixels; $nova_largura = $max_pixels * $x / $y;}
			} else {
				$nova_largura = $max_pixels; $nova_altura = $max_pixels * $y / $x;
			}
			$img_destino = imagecreatetruecolor($nova_largura,$nova_altura);
			imagecopyresampled($img_destino,$img_origen,0,0,0,0,$nova_largura,$nova_altura, $x, $y);
			imagejpeg($img_destino,$destino);
			return TRUE;
		} else return FALSE;
	}
	/**
	 * Cambia el tamany de una imatge
	 **/
	function save_imagen($imagen_old, $imagen, $origen, $destino, $max_pixels){

		if ($imagen && !preg_match("/[^A-Za-z0-9._]/", $imagen)) {

			if (!$this->img_resize($origen.$imagen, $destino.$imagen, $max_pixels, false))
			{unlink($origen.$imagen); return false;} else unlink($origen.$imagen);  // borro el fichero de temporal
			if (isset($imagen_old)
			&& $imagen_old!=""
			&& file_exists($destino.$imagen_old))
			unlink($destino.$imagen_old);
			return true;      // borro el fichero de anterior
		} else return false;
	}
	/**
	 * Cambia el formato de la fecha para que se pueda introducir en una base de datos SQL
	 * El formato SQL es YYYYMMDD
	 **/
	function date_sql_format($date,$current_format){

		if (!isset($date) || $date=="") return false;

		if (strchr($date,"-")) $date=preg_replace("/-/","/",$date);

		if (strchr($date,".")) $date=preg_replace("/\./","/",$date);

		if ($current_format=="d/m/Y" || $current_format=="d/m/y")
		list($day,$month,$year) = explode("/",$date);
		else list($month, $day, $year) = explode("/",$date);

		if (strlen($year)!=4) return false;
		//if ($year<=99)
		//if ($year<65) $year="20$year"; else $year="19$year";

		//echo $day.$month.$year;
		if (!checkdate($month,$day,$year)) return false;

		return sprintf ("%4s%02s%02s", $year, $month, $day);
	}
	/**
	 * Borrar un directorio este lleno o no
	 **/
	function deldir($dir){

		if (!$current_dir = opendir($dir)) return false;

		while($entryname = readdir($current_dir)){
			if(is_dir("$dir/$entryname") and ($entryname != "." and $entryname!="..")){
				$this->deldir("$dir/$entryname");
			}elseif($entryname != "." and $entryname!=".."){
				unlink("$dir/$entryname");
			}
		}
		closedir($current_dir);
		rmdir($dir);
		return true;
	}
	/**
	 * Devuelve una lista de valores de un array separados por coma
	 **/
	function array2list($array_values,$separator){
		reset($array_values);
		$result="";
		foreach($array_values as $value)
		if (is_array($value)){
			$result2="";
			foreach($value as $value2 )
			if ($result2=="") $result2=$value2;else $result2=$result2.";".$value2;
			if ($result=="") $result=$result2;else $result=$result."$separator".$result2;
		} else
		{ if ($result=="") $result=$value;else $result=$result."$separator".$value;}
		return $result;
	}
	/**
	 * Reverse of parse_str().  Converts array into
	 * string with query format
	 **/
	function rev_parse_str ($params) {
		$str = '';
		foreach ($params as $key => $value) {
			$str .= (strlen($str) < 1) ? '' : '&';
			$str .= $key . '=' . rawurlencode($value);
		}
		return ($str);
	}
	/**
	 * Enter description here...
	 *
	 */
	function getPermalink($name,$link){
        
		if (!defined("_PERMALINKS")){
			$MakePermalinks = false;
		} else {
			$MakePermalinks = _PERMALINKS;
		}
		if ($MakePermalinks) {
			
			// replace accented chars
			$accents = '/&([A-Za-z]{1,2})(grave|acute|circ|cedil|uml|lig);/';
			$string_encoded = htmlentities($name,ENT_NOQUOTES,'UTF-8');
            
			$string = preg_replace($accents,'$1',$string_encoded);
			// clean out the rest
			$replace = array('([\40])','(\'|,|%)','([^a-zA-Z0-9-])','(-{2,})');
			$with = array('-','-','','-');
			$string = strtolower(preg_replace($replace,$with,$string));
            
			parse_str($link,$vars);
			
			if(array_key_exists("id_doc",$vars)) {
				if(array_key_exists("idma",$vars))
					$string.= "_".$vars["id_doc"]."_"._IDIOMA.".html";
				else 
					$string.= "_".$vars["id_doc"].".html";
			}
			
			return $string;
		} else return LK_PAG.$this->url_encrypt($link);
	}
	/**
	 * Creates the html code of an hyperlink with permalink.
	 * Returns Html code of an anchor.
	 * @author Elazos Software Factory
	 * @access public
	 * @param string Url of the hyperlink
	 * @param string Text to be shown on the hyperlink
	 * @param string CSS class
	 */
	function html_link($link, $txt, $class=null){
		if (isset($class) && $class!=null && $class!="" ) $class="class=\"$class\""; else $class="";		
		//if ($enc=="") $enc="".LK_HOME."";else $enc="".LK_PAG."".$enc."";
		if ($class=="") return "<a href=\"".$this->getPermalink($txt,$link)."\">".$txt."</a>";
		else return "<a $class href=\"".$this->getPermalink($txt,$link)."\">".$txt."</a>";
	}
	/**
	 * Enter description here...
	 *
	 * @param unknown_type $text
	 * @return unknown
	 */
	function translate($text,$from,$to){
		//echo $text."<br/>\n";
		//echo $text=str_replace(" ","%20",$text);
		$text=rawurlencode($text);
		$url = "https://ajax.googleapis.com/ajax/services/language/translate?v=1.0&q=$text&langpair=$from|$to";
		// sendRequest
		// note how referer is set manually
		$ch = curl_init();
		curl_setopt($ch, CURLOPT_URL, $url);
		curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
		curl_setopt($ch, CURLOPT_REFERER, "http://guiabcn.elazos.com/");
		$body = curl_exec($ch);
		curl_close($ch);
		// now, process the JSON string
		$json = json_decode($body,true);
		//var_dump($json);
		if ($json["responseStatus"]=="200")
		return $json["responseData"]["translatedText"];
		return false;

	}
	/**
	 * Removes a variable of a URL string
	 *
	 * @param unknown_type $href
	 * @param unknown_type $varname
	 * @return unknown
	 */
	protected function DropVarUrl($href, $varname){
		parse_str($href,$array);
		$strResult = "";
		if (array_key_exists($varname,$array)){
			foreach($array as $key=>$value){
				if ($key!=$varname){
					if ($strResult=="") $strResult.="$key=$value";else $strResult.="&$key=$value";
				}
			}
		}
		if ($strResult!="") return $strResult;else return $href;
	}
	/**
	 * return a text as a permalink format. No accents, no espaces.
	 * @param String $name
	 * @return string Text as permalink
	 */
	public static function getTxtPermalink($name){
		$accents = '/&([A-Za-z]{1,2})(grave|acute|circ|cedil|uml|lig);/';
		$string_encoded = htmlentities($name,ENT_NOQUOTES,'UTF-8');
		
		$string = preg_replace($accents,'$1',$string_encoded);
		// clean out the rest
		$replace = array('([\40])','(\'|,|%)','([^a-zA-Z0-9-])','(-{2,})');
		$with = array('-','-','','-');
		$string = strtolower(preg_replace($replace,$with,$string));
		return $string;
	}



	//************************************FIN CLASSE
}
?>
