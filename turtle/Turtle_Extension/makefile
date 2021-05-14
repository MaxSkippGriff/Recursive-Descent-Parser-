CFLAGS = `sdl2-config --cflags` -O2 -Wall -Wextra -pedantic -Wfloat-equal -ansi
INCS = neillsdl2.h
VALGRIND = --error-exitcode=1 --quiet --leak-check=full
SOURCES =  neillsdl2.c
LIBS =  `sdl2-config --libs`  -lm
CC = gcc

# Working test files for both parser and interpreter
EX1 = different_shapes/turtle1.txt
EX2 = different_shapes/turtle2.txt
EX3 = different_shapes/turtle3.txt
EX4 = different_shapes/turtle4.txt


all: parse interp

# Parser and Interpreter files
parse: parse.c parser.h
					$(CC) parse.c -o parse $(CFLAGS)

interp: interp.c interp.h password.h $(SOURCES) $(INCS)
					$(CC) interp.c $(SOURCES) -o interp $(CFLAGS) $(LIBS)


extension: all
					./parse $(EX1)
					./interp $(EX1)

					./parse $(EX2)
					./interp $(EX2)

					./parse $(EX3)
					./interp $(EX3)

					./parse $(EX4)
					./interp $(EX4)


clean:
	rm -f parse interp password

.PHONY: clean run all
