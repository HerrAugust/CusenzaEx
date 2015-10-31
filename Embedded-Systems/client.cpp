/*
 * client.cpp
 *
 *  Created on: 24/ott/2015
 *      Author: Agostino Mascitti
 */
#include "./client.h"

#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#define DEBUG 1
#define COMPUTER_IP "192.168.001.003" /*This is the IP address of the machine that will pronounce the inserted Morse string*/
#define PORT "50006" /*This is the port of the process that will pronounce the inserted Morse string*/

using namespace std;

/*
 * This function sends your Morse string (inserted by using the Grove Touch or Button sensor) to
 * your computer. This, in turn, will open a browser to pronounce your Morse string.
 * This function is IP version independent, ie you can use either IPv4 or IPv6.
 */
bool sendToComputer(const char* message) {
#ifdef DEBUG
	cout << "sendToComputer: ";
	cout << message << endl;
#endif

	struct addrinfo *res, hints, *cur;
	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_canonname = NULL;
	hints.ai_addr = NULL;
	hints.ai_next = NULL;
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_NUMERICSERV;
	if( getaddrinfo(COMPUTER_IP, PORT, &hints, &res) != 0) {
		cerr << "client getaddrinfo " << endl;
		return false;
	}

	int opt = 1, fd;
	for(cur = res; cur != NULL; cur = cur->ai_next) {
		fd = socket(cur->ai_family, cur->ai_socktype, cur->ai_protocol);
		if(fd == -1) continue;
		if( connect(fd, cur->ai_addr, cur->ai_addrlen) != -1)
			break;
		if( setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1 ) {
			cerr << "client setsockopt " << endl;
			return false;
		}
		close(fd);
	}

	if(cur == NULL) {
		cerr << "ERROR: No server address found in client" << endl;
		return false;
	}
	freeaddrinfo(res);

#ifdef DEBUG
	cout << "Client connected. Sending Morse string..."<<endl;
#endif

	/*
	 * if you do not add a \n to the message, the server will not understand that the string is
	 * finished and will make an infinite loop with while(!ready());
	 * Here you send the Morse string to your computer. Please run ServerIntelEdison.java.
	 */
	string endedmsg (message);
	endedmsg.append("\n");
	if( write(fd, endedmsg.c_str(), endedmsg.length() + 1) != (ssize_t) endedmsg.length() + 1) {
		cerr << "ERROR Client write " << endl;
		return false;
	}

	close(fd);
	return true;
}
