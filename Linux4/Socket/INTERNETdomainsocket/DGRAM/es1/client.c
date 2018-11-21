#include "es1.h"

int main(void)  {
	int fd = socket(AF_INET6, SOCK_DGRAM, 0);
	if(fd == -1)
		perror("client socket\n");
	
	//Prepare server address
	struct sockaddr_in6 serveraddr;
	memset(&serveraddr, 0, sizeof(struct sockaddr_in6));
	serveraddr.sin6_family = AF_INET6;
	serveraddr.sin6_port = htons(PORT); //port could be stored in little endian
	strcpy(serveraddr.sin6_addr, "::");

	//Send message to server
	char buf[BUF_SIZE] = "Hello server! I am client";
	if( sendto(fd, buf, strlen(buf)+1, 0, (struct sockaddr*)&serveraddr, sizeof(struct sockaddr_in6)) != strlen(buf)+1 )
		perror("sendto client\n");

	//Wait for reply
	recvfrom(fd, buf, BUF_SIZE, 0, NULL, NULL); //Don't have to give msg back => NULL
	printf("Client-Received: %s\n", buf);

	//Print server address
	inet_ntop( AF_INET6, &serveraddr.sin6_addr, buf, INET6_ADDRSTRLEN );

	return 0;
}