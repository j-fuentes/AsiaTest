<?php
/**
 * Guia de Barcelona - Agenda and Directory
 *
 * This file is part of Guia Barcelona v1.0.0
 * @author Elazos Software Factory
 **/

/**
*Returns xml node for languages.
*@package blocks_public
**/
global $lst_idiomas;

$this->html_out .="<langs>\n";
$i=0;
foreach ($lst_idiomas as $key=>$value) {
$this->html_out .="<item href=\"".LK_PAG."idma=$key\">$value</item>";
$i++;
}
$this->html_out .="</langs>";  

     
?>
