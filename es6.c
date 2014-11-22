#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

/*
13.Un processo padre crea 2 processi figli e dopo 10 secondi di elaborazione chiama la system call wait().
Successivamente entra in un loop infinito all'interno del quale non è prevista wait().
Il primo processo figlio termina a seguito di un e rrore con exit(1) dopo 2 secondi, il secondo processo figlio termina correttamente
dopo 15 secondi con exit(0). Rispondere ai seguenti quesiti:
A. Restano dei processi Zombie nel sistema?
B. Spiegare cosa succede quando termina il primo processo figlio
C. Spiegare cosa succede quando termina il secondo processo figli
*/
void handlerchld0(int sig) {
	puts("child");
}

void run0() {
	signal(SIGCHLD, handlerchld0);

	switch(fork()) {
	case 0: //figlio
		sleep(2);
		puts("primo figlio muore");
		exit(1);
		break;
	case -1:
		perror("fork 1");
		break;
	default: break;
	}
	switch(fork()) {
	case 0:
		sleep (15);
		puts("secondo figlio muore");
		exit(0);
		break;
	case -1:
		perror("fork 2");
		break;
	default: break;
	}
	sleep (10);
	puts("Fine sleep parent");
	wait(NULL);
	puts("fine wait parent");
	//for(;;);
}

int main(void) {
  run0();
  return 0;
}
