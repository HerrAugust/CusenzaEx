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

int main(void) {
es3();
return;
}
