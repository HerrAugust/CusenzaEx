/*
 * UNIX domain datagram socket: convertire in maiuscolo i datagram del client e rispedirglieli. Il client riceve i propri datagram dagli argomenti.
 */

#include "es2.h"

int main(int argc, char* argv[]) {
	struct sockaddr_un myadd, serveradd;
	char resp [30];

	//Rimuovo il vecchio client pathname (poichè statico lo faccio all'inizio)
	remove(CPATH); //non dimenticare perchè bloccherebbe il programma

	//preparo il mio indirizzo
	int fd = socket(AF_UNIX, SOCK_DGRAM, 0);
	memset(&myadd, 0, sizeof(struct sockaddr_un));//non dimenticare perchè bloccherebbe il programma
	strncpy(myadd.sun_path, CPATH, sizeof(myadd.sun_path)-1);
	myadd.sun_family = AF_UNIX;
	
	//mi connetto al mio indirizzo
	bind(fd, (struct sockaddr*)&myadd, sizeof(struct sockaddr_un));

	//preparo l'indirizzo del server
	memset(&serveradd, 0, sizeof(struct sockaddr_un)); //non dimenticare perchè bloccherebbe il programma
	strncat(serveradd.sun_path, SPATH, sizeof(serveradd.sun_path)-1);
	serveradd.sun_family = AF_UNIX;

	//invio gli argomenti e li ricevo e li stampo
	int i;
	for(i = 1; i < argc; i++) {
		int msglen = strlen(argv[i]);
		sendto(fd, argv[i], msglen, 0, (struct sockaddr*) &serveradd, sizeof(struct sockaddr_un));
		socklen_t len = sizeof(struct sockaddr_un);
		recvfrom(fd, resp, sizeof(resp), 0, (struct sockaddr*) &serveradd, &len);
		printf("Client-Ricevuto: %s\n", resp);
	}

	sendto(fd, "fine", strlen("fine"), 0, (struct sockaddr*) &serveradd, sizeof(struct sockaddr_un)); //permette al server di terminare correttamente
	close(fd);
	return 0;
}
