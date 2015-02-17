#include "es2.h"

int main(int argc, char** argv) {
	if(argc < 3)
		perror("Not enough arguments\n");

	//Determine server address and connect
	int fd, opt = 1;
	struct addrinfo hints, *cur, *result;
	memset(&hints, 0, sizeof(struct sockaddr));
	hints.ai_canonname = NULL;
	hints.ai_next = NULL;
	hints.ai_addr = NULL;
	hints.ai_flags = AI_NUMERICSERV;
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	getaddrinfo(argv[1], argv[2], &hints, &result);
	//Byte sharing
	for(cur = result; cur != NULL; cur = cur->ai_next) {
		fd = socket(cur->ai_family, cur->ai_socktype, cur->ai_protocol);
		if(fd == -1) continue;
		if( connect(fd, cur->ai_addr, cur->ai_addrlen) == 0 ) break;
		if( setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1 ) perror("setsockopt client");
		close(fd);
	}

	freeaddrinfo(result);
	if(cur == NULL) perror("cur is NULL in client");

	char buf[BUF_SIZE];
	while(1) {
		int readbytes = read(STDIN_FILENO, buf, BUF_SIZE);
		if(readbytes == -1) perror("read client");
		if(readbytes == 0) break;

		if( write(fd, buf, readbytes) != readbytes) perror("write client");
	}

	return 0;
}