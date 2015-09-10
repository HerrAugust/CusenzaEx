<?php
  function creaDB($link){ 
  	$r = mysql_query('CREATE DATABASE IF NOT EXISTS CentroElaborazione');
  	if(!$r)
  		die('Errore nella creazione del database');
  	mysql_select_db('CentroElaborazione');

  	$query=array("create table if not EXISTS servizio (id integer primary key)",
  		"create table if not exists operatore (matricola integer primary key,
      nome varchar(15),
indirizzo varchar(25))",
"create table if not exists apparato (inventory integer primary key,
rackCorridoio smallint,
rackLato char(2) check (value in ('dx', 'sx') ),
rackFila smallint,
produttore varchar(10),
modello varchar(10),
alimentazione varchar(10),
hw varchar(20),
posizione smallint not null,
soglia smallint default 20 not null,
occupazioneRack smallint not null,
tipo varchar(25) not null check(value in('server',
'data storage', 'switch', 'router', 'ups', 'impianto raffreddamento',
'rack')),
unique(rackCorridoio, rackLato, rackFila) )",
"create table if not exists configurazione (backup varchar(20) primary key,
datastorage_archiviare integer references
apparato(inventory),
servizio_archiviare smallint references
servizio(id),apparato_erogare integer references
apparato(inventory),
servizio_erogare smallint references
servizio(id))",
"create table if not exists connettore (ID smallint primary key,
tipologia varchar(20) not null check(value
in('alimentazione','trasmissione')),
tecnologia varchar(20),
apparato integer references apparato(inventory),
cavo varchar(6) references cavo(targhetta))",
"create table if not exists cavo (targhetta varchar(6) primary key,
tecnologia varchar(10) not null,
tipologia varchar(20) not null check(value
in('alimentazione', 'trasmissione')),
standard varchar(20) not null,
latoA integer references apparato(inventory),
latoB integer references apparato(inventory),
IDconnettore1 smallint references connettore(id),
IDconnettore2 smallint references connettore(id))",
"create table if not exists diagnostica (dataora timestamp,
servizio integer references servizio(id),
apparato integer references apparato(inventory),
temperatura smallint,
chilowatt smallint,
occupazione smallint,
traffico smallint,
soglia smallint not null default 100,
tipo varchar(20) not null,primary key (dataora,servizio,apparato) );",
"create table if not exists crescita(apparato int references apparato(inventory),
datum date,
trafficoCompleto int not null,
primary key(apparato, datum));",
"create table if not exists istallare (operatore integer references operatore(matricola),
apparato integer references apparato(inventory),
dataora timestamp not null,
codice smallint not null default 000,
primary key(operatore, apparato));",
"create table if not exists riconfigurare (operatore integer references
operatore(matricola),
apparato integer references apparato(inventory),
dataora timestamp not null,
codice smallint not null default 444,
primary key(operatore, apparato));",
"create table if not exists configurare (operatore integer references operatore(matricola),
servizio integer references servizio(id),
dataora timestamp not null,
codice smallint default 111 not null,
primary key(operatore, servizio));",
"create table if not exists accesso (operatore integer references operatore(matricola),
dataora_diagnostica timestamp,
servizio_diagnostica integer,
apparato_diagnostica integer,
codice smallint not null default 999,
dataora timestamp not null,primary key(operatore, dataora_diagnostica,
servizio_diagnostica, apparato_diagnostica),
foreign key(dataora_diagnostica,
servizio_diagnostica, apparato_diagnostica) references diagnostica(dataora,
servizio, apparato));",
"CREATE DEFINER = CURRENT_USER TRIGGER `centroelaborazione`.`diagnostica_AFTER_INSERT` AFTER INSERT ON `diagnostica` FOR EACH ROW 
BEGIN 
 declare ftipo varchar(20); 
    declare fapparato int; 
    declare fdatum date; 
	    select tipo into ftipo from apparato where inventory = New.apparato; 
    if strcmp(ftipo, 'router') = 0 then 
  select apparato, datum into fapparato, fdatum from crescita where apparato = New.apparato and datum = New.dataora; 
        if fapparato is null and fdatum is null then 
   insert into crescita value(New.apparato, New.dataora, New.traffico); 
  else 
   update crescita set trafficocompleto = trafficocompleto + New.traffico where apparato = New.apparato and datum = New.dataora; 
        end if; 
    end if; 
