#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

int main(void) {

	int fd[2], fdfile;;
	pipe(fd);

	//ls
	switch(fork()) {
		case -1: perror("fork1"); break;
		case 0: //child:
		close(fd[0]);
		if(fd[1] != STDOUT_FILENO) {
			dup2(fd[1], STDOUT_FILENO);
			close(fd[1]);
		}
		execlp("ls", "ls", ".", (char*)NULL);
		perror("exec ls");
		default:
		break;
	}

	//sort -r > file.txt
	switch(fork()) {
		case -1: perror("fork2"); break;
		case 0: //child:
		fdfile = open("file.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);
		dup2(fdfile, STDOUT_FILENO);
		close(fdfile);

		close(fd[1]);
		if(fd[0] != STDIN_FILENO) {
			dup2(fd[0], STDIN_FILENO);
			close(fd[0]);
		}
		execlp("sort", "sort", "-r", (char*)NULL);
		perror("exec sort");
		default:
		break;
	}

	return 0;
}