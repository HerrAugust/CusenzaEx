client: client.o es2.h
	gcc -std=c99 -o client client.c

server: server.o es2.h
	gcc -std=c99 -o server server.c

launchme: launchme.o
	gcc -o launchme launchme.c

all:
	make client
	make server
	make launchme

clean:
	rm -f *.o *~ launchme client server

run:
	./launchme
