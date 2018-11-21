/**
 * Inviare il messaggio "Ciao server! Sono il client" al server, che a sua volta risponde "Ciao a te, client!" usando Datagram Socket.
 */

#include "es1.h"

int main(void) {
	struct sockaddr_un addresss, addressc;
	char buf[] = "Ciao server! Sono il client";

	int fd = socket(AF_UNIX, SOCK_DGRAM, 0);

	//preparo l'indirizzo del server
	memset(&addresss, 0, sizeof(struct sockaddr_un));
	addresss.sun_family = AF_UNIX;
	strncpy(addresss.sun_path, SPATH, sizeof(addresss.sun_path)-1);

	//preparo il mio indirizzo
	memset(&addressc, 0, sizeof(struct sockaddr_un));
	addressc.sun_family = AF_UNIX;
	snprintf( addressc.sun_path, sizeof(addressc.sun_path), CL_ADDR_FORMAT, (long) getpid() );

	//mi collego il mio indirizzo
	bind( fd, (struct sockaddr *) &addressc, sizeof(struct sockaddr_un) );

	//invio il messaggio
	sendto(fd, buf, sizeof(buf), 0, (struct sockaddr*) &addresss, sizeof(struct sockaddr_un) );
	socklen_t len = sizeof(struct sockaddr_un);
	recvfrom(fd, buf, sizeof(buf), 0, (struct sockaddr*) &addresss, &len);
	printf("Client-ricevuto: %s\n", buf);

	remove(addressc.sun_path);
	close(fd);
	return 0;
}