END",
"CREATE DEFINER = CURRENT_USER TRIGGER `centroelaborazione`.`apparato_BEFORE_INSERT` BEFORE INSERT ON `apparato` FOR EACH ROW 
BEGIN 
IF strcmp(New.tipo, 'rack') = 0 then 
 If New.rackCorridoio is null or New.rackFila is null or New.rackLato is null then 
  signal sqlstate '45000' set message_text = 'Parametri non corretti per rack. Settare solo inventory, soglia, rackCorridoio, rackFila, rackLato, tipo'; 
Else 
 If New.rackCorridoio is not null or New.rackFila is not null or New.rackLato is not null then Signal sqlstate '45000' set message_text = 'Parametri non corretti per apparato non rack. Non settare rackCorridoio, rackFila, rackLato'; 
End if; 
End if; 
end if;
END",
"CREATE DEFINER = CURRENT_USER TRIGGER `centroelaborazione`.`diagnostica_BEFORE_INSERT` BEFORE INSERT ON `diagnostica` FOR EACH ROW BEGIN  
DECLARE done SMALLINT DEFAULT FALSE; DECLARE errore SMALLINT DEFAULT 0; DECLARE ftipo varchar(20); DECLARE fsoglia INT; DECLARE apparati CURSOR FOR select tipo, soglia from apparato where apparato.inventory = New.apparato; DECLARE CONTINUE HANDLER FOR NOT FOUND SET done = TRUE;  
OPEN apparati; myloop: LOOP FETCH apparati into ftipo, fsoglia; IF done THEN LEAVE myloop; END IF; IF fsoglia != New.soglia or strcmp(ftipo, New.tipo) != 0 then     SIGNAL SQLSTATE '45000' SET message_text = 'Tipo o soglia inseriti non combaciano con quanto indicato nella tabella Apparato'; END IF;  
END LOOP;  
CLOSE apparati;  
if strcmp(tipo, 'router') = 0 or strcmp(tipo, 'switch') = 0 or strcmp(tipo, 'server') = 0 then     if New.traffico is null or New.occupazione is not null or New.temperatura is not null or New.chilowatt is not null then set errore = 1;     end if; elseif strcmp(tipo, 'UPS') = 0 then     if New.chilowatt is null or New.traffico is not null or New.occupazione is not null or New.temperatura is not null then     set errore = 1;     end if; elseif strcmp(tipo, 'data storage') = 0 then     if New.occupazione is null or New.chilowatt is not null or New.traffico is not null or New.temperatura is not null then     set errore = 1;     end if; else if New.temperatura is null or New.occupazione is not null or New.chilowatt is not null or New.traffico is not null then     set errore = 1;     end if; end if;  
if errore = 1 then     signal sqlstate '45000' set message_text = 'Errore nel settaggio dei campi occupazione, traffico, chilowatt oppure temperatura'; end if;  
END',
'H05VV-F';     ELSE         IF strcmp(ftecnConn2, 'C13') <> 0 OR strcmp(ftecnConn1, 'C13') <> 0 THEN             SIGNAL SQLSTATE '45000' SET MESSAGE_TEXT = 'La tecnologia dei connettori deve essere C13';         END IF;     END IF; END IF;  
END LOOP;  
CLOSE conn1; CLOSE conn2;      
apploop: LOOP     FETCH appA INTO tipoA;      FETCH appB INTO tipoB;   
    IF done THEN          LEAVE apploop;      END IF;  
    IF (strcmp(tipoA, 'switch') = 0 and strcmp(tipoB, 'router') = 0) or (strcmp(tipoA, 'router') = 0 and strcmp(tipoB, 'switch') = 0) THEN         SET done = done;     ELSE            SIGNAL SQLSTATE '45000' SET MESSAGE_TEXT = 'Vincoli di connessione: Server, UPS, IR, DS <-> Switch <-> Router';      END IF;      END LOOP;   
