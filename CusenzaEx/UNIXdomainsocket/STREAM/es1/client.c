//Client. StreamSocket => NO BIND => DO NOT CREATE CLIENT ADDRRESS!

#include "es1.h"

int main(void) {
	//prepare server address
	int fd = socket(AF_UNIX, SOCK_STREAM, 0);
	
	struct sockaddr_un server;
	memset(&server, 0, sizeof(struct sockaddr_un));
	server.sun_family = AF_UNIX;
	strncpy( server.sun_path, SPATH, sizeof(server.sun_path)-1 );

	//connect to server
	connect(fd, (struct sockaddr*)&server, sizeof(struct sockaddr_un));	

	//Send message
	char msg[] = "Hello server! I am client";
	write(fd, msg, BUF_SIZE);
	
	return 0;
}