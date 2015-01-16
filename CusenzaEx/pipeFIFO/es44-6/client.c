#include "fifo_seqnum_server.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

void removefifo() {
	unlink(FIFO_2SERVER);
	unlink(FIFO_2CLIENT);
}

int main(void) {
	atexit(removefifo);

	char FIFO_2client[FIFO_2CLIENT_LEN];
	struct response response_var;
	struct request request_var;

	sprintf(FIFO_2client, FIFO_2CLIENT, (long) getpid());
	request_var.pid = getpid();
	request_var.myNum = 1;

	mkfifo(FIFO_2SERVER);
	mkfifo(FIFO_2client);

	int fdWrite = open(FIFO_2SERVER, O_WRONLY);
	write(fdWrite, &request_var, sizeof(struct request));
	close(fdWrite);

	int fdRead = open(FIFO_2client, O_RDONLY);
	read(fdRead, &response_var, sizeof(struct response));
	printf("client (pid = %ld): seqNum = %d\n", (long) getpid(), response_var.seqNum);

	return 0;
}