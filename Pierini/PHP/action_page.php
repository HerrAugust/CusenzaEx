<?php
include 'utility.php'; #creaDB()

$link = false;

#connessione/creazione db
if(isset($_POST['creaDB'])) {
	$link = mysql_connect('localhost', 'root', 'MySQL');
	if($link == false)
		die('Ci sono problemi di collegamento al DBMS.');

	#se connessione ok
	if(databaseexists())
		die("Il database esiste già.");
	else
		if(creaDB($link))
			echo "Database creato correttamente";
		else
			echo "Ci sono dei problemi con la creazione del Database. Errore: " . mysql_errno() . "</br>";		
}
else #esegui query
{
	$link = mysql_connect('localhost', 'root', 'MySQL', 'CentroElaborazione');
	if($link == false)
		die('Ci sono problemi di collegamento al DBMS.');
	echo "La tua query:<b> ".$_POST['query']."</b></br></br>";
	if(strpos($_POST['query'], "create") !== FALSE)
		die("Vengono accettate solo query di inserimento!");
	
	$res = mysql_query($_POST['query'], $link);
	if(!$res)
		die ("Errore nell'esecuzione della query. Errore: " . mysql_errno());
	else
		echo "Ho eseguito la query";
}

mysql_close();
?>
