//$ ls /usr/include | cat > file.txtx	

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main(void) {
	int fd[2];
	pipe(fd);
	//ls /usr/include
	switch(fork()) {
		case -1:
		perror("fork1");
		case 0: //child: Apre la pipe, chiude input end, ridireziona lo STDOUT nella pipe (else, con exec, ls non vi potrebbe scrivere)
		close(fd[0]);

		//ls dà output alla pipe
		if(STDOUT_FILENO != fd[1]) {
			if( dup2(fd[1], STDOUT_FILENO) == -1 ) //fd[1] punta dove STDOUT punta e STDOUT viene eliminato
				perror("dup2 di ls");
			if( close(fd[1]) == -1 )
				perror("close di ls");
		}
		execlp("ls", "ls", "/usr/include", (char*) NULL);
		return 1;

		break;
		default:
		break;
	}

	//cat > file.txt
	switch(fork()) {
		case -1:
		perror("fork2");
		case 0: //child: Apre la pipe, chiude output end, ridireziona lo STDIN nella pipe (else, con exec, cat non vi potrebbe leggere), cambia lo STDOUT in "file.txt"
		close(fd[1]);
		
		//STDOUT -> file.txt
		int fdfile = open("file.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);
		if(fdfile == -1)
			perror("cat");
		if(STDOUT_FILENO != fdfile)
			if( dup2(fdfile, STDOUT_FILENO) == -1)
				perror("dup2 di cat");
		//cat riceve input dalla pipe
		if(STDIN_FILENO != fd[0]) {
			if( dup2(fd[0], STDIN_FILENO) == -1) //fd[0] punta dove STDIN punta e STDIN viene eliminato
				perror("dup2 di cat");
			if(close(fd[0]))
				perror("close di cat");
		}
		execlp("cat", "cat", (char*)NULL);
		return 1;

		break;
		default:
		break;
	}

	system("gedit ./file.txt");

	return 0;
}