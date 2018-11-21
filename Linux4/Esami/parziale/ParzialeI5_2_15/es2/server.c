/*
Server:
Il server ha il compito di restituire al client
un codice numerico univoco dato dalla somma del pid con una chiave (es. 0xa5)
un messaggio di testo che contiene in testo ricevuto es. “salve [testo ricevuto]”
*/

#include "es2.h"

int main(void) {
	while(1) {
		unlink(STATICPATH);		
		mkfifo(STATICPATH, 0666);
		const long chiave = 2;
		struct request req;

		int fdlettura = open(STATICPATH, O_RDONLY);
		read(fdlettura, &req, sizeof(struct request));
		printf("Server-Ricevuto: %s\n", req.stringa);

		char clientpath[BUF_SIZE];
		sprintf(clientpath, PATH, req.pid);
		struct response resp; resp.codice = req.pid+chiave; sprintf(resp.stringa, "Salve %s", req.stringa);
		int fdscrittura = open(clientpath, O_WRONLY);
		write(fdscrittura, &resp, sizeof(struct response));

		close(fdlettura);
		close(fdscrittura);
	}

	return 0;
}