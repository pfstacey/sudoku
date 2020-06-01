# Makefile for CS50 Sudoku

# Piper Stacey, Sarah Korb, Marlee Montella, Matt Keating - 2020

CC = gcc
MAKE = make

CFLAGS = -Wall -pedantic -std=c11 -ggdb
PROG = sudoku
PUZZTEST = puzzletest 
OBJS = sudoku.o puzzle.o create.o
PUZZOBJ = puzzle.o
LIB = puzzle.a
TESTFLAG = -DTEST
# LLIBS = common when finished
# rules
all: $(PROG) $(LIB) 

$(PROG): $(OBJS) $(CCLIBS) $(LLIBS) 
	$(CC) $(CFLAGS) $^ -o $@

$(PUZZTEST): $(PUZZOBJS) puzzle.c
	$(CC) $(CFLAGS) $(TESTFLAG) $^ -o $@

$(LIB): $(OBJS0)
	ar cr $(LIB) $(OBJS0)

sudoku.o: puzzle.o puzzle.h create.h
create.o: create.h
puzzle.o: puzzle.h

.PHONY: test clean

test: $(PUZZTEST)
	./$(PUZZTEST)
	#./sudoku create

clean:
	rm -f $(PROG)
	rm -f *~ *.o
	rm -rf *.dSYM