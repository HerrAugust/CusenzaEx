#include "es1.h"

int main(void)  {
	int fd = socket(AF_INET6, SOCK_DGRAM, 0);

	//Prepare client address to reply
	struct sockaddr_in6 clientaddr;

	//Prepare server address
	struct sockaddr_in6  serveraddr;
	memset(&serveraddr, 0, sizeof(struct sockaddr_in6));
	serveraddr.sin6_family = AF_INET6;
	serveraddr.sin6_port = htons(PORT); //port could be stored in little endian
	serveraddr.sin6_addr = in6addr_any; //wildcard address, i.e. address is "any"

	//Bind to server address
	if( bind(fd, (struct sockaddr*)&serveraddr, sizeof(struct sockaddr_in6)) == -1)
		perror("server bind\n");

	//Wait for message
	char buf[BUF_SIZE];
	socklen_t len = sizeof(struct sockaddr_in6);
	if( recvfrom(fd, buf, BUF_SIZE, 0, (struct sockaddr*) &clientaddr, &len) == -1 )
		perror("client recvfrom\n");
	printf("Server-Received: %s\n", buf);

	//Print who sent the message
	char clientstr[INET6_ADDRSTRLEN];
	inet_ntop( AF_INET6, &clientaddr.sin6_addr, clientstr, INET6_ADDRSTRLEN );
	printf("Server-Received message from %s\n", clientstr);

	//Send reply
	strcpy(buf, "Ciao to you, client!");
	sendto(fd, buf, strlen(buf)+1, 0, (struct sockaddr*)&clientaddr, sizeof(struct sockaddr_in6));

	return 0;
}