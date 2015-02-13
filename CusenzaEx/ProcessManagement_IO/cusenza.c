/*
 ============================================================================
 Name        : cusenza.c
 Author      : Agostino Mascitti
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

/*
 * Fare calcolare al figlio l' n-esimo numero di fibonacci
 */
void es5() {
	char n[4] = "-1";
	switch(fork()) {
	case 0: //child
		printf("numero di fibonacci: ");
		scanf("%s", n);
		execlp("../fibonacci/Debug/fibonacci", "fibonacci", n, NULL); //nota!! NULL xk char** argv deve essere ftt così
		break;
	case -1:
		perror("errore fork");
		exit(EXIT_FAILURE);
		break;
	default: //padre
		wait(NULL);
		printf("Completo!");
		break;
	}
}

void es4() {

}

/*
 * 3. Scrivere un programma che una volta aperto un file in O_RDWR genera
un child. I due processi eseguono rispettivamente
printf("parent"); printf("child");
con la differenza che il child scrive su file e parent su STDOUT.
 */
void es3() {
	int fd = open("filees3.txt", O_TRUNC | O_RDWR | O_CREAT, S_IWUSR | S_IRUSR);
	//Nota: mettendo anche O_EXCL darebbe errore: file exists (facendo due runs del programma)!! infatti questo non è il processo a creare il file (è stato qll precedente). Provare!
	char fds[] = "child";
	char fds1[] = "parent";
	if(fd == -1) {
		perror("errore fd");
		exit(EXIT_FAILURE);
	}

	pid_t child = fork();
	switch(child) {
	case 0: //child
		if(write(fd, fds, strlen(fds)) != strlen(fds)) {
			perror("errore child");
			exit(EXIT_FAILURE);
		}
		close(fd);
		break;
	case -1: //errore
		perror("errore");
		exit(EXIT_FAILURE);
	default:
		if(write(STDOUT_FILENO, fds1, strlen(fds1)) != strlen(fds1)) {
			perror("errore parent");
			exit(EXIT_FAILURE);
		}
		break;
	}

}

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

/*
 * Ripetere l'esercizio precendente utilizzando la struttura

struct corso {
	int studenti;
	char nome[40];
}
 */
struct corso {
	int studenti;
	char nome[10+1]; //non 40, per comodo
	struct corso * next;
};

//Suppongo che corr abbia almeno un elemento
void structCorso2String(struct corso* corr) {
	do {
		printf("%s %d", corr->nome, corr->studenti);

		corr = corr->next;
	}while(corr->next != NULL);
}

void es2() {
	struct corso* init = NULL;
	int corsiLetti = 0, fd, i;

	if((fd = open("./fileEs2.txt", O_RDONLY)) == -1) {
		puts("Errore apertura file");
		exit(EXIT_FAILURE);
	}
	else {
		//Impongo che ogni materia abbia 10 caratteri e che gli studenti siamo di due cifre!! vedi fileEs2.txt
		char buffer[10+1];
		struct corso * nuovaStruct;
		while(1) { //leggo una riga.
			if((nuovaStruct = malloc ( sizeof(struct corso) )) == NULL)
				exit(EXIT_FAILURE);
			nuovaStruct->next = NULL;
			if(init == NULL)//TODO sbagliato!
				init = nuovaStruct;
			else
				init->next = nuovaStruct;

			if(read(fd, buffer, 10) == 10) { //-1 e 0
				buffer[11] = '\0';
				strcpy(nuovaStruct->nome , buffer);
				nuovaStruct->nome[11] = '\0';
				corsiLetti++;
			}
			else break;
			for(i=0; i<11; i++) buffer[i] = '\0';
			if(read(fd, buffer, 3) == 3) {
				buffer[4] = '\0';
				nuovaStruct->studenti = atoi(buffer);
			} else break;
		}

		printf("Corsi letti: %d", corsiLetti);
		structCorso2String(init);
	}
}

/*
 * Aprire un file, creandolo se non esiste, scrivere 10 volte la stringa
 * "Stiamo provando a leggere e scrivere un file" leggendo il contenuto
 * del file e stamparlo a video insieme al numero totale di stringhe lette.
 *
 */
void es1() {
	int stringheLette = 0, fd,i;
	char stringaDaStampare[] = "Stiamo provando a leggere e scrivere un file\n";
	const int dimStringa = strlen(stringaDaStampare);

	if((fd = open("./fileEs1.txt", O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR)) != -1) {
		for(i = 0; i < 10; i++)
			if(write(fd, stringaDaStampare, dimStringa) != dimStringa) {
				puts("Non ho scritto tutti i caratteri che dovevo");
				exit(EXIT_FAILURE);
			}

		if(lseek(fd, 0, SEEK_SET) == -1) {
			puts("Error seeking");
			exit(EXIT_FAILURE);
		}

		char buffer[dimStringa+1];
		int charLetti;
		for(i = 0; i < 10; i++) {
			charLetti = read(fd, buffer, dimStringa);
			if(charLetti != dimStringa) {
				puts("Non ho letto tutto ciò che dovevo");
				exit(EXIT_FAILURE);
			}
			buffer[dimStringa+1] = '\0';
			puts(buffer);
			stringheLette++;
		}
		printf("stringheLette = %d", stringheLette);
	}
	else
	{
		puts("Errore apertura file");
		exit(EXIT_FAILURE);
	}
}

int main(void) {
	es3();
	return 0;
}
