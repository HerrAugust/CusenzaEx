<?php
include 'utility.php'; #creaDB()

$link = mysql_connect('localhost', 'root', 'MySQL');
if($link == false)
	die('Ci sono problemi di collegamento al DBMS.');

#connessione/creazione db
if(isset($_POST['creaDB'])) {
	#se connessione ok
	if(databaseexists())
		die("Il database esiste già.");
	else
		if(creaDB($link))
			echo "Database creato correttamente";
		else
			echo "Ci sono dei problemi con la creazione del Database. Errore: " . mysql_error() . "</br>";		
	}
else #esegui query
{
	if(!mysql_select_db('CentroElaborazione'))
		die("Impossibile connettersi al DB CentroElaborazione. Errore: " . mysql_error());

	if(isset($_POST['eseguiQuery'])) #button "0K" in alto
	{
		echo "La tua query:<b> ".$_POST['query']."</b></br></br>";

		if(strpos($_POST['query'], "create") !== FALSE or strpos($_POST['query'], "*") !== false)
			die("Vengono accettate solo query di inserimento e selezione!</br>Inoltre non viene accettato il carattere * per problemi che si potrebbero verificare col disegnamento della tabella risultante dalla query.");

		#impossibile inserire valori in crescita
		if(strpos($_POST['query'], "crescita") !== false)
			die('Lo user non può inserire valori nella tabella Crescita.');

		$resg = mysql_query($_POST['query'], $link);
		if(!$resg)
			die ("Errore nell'esecuzione della query. Errore: " . mysql_error());
		else
			echo "Ho eseguito la query</br>";

		#duplicazione cavi
		if(strpos($_POST['query'], "insert into cavo") !== false)
		{
			$query2 = preg_replace("/\"\s*,/", "_2\",", $_POST['query'], 1);
			$res = mysql_query($query2, $link);
			if(!$res)
				die ("Errore nell'esecuzione della query di duplicazione del cavo. Errore: " . mysql_error());
			else
				echo "Ho eseguito la query di duplicazione del cavo</br>";
		}

		if(strpos($_POST['query'], "select") !== FALSE)
			stampatabella(trovacolonne($_POST['query']), $resg);

		if(strpos($_POST['query'], "show") !== FALSE)
			stampatabella(-1, $resg);

		if(strpos($_POST['query'], "select") !== false && !mysql_free_result($resg))
			echo "Problemi nella cancellazione del buffer della query. Errore: " . mysql_error() . ' Errno: ' . mysql_errno();
	}
	else {
		$numop;
		$cols;
		if(isset($_POST['op1']))
		{
			$numop = "1";
			$cols = array("Produttore", "Modello", "Alimentazione", "Hardware", "Posizione", "Occupazione Rack");
			$query = 'select produttore, modello, alimentazione, hw, posizione, occupazioneRack from apparato where strcmp(tipo, "rack") != 0;';
		}
		elseif(isset($_POST['op2']))
		{
			$numop = "2";
			$cols = array("Switch direttamente collegato");
			if(strlen($_POST['op2Param']) == 0)
				die("Parametro per operazione 2 non settato");
			$query = 'select latob from cavo join apparato on cavo.latob = apparato.inventory where cavo.latoa = ' . $_POST['op2Param'] .' and tipo = "switch";';
		}
		elseif(isset($_POST['op3']))
		{
			$numop = "3";
			$cols = array("Switch");
			if(strlen($_POST['op3Param1']) == 0 or strlen($_POST['op3Param2']) == 0)
				die("Parametro 1 o 2 non settato per operazione 3");
			$query = 'select c1.latob from (cavo c1 join cavo c2 on c1.latob = c2.latoa) join apparato on c2.latoa = apparato.inventory where apparato.tipo = "switch" and c1.latoa = ' . $_POST['op3Param2'] . ' and c2.latob = ' . $_POST['op3Param1'] . ';';
		}
		elseif(isset($_POST['op4']))
		{
			$numop = "4";
			$cols = array("Apparato");
			if(strlen($_POST['op4Param']) == 0)
				die("Parametro non settato per operazione 4");
			$query = 'select latob from cavo join apparato on cavo.latob = apparato.inventory where cavo.latoa = 1 and tipologia = "alimentazione" union select latoa from cavo join apparato on cavo.latoa = apparato.inventory where cavo.latob = ' . $_POST['op4Param'] . ' and tipologia = "alimentazione";';
		}
		elseif(isset($_POST['op5']))
		{
			$numop = "5";
			$cols = array("Apparato, Tipologia cavo/connettori, Connettore1, Connettore2, Targhetta");
			if(strlen($_POST[op5Param]) == 0)
				die("Parametro non settato per operazione 5");
			$query = 'select latob, tipologia, idconnettore1, idconnettore2, targhetta from cavo join apparato on cavo.latob = apparato.inventory where cavo.latoa = 1 union select latoa, tipologia, idconnettore1, idconnettore2, targhetta from cavo join apparato on cavo.latoa = apparato.inventory where cavo.latob = ' . $_POST['op5Param'];
		}
		elseif(isset($_POST['op6']))
		{
			$numop = "6";
			$cols = array("Apparato");
			if(strlen($_POST['op6Param']) == 0)
				die("Parametro non settato per operazione 6");
			$query = 'select apparato_erogare from configurazione where servizio_erogare = ' . $_POST['op6Param'];
		}
		elseif(isset($_POST['op7']))
		{
			$numop = "7";
			$cols = array("Backup, Data Storage");
			if(strlen($_POST['op7Param']) == 0)
				die("Parametro non settato per operazione 7");
			$query = 'select backup, datastorage_archiviare from configurazione where servizio_erogare = ' . $_POST['op7Param'] . ' and apparato_erogare = ' . $_POST['op7Param'];
		}
		elseif(isset($_POST['op8']))
		{
			$numop = "8";
			$cols = array("Apparato, Ora superamento");
			$query = 'CREATE DEFINER=CURRENT_USER PROCEDURE `operazione9`() BEGIN  
			DECLARE done SMALLINT DEFAULT FALSE; DECLARE fapparato INT; DECLARE fdataora TIMESTAMP;
			DECLARE ftemperatura, fchilowatt, foccupazione, ftraffico, fsoglia SMALLINT; DECLARE ftipo varchar(20);
			DECLARE fstatistica int; 
			DECLARE diagnostiche CURSOR FOR select dataora, apparato, temperatura, chilowatt, occupazione, traffico, soglia, tipo from diagnostica;
			DECLARE CONTINUE HANDLER FOR NOT FOUND SET done = TRUE;  
			DROP TABLE IF EXISTS tempop9;
			DROP TABLE IF EXISTS tempop9superamenti; CREATE TEMPORARY TABLE tempop9(inventory INT primary key, statistica INT); 
			CREATE TEMPORARY TABLE tempop9superamenti(inventory INT primary key, dataora TIMESTAMP);  
			OPEN diagnostiche; diagnostiche_loop: LOOP   
			FETCH diagnostiche INTO fdataora, fapparato, ftemperatura, fchilowatt, foccupazione, ftraffico, fsoglia, ftipo;  
			IF done THEN         LEAVE diagnostiche_loop;     END IF;    
			select statistica into fstatistica from tempop9 where inventory = fapparato;     
			if fstatistica is null then set fstatistica = 0; end if;        
			IF strcmp(ftipo, "router") = 0 or strcmp(ftipo,"switch") = 0 or strcmp(ftipo,"server") = 0 THEN     
			set fstatistica = fstatistica + ftraffico; ELSEIF strcmp(ftipo, "data storage") = 0 THEN        
			set fstatistica = fstatistica + foccupazione;     ELSEIF strcmp(ftipo, "UPS") = 0 THEN      
			set fstatistica = fstatistica + fchilowatt;     ELSE
			set fstatistica = fstatistica + ftemperatura;     END IF;       
			IF fstatistica > fsoglia THEN  
			INSERT INTO tempop9superamenti VALUE(fapparato, fdataora);    
			DELETE FROM tempop9 WHERE inventory = fapparato;    
			ELSE
			INSERT INTO tempop9 VALUE(fapparato, fstatistica);  
			END IF;      
			set done = false;    
			END LOOP;  
			close diagnostiche;  
			select * from tempop9superamenti;  
			END';
		}
		elseif(isset($_POST['op9']))
		{
			$numop = "9";
			$cols = array("Crescita di traffico");
			$query = 'CREATE DEFINER=CURRENT_USER PROCEDURE `operazione10new`() 
			BEGIN declare done int default false; 
			declare frouterid int; 
			declare sommaoggi int; 
			declare sommaieri int; 
			declare differenza int; 
			declare router int; 
			declare i int; 
			declare routers cursor for select inventory from apparato where tipo = "router"; 
			declare continue handler for not found set done = true;  
			drop table if exists tempop10; 
			create table tempop10(router int, datai date, differenza int default 0);  
				open routers; 
				myloop: loop 
				set i = 0; 
				fetch routers into router; 
				if done then leave myloop; end if; 

				internalloop: loop 
				set sommaoggi = 0; 
				set sommaieri = 0; 
				if i = 30 then leave internalloop; end if; 

				select trafficocompleto into sommaoggi from crescita where apparato = router and datum = date_sub(CURRENT_DATE, interval i day); 
				select trafficocompleto into sommaieri from crescita where apparato = router and datum = date_sub(CURRENT_DATE, interval i+1 day); 
				set differenza = sommaoggi-sommaieri; 
				if differenza != 0 then insert into tempop10 value(router, date_sub(CURRENT_DATE, interval i day), differenza); 
				end if; 
				set i = i + 1; 
				end loop; 
				end loop;  
				close routers; END ';
			}
			elseif(isset($_POST['op10']))
			{
				$numop = "10";
				$cols = array("Timestamp", "Apparato");
				$query = 'select d.dataora, d.apparato from diagnostica d where chilowatt in(select max(chilowatt) from diagnostica) ';
			}
			elseif(isset($_POST['op11']))
			{
				$numop = "11";
				$cols = array("Operatore");
				$query = 'select operatore from istallare;';
			}
			elseif(isset($_POST['op12']))
			{
				$numop = "12";
				$cols = array("Codice");
				if(strlen($_POST['op12Param']) == 0)
					die("Parametro non settato per operazione 12");
				$operatore = $_POST['op12Param'];
				$query = ' select istallare.codice from istallare where operatore = ' . $operatore . ' union select riconfigurare.codice from riconfigurare where operatore = ' . $operatore . ' 
				union select configurare.codice from configurare where operatore = ' . $operatore . ' union select accesso.codice from accesso where operatore = ' . $operatore;
			}
			elseif(isset($_POST['op13']))
			{
				$numop = "13";
				$cols = array("Tipo di attività", "Operatore", "Timestamp");
				if(strlen($_POST['op13Param']) == 0)
					die("Parametro non settato per operazione 13");
				$param = $_POST['op13Param'];
				$query = 'select "istallare", istallare.operatore, istallare.dataora from istallare where apparato = ' . $param . ' union select "riconfigurare", 
				riconfigurare.operatore, riconfigurare.dataora from riconfigurare where apparato = ' . $param;
			}

			echo 'Operazione ' . $numop;
			$res = mysql_query($query);
			if($res) {
				stampatabella($cols, $res);
				mysql_free_result($res);
			}
			else {
				die("Errore nell'esecuzione della query");
			}
		}

	}



	mysql_close();
	?>
