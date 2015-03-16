<?php
/**
 * Guia de Barcelona - Agenda and Directory
 *
 * This file is part of Guia Barcelona v1.0.0
 * @author Elazos Software Factory
 **/
require_once("includes/classification.class.inc");
error_reporting(E_ALL);
$tree_id = $_GET["tree"];

header('Content-Type: text/html; charset=UTF-8');

$class = new classification;
/*
//$class->Debug = 1;
//echo $class->getClassTreeXML("0040101",1);

$class->query("select count(distinct a.entity_id) as num from classification c, agenda a where c.tree_id = $tree_id and c.entity_id = a.entity_id and a.internetflag = 2;");
$class->next_record_assoc();
$numClass = $class->Record["num"];
$class->query("select count(distinct a.entity_id) num from agenda a where internetflag = 2;");
$class->next_record_assoc();
$numTotal = $class->Record["num"];

echo "<span style=\"font: normal 18px arial;color:blue\">AG : SI($numClass) Total($numTotal) ".number_format((($numClass/$numTotal)*100))."%</span><br/>";

$class->query("select count(distinct a.entity_id) as num from classification c, equipment a where c.tree_id = $tree_id and c.entity_id = a.entity_id and a.internetflag = 2;");
$class->next_record_assoc();
$numClass = $class->Record["num"];
$class->query("select count(distinct a.entity_id) num from equipment a where internetflag = 2;");
$class->next_record_assoc();
$numTotal = $class->Record["num"];

echo "<span style=\"font: normal 18px arial;color:blue\">EQ : SI($numClass) Total($numTotal) ".number_format((($numClass/$numTotal)*100))."%</span><br/>";
*/

echo "<span style=\"font: normal 18px arial;color:blue\">Estructura Arbre $tree_id + total de pàgines vistes 2012 </span><br/>";

echo "<span style=\"font: normal 12px arial;color:grey\">*Les pàgines vistes de paginacions estan incloses<br/>*Entre parentesis el nombre de registres ASIA asignats</span><br/><br/>";

echo "<span style=\"font: normal 12px arial;color:grey\">Pàgines vistes uniques totals a GUIA :  2.693.566</span></br>";
echo "<span style=\"font: normal 12px arial;color:grey\">Pàgines vistes uniques cerques :   519.317 (19%)</span></br>";
echo "<span style=\"font: normal 12px arial;color:grey\">Pàgines vistes uniques cerques x codi tematic :    206.926 (8%)</span></br></br>";

$result = $class->getClassTreeArray("00".$tree_id."00",1,10);
$pv = PageViewsByClass();
printTree($result,$class,$pv);

Echo "<br/>END successfully";

function printTree($result, &$class, &$pv=null){
	
	$totalpv = 206926;
	
    $strTemp = "";
    $i = 1;
	foreach($result as $node1){	
		$level = ((strlen($node1["code"])-7)/3)-1;		

		$class->query("select count(distinct c.entity_id) num from classification c where code = '".$node1["code"]."';");
		$class->next_record_assoc();
		$num = $class->Record["num"];
		
		//echo $level."<br/>";
		//echo "<span style=\"padding-left:".($level*100)."px\">".$node1["code"]." ".$node1["desc"]."</span><br/>";
		echo "<span style=\"padding-left:".($level*50)."px\"><span style=\"font: normal 18px arial;color:red\">".($level+1).".$i </span>".$node1["desc"]." ($num)</span>";
		if (array_key_exists($node1["code"],$pv)) echo "<span style=\"font: normal 18px arial;color:red\"> [Pàgines Vistes ".$pv[$node1["code"]]."]</span>";
		echo "<br/>";	
		$i++;
		if (is_array($node1["ramas"]) && count($node1["ramas"])) PrintTree($node1["ramas"],$class,&$pv);
	}
	return $strTemp;
}

function  PageViewsByClass(){
	$dbi = new object;

	$total = 0;
	$dbi->query("SELECT * FROM stats_x_class");
	$result = $dbi->select_array();

	foreach($result as $row){
		//echo "for1<br/>";
		$vars = parse_url($row["Page"]);

			
		if (array_key_exists("query",$vars) && $vars["query"]!=""){
			parse_str($vars["query"],$vars);
		}
			
		$key = array_keys($vars);

			
		foreach($key as $keyName){
				
			switch($keyName){
				case "code0":
				case "code1":
				case "code2":
				case "code3":
				case "code4":
				case "code5":
					if (!array_key_exists($vars[$keyName],$pv)) $pv[$vars[$keyName]] = $pv[$vars[$keyName]] + $row["Pageviews"];
					else $pv[$vars[$keyName]] = $pv[$vars[$$keyName]] + $row["Pageviews"];

					$total = $total + $row["Pageviews"];
					break;
			}

		}
	}

	
	arsort($pv);
	return $pv;

}


?>