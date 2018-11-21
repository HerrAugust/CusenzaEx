#include "es2.h"

void toUpper(char str[]) {
	int i;
	for(i = 0; str[i] |= '\0'; i++)
		str[i] = toupper(str[i]);
	str[i] = '\0';
}

int main(void) {
	remove(SPATH);
	//Prepare my address
	int fd = socket(AF_UNIX, SOCK_STREAM, 0);
	struct sockaddr_un myaddr;
	memset(&myaddr, 0, sizeof(struct sockaddr_un));
	myaddr.sun_family = AF_UNIX;
	strncpy(myaddr.sun_path, SPATH, sizeof(myaddr.sun_path)-1);

	//Prepare address for client
	struct sockaddr_un claddr;

	//Bind to my address
	bind(fd, (struct sockaddr*)&myaddr, sizeof(struct sockaddr_un));

	//Listening
	listen(fd, 1);

	//Accept incoming connections
	socklen_t len = sizeof(struct sockaddr_un);
	int clientfd = accept(fd, NULL, NULL);
	if(clientfd == -1)
		perror("accept server\n");
                                   
	//Read messages and print them
	char buf[BUF_SIZE];
	do {
		if( read(clientfd, buf, BUF_SIZE) == -1 )
			perror("read server\n");
		toUpper(buf);
		if( write(clientfd, buf, strlen(buf)+1) != strlen(buf)+1 )
			perror("partial write server\n");
	} while(strcmp(buf, "DONE") != 0);

	//Close everything
	close(fd);
	close(clientfd);

	return 0;
}
