#include "fifo_seqnum.h"
#include <sys/std.h>
#include <unistd.h>

int main(void) {
	struct msgS2C response;
	struct msgC2S request;
	char myfifo[SERVER2CLIENT_TEMPLATE_LEN];
	int fdWrite, fdRead;

	//prepare fifo where server will send to me the result
	sprintf(myfifo, SERVER2CLIENT_TEMPLATE, getpid());
	mkfifo(myfifo, 0666);

	//send message to server
	fdWrite = open(FIFO_2SERVER, O_WRONLY);
	request.seqNum = seqNum++;
	request.pid = getpid();
	write(fdWrite, &request, sizeof(struct msgC2S));

	//read reply from server
	fdRead = open(myfifo, O_RDONLY);
	read(fdRead, &response, sizeof(struct msgS2C));
}