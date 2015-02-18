#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

void removefifo() { unlink("/tmp/provafifo"); }

int main(void) {
	char wtp[6];
	atexit(removefifo);

	mkfifo("/tmp/provafifo", 0666);
	int fd = open("/tmp/provafifo", O_RDONLY);
	int numread = read(fd, wtp, 6);
	if(numread == 0) //non si è bloccato e ha restituito 0 perchè il write end è chiuso
		puts("write end closed");

	close(fd);
	return 0;
}