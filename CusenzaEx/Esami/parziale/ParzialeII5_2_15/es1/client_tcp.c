#include "es1.h"

int main(void) {
	int fd = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in server;
	memset(&server, 0, sizeof(struct sockaddr_in));
	server.sin_family = AF_INET;
	inet_pton(AF_INET, "localhost", &server.sin_addr);
	server.sin_port = htons(PORT);

	connect(fd, (struct sockaddr*)&server, sizeof(struct sockaddr_in));

	char buf[BUF_SIZE];
	while(1) {
		int readybytes = read(STDIN_FILENO, buf, BUF_SIZE);
		if(readybytes == 0) break;
		if(readybytes == -1) perror("client read");
		if( write(fd, buf, readybytes) != readybytes ) perror("write client");
	}

	return 0;
}