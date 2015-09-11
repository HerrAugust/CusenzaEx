<?php
  function creaDB($link){ 
  	$r = mysql_query('CREATE DATABASE IF NOT EXISTS CentroElaborazione');
  	if(!$r)
  		die('Errore nella creazione del database');
  	mysql_select_db('CentroElaborazione');

  	$query=array('create table if not EXISTS servizio (id integer primary key)',
  		'create table if not exists operatore (matricola integer primary key,
      nome varchar(15),
indirizzo varchar(25))',
'create table if not exists apparato (inventory integer primary key,
rackCorridoio smallint,
rackLato char(3),
rackFila smallint,
produttore varchar(10),
modello varchar(10),
alimentazione varchar(10),
hw varchar(20),
posizione smallint not null,
soglia smallint default 20 not null,
occupazioneRack smallint not null,
tipo varchar(25) not null,
unique(rackCorridoio, rackLato, rackFila) )',
'create table if not exists configurazione (backup varchar(20) primary key,
datastorage_archiviare integer references
apparato(inventory),
servizio_archiviare smallint references
servizio(id),apparato_erogare integer references
apparato(inventory),
servizio_erogare smallint references
servizio(id))',
'create table if not exists connettore (ID smallint primary key,
tipologia varchar(20) not null check(value
in("alimentazione","trasmissione")),
tecnologia varchar(20),
apparato integer references apparato(inventory),
cavo varchar(6) references cavo(targhetta))',
'create table if not exists cavo (targhetta varchar(6) primary key,
tecnologia varchar(10) not null,
tipologia varchar(20) not null check(value
in("alimentazione", "trasmissione")),
standard varchar(20) not null,
latoA integer references apparato(inventory),
latoB integer references apparato(inventory),
IDconnettore1 smallint references connettore(id),
IDconnettore2 smallint references connettore(id))',
'create table if not exists diagnostica (dataora timestamp default CURRENT_TIMESTAMP,
servizio integer references servizio(id),
apparato integer references apparato(inventory),
temperatura smallint,
chilowatt smallint,
occupazione smallint,
traffico smallint,
soglia smallint not null default 100,
tipo varchar(20) not null,primary key (dataora,servizio,apparato) );',
'create table if not exists crescita(apparato int references apparato(inventory),
datum date,
trafficoCompleto int not null,
primary key(apparato, datum));',
'create table if not exists istallare (operatore integer references operatore(matricola),
apparato integer references apparato(inventory),
dataora timestamp not null DEFAULT CURRENT_TIMESTAMP,
codice smallint not null default 000,
primary key(operatore, apparato));',
'create table if not exists riconfigurare (operatore integer references
operatore(matricola),
apparato integer references apparato(inventory),
dataora timestamp not null DEFAULT CURRENT_TIMESTAMP,
codice smallint not null default 444,
primary key(operatore, apparato));',
'create table if not exists configurare (operatore integer references operatore(matricola),
servizio integer references servizio(id),
dataora timestamp not null DEFAULT CURRENT_TIMESTAMP,
codice smallint default 111 not null,
primary key(operatore, servizio));',
'create table if not exists accesso (operatore integer references operatore(matricola),
dataora_diagnostica timestamp DEFAULT CURRENT_TIMESTAMP,
servizio_diagnostica integer,
apparato_diagnostica integer,
codice smallint not null default 999,
dataora timestamp not null DEFAULT CURRENT_TIMESTAMP,primary key(operatore, dataora_diagnostica,
servizio_diagnostica, apparato_diagnostica),
foreign key(dataora_diagnostica,
servizio_diagnostica, apparato_diagnostica) references diagnostica(dataora,
servizio, apparato));',


'CREATE DEFINER=`root`@`localhost` TRIGGER `centroelaborazione`.`apparato_BEFORE_INSERT` BEFORE INSERT ON `apparato` FOR EACH ROW
BEGIN
if new.tipo != "rack" and new.tipo != "router" and new.tipo != "switch" and new.tipo != "server" and new.tipo != "data storage" and new.tipo != "UPS" and new.tipo != "impianto raffreddamento" then
  signal sqlstate "45000" set message_text = "tipo può essere solo uno tra: rack, router, switch, server, data storage, impianto raffreddamento, UPS";
