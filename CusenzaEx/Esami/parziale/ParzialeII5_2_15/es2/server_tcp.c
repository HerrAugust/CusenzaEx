#include "es2.h"

int main(int argc, char** argv) {
	if(argc != 3) // ./server.run, localhost, 50000, (char*) NULL
		perror("Not enough arguments!\n");

	//search for address
	int fd, opt = 1;
	struct addrinfo hints, *cur, *res;
	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_next = NULL;
	hints.ai_addr = NULL;
	hints.ai_canonname = NULL;
	hints.ai_flags = AI_PASSIVE | AI_NUMERICSERV;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_family = AF_UNSPEC;

	getaddrinfo(NULL, argv[2], &hints, &res); //argv[2] only because there is just a process per port
	for(cur = res; cur != NULL; cur = cur->ai_next) {
		fd = socket(cur->ai_family, cur->ai_socktype, cur->ai_protocol);
		if(fd == -1) continue;
		if( setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1 ) perror("server setsockopt");
		if( bind(fd, cur->ai_addr, cur->ai_addrlen) == 0 ) break;
		close(fd);
	}

	freeaddrinfo(res);
	if(cur == NULL) perror("cur");
	listen(fd, 1);
	int cfd = accept(fd, NULL, NULL);

	char buf[BUF_SIZE];
	while(1) {
		int readbyte = read(cfd, buf, BUF_SIZE);
		if(readbyte == -1) perror("read server");
		if(readbyte == 0) break;

		if( write(STDOUT_FILENO, buf, readbyte) != readbyte ) perror("write server");
	}

	close(cfd);
	close(fd);
	return 0;
}
