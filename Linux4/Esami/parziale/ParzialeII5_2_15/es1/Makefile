client: client_tcp.o es1.h
	gcc -o client.run client_tcp.c

server: server_tcp.o es1.h
	gcc -o server.run server_tcp.c

all:
	make client
	make server
	touch filecopy.txt #Assumption: there is alread "file.txt"

clean:
	rm -f *~ *.o *.run filecopy.txt