end if;

if new.soglia is null or new.soglia < 0 then
  signal sqlstate "45000" set message_text = "soglia non può essere null o minore di 0";
end if;

IF strcmp(New.tipo, "rack") = 0 then 
  if new.racklato != "dx" and new.racklato != "sx" then
    signal sqlstate "45000" set message_text = "rackLato può essere solo uno tra: dx, sx";
    end if;
    
    if new.rackCorridoio < 0 or rackFila < 0 then
    signal sqlstate "45000" set message_text = "Valori non positivi per rackCorridoio o rackFila";
  end if;

  If New.rackCorridoio is null or New.rackFila is null or New.rackLato is null then 
    signal sqlstate "45000" set message_text = "Parametri non corretti per rack. Settare solo inventory, soglia, rackCorridoio, rackFila, rackLato, tipo. Non settare occupazioneRack e posizione";
  END IF; 
    set new.occupazioneRack = -1;
    set new.posizione = -1;
else
  If New.rackCorridoio is not null or New.rackFila is not null or New.rackLato is not null or new.occupazioneRack is null or new.occupazioneRack = 0 or new.posizione is null or new.posizione = 0 then 
    signal sqlstate "45000" set message_text = "Parametri non corretti per apparato non rack. Non settare rackCorridoio, rackFila, rackLato. Settare occupazioneRack e posizione"; 
  end if;
END IF;
END',

'CREATE DEFINER = CURRENT_USER  TRIGGER `centroelaborazione`.`archiviare` BEFORE INSERT ON `configurazione` FOR EACH ROW
begin
DECLARE type varchar(20); DECLARE done smallint DEFAULT 1; 
DECLARE cur1 CURSOR FOR select apparato.tipo from apparato join configurazione on apparato.inventory = NEW.datastorage_archiviare; 
DECLARE CONTINUE HANDLER FOR NOT FOUND SET done = 0; OPEN cur1;
myloop: LOOP  
IF !done THEN LEAVE myloop; END IF;
FETCH cur1 INTO type;
  IF strcmp(type,"router") != 0 THEN 
  SIGNAL SQLSTATE "45000"
  SET MESSAGE_TEXT = "Archiviazione permessa solo nei data storage";
LEAVE myloop; 
END IF;
END LOOP; CLOSE cur1; end',

'CREATE DEFINER = CURRENT_USER TRIGGER `centroelaborazione`.`cavo_BEFORE_INSERT` BEFORE INSERT ON `cavo` FOR EACH ROW
BEGIN  
DECLARE tipoA char(20); DECLARE tipoB char(20);   
DECLARE ftecnConn1 varchar(20); DECLARE ftecnConn2 varchar(20); DECLARE ftipConn1 varchar(20); DECLARE ftipConn2 varchar(20);
DECLARE done INT DEFAULT FALSE;  
DECLARE conn1 CURSOR FOR SELECT Connettore.tipologia, Connettore.tecnologia from cavo join connettore on New.IDconnettore1 = connettore.ID;
 DECLARE conn2 CURSOR FOR SELECT Connettore.tipologia, Connettore.tecnologia from cavo join connettore on New.IDconnettore2 = connettore.ID ;  
DECLARE appA CURSOR FOR SELECT Apparato.tipo from Apparato join Cavo on apparato.inventory = cavo.latoA;  DECLARE appB CURSOR FOR SELECT Apparato.tipo from Apparato join Cavo on apparato.inventory = cavo.latoB;  
DECLARE CONTINUE HANDLER FOR NOT FOUND SET done = TRUE;  
if new.tipologia != "trasmissione" and new.tipologia != "alimentazione" then
  signal sqlstate "45000" set message_text = "La tipologia deve essere trasmissione o alimentazione";
