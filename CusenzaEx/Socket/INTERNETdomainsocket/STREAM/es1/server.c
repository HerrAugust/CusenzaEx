#include "es1.h"

int main(void) {
	struct addrinfo hints;
	struct addrinfo* res;
	//Look for my address. Instead of:
	/*
	struct sockaddr_in server;
	memset(&server, 0, sizeof(struct sockaddr_in));
	server.sin_family = AF_INET;
	server.sin_port = htons(PORT); 
	*/
	memset( &hints, 0, sizeof(struct addrinfo) );
	hints.ai_canonname = NULL;
	hints.ai_addr = NULL;
	hints.ai_next = NULL;
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE | AI_NUMERICSERV;
	getaddrinfo(NULL, "50000", &hints, &res);

	int opt = 1, fd;
	struct addrinfo* cur;
	for(cur = res; cur != NULL; cur = cur->ai_next) {
		fd = socket(cur->ai_family, cur->ai_socktype, cur->ai_protocol);
		if(fd == -1) continue;
		if( setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1 )
			perror("server setsockopt");
		if( bind(fd, cur->ai_addr, cur->ai_addrlen) == 0 )
			break;
		else
			close(fd);
	}

	if(cur == NULL)
		perror("no server address in server");
	freeaddrinfo(res);

	listen(fd, 1);
	int cfd = accept(fd, NULL, NULL);
	char buf[BUF_SIZE];
	if( read(cfd, buf, BUF_SIZE) == -1 )
		perror("server read");
	printf("Server-Read: %s\n", buf);

	strcpy(buf, "Ciao to you, client!");
	if( write(cfd, buf, strlen(buf)+1) != strlen(buf)+1 )
		perror("server write");

	return 0;
}