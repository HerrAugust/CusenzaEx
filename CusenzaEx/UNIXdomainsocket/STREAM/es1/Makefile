client: client.o es1.h
	gcc -std=c99 -o client client.c

server: server.o es1.h
	gcc -std=c99 -o server server.c

launchme: launchme.o
	gcc -std=c99 -o launchme launchme.c

all:
	make client
	make server
	make launchme

run:
	./launchme

clean:
	rm -f server client launchme *.o *~
