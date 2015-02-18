/*
Write a program that does the same as "ls /home/agostino/Workspace/EserciziUni/CusenzaEx | grep es" using popen() and pclose()
*/

#include <stdio.h>

int main() {
	char buf[30];

	//create a pipe for writing the writes ls
	FILE * piper = popen("ls /home/agostino/Workspace/EserciziUni/CusenzaEx", "r");

	FILE * pipew = popen(strcat("grep es", buf), "w");



	pclose(piper);
	pclose(pipew);
	return 0;
}