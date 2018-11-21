#include "es2.h"

int main(int argc, char** argv) {
	int fd = socket(AF_INET6, SOCK_DGRAM, 0), i;

	//Prepare server address
	struct sockaddr_in6 serveradd;
	memset(&serveradd, 0, sizeof(struct sockaddr_in6));
	serveradd.sin6_family = AF_INET6;
	serveradd.sin6_port = htons(PORT);

	for(i = 1; i < argc; i++) {
		//Send messages
		if( sendto(fd, argv[i], strlen(argv[i])+1, 0, (struct sockaddr*)&serveradd, sizeof(struct sockaddr_in6)) != strlen(argv[i])+1 )
			perror("client sendto");

		//Receive and print converted messages
		if( recvfrom(fd, argv[i], strlen(argv[i])+1, 0, NULL, NULL) != strlen(argv[i])+1 )
			perror("client recvfrom");
		printf("Client-Received: %s\n", argv[i]);
	}

	//Send "Done"
	if( sendto(fd, "Done", 5, 0, (struct sockaddr*)&serveradd, sizeof(struct sockaddr_in6)) != 5 )
		perror("Failed to send \"Done\" to server. Must be done manually");

	return 0;
}