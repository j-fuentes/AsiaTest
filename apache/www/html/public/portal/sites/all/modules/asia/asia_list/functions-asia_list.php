<?php

//*****************************/
/* Functions de blocks       */
/*                           */
/*****************************/



function mostra_form_prox_activitats(){
 global $language;
  $idma = $language->language;
  
  $urlmoreinfo="";
  $canal = variable_get('asia_canal','');
  $periode = variable_get('showPeriode','');
  $columns = variable_get('columns','');
  $settings_asia_list = variable_get('settings_asia_list','');
  $fieldsshow = variable_get('fieldsshow','');
  $nr = variable_get('nresult','');
  
 $url = "http://guia.bcn.cat/index.php?pg=search&xout=1&type=AG&ajax=search&idma=".$idma;

	if(hasValue(variable_get('code0', ''))){
		$codi0 = variable_get('code0', '');	
		$url = $url."&code0=".$codi0;
		$urlmoreinfo="&code0=".$codi0;
	}
	if(hasValue(variable_get('code1', ''))){
		$codi1 = variable_get('code1', '');
		$url = $url."&code1=".$codi1;
		$urlmoreinfo.="&code1=".$codi1;
	}



	if($canal != ''){
		$url = $url."&canal=".$canal;
	}
	
	switch($periode){
		case 'rang':
			$datein=variable_get('dataInicial','');
			$dateout=variable_get('dataFinal','');		
			$url = $url."&dt=".$datein.','.$dateout;
			$urlmoreinfo.="&dt=".$datein.','.$dateout;
		break;
		case 'totes':
			$url = $url;
		break;
		default:
			if($periode != '') {
				$url = $url."&d=".$periode;
				$urlmoreinfo.="&d=".$periode;
			}
		break;
	}
	
	
	if($nr != ''){$url = $url."&nr=".$nr;}
	// Si esta activat el recull de variable districte a la configuració ($settings_asia_list[2]) del block i aquest existeix.
	// Recull la variable i mostra els resultats
	if(isset($_GET["districtstr"]) && $settings_asia_list[2]==2){
		$districte =  str_replace( " " ,"+",$_GET["districtstr"]);
		$url = $url."&districtstr=".$districte;
		$urlmoreinfo.= "&districtstr=".$districte;
		
	}

		
		
 $str = file_get_contents($url);
 $arrXml = new SimpleXmlElement($str);
   $variables = array(
    'arrXml' => $arrXml,	
	'settings_asia_list' => $settings_asia_list,
	'urlmoreinfo' => $urlmoreinfo,	
	'fieldsshow' => $fieldsshow,
  );
  
  	//Si per configuració esta triat la presentació a 1 o 2 columnes
	if ($columns=='2'){	
		return theme('properes_activitats2col', $variables);
	}else{	
		return theme('properes_activitats', $variables);
	}
}