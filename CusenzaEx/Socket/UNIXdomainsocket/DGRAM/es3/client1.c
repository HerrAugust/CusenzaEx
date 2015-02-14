/**
 * Write a program in which, using Datagram Sockets, server accepts two connections and, for each of them, it takes a message from client
 * and writes it onto the STDOUT_FILENO. Clients (3) take their messages from "input" file (one message per line).
 * Client1
 */

#include "es3.h"

int main(void) {
	//create socket
	int fd = socket(AF_UNIX, SOCK_DGRAM, 0), i;

	//prepare server address
	struct sockaddr_un svadd;
	memset(&svadd, 0, sizeof(struct sockaddr_un));
	svadd.sun_family = AF_UNIX;
	strncpy(svadd.sun_path, SPATH, sizeof(svadd.sun_path)-1);

	//prepare myaddress
	struct sockaddr_un myadd;
	memset(&myadd, 0, sizeof(struct sockaddr_un));
	myadd.sun_family = AF_UNIX;
	sprintf(myadd.sun_path, "/tmp/client1%ld", (long) getpid());

	//take message from file
	char msg[BUF_SIZE];
	int fdfile = open("input", O_RDONLY);
	for(i = 0; i < BUF_SIZE; i++)
		if(read(fdfile, msg+i, 1) == 1)
			if(*msg+i == '\n')
				break;
	if(i == BUF_SIZE) i--;
	*(msg+i) = '\0';
	printf("Client1-Message: %s\n", msg);

	//send to server
	sendto(fd, msg, sizeof(msg), 0, (struct sockaddr*) &svadd, sizeof(struct sockaddr_un));
	
	//close
	close(fd);
	close(fdfile);

	return 0;
}
