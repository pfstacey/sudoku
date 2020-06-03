# Makefile for CS50 Sudoku

# Piper Stacey, Sarah Korb, Marlee Montella, Matt Keating - 2020

CC = gcc
MAKE = make
VALGRIND = valgrind --leak-check=full --show-leak-kinds=all

CFLAGS = -Wall -pedantic -std=c11 -ggdb
PROG = sudoku
OBJS = sudoku.o puzzle.o create.o solve.o file.o
OBJS0 = puzzle.o create.o solve.o file.o
LIB = common.a
LLIBS = libcs50-given.a



# rules
all: $(PROG) $(LIB) 

$(PROG): $(OBJS) $(CCLIBS) $(LIB) $(LLIBS)
	$(CC) $(CFLAGS) $^ -o $@

$(LIB): $(OBJS0)
	ar cr $(LIB) $(OBJS0)

sudoku.o: puzzle.o puzzle.h create.h
create.o: create.h
puzzle.o: puzzle.h
solve.o: solve.h create.h puzzle.h set.h
file.o: file.h

.PHONY: test graphics clean

test: ./testing.sh
	./testing.sh &> testing.out
	cat testing.out

graphics: 
	gcc `pkg-config --cflags gtk+-3.0` puzzle.c solve.c libcs50-given.a create.c -o graphics graphics.c `pkg-config --libs gtk+-3.0`
	./graphics

mem:
	$(VALGRIND) cat board | ./sudoku solve

clean:
	rm -f $(PROG)
	rm -f *~ *.o
	rm -rf *.dSYM
	rm -f core
	rm -f $(LIB) *~ *.o
	rm -f board
