#include "es2.h"

int main(int argc, char** argv) {
	//Prepare server address
	int fd = socket(AF_UNIX, SOCK_STREAM, 0);
	struct sockaddr_un svaddr;
	memset(&svaddr, 0, sizeof(struct sockaddr_un));
	svaddr.sun_family = AF_UNIX;
	strncpy( svaddr.sun_path, SPATH, sizeof(svaddr.sun_path)-1 );

	//Connect to server
	connect(fd, (struct sockaddr*)&svaddr, sizeof(struct sockaddr_un));

	int i;
	char buf[BUF_SIZE];
	for(i = 1; i < argc; i++) {
		//Send arguments
		if(write(fd, argv[i], strlen(argv[i])+1) != strlen(argv[i])+1 )
			perror("partial write client\n");
		if( read(fd, buf, strlen(argv[i])+1) != strlen(argv[i])+1 )
			perror("partial read client\n");
		printf("Client-Recived: %s\n", buf);
	}

	//Send "Done"
	char bufend[] = "Done";
	if( write(fd, bufend, strlen(bufend)+1) != strlen(bufend)+1 )
		perror("second write client\n");

	return 0;
}