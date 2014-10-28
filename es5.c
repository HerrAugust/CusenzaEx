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

int main() {
es5();
return 0;
}
