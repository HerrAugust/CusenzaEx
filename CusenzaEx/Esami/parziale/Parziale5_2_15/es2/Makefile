server: server.o es2.h
	gcc -o server.run server.c

client: client.o es2.h
	gcc -o client.run client.c

all:
	make server
	make client

clean:
	rm -f *.o *~ server.run client.run
