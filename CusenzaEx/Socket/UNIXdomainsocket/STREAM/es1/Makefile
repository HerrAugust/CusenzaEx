client: client.o es1.h
	gcc -std=c99 -o client.run client.c

server: server.o es1.h
	gcc -std=c99 -o server.run server.c

launchme: launchme.o
	gcc -std=c99 -o launchme.run launchme.c

all:
	make client
	make server
	make launchme

run:
	./launchme

clean:
	rm -f server.run client.run launchme.run *.o *~
