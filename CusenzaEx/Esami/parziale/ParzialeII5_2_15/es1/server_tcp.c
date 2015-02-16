#include "es1.h"

#define BACKLOG 0

int main(void) {
	//preparo l'address del server
	int fd = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in myaddr;
	memset(&myaddr, 0, sizeof(struct sockaddr_in));
	myaddr.sin_family = AF_INET;
	inet_pton(AF_INET, "localhost", &myaddr.sin_addr); //attenzione
	myaddr.sin_port = htons(PORT); //attenzione

	//mi metto in attesa di richieste di connessione
	struct sockaddr_in client;
	socklen_t len = sizeof(struct sockaddr_in);
	bind(fd, (struct sockaddr*)&myaddr, sizeof(struct sockaddr_in));
	listen(fd, 0);
	int cfd = accept(fd, (struct sockaddr*)&client, &len);

	//finchè c'è da leggere copio il file
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