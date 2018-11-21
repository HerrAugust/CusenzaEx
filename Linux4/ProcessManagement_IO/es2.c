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
			if(init == NULL)
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

int main(void) {
es2();
return 0;
}
