#include "es2.h"
#include <ctype.h> //toupper(int)

void toUpper(char str[]) {
	int i;
	for(i = 0; str[i] != '\0'; i++)
		str[i] = toupper(str[i]);
}

int main(void) {
	//Prepare server address
	int fd = socket(AF_INET6, SOCK_DGRAM, 0);
	struct sockaddr_in6 serveraddr;
	memset(&serveraddr, 0, sizeof(struct sockaddr_in6));
	serveraddr.sin6_family = AF_INET6;
	serveraddr.sin6_port = htons(PORT);

	//Bind to server address
	if( bind(fd, (struct sockaddr*)&serveraddr, sizeof(struct sockaddr_in6)) == -1 )
		perror("server bind");

	char buf[BUF_SIZE];
	char clientstr[INET6_ADDRSTRLEN];
	struct sockaddr_in6 clientaddr;
	socklen_t len = sizeof(struct sockaddr_in6);
	while(1) {
		//Wait for messages
		if( recvfrom(fd, buf, BUF_SIZE, 0, (struct sockaddr*)&clientaddr, &len) == -1)
			perror("server recvfrom");

		inet_ntop(AF_INET6, &clientaddr.sin6_addr, clientstr, INET6_ADDRSTRLEN);
		printf( "Server-Receive message from: (%s, %u)", clientstr, ntohs(clientaddr.sin6_port) );

		//Convert to upper and send back message
		if(strcmp(buf, "Done") == 0) break;
		toUpper(buf);

		if( sendto(fd, buf, strlen(buf)+1, 0,(struct sockaddr*)&clientaddr, sizeof(struct sockaddr_in6) ) != strlen(buf)+1 )
			perror("server sendto");
	}
	

	return 0;
}