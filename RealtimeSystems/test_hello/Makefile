CC 		= gcc
CFLAGS 	= `allegro-config --cflags --libs` # sudo apt install liballegro4
LDLIBS 	= -lpthread -lrt

SRC 	= hello.c ptask.c timeutil.c
BIN 	= hellos



.PHONY: all
all:  $(SRC)
	gcc -o $(BIN) $(SRC) $(LDLIBS) $(CFLAGS)

.PHONY: clean
clean:
	rm -f *~ *.bak *.o $(BIN)

.PHONY: rebuild
rebuild: clean all