<?php
error_reporting(0);
session_start();

// ***************************************** //
// **********	DECLARE VARIABLES  ********** //
// ***************************************** //

$username = 'memcache';
$password = 'kjoewnvpnp76012';

$random1 = 'secret_key1';
$random2 = 'secret_key2';

$hash = md5($random1.$pass.$random2);
$self = $_SERVER['REQUEST_URI'];

// ************************************ //
// **********	USER LOGOUT  ********** //
// ************************************ //

if(isset($_GET['logout']))
{
	unset($_SESSION['login']);
}

// ******************************************* //
// **********	USER IS LOGGED IN	********** //
// ******************************************* //

if (isset($_SESSION['login']) && $_SESSION['login'] == $hash) {
	display_page();
	?>
<?php
}
// *********************************************** //
// **********	FORM HAS BEEN SUBMITTED	********** //
// *********************************************** //

else if (isset($_POST['submit'])) {

	if ($_POST['username'] == $username && $_POST['password'] == $password){

		//IF USERNAME AND PASSWORD ARE CORRECT SET THE LOG-IN SESSION
		$_SESSION["login"] = $hash;
		header("Location: $_SERVER[PHP_SELF]");

	} else {

		// DISPLAY FORM WITH ERROR
		display_login_form();
		echo '<p>Username or password is invalid</p>';

	}
}


// *********************************************** //
// **********	SHOW THE LOG-IN FORM	********** //
// *********************************************** //

else {

	display_login_form();

}


function display_login_form(){ ?>

<form action="<?php echo $self; ?>" method='post'>
	<label for="username">username</label> <input type="text"
		name="username" id="username"> <label for="password">password</label>
	<input type="password" name="password" id="password"> <input
		type="submit" name="submit" value="submit">
</form>

<?php } 

