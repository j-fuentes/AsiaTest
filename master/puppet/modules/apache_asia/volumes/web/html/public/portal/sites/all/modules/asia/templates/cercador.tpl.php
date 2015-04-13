<?php
/**
* @file cercador.tpl.php
* Renderiza una lista de items.
*
* - $items
*
* 
*/
global $language;
?>

<form action="<?php echo $GLOBALS['base_url'].'/'.$language->language ?>/llistat" method="get">
<div>
	<input type="text" name="cerca" id="cerca" value="" />
     


<?php /* if($items["districte"]==1){ ?>

  <select id="districtstr" name="districtstr">
        <option value="">Tots els districtes</option>
        <option value="Ciutat+Vella">Ciutat Vella</option>
        <option value="Eixample">Eixample</option>
        <option value="Sants-Montjuïc">Sants-Montjuïc</option>
        <option value="Les+Corts">Les Corts</option>
        <option value="Sarrià-Sant+Gervasi">Sarrià-Sant Gervasi</option>
        <option value="Gràcia">Gràcia</option>
        <option value="Horta-Guinardó">Horta-Guinardó</option>
        <option value="Nou+barris">Nou barris</option>
        <option value="Sant+Andreu">Sant Andreu</option>
        <option value="Sant+Martí">Sant Martí</option>
	</select>

<?php } */ ?>   

    <input type="submit" value="<?php print t('Search') ?>" /></div>
</form>