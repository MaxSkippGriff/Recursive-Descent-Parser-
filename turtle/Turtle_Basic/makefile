CFLAGS = `sdl2-config --cflags` -O2 -Wall -Wextra -pedantic -Wfloat-equal -ansi
INCS = neillsdl2.h
VALGRIND = --error-exitcode=1 --quiet --leak-check=full
SOURCES =  neillsdl2.c
LIBS =  `sdl2-config --libs` -lm
CC = gcc

# Folder contains different shapes which the parser/interpreter
# can draw.
EX1 = different_shapes/turtle1.txt
EX2 = different_shapes/turtle2.txt
EX3 = different_shapes/turtle3.txt
EX4 = different_shapes/turtle4.txt
EX5 = different_shapes/turtle5.txt
EX6 = different_shapes/turtle6.txt
EX7 = different_shapes/turtle7.txt

all: parse interp

parse: parser.c parser.h
						$(CC) parser.c -o parser $(CFLAGS)

interp: interpreter.c interpreter.h $(SOURCES) $(INCS)
						$(CC) interpreter.c $(SOURCES) -o interpreter $(CFLAGS) $(LIBS)

run: all

							./parser $(EX1)
							./interpreter $(EX1)

							./parser $(EX2)
							./interpreter $(EX2)

							./parser $(EX3)
							./interpreter $(EX3)

							./parser $(EX4)
							./interpreter $(EX4)

							./parser $(EX5)
							./interpreter $(EX5)

							./parser $(EX6)
							./interpreter $(EX6)

							./parser $(EX7)
							./interpreter $(EX7)

clean:
	rm -f parse interp

.PHONY: clean run all
