<?php
include 'utility.php'; #creaDB()

#connessione/creazione db
if($_POST['creaDB']) {
	$link = mysql_connect('localhost', 'root', 'MySQL', '8080');
	if (!$link) {
		echo 'Connected unsuccessfully';
	}
	else { #connessione ok
		if(databasenotexists() && creaDB($link))
			echo "Database creato correttamente";
		else
			die('Ci sono dei problemi con la creazione del Database' . mysql_errno());
	}
		
}
else #esegui query
{
	$pieces = explode(' ', $_POST['query']);
	if($pieces == false or strcmp($pieces[0], "insert") !== 0 or strcmp($pieces[1], "into") !== 0)  {
		die('La query richiesta non è corretta. Vengono accettate solo quelle di inserimento!');
	}
	else {
		$res = mysql_query($_POST['query']);
		if(!$res)
			die("Errore nell'esecuzione della query: " . mysql_errno());
	}
}

?>
