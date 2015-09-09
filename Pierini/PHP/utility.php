<?php
  function creaDB($link){ 
  	$query=array("CREATE DATABASE IF NOT EXISTS CentroElaborazione",
  		"create table if not EXISTS servizio (id integer primary key)",
  		"create table if not exists operatore (matricola integer primary key,
      nome varchar(15),
indirizzo varchar(25))",
"create table if not exists apparato (inventory integer primary key,
rackCorridoio smallint,
rackLato char(2) check (value in (\"dx\", \"sx\") ),
rackFila smallint,
produttore varchar(10),
modello varchar(10),
alimentazione varchar(10),
hw varchar(20),
posizione smallint not null,
soglia smallint default 20 not null,
occupazioneRack smallint not null,
tipo varchar(25) not null check(value in(\"server\",
\"data storage\", \"switch\", \"router\", \"ups\", \"impianto raffreddamento\",
\"rack\")),
unique(rackCorridoio, rackLato, rackFila) )","create table if not exists configurazione (backup varchar(20) primary key,
datastorage_archiviare integer references
apparato(inventory),
servizio_archiviare smallint references
servizio(id),apparato_erogare integer references
apparato(inventory),
servizio_erogare smallint references
servizio(id))",
"create table if not exists connettore (ID smallint primary key,
tipologia varchar(20) not null check(value
in(\"alimentazione\",\"trasmissione\")),
tecnologia varchar(20),
apparato integer references apparato(inventory),
cavo varchar(6) references cavo(targhetta))",
"create table if not exists cavo (targhetta varchar(6) primary key,
tecnologia varchar(10) not null,
tipologia varchar(20) not null check(value
in(\"alimentazione\", \"trasmissione\")),
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
servizio, apparato));");
  	for($i=0;$i<count($query);$i++){
  	  $result=mysql_query($query[$i], $link);
  	  if(!$result){ 
  	     echo('Invalid query:'.mysql_error().'-'.$query[$i]);
  	     return false;
  	  }
    }
    return true;
  }

  function databasenotexists() {
  	if(mysql_select_db('CentroElaborazione')) {
  		return true;
  	}
  	else return false;
  }
?>
