#include <stdlib.h>

int main(void) {
	system("./server.run &");
	system("./client.run");
	//Note: you have to manually close all servers obtained via "ps -f f" in Terminal!
	return 0;
}
