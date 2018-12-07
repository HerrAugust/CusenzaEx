CC 		= gcc
CFLAGS 	= -g `allegro-config --cflags --libs` # sudo apt install liballegro4
LDLIBS 	= -lpthread -lrt

SRC 	= main.c
BIN 	= assembly_chain



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
	sudo ./$(BIN)