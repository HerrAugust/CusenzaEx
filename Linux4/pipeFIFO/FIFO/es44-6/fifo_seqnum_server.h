/*
 * Avoid denial-of-service attack
 */

#ifndef FIFO_SEQNUM_SERVER_H
#define FIFO_SEQNUM_SERVER_H

#include <unistd.h>

#define FIFO_2SERVER "/tmp/FIFO_2SERVER"
#define FIFO_2CLIENT "/tmp/response%ld"
#define FIFO_2CLIENT_LEN (sizeof(FIFO_2CLIENT) + 20) //20 for pid

struct response {
	int seqNum;
};

struct request {
	pid_t pid;
	int myNum;
};

#endif