end if;
IF strcmp(New.tipologia, "trasmissione") = 0 THEN     IF strcmp(New.standard, "fibra ottica multimodale") <> 0 AND strcmp(New.standard, "rame") <> 0 THEN         SIGNAL SQLSTATE "45000" SET MESSAGE_TEXT = "Lo standard può essere o rame o fibra ottica multimodale";     END IF; END IF;   
OPEN conn1; OPEN conn2;  
myloop: LOOP FETCH conn1 INTO ftipConn1, ftecnConn1; FETCH conn2 INTO ftipConn2, ftecnConn2;  
IF done THEN   LEAVE myloop; END IF;    IF strcmp(ftipConn1, New.tipologia) != 0 or strcmp(ftipConn2, New.tipologia) != 0  THEN     SIGNAL SQLSTATE "45000" SET MESSAGE_TEXT = "Cavo.tipologia = alim/tx => Conn.tipologia = alim/tx"; END IF;  
IF strcmp(New.standard, "rame") = 0 THEN     IF strcmp(ftecnConn1, "RJ45") <> 0 OR strcmp(ftecnConn2, "RJ45") <> 0 THEN         SIGNAL SQLSTATE "45000" SET MESSAGE_TEXT = "La tecnologia del cavo deve essere RJ45";     END IF; END IF;  
IF strcmp(New.tipologia, "alimentazione") = 0 THEN     IF strcmp(New.tecnologia, "H05VV-F") <> 0 THEN         SIGNAL SQLSTATE "45000" SET MESSAGE_TEXT = "La tecnologia deve essere H05VV-F";     ELSE         IF strcmp(ftecnConn2, "C13") <> 0 OR strcmp(ftecnConn1, "C13") <> 0 THEN             SIGNAL SQLSTATE "45000" SET MESSAGE_TEXT = "La tecnologia dei connettori deve essere C13";         END IF;     END IF; END IF;  
END LOOP;  
CLOSE conn1; CLOSE conn2;      
SET done = FALSE; OPEN appA; OPEN appB;   
apploop: LOOP     FETCH appA INTO tipoA;      FETCH appB INTO tipoB;   
    IF done THEN          LEAVE apploop;      END IF;  
    IF (strcmp(tipoA, "switch") = 0 and strcmp(tipoB, "router") = 0) or (strcmp(tipoA, "router") = 0 and strcmp(tipoB, "switch") = 0) THEN         SET done = done;     ELSE            SIGNAL SQLSTATE "45000" SET MESSAGE_TEXT = "Vincoli di connessione: Server, UPS, IR, DS <-> Switch <-> Router";      END IF;      END LOOP;   
CLOSE appA; CLOSE appB;   
END',

'CREATE DEFINER=`root`@`localhost` TRIGGER `centroelaborazione`.`connettore_BEFORE_INSERT` BEFORE INSERT ON `connettore` FOR EACH ROW
BEGIN
declare done int default false;
declare fstandard varchar(20);
declare ftecnologia varchar(20);
declare cavi cursor for select cavo.standard, cavo.tecnologia from cavo join connettore on connettore.cavo = cavo.targhetta;
DECLARE CONTINUE HANDLER FOR NOT FOUND SET done = TRUE;

if new.tipologia != "alimentazione" and new.tipologia != "trasmissione" then
  signal sqlstate "45000" set message_text = "La tipologia può essere alimentazione o trasmissione";
end if;

if new.tecnologia is null then
  signal sqlstate "01000" set message_text = "Attenzione: i valori corretti per la tecnologia del connettore saranno impostati automaticamente all\'inserimento del cavo";
end if;
END',

'CREATE DEFINER = CURRENT_USER TRIGGER `centroelaborazione`.`diagnostica_AFTER_INSERT` AFTER INSERT ON `diagnostica` FOR EACH ROW 
BEGIN 
 declare ftipo varchar(20); 
    declare fapparato int; 
    declare fdatum date; 
	    select tipo into ftipo from apparato where inventory = New.apparato; 
    if strcmp(ftipo, "router") = 0 then 
  select apparato, datum into fapparato, fdatum from crescita where apparato = New.apparato and datum = New.dataora; 
        if fapparato is null and fdatum is null then 
   insert into crescita value(New.apparato, New.dataora, New.traffico); 
  else 
   update crescita set trafficocompleto = trafficocompleto + New.traffico where apparato = New.apparato and datum = New.dataora; 
        end if; 
    end if; 
