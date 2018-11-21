#include "fifo_seqnum.h"
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>	

char myfifo[SERVER2CLIENT_TEMPLATE_LEN];

static void removeFIFO() {
	unlink(myfifo);
	printf("client: FIFO removed\n");
}

static void handler(int s) {
	removeFIFO();
	fflush(NULL);
	_exit(EXIT_SUCCESS);
}

int main(void) {
	struct msgS2C response;
	struct msgC2S request;
	int fdWrite, fdRead;

	atexit(removeFIFO);
	signal(SIGINT, handler);
	signal(SIGTERM, handler);

	//prepare fifo where server will send to me the result
	sprintf(myfifo, SERVER2CLIENT_TEMPLATE, getpid());
	mkfifo(myfifo, 0666);

	//send message to server
	fdWrite = open(FIFO_2SERVER, O_WRONLY);
	request.seqNum = 1;
	request.pid = getpid();
	write(fdWrite, &request, sizeof(struct msgC2S));
	printf("client: written pid %ld\n", (long) getpid());

	//read reply from server
	fdRead = open(myfifo, O_RDONLY);
	read(fdRead, &response, sizeof(struct msgS2C));
	printf("client: read %d\n", response.total);

	return 0;
}