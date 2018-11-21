#include <stdlib.h>

int main() {
	system("./server &");
	system("./client1");
	system("./client2");
	system("./client3");
	return 0;
}
