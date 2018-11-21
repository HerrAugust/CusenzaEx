#include <unistd.h>

#define FIFO_2SERVER "/tmp/seqnumfifo"
#define SERVER2CLIENT_TEMPLATE "/tmp/seqnum_%ld"
#define SERVER2CLIENT_TEMPLATE_LEN sizeof(SERVER2CLIENT_TEMPLATE) + 20

struct msgS2C {
	int total;
};

struct msgC2S {
	pid_t pid; //pid of child
	int seqNum;
};