END',

'CREATE DEFINER=CURRENT_USER TRIGGER `centroelaborazione`.`diagnostica_BEFORE_INSERT` BEFORE INSERT ON `diagnostica` FOR EACH ROW
BEGIN  
DECLARE done SMALLINT DEFAULT FALSE; DECLARE errore SMALLINT DEFAULT 0; DECLARE ftipo varchar(20); DECLARE fsoglia INT; DECLARE apparati CURSOR FOR select tipo, soglia from apparato where apparato.inventory = New.apparato; DECLARE CONTINUE HANDLER FOR NOT FOUND SET done = TRUE;  
OPEN apparati; myloop: LOOP FETCH apparati into ftipo, fsoglia; IF done THEN LEAVE myloop; END IF; IF fsoglia != New.soglia or strcmp(ftipo, New.tipo) != 0 then     SIGNAL SQLSTATE "45000" SET message_text = "Tipo o soglia inseriti non combaciano con quanto indicato nella tabella Apparato"; END IF;  
END LOOP;  
CLOSE apparati;  
if strcmp(tipo, "router") = 0 or strcmp(tipo, "switch") = 0 or strcmp(tipo, "server") = 0 then     if New.traffico is null or New.occupazione is not null or New.temperatura is not null or New.chilowatt is not null then  set errore = 1;     end if; elseif strcmp(tipo, "UPS") = 0 then     if New.chilowatt is null or New.traffico is not null or New.occupazione is not null or New.temperatura is not null then     set errore = 1;     end if; elseif strcmp(tipo, "data storage") = 0 then     if New.occupazione is null or New.chilowatt is not null or New.traffico is not null or New.temperatura is not null then     set errore = 1;     end if; else if New.temperatura is null or New.occupazione is not null or New.chilowatt is not null or New.traffico is not null then     set errore = 1;     end if; end if;  
if errore = 1 then     signal sqlstate "45000" set message_text = "Errore nel settaggio dei campi occupazione, traffico, chilowatt oppure temperatura"; end if;  
END',



'insert into operatore values (1,"Luigi", "Via Roma 2"), (2, "Ugo", "Via XX Settembre 19"), (3, "Matteo", "Via Roma 3"), (4, "Pino", "Via Roma 4");',

'insert into servizio values (1), (2), (3), (4), (5), (6), (7), (8), (9), (10);'
);
  	
  	for($i=0;$i<count($query);$i++){
  	  $result=mysql_query($query[$i], $link);
  	  if(!$result){
  	     echo 'Invalid query:'.mysql_error().'-'.$query[$i] . '</br>';
  	     return false;
  	  }
    }
    return true;
  }

  function databaseexists() {
  	if(mysql_select_db('CentroElaborazione'))
  		return true;
  	else
  		return false;
  }

  /*
  * Stampa a video la tabella relativa al risultato della query
  */
  function stampatabella($columns,$rows){
    echo '<!DOCTIPE html><link rel="stylesheet" type="text/css" href="general.css"/><table><tr>';
    for($i=0; $i < count($columns); $i++)
      echo '<th><b>' . $columns[$i] . '</b></th>';
    echo'</tr>';

    for($j=0; $j < mysql_num_rows($rows); $j++) {
        $row = mysql_fetch_row($rows);
        echo '<tr>';
        for($i=0; $i < count($columns); $i++)
          echo '<td>' . $row[$i] . '</td>';
        echo '</tr>';
    }

    echo '</table></br>';
}

  /*
  * Data una query di selezione restituisce le colonne che dovrebbe mostrare in un array
  */
  function trovacolonne($query) {
    $query = str_replace("select", "", $query);
    $query = preg_replace('/from(.*)/', '', $query);
    return explode(",", $query);
  }

?>
