/*
 * Write a program that uses 2 pipes to enable bidirectional communication between a parent and child process. The parent should
 * loop reading a block of text from standard input and use one of the pipes to send the text to the child, which converts it
 * to uppercase and send it back to the parent via the other pipe. The parent reads the data coming back from the child and echoes
 * it on standard output before continuing around the loop once more.
 */

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>

 void toUppercase(char* string) {
 	int i = 0;
 	while(string[i] != '\0') {
 		string[i] = toupper(string[i++]);
 		printf("char at %d: %c", i, string[i]);
 	}
 }

 int main(void) {
 	//creo due pipes, una per direzione
 	int fdP2C[2]; //padre scrive e figlio legge
 	pipe(fdP2C);
 	int fdC2P[2]; //child scrive e padre legge
 	pipe(fdC2P);

 	//creo padre e figlio
 	switch(fork()) {
 		case 0: //child converte in uppercase e manda al parent
 		close(fdP2C[1]); //il figlio non scrive
 		close(fdC2P[0]); //il figlio non legge ma scrive
 		char upper[20];
 		while(1) {
 			//aspetta il testo dal parent
 			read(fdP2C[0], upper, 20);
 			//converte in uppercase
 			toUppercase(upper);
 				//invia il testo uppercase
 			write(fdC2P[1], upper, strlen(upper)+1);
 			if(strcmp(upper, "BASTA") == 0) {
 				close(fdP2C[0]);
 				close(fdC2P[1]);
 				return 0;
 			}
 		}
 		break;
 		default: //parent
 		close(fdP2C[0]);
 		close(fdC2P[1]);
 		break;
 	}

	char wtp [20];
 	while(1) {
 		//legge il testo
 		puts("Inserire testo. \"basta\" per terminare. ");
 		scanf ("%s", wtp);
 		//manda il testo al figlio
 		write(fdP2C[1], wtp, strlen(wtp)+1); //notare +1, senza il quale non viene scritto \0
 		//aspetta il testo uppercase
 		read(fdC2P[0], wtp, strlen(wtp)+1);
 		if(strcmp(wtp, "BASTA") == 0) { wait(NULL); break; }
 		//scrive in output il testo uppercase
 		puts(wtp);
 	}

 	return 0;
 }