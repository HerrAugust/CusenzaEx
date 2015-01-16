#include <stdio.h>
#include <fcntl.h>
#include "fifo_seqnum_server.h"

void removefifo() {
	unlink(FIFO_2SERVER);
}

int main(void) {
	mkfifo(FIFO_2SERVER);
	struct response response_var;
	struct request request_var;
	int total = 0;
	char FIFO_2client[FIFO_2CLIENT_LEN];

	atexit(removefifo);
	open(FIFO_2SERVER, O_WRONLY | O_NONBLOCK); //needed to make read block when there is no client. unused fd

	while(1) {
		int fdRead = open(FIFO_2SERVER, O_RDONLY | O_NONBLOCK);
		int flag = fcntl(fdRead, F_GETFL); flag &= ~O_NONBLOCK; fdRead = fcntl(fdRead, F_SETFL, flag);
		int byteread = read(fdRead, &request_var, sizeof(struct request));
		if(request_var.myNum != 1) { printf("Letti %d. Error\n", byteread); return 0; }
		printf("server (pid = %ld): Read %d\n", (long) getpid(), request_var.myNum);

		sprintf(FIFO_2client, FIFO_2CLIENT, request_var.pid);
		response_var.seqNum = total;
		int fdWrite = open(FIFO_2client, O_WRONLY);
		write(fdWrite, &response_var, sizeof(struct response));
		close(fdWrite);

		total += request_var.myNum;
		printf("total = %d\n", total);
	}

	return 0;
}