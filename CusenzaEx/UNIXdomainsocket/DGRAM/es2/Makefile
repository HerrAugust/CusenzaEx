#Makefile
client: client.o es2.h
	gcc -o client client.c

server: server.o es2.h
	gcc -o server server.c

clean:
	rm -f *.o server client

all:
	make server
	make client