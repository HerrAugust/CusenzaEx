client: client_tcp.c es2.h
	gcc -o client.run client_tcp.c

server: server_tcp.c es2.h
	gcc -o server.run server_tcp.c

all:
	make client
	make server
	touch filecopy.txt

clean:
	rm -f *~ *.o *.run filecopy.txt
