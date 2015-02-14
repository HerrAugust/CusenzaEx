/*
 * UNIX domain datagram socket:convertire in maiuscolo i datagram del client e rispedirglieli. Il client riceve i propri datagram dagli argomenti.
 */

#include "es2.h"

void covertToUpper(char *str)
{
    int i = 0;
    int len = strlen(str);

    for(i = 0; str[i]; i++)
    {
       str[i] = toupper(str[i]);
    }
    //terminate string
    str[i]= '\0';
}

int main(void) {
	struct sockaddr_un myadd, clientadd;
	char buf[30];

	int fd = socket(AF_UNIX, SOCK_DGRAM, 0);

	//Rimuovo il vecchio server pathname
	remove(SPATH);//non dimenticare perchè bloccherebbe il programma

	//Creo il mio address e mi ci collego
	memset(&myadd, 0, sizeof(struct sockaddr_un));//non dimenticare perchè bloccherebbe il programma
	strncat(myadd.sun_path, SPATH, sizeof(myadd.sun_path)-1);
	myadd.sun_family = AF_UNIX;
	bind(fd, (struct sockaddr*)&myadd, sizeof(struct sockaddr_un));
	
	//Preparo l'indirizzo del client (poichè statico)
	memset(&clientadd, 0, sizeof(struct sockaddr_un));//non dimenticare perchè bloccherebbe il programma
	strncat(clientadd.sun_path, CPATH, sizeof(clientadd.sun_path)-1);
	clientadd.sun_family = AF_UNIX;

	while(1) {
		socklen_t len = sizeof(struct sockaddr_un);
		//Ricevo i dati
		int ret = recvfrom(fd, buf, sizeof(buf), 0, (struct sockaddr*) &clientadd, &len);
		if(strcmp(buf, "fine") == 0) break;
	
		//Li elaboro
		covertToUpper(buf);

		//Li rinvio
		sendto(fd, buf, strlen(buf), 0, (struct sockaddr*)&clientadd, len);
	}

	return 0;
}
