/*
 * Consegna: creare un processo e mandare un messaggio del tipo "ciao". Il figlio dovrà rispondere "Io sono <pid>".
 */

#include <stdio.h>
#include <unistd.h>
#include <string.h>

void int2string(char * wtp, long n) {
	char numchar[10] = "0123456789";
	int i = 10, cifra, index = 0;
	while( ( cifra = n % 10 - n % (i/10) * (i/10) ) != n) {
		wtp[index++] = numchar[cifra];
		i *= 10;
	}
	wtp[index] = '\0';
	printf("Debug: wtp = %s\n",wtp);
}

int main(void) {
	int fd[2], fdDaChild[2];
	pipe(fd);
	pipe(fdDaChild);

	switch(fork()) {
		case -1: perror("Errore fork"); break;

		case 0: //child. deve ricevere "ciao" e poi scrivere "Io sono <pid>"
		close(fd[1]); //chiudo output padre -> child
		close(fdDaChild[0]); //chiudo input child -> padre
		char msgP2C[13]; //lo uso anche per il mio msg
		if( read(fd[0], msgP2C, 11) != 11 ) perror("Errore messaggio padre -> child\n"); //nota: qui NON è 5 (comprensivo di \0) come nei file xk si può trasferire, in generale, di tutto, anche bite (vedi istruz. dopo)
		msgP2C[12] = '\0';
		printf("Ho ricevuto il messaggio %s\n", msgP2C);
		char wtp[6];
		char iosono[14] = "Io sono ";
		int2string(wtp,getpid());
		strcpy(msgP2C, strcat(iosono, wtp));
		printf("Invio messaggio Io sono %ld\n", (long) getpid());
		write( fdDaChild[1], msgP2C, strlen(msgP2C));
		break;

		default: //parent
		close(fd[0]);
		close(fdDaChild[1]);
		char msg[14] = "Ciao child!";
		puts("P: Mando il messaggio \"Ciao child!\"");
		write(fd[1], msg, 11);
		puts("P: Attendo il messaggio dal child");
		read(fdDaChild[0], msg, 10);
		msg[13] = '\0';
		printf("P: Ho ricevuto il messaggio %s", msg);
		break;
	}
	puts("\n");

	return 0;
} 
