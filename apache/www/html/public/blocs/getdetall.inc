<?php
//$this->html_out .= "</merce>";

global $d;

$url = "http://212.15.224.54/APPS/asiw/XmlController?xml=";

$c = "0040002023025";

$request="<request>
  <header module=\"QueryGraella\" operation=\"getGraella\"/>
  <body>
    <dependencia></dependencia>
    <classificacions_cerca>
      <operador>OR</operador>
      <classificacio_cerca>$c</classificacio_cerca>
    </classificacions_cerca>
    <paraules></paraules>
    <quan>
      <literal>I</literal>
      <interval_dates>
        <data_inici>$d</data_inici>
        <data_fi>$d</data_fi>
      </interval_dates>
    </quan>
    <on>
      <carrer_cerca></carrer_cerca>
      <num_inici></num_inici>
      <num_fi></num_fi>
      <districte_cerca></districte_cerca>
      <barri_cerca></barri_cerca>
      <id></id>
    </on>
    <municipi_cerca></municipi_cerca>
    <provincia_cerca></provincia_cerca>
    <nens_i_nenes></nens_i_nenes>
    <inetflag></inetflag>
    <permanents>0</permanents>
    <ordenacio>D</ordenacio>
    <primer></primer>
    <ultim></ultim>
    <graella>
			<files>
				<grup>
					<text_grup>Tot</text_grup>
					<classificacions_cerca>
						<operador>AND</operador>
						<classificacio_cerca>00400</classificacio_cerca>
					</classificacions_cerca>
				</grup>
			</files>
			<columnes>
				<grup>
					<text_grup>Dia 22</text_grup>
					<interval_temps>
						<quan>
							<literal>I</literal>
							<interval_dates>
								<data_inici>$d 00:00</data_inici>
								<data_fi>$d 23:59</data_fi>
							</interval_dates>
						</quan>
						<ordenat_hores>1</ordenat_hores>
					</interval_temps>
				</grup>
			</columnes>
			<llegenda>
				<indicador>
					<id_indicador>01</id_indicador>
					<classificacions_cerca><operador>AND</operador><classificacio_cerca>$c</classificacio_cerca></classificacions_cerca>
				</indicador>			
			</llegenda>
		</graella>
	</body>
</request>";

// Open the file using the HTTP headers set above
if ($fileXML = file_get_contents($url.urlencode($request))){
	$fileXML = new SimpleXMLElement($fileXML);
	$result = "";
	if (array_key_exists("debug", $_GET)) {print_r($fileXML);die;}
	foreach($fileXML->body->resultat->graella->files->casella->actes->acte as $acte){
		$result.="<acte><id>".$acte->id."</id><data>".$acte->data->data_proper_acte."</data></acte>";
	}	
	$this->html_out .= $result;
} else {
	echo "error al cargar XML ASIA\n";
}
?>