#include "es1.h"
#include <netdb.h>

#define BACKLOG 0

int main(void) {
	//prepare address for server
	int fd = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in myaddr;
	memset(&myaddr, 0, sizeof(struct sockaddr_in));
	myaddr.sin_family = AF_INET;
	inet_pton(AF_INET, "localhost", &myaddr.sin_addr); //attention
	myaddr.sin_port = htons(PORT); //attention

	//Wait for connection request
	struct sockaddr_in client;
	socklen_t len = sizeof(struct sockaddr_in);
	bind(fd, (struct sockaddr*)&myaddr, sizeof(struct sockaddr_in));
	listen(fd, 0);
	int cfd = accept(fd, (struct sockaddr*)&client, &len);

	char service[BUF_SIZE], host[BUF_SIZE];
	getnameinfo((struct sockaddr*)&client, len, host, BUF_SIZE, service, BUF_SIZE, NI_NUMERICSERV);
	printf("Server-Accepted connection from (%s %s)\n", host, service);

	//Until there is something to be read
	char buf[BUF_SIZE];
	while(1) {
		int readbytes = read(cfd, buf, BUF_SIZE);
		if(readbytes == 0) break;
		if(readbytes == -1) perror("server read");
		if( write(STDOUT_FILENO, buf, readbytes) != readbytes ) perror("write server");
	}

	close(fd);
	close(cfd);
	return 0;
}
	
