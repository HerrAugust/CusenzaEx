client: client.o es2.h
	gcc -std=c99 -o client.run client.c

server: server.o es2.h
	gcc -std=c99 -o server.run server.c

launchme: launchme.o
	gcc -o launchme.run launchme.c

all:
	make client
	make server
	make launchme

clean:
	rm -f *.o *~ launchme.run client.run server.run

run:
	./launchme
