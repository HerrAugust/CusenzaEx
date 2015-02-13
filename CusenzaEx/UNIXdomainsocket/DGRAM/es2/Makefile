#Makefile
client: client.o es2.h
	gcc -o client.run client.c

server: server.o es2.h
	gcc -o server.run server.c

clean:
	rm -f *.o server.run client.run

all:
	make server
	make client
