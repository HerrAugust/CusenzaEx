CC 		= gcc
CFLAGS 	= `allegro-config --cflags --libs` # sudo apt install liballegro4
LDLIBS 	= -lpthread -lrt

SRC 	= transparent_bck.c
BIN 	= tra



.PHONY: all
all:  $(SRC)
	gcc -o $(BIN) $(SRC) $(LDLIBS) $(CFLAGS)

.PHONY: clean
clean:
	rm -f *~ *.bak *.o $(BIN)

.PHONY: rebuild
rebuild: clean all

.PHONY: run
run: 
	./$(BIN)