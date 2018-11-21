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
	es1();
	return 0;
}
