<?php
/**
* @file mapa-districte.tpl.php
* Renderiza una lista de items.
*
* - $items
* 
*/
global $language;
$base_url=$GLOBALS['base_url'].'/'.$language->language;
$strVariablesUrl="";

if(hasValue($code0)){
	$strVariablesUrl = "&amp;code0=".$code0;
}	
if(hasValue($code1)){	
	$strVariablesUrl = $strVariablesUrl."&amp;code1=".$code1;
}


// Si $showMapList -->  0 = NO MOSTREM RES  //  1 = MAPA  //  2 = LLISTAT   //  3 = MAPA + LLISTAT
$showMapList = 0;
if($arraySelectMap) { // si existeix la variable:
	foreach ($arraySelectMap as $elem) $showMapList = $showMapList + $elem;	
}
else $showMapList = 3;  // valor per defecte:

?>

<div id="mapa-districtes">

<? if($showMapList == 1 || $showMapList == 3) { /* Si hem de mostrar el MAPA: */

// Mides inicials del mapa:
$originalWidth = 211; $originalHeight = 186;


if($widthMap) $newWidth = $widthMap;			
else $newWidth = 211;


// Calcul proporcional de la nova alçada:
$newHeight = $newWidth*($originalHeight/$originalWidth); // 186/211

// Càlcul del ratio WIDTH & HEIGHT:
$ratio_W = ($newWidth/$originalWidth);
$ratio_H = ($newHeight/$originalHeight);



/***********************************************************  Coords prop. al mapa (w x h = 115x100 px)   ***********************************************************/
$coords_santmarti = array(141,106,152,106,151,114,158,116,176,106,180,108,181,114,179,114,179,116,181,119,180,121,180,125,180,128,180,130,180,135,177,142,180,146,183,149,178,150,175,150,174,148,164,147,158,150,151,150,147,148,142,150,138,150,136,150,136,152,134,155,130,155,135,151,135,149,133,149,132,146,129,146,128,135,125,135,125,133,133,133,139,126,139,123,141,122);
$coords_santandreu = array(158,92,164,97,165,97,166,92,172,89,175,88,180,85,189,80,192,77,198,68,201,69,201,74,201,84,199,85,199,91,198,92,198,95,199,97,191,110,187,109,184,114,183,111,181,110,181,108,177,104,175,104,158,114,153,114,153,111,154,110,153,105,151,105,154,101,154,95);
$coords_noubarris = array(161,55,164,56,166,56,169,55,172,57,176,56,179,51,186,50,189,53,194,53,200,56,202,54,202,52,206,54,209,57,202,65,198,66,195,70,194,73,189,77,177,84,174,87,165,91,165,95,160,91,158,91,155,92,155,90,153,87,152,84,150,81,152,80,152,75,155,73,158,71,160,66,162,65,163,63,160,61);
$coords_hortaguinardo = array(136,37,138,38,143,37,145,37,150,41,151,42,153,43,155,45,153,48,157,50,160,51,162,50,166,53,165,55,163,55,160,55,160,56,160,59,158,62,160,63,158,65,157,69,155,71,155,72,150,74,150,79,148,78,147,80,148,82,151,85,151,88,153,91,153,95,152,98,153,101,149,105,130,105,131,99,132,91,132,87,128,86,127,82,130,80,130,74,128,74,125,72,123,70,121,69,120,67,122,66,123,60,121,59,119,63,116,61,114,62,108,60,108,57,107,55,110,50,114,49,117,49,123,47,130,44);
$coords_gracia = array(114,64,117,63,118,64,119,65,121,62,121,65,119,67,121,70,122,70,123,73,130,75,128,79,126,80,126,86,128,87,130,88,130,95,129,99,129,110,123,111,121,108,110,108,108,108,109,101,110,99,115,92,114,88,117,82,113,77,113,72,115,68);
$coords_sarriasantgervasi = array(61,29,57,27,51,28,49,31,49,34,53,39,59,37,66,37,69,42,74,48,75,47,77,51,75,54,75,57,74,59,75,68,73,71,75,71,75,75,77,78,75,81,75,85,80,88,82,88,91,99,106,106,109,97,111,97,114,92,113,90,115,82,112,80,112,71,114,68,113,63,108,60,106,53,112,48,110,45,110,42,101,33,101,30,98,28,100,24,99,21,90,21,87,17,89,14,86,12,83,7,83,5,86,0,82,0,80,2,79,5,78,10,75,10,72,12,75,15,75,17,77,17,75,17,72,17,72,22,68,27);
$coords_lescorts = array(72,60,67,60,59,64,55,73,55,75,54,78,53,77,49,80,51,86,50,92,57,99,60,99,60,101,72,103,80,107,87,107,93,101,90,99,82,91,75,86,74,80,75,78,75,73,75,73,71,72,73,67);
$coords_santsmontjuic = array(39,141,41,142,44,142,44,138,45,136,46,129,53,127,57,127,57,123,60,114,59,108,59,103,65,103,75,106,80,109,85,109,80,112,80,125,80,125,100,143,100,146,98,148,97,150,93,154,95,158,93,158,91,153,85,156,87,159,87,161,83,161,82,157,78,157,80,161,78,163,67,166,65,159,60,162,50,160,54,157,50,155,39,164,37,161,35,161,33,163,35,166,31,167,33,170,50,165,56,165,57,172,38,181,34,177,26,182,4,161,0,150,0,141,2,137,1,128);
$coords_eixample = array(95,102,97,103,110,111,121,110,124,112,130,111,130,107,139,107,139,122,137,121,138,125,132,131,126,131,123,129,117,129,115,128,108,128,105,124,94,130,93,135,82,123,82,112);
$coords_ciutatvella = array(102,155,100,148,102,144,95,137,95,131,104,126,107,129,114,129,117,130,123,131,123,136,128,136,127,147,130,148,130,150,127,152,123,155,119,155,107,161,107,165,91,169,94,167,104,163,95,163,79,168,75,171,68,176,58,183,57,185,56,183,66,173,68,170,70,170,72,167,75,167,78,166,97,160,99,161,102,161,105,159,106,159,115,149,115,146,113,144,112,148,109,150,106,149,109,148,111,144,105,146,103,148,105,153);

?>

        <img src="<?php echo $GLOBALS['base_url'] . '/' . drupal_get_path('module', 'asia') . "/img/mapa.gif"; ?>"
	        	alt="Mapa districtes" width="<?php echo $newWidth; ?>" height="<?php echo $newHeight; ?>" usemap="#mapadistrictes" />
       		<map name="mapadistrictes" id="mapadistrictes">
            <area class="mapa-santmarti" alt="Sant Martí" title="Sant Martí" shape="poly" coords="<?php echo changeCoordsRatio($coords_santmarti, $ratio_W, $ratio_H); ?>" href="<?php echo $base_url; ?>/llistat?districtstr=Sant+Martí<?php echo $strVariablesUrl; ?>" />
            <area class="mapa-santandreu" shape="poly" coords="<?php echo changeCoordsRatio($coords_santandreu, $ratio_W, $ratio_H); ?>" href="<?php echo $base_url; ?>/llistat?districtstr=Sant+Andreu<?php echo $strVariablesUrl; ?>" alt="Sant Andreu" title="Sant Andreu" />
            <area class="mapa-noubarris" shape="poly" coords="<?php echo changeCoordsRatio($coords_noubarris, $ratio_W, $ratio_H); ?>" href="<?php echo $base_url; ?>/llistat?districtstr=Nou+Barris<?php echo $strVariablesUrl; ?>" alt="Nou Barris" title="Nou Barris" />
            <area class="mapa-hortaguinardo" shape="poly" coords="<?php echo changeCoordsRatio($coords_hortaguinardo, $ratio_W, $ratio_H); ?>" href="<?php echo $base_url; ?>/llistat?districtstr=Horta-Guinardó<?php echo $strVariablesUrl; ?>" alt="Horta - Guinardó" title="Horta - Guinardó"  />
            <area class="mapa-gracia" alt="Gràcia" shape="poly" coords="<?php echo changeCoordsRatio($coords_gracia, $ratio_W, $ratio_H); ?>" href="<?php echo $base_url; ?>/llistat?districtstr=Gràcia<?php echo $strVariablesUrl; ?>"  title="Gràcia" />
            <area class="mapa-sarriasantgervasi" alt="Sarrià - Sant Gervasi" shape="poly" coords="<?php echo changeCoordsRatio($coords_sarriasantgervasi, $ratio_W, $ratio_H); ?>" href="<?php echo $base_url; ?>/llistat?districtstr=Sarrià-Sant+Gervasi<?php echo $strVariablesUrl; ?>" title="Sarrià - Sant Gervasi"  />
            <area class="mapa-lescorts" alt="Les Corts" title="Les Corts" shape="poly" coords="<?php echo changeCoordsRatio($coords_lescorts, $ratio_W, $ratio_H); ?>" href="<?php echo $base_url; ?>/llistat?districtstr=Les+Corts<?php echo $strVariablesUrl; ?>" />
            <area class="mapa-santsmontjuic" alt="Sants - Montjuïc" shape="poly" coords="<?php echo changeCoordsRatio($coords_santsmontjuic, $ratio_W, $ratio_H); ?>" href="<?php echo $base_url; ?>/llistat?districtstr=Sants-Montjuïc<?php echo $strVariablesUrl; ?>" title="Sants - Montjuïc" />
            <area class="mapa-eixample" alt="Eixample" shape="poly" coords="<?php echo changeCoordsRatio($coords_eixample, $ratio_W, $ratio_H); ?>" href="<?php echo $base_url; ?>/llistat?districtstr=Eixample<?php echo $strVariablesUrl; ?>" title="Eixample"/>
            <area class="mapa-ciutatvella" alt="Ciutat Vella" shape="poly" coords="<?php echo changeCoordsRatio($coords_ciutatvella, $ratio_W, $ratio_H); ?>" href="<?php echo $base_url; ?>/llistat?districtstr=Ciutat+Vella<?php echo $strVariablesUrl; ?>" title="Ciutat Vella"/>
        </map>
<? }
   if($showMapList >= 2) { /* Si hem de mostrar el LLISTAT */ ?>
   
        <ul>
          <li><a href="<?php echo $base_url; ?>/llistat?districtstr=Ciutat+Vella<?php echo $strVariablesUrl; ?>" class="mapa-ciutatvella">Ciutat Vella</a></li>
          <li><a href="<?php echo $base_url; ?>/llistat?districtstr=Eixample<?php echo $strVariablesUrl; ?>" class="mapa-eixample">Eixample</a></li>
          <li><a href="<?php echo $base_url; ?>/llistat?districtstr=Sants-Montjuïc<?php echo $strVariablesUrl; ?>" class="mapa-santsmontjuic">Sants-Montjuïc</a></li>
          <li><a href="<?php echo $base_url; ?>/llistat?districtstr=Les+Corts<?php echo $strVariablesUrl; ?>" class="mapa-lescorts">Les Corts</a></li>
          <li><a href="<?php echo $base_url; ?>/llistat?districtstr=Sarrià-Sant+Gervasi<?php echo $strVariablesUrl; ?>" class="mapa-sarriasantgervasi">Sarrià-Sant Gervasi</a></li>
          <li><a href="<?php echo $base_url; ?>/llistat?districtstr=Gràcia<?php echo $strVariablesUrl; ?>" class="mapa-gracia">Gràcia</a></li>
          <li><a href="<?php echo $base_url; ?>/llistat?districtstr=Horta-Guinardó<?php echo $strVariablesUrl; ?>" class="mapa-hortaguinardo">Horta-Guinardó</a></li>
          <li><a href="<?php echo $base_url; ?>/llistat?districtstr=Nou+Barris<?php echo $strVariablesUrl; ?>" class="mapa-noubarris">Nou Barris</a></li>
          <li><a href="<?php echo $base_url; ?>/llistat?districtstr=Sant+Andreu&<?php echo $strVariablesUrl; ?>" class="mapa-santandreu">Sant Andreu</a></li>
          <li><a href="<?php echo $base_url; ?>/llistat?districtstr=Sant+Martí<?php echo $strVariablesUrl; ?>" class="mapa-santmarti">Sant Martí</a></li>
        </ul>
<? } ?>
</div>

