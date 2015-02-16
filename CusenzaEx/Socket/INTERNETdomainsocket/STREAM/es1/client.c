#include "es1.h"

int main(void) {
	//Look for server address. Instead of:
	/*
	struct sockaddr_in server;
	memset(&server, 0, sizeof(struct sockaddr_in));
	server.sin_family = AF_INET;
	server.sin_port = htons(PORT); 
	*/
	struct addrinfo *res, hints, *cur;
	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_canonname = NULL;
	hints.ai_addr = NULL;
	hints.ai_next = NULL;
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_NUMERICSERV;
	if( getaddrinfo("localhost", "50000", &hints, &res) != 0)
		perror("client getaddrinfo");

	int opt = 1, fd;
	for(cur = res; cur != NULL; cur = cur->ai_next) {
		fd = socket(cur->ai_family, cur->ai_socktype, cur->ai_protocol);
		if(fd == -1) continue;
		if( connect(fd, cur->ai_addr, sizeof(struct sockaddr_in)) != -1)
			break;
		if( setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1 )
			perror("client setsockopt");
		close(fd);
	}

	if(cur == NULL)
		perror("no server address found in client");
	freeaddrinfo(res);

	char buf[BUF_SIZE] = "Hello server! I am client";
	if( write(fd, buf, strlen(buf)+1) != strlen(buf)+1 )
		perror("client write");

	if( read(fd, buf, BUF_SIZE) == -1 )
		perror("client read");
	printf("Client-Read: %s\n", buf);

	return 0;
}