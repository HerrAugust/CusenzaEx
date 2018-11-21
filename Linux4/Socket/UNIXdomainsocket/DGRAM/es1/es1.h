#include <stdio.h>
#include <sys/un.h>
#include <sys/socket.h>
#include <ctype.h>

#define CL_ADDR_FORMAT "/tmp/cl%ld"
#define SPATH "/tmp/server"