<!DOCTYPE html>
<html lang="it-IT">
<html>

<head>
	<title>Centro di elaborazione</title>
	<meta charset="UTF-8"/>
	<link rel="stylesheet" href="mainpage.css">
</head>

<body>
<?php echo "text"; ?>
	<h2>Entità e Relazioni</h2>

	<div id="inserimentoER">
	<div id="entita">
	<p>Voglio inserire un'entità:</p>
	<form action="action_page.php">
		<input type="text" placeholder="Apparato"></br>
		<input type="text" placeholder="Cavo"/></br>
		<input type="text" placeholder="Rack"/></br>
		<input type="text" placeholder="Backup di configurazione"/></br>
		<input type="text" placeholder="Servizio"/> </br>
		<input type="text" placeholder="Operatore"/> </br>
		<input type="text" placeholder="Attività"/> </br>
		<input type="text" placeholder="Centro di elaborazione"/> </br>
		<input type="submit" value="0K"/>
		<input type="submit" value="Cancella"/>
	</form>
	</div>

	<div id="associazioni">
	<p>Voglio inserire un'associazione tra entità:</p>
	<form>
		<input type="text" placeholder="Apparato"/> è allocato in <input type="text" placeholder="Rack"/> </br>
		<input type="text" placeholder="Apparato"/> è connesso a <input type="text" placeholder="Apparato"/> tramite <input type="text" placeholder ="Cavo"/> </br>
		<input type="text" placeholder="Servizio"/> è configurato in <input type="text" placeholder="Apparato"/> </br>
		<input type="text" placeholder="Backup di configurazione"/> riguarda <input type="text" placeholder="Apparato"/> e <input type="text" placeholder="Servizio"/> </br>
		<input type="text" placeholder="Rack"/> si trova in <input type="text" placeholder="Centro di elaborazione"/> </br>
		<input type="text" placeholder="Operatore"/> lavora in <input type="text" placeholder="Centro di elaborazione"/> </br>
		<input type="text" placeholder="Operatore"/> compie <input type="text" placeholder="Attività"/> </br>
		<input type="submit" value="0K"/>
		<input type="submit" value="Cancella"/>
	</form>
	</div>
	</div>


	<h2>Operazioni</h2>
	<div id="operazioni">
		<div id="op1" width="100px">
			<p>Operazione 1</p>
			<p>Realizzare il censimento degli apparati elencando per ciascuno di essi, oltre ai dati tecnici, anche l'allocazione del rack che lo contiene e la posizione all'interno del rack</p>
			<form>
				<input type="submit" value="0K"/>
			</form>
		</div>
		<div id="op2">
			<p>Operazione 2</p>
			<p>Dato un router si vogliono determinare gli switch direttamente collegati.</p>
			<form>
				<input type="text" placeholder="Router"/>
				<input type="submit" value="0K"/>
			</form>
		</div>
		<div id="op3">
			<p>Operazione 3</p>
			<p>Dato un router e un apparato ad esso connesso, si vuole determinare attraverso quali switch è realizzata la connessione (da notare che i percorsi sono duplicati e che gli switch coinvolti avranno in comune con l'apparato gli elementi di localizzazione ovvero corridoio o rack).</p>
			<form>
				<input type="text" placeholder="Router"/> connesso a <input type="text" placeholder="Apparato"/>
				<input type="submit" value="0K"/>
			</form>
		</div>
		<div id="op4">
			<p>Operazione 4</p>
			<p>Si vuole determinare quali apparati sono alimentati da un dato UPS (fare attenzione che gli UPS avranno anche collegamenti di trasmissione).</p>
			<form>
				<input type="text" placeholder="UPS"/>
				<input type="submit" value="0K"/>
			</form>
		</div>
		<div id="op5">
			<p>Operazione 5</p>
			<p>Dato un apparato si vogliono conoscere gli apparati ad esso direttamente collegati, riportando la tipologia e gli identificativi dei connettori e dei cavi utilizzati.</p>
			<form>
				<input type="text" placeholder="Apparato"/>
				<input type="submit" value="0K"/>
			</form>
		</div>
		<div id="op6">
			<p>Operazione 6</p>
			<p>Dato un servizio si vuole sapere su quali apparati è erogato.</p>
			<form>
				<input type="number" placeholder="Servizio"/>
				<input type="submit" value="0K"/>
			</form>
		</div>
		<div id="op7">
			<p>Operazione 7</p>
			<p>Dato un servizio su uno specifico apparato, si vuole recuperare la configurazione di backup.</p>
			<form>
				<input type="number" placeholder="Servizio"/>
				<input type="submit" value="0K"/>
			</form>
		</div>
		<div id="op8">
			<p>Operazione 8</p>
			<p>Elencare giornalmente i superamenti dei valori di soglia sui dati statistici, indicando l'apparato e l'ora in cui il superamento è avvenuto .</p>
			<form>
				<input type="submit" value="0K"/>
			</form>
		</div>
		<div id="op9">
			<p>Operazione 9</p>
			<p>Calcolare la crescita del volume di traffico su ciascun router rispetto al giorno precedente.</p>
			<form>
				<input type="submit" value="0K"/>
			</form>
		</div>
		<div id="op10">
			<p>Operazione 10</p>
			<p>Su base giornaliera, calcolare quale UPS, in quale ora, ha erogato il maggior picco di potenza.</p>
			<form>
				<input type="submit" value="0K"/>
			</form>
		</div>
		<div id="op11">
			<p>Operazione 11</p>
			<p>Elencare quali operatori sono abilitati all'installazione di apparati.</p>
			<form>
				<input type="submit" value="0K"/>
			</form>
		</div>
		<div id="op12">
			<p>Operazione 12</p>
			<p>Ritrovare i dati di accesso di un dato operatore.</p>
			<form>
				<input type="number" placeholder="Operatore"/>
				<input type="submit" value="0K"/>
			</form>
		</div>
		<div id="op13">
			<p>Operazione 13</p>
			<p>Dato un apparato ricostruire la cronologia di tutti gli interventi, indicando il tipo di attività e l'operatore che l'ha eseguita</p>
			<form>
				<input type="text" placeholder="Apparato"/>
				<input type="submit" value="0K"/>
			</form>
		</div>
	</div>

</body>

</html>