CPPFLAGS = 	-g 
LDFLAGS	+=	-g
LDLIBS 	+= -lncurses -lmenu
CC 	= g++

.PHONY: all clean run

all: main

main: main.o

clean:
	rm -rf main.o main
run: main
	./main