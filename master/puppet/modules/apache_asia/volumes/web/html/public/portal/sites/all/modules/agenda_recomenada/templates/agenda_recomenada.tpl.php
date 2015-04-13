<?php
/**
* @file especialitat.tpl.php
* 
*
* - $arrXml
*
* 
*/

/* Variables */
global $language;
$base_url=$GLOBALS['base_url'].'/'.$language->language;
?>

<?php  

/*$total = $arrXml->hrecom->list->found['total'];
$to = $arrXml->hrecom->list->found['to'];*/


print '<ul id="llistat-categories"><li><a data-id="map-0" href="'.$base_url.'/agenda-recomenada/agenda500-tots" class="active">Tots els actes</a></li><li><a data-id="map-1" href="'.$base_url.'/agenda-recomenada/agenda500-tots?c=0061401000">Música</a></li><li><a data-id="map-2" href="'.$base_url.'/agenda-recomenada/agenda500-tots?c=0061401001">Exposicions</a></li><li><a data-id="map-3" href="'.$base_url.'/agenda-recomenada/agenda500-tots?c=0061401002">Esports</a></li><li><a data-id="map-4" href="'.$base_url.'/agenda-recomenada/agenda500-tots?c=0061401003">Festes Populars</a></li><li><a href="'.$base_url.'/agenda-recomenada/agenda500-tots?c=0061401007">Festivals</a></li><li><a data-id="map-5" href="'.$base_url.'/agenda-recomenada/agenda500-tots?c=0061401004">Teatre i dansa</a></li><li><a href="'.$base_url.'/agenda-recomenada/agenda500-tots?c=0061401005">Fires i congressos</a></li><li><a data-id="map-6" href="'.$base_url.'/agenda-recomenada/agenda500-tots?c=0061401006">Nens i nenes</a></li><li><a href="'.$base_url.'/agenda-recomenada/agenda500-tots?c=0061401008">Vida nocturna</a></li></ul>';



print '<div id="agenda-recomenada">';

$result =$arrXml->xpath("//row");



	foreach($result as $llistat) {
		$item = $llistat->item;
		$name = parsejaComilles($item->name);		
		$id = $item['href'];
	
		if(isset($item->detall->allimgsizes->{'post-image-col1'})){
			$picture = $item->detall->allimgsizes->{'post-image-col1'};
		}else{
	    	$picture = $item->imatgeCos;
		}
	
		
	
		$resum  = $item->resum;
		
		$on = $item->institutionname;
		$tit_on = $item->institutionname['label'];
		$id_on = $item->equipment_id;
		$quan = $item->date;
		$tit_quan = $item->date['label'];
		
		$href = $base_url.'/detall/'.$id;
		
		
		if(isset( $item->detall->allimgsizes->{'post-image-square1'})){
			$pictureComparteix = $item->detall->allimgsizes->{'post-image-square1'};
		}else{
	    	$pictureComparteix = "";
		}
		
		print '<div class="item box">';
		
		
		$titleShare=urlencode($name);
		$urlShare=urlencode($href);
		$summaryShare=urlencode($name);
		$imageShare=urlencode($pictureComparteix);

?>

<div class="compartir">
    <div class="facebook-button">
    <a onClick="window.open('http://www.facebook.com/sharer.php?s=100&amp;p[title]=<?php echo $titleShare;?>&amp;p[summary]=<?php echo $summaryShare;?>&amp;p[url]=<?php echo $urlShare; ?>&amp;p[images][0]=<?php echo $imageShare;?>','sharer','toolbar=0,status=0,width=548,height=325');" href="javascript: void(0)"><img class="facebook" src="<?php print "/".drupal_get_path('theme', 'bcn')."/images/fb-share.gif" ?>" /></a>
    </div>
    <div class="tweet-button">
        <a onClick="window.open('https://twitter.com/intent/tweet?url=<?php echo $urlShare;?>&text=<?php echo $titleShare;?>&lang=<?php echo $language->language ?>','sharer','toolbar=0,status=0,width=548,height=325');" href="javascript: void(0)"><img class="twitter" src="<?php print "/".drupal_get_path('theme', 'bcn')."/images/twitter-share.gif" ?>" /></a>
    </div>
    <div class="share-button">
       <span><?php print t("Share on"); ?></span><img class="share" src="<?php print "/".drupal_get_path('theme', 'bcn')."/images/share-button.gif" ?>" />
    </div>   
    
</div>

<?php		
			
			
			if (verificar_url($picture)){ 
					print '<div class="media"><img alt="" src="'.$picture.'"/></div>';	
			}
			
			print '<div class="content-ag">';
			
			print '<h3 class="properes"><a href="'.$href.'">'.$name.'</a></h3>';

			print "<p class='resum'>".$resum."</p>";	
				
			print '<div class="dades">';				
				print '<dl>';

				    if (hasValue($on)){
					    print '<dt>'.$tit_on.'</dt>';
							if(hasValue($id_on)){
  				    		  print '<dd><a href="'.$base_url.'/detall/'.$id_on['href'].'">'.$on.'</a></dd>';
							}else{
  				    		  print '<dd>'.$on.'</dd>';
							}
		     		}
				
					if (hasValue($quan)){
						print '<dt>'.$tit_quan.'</dt>';
						print '<dd>'.$quan.'</dd>';
					}else if (hasValue($item->begindate) || hasValue($item->enddate)){
						print '<dt>'.$item->begindate['label2'].'</dt>';
						print '<dd>'.$item->begindate['label'].' '.$item->begindate.' '.$item->enddate['label'].' '.$item->enddate.'.</dd>';
					}		
				
				
					print '</dl>';		
			
			
		
			print '</div>';
		 print '</div>'; 
		
		print '</div>'; // final del item d'un llistat
		
		
		}

 print '</div>' ;

/* if((string)$total != (string)$to){
	print '<div id="mes-activitats"><a href="'.$base_url.'/agenda-recomenada/agenda500">'.t("See more activities").'</a></div>';
 }
*/


?>