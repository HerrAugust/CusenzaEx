#ifndef ES2_H
#define ES2_H

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <signal.h>
#include <string.h>

#define BUF_SIZE 30
#define STATICPATH "/tmp/server"
#define PATH "/tmp/fifocli%ld"

struct request {
	char stringa[BUF_SIZE];
	long pid;
};

struct response {
	long codice;
	char stringa[BUF_SIZE+6];
};

#endif