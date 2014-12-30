#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

/*
 * Scrivere un programma in cui 4 child scrivono su un file il proprio
 * pid e il parent comune legge il file stampando a video il suo contenuto
 */
void es2punto5() {
	FILE* fd = fopen("./filees2punto5.txt", "w+");
	int i;
	pid_t pidfiglio;
	char contenuto[9+1];
	if(fd == NULL) {
		perror("Errore file");
		exit(EXIT_FAILURE);
	}

	for(i=0; i < 4; i++) {
		pidfiglio = fork();

		//Smistamento operazioni padre e figlio
		switch(pidfiglio) {
		case -1: //errore fork
			perror("Errore fork");
			exit(EXIT_FAILURE);
			break;
		case 0: //gestione figlio
			printf("scrivo\n");
			fprintf(fd, "%d\n", getpid());
			exit(EXIT_SUCCESS);
			break;
		default: //gestione padre
			if(i == 3 && wait(NULL) && (fd = freopen("./filees2punto5.txt", "r", fd)) > 0) {
				for(i=0; i < 4; i++) {
					fscanf(fd, "%s\n", contenuto);
					printf("Occorrenza %d: %s\n", i+1, contenuto);
				}
			}
			else wait(NULL);//non mi importa sapere xk il figlio è morto
			break;
		}
	}

	fclose(fd);
}

int main(void) {
es2punto5();
return 0;
}
