<?php
error_reporting(E_ERROR);
date_default_timezone_set("Europe/Madrid");
$memcache = new Memcache;
$memcache->connect('localhost', 11211)
or die ("Could not connect to memcache server");

function getMemcacheKeys($memcache) {
	$result = array();
	$list = array();
	$allSlabs = $memcache->getExtendedStats('slabs');
	$items = $memcache->getExtendedStats('items');
	$i = 0;
	$chunk_size = 0;
	foreach($allSlabs as $server => $slabs) {
		
		foreach($slabs AS $slabId => $slabMeta) {
			//$chunk_size += $slabMeta["chunk_size"];
			$cdump = $memcache->getExtendedStats('cachedump',(int)$slabId);
			foreach($cdump AS $keys => $arrVal) {
				if (!is_array($arrVal)) continue;
				foreach($arrVal AS $k => $v) {
					$result[$i]["key"] =  $k;
					$result[$i]["dtime"] = $v[1];
					$result[$i]["bytes"] =  $v[0];
					$i++;
				}
			}
		}
	}
	//echo $chunk_size/1024;
	return $result;
}
/**
 * Inicio
 *
 */
$totalMem = 256*1024*1024;
$result = getMemcacheKeys($memcache);
ksort($result);
$time = time();
$totalBytes = 0;
$totalItems = 0;
$totalLive = 0;
$totalBytesLive = 0;
$OutString = '<table border="1">';
foreach($result as $pos=>$valors){
	$expired = true;
	$dtime = $valors["dtime"];
	$OutString .= '<tr>';
	if (($dtime-$time)>0) $expired = false;
	$OutString .="<td>". $valors["key"]."</td><td>".date('d/m/Y H:i:s',$dtime)."</td><td> bytes : ".$valors["bytes"]."</td>";
	if ($expired) $OutString .= "<td> EXPIRED </td> ";else {
		$OutString .= '<td> <form name="'.uniqid().'" action="gestiocache.php" method="post"><input type="hidden" name="key" value="'.$valors["key"].'"><input type="submit"
					value="Borrar"></form></td>';
	}
	$OutString .= "</tr>";
	$totalBytes+=$valors["bytes"];
	$totalItems+=1;
	if (!$expired)  {
		$totalBytesLive+=$valors["bytes"];
		$totalLive+=1;
	} else {
		//echo "borrant ".$valors["key"]."<br/>";
		//$memcache->delete($valors["key"]);
	}
}
$OutString .= "</table>";
echo "Total Items : ".$totalItems." Total MBytes : ".number_format($totalBytes/1024/1024,2,',','.')." Mb<br/>";
echo "Total Active Items : ".$totalLive." (".number_format($totalLive/$totalItems*100,0,',','.')."%) Total MBytes : ".number_format($totalBytesLive/1024/1024,2,',','.')." Mb (".number_format($totalBytesLive/$totalBytes*100,2,',','.')."%)(".number_format($totalBytesLive/$totalMem*100,2,',','.')."%)<br/><br/>";
echo $OutString;
?>