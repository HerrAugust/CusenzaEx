CC 		= gcc
CFLAGS 	= `allegro-config --cflags --libs` # sudo apt install liballegro4
LDLIBS 	= #-lpthread

SRC 	= test_allegro.c
BIN 	= test_allegro



.PHONY: all
all:  $(SRC)
	gcc -o $(BIN) $(SRC) $(LDLIBS) $(CFLAGS)

.PHONY: clean
clean:
	rm -f *~ *.bak *.o $(BIN)

.PHONY: rebuild
rebuild: clean all