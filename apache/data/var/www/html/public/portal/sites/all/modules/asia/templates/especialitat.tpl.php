<?php
/**
* @file especialitat.tpl.php
* 
*
* - $arrXml
*
* 
*/

?>

<?php 
if(count($arrXml->search->noresults->query)==0){
 ?>
<select id="especialitat-aux">


<?php 
$count = 0;
foreach($arrXml->search->bleft->leftfilter->facetlist->class->item as $llistat) {

	if($count == "0"){
		echo "<option value='' selected=\"selected\">...</option>";
	}

   $name = $llistat["name"];
   $value = str_replace('code1=', "", strrchr($llistat['href'], 'code1=')); 
  
  ?>
	    <option value="<?php print $value;?>"> <?php print $name;?></option>
<?php
$count++;

	}  ?>





</select>

<?php } 
else {

print "Aquesta especialitat no existeix";

} ?>