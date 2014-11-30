#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

 /*
  * Dimostrare che dup conserva i flag (in effetti viene copiato il puntatore allo stesso file description)
  */
  void es0() {
  	int fd = open("filees3.txt", O_CREAT | O_RDONLY, S_IRUSR | S_IWUSR);
  	int flag = fcntl(fd, F_GETFL);

  	int fd1 = dup(fd);
  	int flag_fd1 = fcntl(fd1, F_GETFL);

  	if( flag_fd1 & flag )
  		puts("ipotesi attesa: dup conserva le flag");
  	else
  		puts("ipotesi NON attesa: dup NON conserva le flag");
  }


/*
 * Dimostrare che CLOEXEC viene cancellata con dup
 */
 void es1() {
 	/*
 	 * Setto CLOEXEC per un file descriptor; duplico questo file descriptor e verifico che nel nuovo non c'è CLOEXEC
 	 */
 	 //apro il file
 	 int fd = open("filees3.txt", O_CREAT | O_RDONLY, S_IRUSR | S_IWUSR);

 	 //setto FD_CLOEXEC
 	 int flag = fcntl(fd, F_GETFD) | FD_CLOEXEC;
 	 fcntl(fd, F_SETFD, flag);

 	 //duplico
 	 int fd1 = dup(fd);

 	 //verifico la presenza di FD_CLOEXEC
 	 int flag_fd1 = fcntl(fd1, F_GETFD);
 	 if(flag_fd1 & FD_CLOEXEC)
 	 	puts ("ipotesi NON attesa: dup conserva FD_CLOEXEC");
 	 else
 	 	puts("ipotesi attesa: dup non conserva FD_CLOEXEC");
 }


 /*
  * Dimostrare che CLOEXEC viene cancellata con exec
  */
  void es2() {
  	fcntl(STDOUT_FILENO,F_SETFD,fcntl(STDOUT_FILENO, F_GETFD) | FD_CLOEXEC);

  	puts("Mi aspetto lamentele da parte di ls!");
  	execlp("ls", "ls", (char*)NULL);
  }

 /*
  * Dimostrare che CLOEXEC non viene settata con la open che non specifica O_CLOEXEC 
  */
  void es3() {
  	int fd = open("filees3.txt", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);

  	int flag = fcntl(fd, F_GETFD);

  	if(flag & FD_CLOEXEC)
  		puts("ci sta FD_CLOEXEC - ipotesi non attesa");
  	else
  		puts("NON ci sta FD_CLOEXEC - ipotesi ATTESA");
  }


int main(void) {
	es0();
	es1();
	es2();
	es3();

	return 0;
}
