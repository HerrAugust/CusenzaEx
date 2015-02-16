	/*
Client:
Per ogni stringa digitata da linea di comando
crea un processo
crea una fifo su pathname
/tmp/fifocli[pid]
scrive sulla fifo il suo pid e la una stringa (es. il proprio nome)
 */

#include "es2.h"

static char mypath[BUF_SIZE];

void removefifo() {
	unlink(mypath);
}

int main(int argc, char** argv) {
	while(1) {
		char input[BUF_SIZE];
		printf("Inserire una stringa: ");
		scanf("%s", input);
		switch(fork()) {
			case -1: perror("fork");
			case 0:
			atexit(removefifo);
			sprintf(mypath, PATH, (long) getpid());
			mkfifo(mypath, 0666);

			struct request msg; msg.pid = (long) getpid(); strcpy(msg.stringa, argv[0]);

			int fdscrittura = open(STATICPATH, O_WRONLY);
			write(fdscrittura, &msg, sizeof(struct request));

			int fdlettura = open(mypath, O_RDONLY);
			struct response risposta;
			read(fdlettura, &risposta, sizeof(struct response));
			printf("Client-Ricevuto: %ld %s\n", risposta.codice, risposta.stringa);

			close(fdlettura);
			close(fdscrittura);
			_exit(EXIT_SUCCESS);
			default:
			break;
		}
	}

	return 0;
}