function display_page(){
	header('Content-Type: text/html; charset=UTF-8');
	
	$hostprod = "10.254.160.13";
	$hostpre = "10.10.10.5";
	
	$key = array_keys($_POST);
	
	$key = $key[0];
	
	if ($key!="") {
	
		$host = $hostprod;
	
		switch($key){
			case "prepro";
			$host = $hostpre;
			break;
		}
	
		$memcache_obj = new Memcache;
		if ($memcache_obj->connect($host, 11211)){
	
	
			switch($key){
				case "prepro":
				case "prod":
					if ($memcache_obj->flush())
						echo "All $host cache deleted ".date('d/m/Y H:i:s');
					 else
					 	echo "Error on cache flush all";
	
					 	//echo "flush $host $key";
					 	break;
					 	case "id_doc":
					 	if ($_POST["id_doc"]!=""){
					 			
					 		if ($memcache_obj->delete($_POST["id_doc"]."ca"))
					 			echo "$host - ".$_POST["id_doc"]."ca cache deleted ".date('d/m/Y H:i:s')."<br/>";
					 		else
					 			echo "$host - ".$_POST["id_doc"]."ca Error on cache delete - variable doesn't exist in cache<br/>";
	
					 		if ($memcache_obj->delete($_POST["id_doc"]."es"))
					 			echo "$host - ".$_POST["id_doc"]."es cache deleted ".date('d/m/Y H:i:s')."<br/>";
						 	else
						 		echo "$host - ".$_POST["id_doc"]."es Error on cache delete - variable doesn't exist in cache<br/>";
						 		
						 	if ($memcache_obj->delete($_POST["id_doc"]."en"))
					 		echo "$host - ".$_POST["id_doc"]."en cache deleted ".date('d/m/Y H:i:s')."<br/>";
					 		else
						 		echo "$host - ".$_POST["id_doc"]."en Error on cache delete - variable doesn't exist in cache<br/>";
						 		
						 	//echo "delete $host $key ".$_POST["id_doc"];
						}
					 	break;
					 	default:
					 	if ($key=="key") $key=$_POST['key'];
					 		
					 	if ($memcache_obj->delete($key))
					 	echo "$host - $key cache deleted ".date('d/m/Y H:i:s')."<br/>";
					 	else
					 	echo "$host - $key Error on cache delete - variable doesn't exist in cache<br/>";
					 		
					 	//echo "delete $host $key";
					 	break;
		}
	
		$memcache_obj->close();
	
					 	} else {
			echo "No s'ha podut conectar al servidor ";
		}
	}
	
	?>
	<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
	<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="ca" lang="ca">
	<head>
	<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
	<title>Guia de Barcelona - Gestió de la Cache</title>
	<meta name="title" content="Guia de Barcelona - Ajuntament de Barcelona"></meta>
	<meta http-equiv="CONTENT-LANGUAGE" content="ca"></meta>
	<meta http-equiv="EXPIRES" content="0"></meta>
	<meta name="RESOURCE-TYPE" content="DOCUMENT"></meta>
	<meta name="DISTRIBUTION" content="GLOBAL"></meta>
	<meta name="AUTHOR" content="Ajuntament de Barcelona"></meta>
	<meta name="ROBOTS" content="INDEX, FOLLOW"></meta>
	<meta name="REVISIT-AFTER" content="1 DAYS"></meta>
	<meta name="RATING" content="GENERAL"></meta>
	<meta name="GENERATOR"
		content="Copyright 2013 by Ajuntament de Barcelona"></meta>
	<style>
	.cform {
		background: #f8f8f8;
		border: 1px solid #e5e5e5;
		padding: 10px;
		width: auto;
		margin: 10px;
		float: left;
	}
	</style>
	</head>
	<body>
		<h1>Gestió de la Cache GUIA BCN i CANALS</h1>
		<p>	Hello, you have successfully logged in! <a href="?logout=true">Logout?</a></p>
		<!--  
		<div class="cform">
			<h2>Cache del ID PRODUCCIÓ, Canals, drupals i altres</h2>
			<form name="input1" action="gestiocache.php" method="post">
				id : <input type="text" name="id_doc"> <input type="submit"
					value="Borrar cache del ID GUIA PRODUCCIÓ ">
				<p>Borrar la informació de un ID per a els tots els canals</p>
			</form>
		</div>
		
		<div class="cform">
			<h2>Gestió per altres Caches PRODUCCIÓ </h2>
			<form name="input1" action="gestiocache.php" method="post">
				Key : <input type="text" name="key"> <input type="submit"
					value="Borrar una variable de PRODUCCIÓ">
				<p>Borrar una variable cache. Ej: Per borrar la home mobile posar el nom del fitxer XSL : mobileguiabcn_ca</p>
			</form>
		</div>
		-->

	
		<div class="cform">
			<h2>Cache HOME GUIA Producció</h2>
			<form name="input2" action="gestiocache.php" method="post">
				<input type="hidden" name="guiabcn_ca"> <input type="submit"
					value="Borrar home GUIA PRODUCCIÓ - CATALA">
			</form>
			<form name="input3" action="gestiocache.php" method="post">
				<input type="hidden" name="guiabcn_es"> <input type="submit"
					value="Borrar home GUIA PRODUCCIÓ - ESPANYOL">
			</form>
			<form name="input4" action="gestiocache.php" method="post">
				<input type="hidden" name="guiabcn_en"> <input type="submit"
					value="Borrar home GUIA PRODUCCIÓ - ENGLISH">
			</form>
		</div>
		<!--
		<div class="cform">
			<h2>Cache HOME Escoles Producció</h2>
			<form name="input3" action="gestiocache.php" method="post">
				<input type="hidden" name="escoles_ca"> <input type="submit"
					value="Borrar home ESCOLES PRODUCCIÓ - CATALA">
			</form>
			<form name="input3" action="gestiocache.php" method="post">
				<input type="hidden" name="escoles_es"> <input type="submit"
					value="Borrar home ESCOLES PRODUCCIÓ - ESPANYOL">
			</form>
			<form name="input4" action="gestiocache.php" method="post">
				<input type="hidden" name="escoles_en"> <input type="submit"
					value="Borrar home ESCOLES PRODUCCIÓ - ENGLISH">
			</form>
		</div>
		  
		<div class="cform">
			<h2>Cache HOME Esports Producció</h2>
			<form name="input3" action="gestiocache.php" method="post">
				<input type="hidden" name="esports_ca"> <input type="submit"
					value="Borrar home ESPORTS PRODUCCIÓ - CATALA">
			</form>
			<form name="input3" action="gestiocache.php" method="post">
				<input type="hidden" name="esports_es"> <input type="submit"
					value="Borrar home ESPORTS PRODUCCIÓ - ESPANYOL">
			</form>
			<form name="input4" action="gestiocache.php" method="post">
				<input type="hidden" name="esports_en"> <input type="submit"
					value="Borrar home ESPORTS PRODUCCIÓ - ENGLISH">
			</form>
		</div>
		-->
		<div class="cform">
			<h2>Cache Producció - ATENCIÓ !!!!!</h2>
			<form name="input4" action="gestiocache.php" method="post">
				<input type="hidden" name="prod"> <input type="submit"
					value="Borrar tota la cache PRODUCCIÓ">
				<p>Aquesta acció s'ha de fer en moments de poc tràfic. Es recomana
					24h-8h.</p>
			</form>
		</div>
	<!--  
		<div class="cform">
			<h2>Cache PRE-Producció</h2>
			<form name="input4" action="gestiocache.php" method="post">
				<input type="hidden" name="prepro"> <input type="submit"
					value="Borrar tota la cache pre-pro">
	
			</form>
		</div>
	-->	
		<div class="cform">
			<h2>Totes les variables de cache producció</h2>
			<?php echo file_get_contents("http://guia.bcn.cat/mstats25.php");?>
		</div>
		
	</body>
	</html>
		
<?php }
?>

