#Makefile for es3. Launch these programs in Terminal (Bash) with "make all", press enter and then "make run" 

server: server.o es3.h
	gcc -o server server.c

client1: client1.o es3.h
	gcc -o client1 client1.c

client2: client2.o es3.h
	gcc -o client2 client2.c

client3: client3.o es3.h
	gcc -o client3 client3.c

launchme: launchme.o
	gcc -o launchme launchme.c

run:
	./launchme

all:
	make server
	make client1
	make client2
	make client3
	make launchme

clean:
	rm -f *.o client1 client2 client3 server launchme *~
