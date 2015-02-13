//Server

#include "es1.h"

int main(void) {
	remove(SPATH);

	//Prepare my address
	int sfd = socket(AF_UNIX, SOCK_STREAM, 0);

	struct sockaddr_un myaddr;
	memset(&myaddr, 0, sizeof(struct sockaddr_un));
	myaddr.sun_family = AF_UNIX;
	strncpy( myaddr.sun_path, SPATH, sizeof(myaddr.sun_path)-1 );

	//Bind to my address
	bind( sfd, (struct sockaddr*)&myaddr, sizeof(struct sockaddr_un) );

	//State I am listening
	listen( sfd, 5 );

	//Wait for messages
	int cfd = accept(sfd, NULL, NULL); //Not interested in sender address: I have its file descriptor!
	char buf[BUF_SIZE];
	read(cfd, buf, BUF_SIZE); //I have to read from my address: have to wake up when someone writes in my address
	printf("Server-Message: %s\n", buf);

	//Close all
	close(cfd);
	close(sfd);

	return 0;
}
