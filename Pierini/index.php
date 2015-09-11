<!DOCTYPE html>
<html lang="it-IT">
<html>

<head>
	<title>Centro di elaborazione</title>
	<meta charset="UTF-8"/>
	<link rel="stylesheet" href="mainpage.css">
</head>

<body>
	<h2>Entità e Relazioni</h2>

	<div id="inserimentoER">
	<p>Voglio inserire una tupla in un'entità o in una relazione:</p>
	<form action="./PHP/action_page.php" method="post">
		<input id="txtinput" type="text" name="query" placeholder="Istruzione MySQL"></br>
		<input type="submit" name="eseguiQuery" value="0K"/>
		<input type="submit" name="creaDB" value="Crea Database"/>
		</form>
	</div>

	<br/>

	<h2>Operazioni</h2>
	<div id="operazioni">
		<div id="op1" width="100px">
			<p>Operazione 1</p>
			<p>Realizzare il censimento degli apparati elencando per ciascuno di essi, oltre ai dati tecnici, anche l'allocazione del rack che lo contiene e la posizione all'interno del rack</p>
			<form action="./PHP/action_page.php" method="post">
				<input type="submit" value="0K" name="op1"/>
			</form>
		</div>
		<div id="op2">
			<p>Operazione 2</p>
			<p>Dato un router si vogliono determinare gli switch direttamente collegati.</p>
			<form action="./PHP/action_page.php" method="post">
				<input type="text" placeholder="Router" name="op2Param"/>
				<input type="submit" value="0K" name="op2"/>
			</form>
		</div>
		<div id="op3">
			<p>Operazione 3</p>
			<p>Dato un router e un apparato ad esso connesso, si vuole determinare attraverso quali switch è realizzata la connessione (da notare che i percorsi sono duplicati e che gli switch coinvolti avranno in comune con l'apparato gli elementi di localizzazione ovvero corridoio o rack).</p>
			<form action="./PHP/action_page.php" method="post">
				<input type="text" placeholder="Router" name="op3Param1"/> connesso a <input type="text" placeholder="Apparato" name="op3Param2"/>
				<input type="submit" value="0K" name="op3"/>
			</form>
		</div>
		<div id="op4">
			<p>Operazione 4</p>
			<p>Si vuole determinare quali apparati sono alimentati da un dato UPS (fare attenzione che gli UPS avranno anche collegamenti di trasmissione).</p>
			<form action="./PHP/action_page.php" method="post">
				<input type="text" placeholder="UPS" name="op4Param"/>
				<input type="submit" value="0K" name="op4"/>
			</form>
		</div>
		<div id="op5">
			<p>Operazione 5</p>
			<p>Dato un apparato si vogliono conoscere gli apparati ad esso direttamente collegati, riportando la tipologia e gli identificativi dei connettori e dei cavi utilizzati.</p>
			<form action="./PHP/action_page.php" method="post">
				<input type="text" placeholder="Apparato" name="op5Param"/>
				<input type="submit" value="0K" name="op5"/>
			</form>
		</div>
		<div id="op6">
			<p>Operazione 6</p>
			<p>Dato un servizio si vuole sapere su quali apparati è erogato.</p>
			<form action="./PHP/action_page.php" method="post">
				<input type="number" placeholder="Servizio" name="op6Param"/>
				<input type="submit" value="0K"  name="op6"/>
			</form>
		</div>
		<div id="op7">
			<p>Operazione 7</p>
			<p>Dato un servizio su uno specifico apparato, si vuole recuperare la configurazione di backup.</p>
			<form action="./PHP/action_page.php" method="post">
				<input type="number" placeholder="Servizio" name="op7Param1"/>
				<input type="number" placeholder="Apparato" name="op7Param2"/>
				<input type="submit" value="0K" name="op7"/>
			</form>
		</div>
		<div id="op8">
			<p>Operazione 8</p>
			<p>Elencare giornalmente i superamenti dei valori di soglia sui dati statistici, indicando l'apparato e l'ora in cui il superamento è avvenuto .</p>
			<form action="./PHP/action_page.php" method="post">
				<input type="submit" value="0K" name="op8"/>
			</form>
		</div>
		<div id="op9">
			<p>Operazione 9</p>
			<p>Calcolare la crescita del volume di traffico su ciascun router rispetto al giorno precedente.</p>
			<form action="./PHP/action_page.php" method="post">
				<input type="submit" value="0K" name="op9"/>
			</form>
		</div>
		<div id="op10">
			<p>Operazione 10</p>
			<p>Su base giornaliera, calcolare quale UPS, in quale ora, ha erogato il maggior picco di potenza.</p>
			<form action="./PHP/action_page.php" method="post">
				<input type="submit" value="0K" name="op10"/>
			</form>
		</div>
		<div id="op11">
			<p>Operazione 11</p>
			<p>Elencare quali operatori sono abilitati all'installazione di apparati.</p>
			<form action="./PHP/action_page.php" method="post">
				<input type="submit" value="0K" name="op11"/>
			</form>
		</div>
		<div id="op12" action="./PHP/action_page.php" method="post">
			<p>Operazione 12</p>
			<p>Ritrovare i dati di accesso di un dato operatore.</p>
			<form action="./PHP/action_page.php" method="post">
				<input type="number" placeholder="Operatore" name="op12Param"/>
				<input type="submit" value="0K" name="op12"/>
			</form>
		</div>
		<div id="op13">
			<p>Operazione 13</p>
			<p>Dato un apparato ricostruire la cronologia di tutti gli interventi, indicando il tipo di attività e l'operatore che l'ha eseguita</p>
			<form action="./PHP/action_page.php" method="post">
				<input type="number" placeholder="Apparato" name="op13Param"/>
				<input type="submit" value="0K" name="op13"/>
			</form>
		</div>
	</div>

</body>

</html>
