<?php
/**
 * Guia de Barcelona - Agenda and Directory
 *
 * This file is part of Guia Barcelona v1.0.0
 * @author Elazos Software Factory
 **/
/**
 * Class Recommendation Engine file
 * @author Elazos Software Factory 
 **/
/**
 * Class Object file
 **/
require_once("includes/object.class.inc");
/**
 * Handles entitys - using table prefix_entitys.
 * Gestiona clientes con la tabla prefix_entitys.
 * @author Elazos Software Factory
 * @version 1.0
 * @package BusObj
 */
class engine extends object {
	/**
	 * Message after execution of any method.
	 * Se almacenan el mensaje generado por la ejecuci�n de un metodo.
	 * @var string
	 */
	var $txt_error;
	/**
	 * Enter description here...
	 *
	 * @param unknown_type $day
	 */
	public function CalculateItemRelation($day = null){
		if ($day==null) $day = date("Y-m-d", time()-((3600*24*(1))));
		
		$sql = "select distinct user_id FROM counters where dtDay = '$day';";
		if ($this->query($sql)){
			if ($this->num_rows()>0){
				$users = $this->select_array();
				foreach($users as $usrItem){
					$sql = "SELECT entity_id, counter, vote FROM counters where dtDay = '$day' and user_id = '".$usrItem["user_id"]."' order by counter, vote desc limit 5;";
					if ($this->query($sql)){
						if ($this->num_rows()>0){
							$entities = $this->select_array();
							$i=0;
							foreach($entities as $item){
								for($z=$i+1;$z<count($entities);$z++){
									if ($item["entity_id"]!=$entities[$z]["entity_id"])
									$this->setPair($item["entity_id"],$entities[$z]["entity_id"], $item["counter"],$item["vote"]);
								}
								$i++;
							}
						}
					}
				}
			}
		}
	}

