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
EX5 = different_shapes/turtle5.txt
EX6 = different_shapes/turtle6.txt


# Working test files for the extension
TURTLE2_EXT = turtle2_ext.no
TURTLE3_EXT = turtle3_ext.no
TURTLE4_EXT = turtle4_ext.no

all: parse interp

# Parser and Interpreter files
parse: unit_test_parse.c parse.h
					$(CC) unit_test_parse.c -o unit_test_parse $(CFLAGS)

interp: unit_test_interp.c interp.h $(SOURCES) $(INCS)
					$(CC) unit_test_interp.c $(SOURCES) -o unit_test_interp $(CFLAGS) $(LIBS)

parsetest: unit_test_parse.c parse.h
					$(CC) unit_test_parse.c -o unit_test_parse $(CFLAGS)

interptest: unit_test_interp.c interp.h $(SOURCES) $(INCS)
					$(CC) unit_test_interp.c $(SOURCES) -o unit_test_interp $(CFLAGS) $(LIBS)


clean:
	rm -f parse interp parsetest interptest

.PHONY: clean run all
