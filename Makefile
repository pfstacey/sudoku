# Makefile for CS50 Sudoku

# Piper Stacey, Sarah Korb, Marlee Montella, Matt Keating - 2020

CC = gcc
MAKE = make
VALGRIND = valgrind --leak-check=full --show-leak-kinds=all
LIB = common
LLIBS = $(LIB)/common.a $(LIB)/libcs50-given.a 
CFLAGS = -Wall -pedantic -std=c11 -ggdb -I $(LIB)
PROG = sudoku
OBJS = sudoku.o
OBJS0 = puzzle.o create.o solve.o file.o


# rules
all: $(PROG) 
	make -C common

$(PROG): $(OBJS) $(LLIBS) 
	$(CC) $(CFLAGS) $^ -o $@

create.o: $(LIB)/create.h
puzzle.o: $(LIB)/puzzle.h
solve.o: $(LIB)/solve.h $(LIB)/create.h $(LIB)/puzzle.h $(LIB)/set.h
sudoku.o: $(LIB)/puzzle.h $(LIB)/create.h $(LIB)/solve.h

.PHONY: test graphics clean

test: ./testing.sh
	./testing.sh &> testing.out
	cat testing.out

graphics: 
	gcc `pkg-config --cflags gtk+-3.0` $(LIB)/puzzle.c $(LIB)/solve.c $(LIB)/libcs50-given.a $(LIB)/create.c -o graphics graphics.c `pkg-config --libs gtk+-3.0`
	./graphics

mem:
	$(VALGRIND) cat board | ./sudoku solve

clean:
	rm -f $(PROG)
	rm -f *~ *.o
	rm -rf *.dSYM
	rm -f core
	rm -f board
