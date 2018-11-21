/**
 * Scrivere un programma che mostri cosa succede se:
 * 1) entrambi gli ends sono aperti
 * 2) pipe reader aperto e pipe writer chiusa
 * 3) pipe reader chiusa e pipe writer aperta
 */

#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

static void run1();
static void run2();
static void run3();

int runcorrente = 0;

void handler(int s) {
	printf("run%d() ha mandato un %s\n", runcorrente, strsignal(s));
}

//Consiglio di fare 3 programmi distinti, uno per ogni run?() perchè si capisce meglio.
int main(void) {
	signal(SIGPIPE, handler);

	run1();
	run2();
	run3();

	return 0;
}

//Tutto 0K
void run1() {
	runcorrente = 1;
	printf("Entrambi gli ends sono aperti\n");
	int fd[2];
	char buf[5] = "PIPE";
	char ric[5];
	pipe(fd);
	switch(fork()) {
		case 0: //processo figlio
		close(fd[0]);
		if(write(fd[1], buf, 4) != 4)
			perror("run1()-il figlio non ha scritto\n");
		printf("run1()-Il figlio ha scritto\n");
		close(fd[1]);
		break;
		case -1:
		perror("Problema in run1()\n");
		break;
		default: //padre
		close(fd[1]);
		if(read(fd[0], ric, 4) != 4)
			perror("Errore padre run1()\n");
		ric[4] = '\0';
		printf("run1()-Letto: %s\n", ric);
		close(fd[0]);
	}
}

//run2() ha mandato un Broken pipe
//infatti non c'è nessuno che ascolta in lettura!
void run2() {
	runcorrente = 2;
	printf("Reader chiuso e writer aperto\n");
	int fd[2];
	char buf[5] = "PIPE";
	pipe(fd);
	switch(fork()) {
		case -1:
		perror("Problema in run2()\n");
		break;
		case 0: //figlio, scrive
		close(fd[0]);
		if(write(fd[1], buf, 4) == 4)
		printf("run2()-Il figlio ha scritto\n");
		close(fd[1]);
		break;
		default: //padre
		close(fd[0]);
		close(fd[1]);
	}
}

//Errore padre run3()
//Infatti sulla pipe c'è soltanto EOF, visto che tutti i writers sono chiusi
void run3() {
	runcorrente = 3;
	printf("Reader aperto e writer chiuso\n");
	int fd[2];
	char buf[5] = "ERRR";
	char ric[5];
	pipe(fd);
	switch(fork()) {
		case -1:
		perror("Problema in run3()\n");
		break;
		case 0: //figlio, scrive
		close(fd[0]);
		close(fd[1]);
		break;
		default: //padre
		close(fd[1]);
		if(read(fd[0], ric, 4) != 4) {
			perror("Errore padre run3()\n");
			printf("ric: %s", ric);
		}
		else {
			ric[4] = '\0';
			printf("run3()-Letto: %s\n", ric);
		}
		close(fd[0]);
	}
}