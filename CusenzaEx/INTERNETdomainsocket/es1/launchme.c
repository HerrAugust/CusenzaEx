#include <stdlib.h>

int main(void) {
	system("./server.run &");
	system("./client.run");
	return 0;
}
