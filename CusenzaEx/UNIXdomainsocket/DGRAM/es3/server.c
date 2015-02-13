/**
 * Write a program in which, using Datagram Sockets, server accepts two connections and, for each of them, it takes a message from client
 * and writes it onto the STDOUT_FILENO. Clients (3) take their messages from "input" file (one message per line).
 * Client2
 */

#include "es3.h"

int main(void) {
	//create new socket and remove old file ( in fact I have to bind() )
	remove(SPATH);
	int fd = socket(AF_UNIX, SOCK_DGRAM, 0), i;

	struct sockaddr_un myadd;
	memset(&myadd, 0, sizeof(struct sockaddr_un));
	myadd.sun_family= AF_UNIX;
	strncpy(myadd.sun_path, SPATH, sizeof(struct sockaddr_un)-1);


	bind(fd, (struct sockaddr*)& myadd, sizeof(struct  sockaddr_un));

	//take messages and print them
	char msg[BUF_SIZE];
	for(i = 0; i < 3; i++) {
		ssize_t rb = recvfrom(fd, msg, BUF_SIZE, 0, NULL, NULL); //NULL because I am not interested in the source address because I don't have to send back msg
		if(rb == -1)
			printf("recvfrom server");
		printf("Server-Read: %s\n", msg);
	}

	close(fd);

	return 0;
}
