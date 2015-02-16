#Attention: have a look at launchme.c!
client: client.o es3.h
	gcc -o client.run client.c

server: server.o es3.h
	gcc -o server.run server.c

launchme: launchme.o
	gcc -o launchme.run launchme.c

all:
	make client
	make server
	make launchme

run:
	./launchme.run

clean:
	rm -f *.o *~ client.run server.run launchme.run
