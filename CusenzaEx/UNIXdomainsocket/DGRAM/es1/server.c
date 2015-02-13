/**
 * Inviare il messaggio "Ciao server! Sono il client" al server, che a sua volta risponde "Ciao a te, client!" usando Datagram Socket.
 */

#include "es1.h"

int main(void) {
	char resp[30];
	char buf[] = "Ciao a te, client!";
	struct sockaddr_un myaddress, clientaddress;

	int fd = socket(AF_UNIX, SOCK_DGRAM, 0);

	remove(SPATH);

	//preparo il mio indirizzo
	memset(&myaddress, 0, sizeof(struct sockaddr_un));
	myaddress.sun_family = AF_UNIX;
	strncpy( myaddress.sun_path, SPATH, sizeof(myaddress.sun_path)-1 );

	//collego fd al mio indirizzo
	bind( fd, (struct sockaddr *) &myaddress, sizeof(struct sockaddr_un) );

	//aspetto il messaggio e invio il mio
	socklen_t len = sizeof(struct sockaddr_un);
	recvfrom(fd, resp, sizeof(resp), 0, (struct sockaddr *) &clientaddress, &len );
	printf("Server-Ricevuto: %s\n", resp);
	sendto(fd, buf, sizeof(buf), 0, (struct sockaddr*) &clientaddress, len);

	return 0;
}