	/**
	 * Enter description here...
	 *
	 * @param unknown_type $item1
	 * @param unknown_type $item2
	 * @param unknown_type $counter
	 */
	public function setPair($item1,$item2, $counter, $vote = false){
		if($this->query("select * from recommend where entityid1 = $item1 and entityid2 = $item2;")){
			if ($this->num_rows()>0){
				$this->query("update recommend set counter = (counter + 1) where entityid1 = $item1 and entityid2 = $item2;");
			} else {
				$this->query("insert into recommend (entityid1,entityid2,counter,sum) values ($item1,$item2,$counter,0);");
			}
		}
		if ($vote){
			if($this->query("select * from voted where entityid1 = $item1 and entityid2 = $item2;")){
				if ($this->num_rows()>0){
					$this->query("update voted set counter = (counter + 1) where entityid1 = $item1 and entityid2 = $item2;");
				} else {
					$this->query("insert into voted (entityid1,entityid2,counter,sum) values ($item1,$item2,$counter,0);");
				}
			}
		}

	}
	/**
	 * Enter description here...
	 *
	 * @param unknown_type $entity_id
	 */
	public function ItemRecommended($entity_id, $limit){
		if($this->query("select * from recommend where entityid1 = $entity_id or entityid2 = $entity_id order by counter desc limit $limit;")){
			if ($this->num_rows()>0){
				$entities = $this->select_array();
				foreach($entities as $item){
					if ($entity_id!=$item["entityid1"]) $result[]=$item["entityid1"];
					if ($entity_id!=$item["entityid2"]) $result[]=$item["entityid2"];
				}
				return array_unique($result);
			}
		}
		return false;
	}
	/**
	 * Enter description here...
	 *
	 * @param unknown_type $entity_id
	 */
	public function ItemVoted($entity_id, $limit){
		if($this->query("select * from voted where entityid1 = $entity_id or entityid2 = $entity_id order by counter desc limit $limit;")){
			if ($this->num_rows()>0){
				$entities = $this->select_array();
				foreach($entities as $item){
					if ($entity_id!=$item["entityid1"]) $result[]=$item["entityid1"];
					if ($entity_id!=$item["entityid2"]) $result[]=$item["entityid2"];
				}
				return array_unique($result);
			}
		}
		return false;
	}
	/**
	 * Enter description here...
	 *
	 * @return unknown
	 */
	public function TotalVisits($DaysAgo){
		if ($this->query("SELECT sum(counter) as total FROM `counters` WHERE dtDay >= DATE_ADD(CURDATE(), INTERVAL -$DaysAgo DAY);")){
			if ($this->num_rows()>0){
				$this->next_record_assoc();
				return $this->Record["total"];
			}
		}
		return false;
	}
	/**
	 * Enter description here...
	 *
	 * @param unknown_type $DaysAgo
	 * @return unknown
	 */
	public function  MaxVisitsEntity($DaysAgo){
		if ($this->query("SELECT sum(visits) as total, entity_id FROM visits_day WHERE dtDay >= DATE_ADD(CURDATE(), INTERVAL -$DaysAgo DAY) group by entity_id order by total desc limit 1;")){
			if ($this->num_rows()>0){
				$this->next_record_assoc();
				return $this->Record["total"];
			}
		}
		return false;

	}
	/**
	 * Enter description here...
	 *
	 * @param unknown_type $DaysAgo
	 */
	public function CalcPopularity($DaysAgo){
		
		$this->query("delete from popularity where entity_id not in (select entity_id from entity);");
		$this->query("delete from visits_day where entity_id not in (select entity_id from entity);");
				
		$totalVisits = $this->MaxVisitsEntity($DaysAgo);

		echo "Max Visits for a entity_id : $totalVisits<br/>\n";
	
		
		$this->query("SELECT entity_id FROM popularity;");
		if ($this->num_rows()>0){
			while($this->next_record_assoc())
			$idPopulars[] = $this->Record["entity_id"];
		} else 	$idPopulars = array();

		if ($this->query("SELECT entity_id, sum(visits) as total FROM visits_day WHERE dtDay >= DATE_ADD(CURDATE(), INTERVAL -$DaysAgo DAY) group by entity_id;")){
			if ($this->num_rows()>0){
				$entities = $this->select_array();
				$currentEntities = array();
				foreach($entities as $item){
					$total = $item["total"];
					$entity_id = $item["entity_id"];
					$popularity = round($total/$totalVisits,2);
					//$popularity = $total;
					if (($pos=array_search($entity_id,$idPopulars))!==false){
						if ($popularity>0){
							$this->query("update popularity set popularity = $popularity where entity_id = $entity_id;");
							unset($idPopulars[$pos]);
							if (($tmp=$this->affected_rows())>0) {
							    $this->query("insert tmp_entity (entity_id, action, processed) values ($entity_id,'s',false) on duplicate key update processed = false, action = 's';");	
							}
						}
					} else {
						if ($popularity>0){
						$this->query("insert into popularity (entity_id, popularity) values ($entity_id,$popularity);");
						$this->query("insert tmp_entity (entity_id, action, processed) values ($entity_id,'s',false) on duplicate key update processed = false, action = 's';");
						}
					}
				}
			}
		}
		unset($entities); //free memory
		foreach($idPopulars as $entity_id){
			$this->query("delete from popularity where entity_id = $entity_id;");
			$this->query("insert tmp_entity (entity_id, action, processed) values ($entity_id,'d',false) on duplicate key update processed = false, action = 's';");
		}
		return false;
	}
	/**
	 * Enter description here...
	 *
	 */
	public function generateTestData($visites,$pagines){

		$this->query("SELECT entity_id FROM entity;");
		if ($this->num_rows()>0){
			while($this->next_record_assoc())
			$identities[] = $this->Record["entity_id"];
		} else 	$identities = array();
		$Max = count($identities)/2;

		$date = date("Y-m-d", time()-((3600*24*(1))));

		for($visit=0;$visit<$visites;$visit++) {
			$user_id = "usr".uniqid(true);
			for($pagina=rand(0,4);$pagina<$pagines;$pagina++) {
				$entity_id = $identities[rand(0,$Max)];
				$count = rand(1,3);				
				if (rand(1,100)==1) $vote = 1; else $vote = 0;
				$this->query("insert into counters (entity_id,dtDAy,user_id, counter,vote) values ($entity_id,'$date','$user_id', $count,$vote);");
			}
		}

	}
	/**
	 * More viewed for today, last 7 days, month  *
	 *
	 * @param unknown_type $type
	 */
	public function CalcMViewed($type){
		$this->query("delete from mviewedvoted where itype = $type;");
		switch($type){
			case 1;
			if (!$this->query("insert into mviewedvoted select c.entity_id, $type, sum(counter) as counter from counters c, entity e where c.entity_id = e.entity_id and dtDay = CURDATE() group by c.entity_id order by counter desc limit 10;")){
				echo "Error calculating today more viewed.";
			}
			break;
			case 2;
			if (!$this->query("insert into mviewedvoted select c.entity_id, $type, sum(visits) as counter from visits_day c, entity e where c.entity_id = e.entity_id and dtDay >= DATE_SUB(CURDATE(), INTERVAL 7 DAY) group by c.entity_id order by counter desc limit 10;")){
				echo "Error calculating 7 days more viewed.";
			}
			break;
			case 3;
			if (!$this->query("insert into mviewedvoted select c.entity_id, $type, sum(visits) as counter from visits_day c, entity e where c.entity_id = e.entity_id and dtDay >= DATE_SUB(CURDATE(), INTERVAL 1 MONTH) group by c.entity_id order by counter desc limit 10;")){
				echo "Error calculating 30 days more viewed.";
			}
			break;
			case 4;
			if (!$this->query("insert into mviewedvoted select c.entity_id, $type, sum(vote) as counter from counters c, entity e where c.entity_id = e.entity_id and dtDay = CURDATE() and vote > 0 group by c.entity_id order by counter desc limit 10;")){
				echo "Error calculating today more voted.";
			}
			break;
			case 5;
			if (!$this->query("insert into mviewedvoted select c.entity_id, $type, sum(votes) as counter from visits_day c, entity e where c.entity_id = e.entity_id and dtDay >= DATE_SUB(CURDATE(), INTERVAL 7 DAY) and votes > 0 group by c.entity_id order by counter desc limit 10;")){
				echo "Error calculating 7 days more voted.";
			}
			break;
			case 6;
			if (!$this->query("insert into mviewedvoted select c.entity_id, $type, sum(votes) as counter from visits_day c, entity e where c.entity_id = e.entity_id and dtDay >= DATE_SUB(CURDATE(), INTERVAL 1 MONTH) and votes > 0 group by c.entity_id order by counter desc limit 10;")){
				echo "Error calculating 30 days more voted.";
			}
			break;
		}
	}
	/**
	 * Enter description here...
	 *
	 * @return unknown
	 */
	public function CalcVisitsDay($dayAgo){
		echo "Calc visits day...<br/>";
		$today = date("Y-m-d");
		$dayAgo = date("Y-m-d", time()-((3600*24*($dayAgo))));
		$this->query("insert into visits_day select entity_id, dtday, sum(counter) as visits, sum(vote) as votes from counters where dtday < '$today' group by entity_id, dtday;");
		if ($this->query("select max(dtDay) as day from visits_day;")){
			if ($this->num_rows()>0){
				$this->next_record_assoc();
				$dtDay = $this->Record["day"];
				$this->query("delete from counters where dtday <= '$dtDay';");
			}
		}
		$this->query("delete from visits_day where dtday < '$dayAgo';");
	}

}


?>