CLOSE appA; CLOSE appB;   
END ",
"CREATE TRIGGER vincolo BEFORE INSERT ON cavo BEGIN  
DECLARE tipoA char(20); DECLARE tipoB char(20);   
DECLARE ftecnConn1 varchar(20); DECLARE ftecnConn2 varchar(20); DECLARE ftipConn1 varchar(20); DECLARE ftipConn2 varchar(20); DECLARE done INT DEFAULT FALSE;  
DECLARE conn1 CURSOR FOR SELECT Connettore.tipologia, Connettore.tecnologia from cavo join connettore on New.IDconnettore1 = connettore.ID; DECLARE conn2 CURSOR FOR SELECT Connettore.tipologia, Connettore.tecnologia from cavo join connettore on New.IDconnettore2 = connettore.ID ;  
DECLARE appA CURSOR FOR SELECT Apparato.tipo from Apparato join Cavo on apparato.inventory = cavo.latoA;  DECLARE appB CURSOR FOR SELECT Apparato.tipo from Apparato join Cavo on apparato.inventory = cavo.latoB;  
DECLARE CONTINUE HANDLER FOR NOT FOUND SET done = TRUE;  
IF strcmp(New.tipologia, 'trasmissione') = 0 THEN     IF strcmp(New.standard, 'fibra ottica multimodale') <> 0 AND strcmp(New.standard, 'rame') <> 0 THEN         SIGNAL SQLSTATE '45000' SET MESSAGE_TEXT = 'Lo standard può essere o rame o fibra ottica multimodale';     END IF; END IF;   
OPEN conn1; OPEN conn2;  
myloop: LOOP FETCH conn1 INTO ftipConn1, ftecnConn1; FETCH conn2 INTO ftipConn2, ftecnConn2;  
IF done THEN   LEAVE myloop; END IF; IF strcmp(ftipConn1, New.tipologia) != 0 or strcmp(ftipConn2, New.tipologia) != 0  THEN     SIGNAL SQLSTATE '45000' SET MESSAGE_TEXT = 'Cavo.tipologia = alim/tx => Conn.tipologia = alim/tx'; END IF;  
IF strcmp(New.standard, 'rame') = 0 THEN     IF strcmp(ftecnConn1, 'RJ45') <> 0 OR strcmp(ftecnConn2, 'RJ45') <> 0 THEN         SIGNAL SQLSTATE '45000' SET MESSAGE_TEXT = 'La tecnologia del cavo deve essere RJ45';     END IF; END IF;  
IF strcmp(New.tipologia, 'alimentazione') = 0 THEN     IF strcmp(New.tecnologia, 'H05VV-F') <> 0 THEN         SIGNAL SQLSTATE '45000' SET MESSAGE_TEXT = 'La tecnologia deve essere H05VV-F';     ELSE         IF strcmp(ftecnConn2, 'C13') <> 0 OR strcmp(ftecnConn1, 'C13') <> 0 THEN             SIGNAL SQLSTATE '45000' SET MESSAGE_TEXT = 'La tecnologia dei connettori deve essere C13';         END IF;     END IF; END IF;  
END LOOP;  
CLOSE conn1; CLOSE conn2;      
SET done = FALSE; OPEN appA; OPEN appB;   
apploop: LOOP     FETCH appA INTO tipoA;      FETCH appB INTO tipoB;   
    IF done THEN          LEAVE apploop;      END IF;  
    IF (strcmp(tipoA, 'switch') = 0 and strcmp(tipoB, 'router') = 0) or (strcmp(tipoA, 'router') = 0 and strcmp(tipoB, 'switch') = 0) THEN         SET done = done;     ELSE            SIGNAL SQLSTATE '45000' SET MESSAGE_TEXT = 'Vincoli di connessione: Server, UPS, IR, DS <-> Switch <-> Router';      END IF;      END LOOP;   
CLOSE appA; CLOSE appB;   
END",
"CREATE TRIGGER archiviare BEFORE INSERT ON configurazione begin DECLARE type varchar(20); DECLARE done smallint DEFAULT 1; DECLARE cur1 CURSOR FOR select apparato.tipo from apparato join configurazione on apparato.inventory = NEW.datastorage_archiviare; DECLARE CONTINUE HANDLER FOR NOT FOUND SET done = 0; OPEN cur1; WHILE done DO  FETCH cur1 INTO type;  IF STRCMP(type,'router') <> 0 THEN   SIGNAL SQLSTATE '45000'         SET MESSAGE_TEXT = 'L'archiviazione è permessa solo nei data storage'; LEAVE;  END IF; END WHILE; CLOSE cur1; end ");
  	
  	for($i=0;$i<count($query);$i++){
  	  $result=mysql_query($query[$i], $link);
  	  if(!$result){
  	     echo 'Invalid query:'.mysql_error().'-'.$query[$i] . "</br>";
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
?>
