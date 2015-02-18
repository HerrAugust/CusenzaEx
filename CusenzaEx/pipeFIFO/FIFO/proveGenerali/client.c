#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

void removefifo() { unlink("/tmp/provafifo"); }

int main(void) {
	atexit(removefifo);

	mkfifo("/tmp/provafifo", 0666);
	int fd = open("/tmp/provafifo", O_WRONLY);
	write(fd, "123456", 6);

	close(fd);
	return 0;
}