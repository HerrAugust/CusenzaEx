#include <stdio.h>
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>

/*
 * Dimostrare che un processo stopped riceve subito il segnale
 */
 void handler(int s) {
 	printf("Ricevuto %d\n", s);

 }

 void es1() {
 	signal(SIGINT, handler);
 	puts("Mandare ora un SIGINT (^C)\n");
 	sleep(10);
 	puts("fine sleep => segnali gia' deliverd\n");
 }

 /*
 * Bloccare tre segnali, stampare i segnali pending e, dopo avere bloccato un altro segnale, bloccare tutti
 */
 void es2() {
 	signal(SIGINT, handler); //^C
 	signal(SIGTSTP, handler); //^Z
 	signal(SIGQUIT, handler); //^\ term + core dump
 	sigset_t blocco1;
 	sigset_t pending;

 	sigaddset(&blocco1, SIGINT);
 	sigaddset(&blocco1, SIGTSTP);
 	sigprocmask(SIG_SETMASK, &blocco1, NULL);

 	puts("Ho bloccato SIGINT e SIGTERM. Inviarli alcune volte\n");
 	sleep(5);

 	sigpending(&pending);
 	if(sigismember(&pending, SIGINT))
 		puts("\nSIGINT pending\n");
 	if(sigismember(&pending, SIGTSTP))
 		puts("SIGSTP pending\n");

 	sigemptyset(&blocco1);
 	sigaddset(&blocco1, SIGQUIT);
 	sigprocmask(SIG_BLOCK, &blocco1, NULL);
 	puts("Bloccato anche SIGQUIT. Inviare un SIGQUIT");
 	sleep(5);

 	sigpending(&pending);
 	if(sigismember(&pending, SIGINT))
 		puts("\nSIGINT pending\n");
 	if(sigismember(&pending, SIGTSTP))
 		puts("SIGSTP pending\n");
 	if(sigismember(&pending, SIGQUIT))
 		puts("SIGQUIT pending\n");

 	puts("sto per sbloccare i segnali bloccati. Preparsi all'handler");
 	sigprocmask(SIG_UNBLOCK, &blocco1, NULL);
 	//lo handler() viene richiamata una sola volta per segnale!
 }

/*
 * Dimostrare che i segnali non sono accodati
 */
 void handleres3(int sig) {
 	static int i = 0;
 	printf("Chiamata numero %d di handleres3\n", ++i);
 }

 void es3() {
 	/*
 	 * Blocco SIGINT, lo raise 5 volte, installo l'handler, sblocco SIGINT e conto il numero di volte che viene chiamato.
 	 */
 	 sigset_t newmask;
 	 sigaddset(&newmask, SIGINT);
 	 sigprocmask(SIG_SETMASK, &newmask, NULL);

 	 int i = 0;
 	 for(; i < 5; i++)
 	 	raise(SIGINT);

 	 signal(SIGINT, handleres3);

 	 sigprocmask(SIG_UNBLOCK, &newmask, NULL);
 	 puts("Se handleres3 è stato richiamato solo 1 volta, l'esercizio è riuscito\n");
 }

int main() {
	printf("PID: %ld\n", (long)getpid());
	//es1();
	//es2();
	es3();

	return 0;
}