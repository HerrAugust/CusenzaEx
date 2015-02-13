#Makefile
client: client.o es1.h
	gcc -o client client.c

server: server.o es1.h
	gcc -o server server.c

clean:
	rm -f *.o server client

all:
	make client
	make server