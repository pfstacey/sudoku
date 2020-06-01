# Makefile for CS50 Sudoku

# Piper Stacey, Sarah Korb, Marlee Montella, Matt Keating - 2020

CC = gcc
MAKE = make

CFLAGS = -Wall -pedantic -std=c11 -ggdb
PROG = sudoku
<<<<<<< HEAD
PUZZTEST = puzzletest 
OBJS = sudoku.o puzzle.o create.o
PUZZOBJ = puzzle.o
=======
OBJS = sudoku.o puzzle.o create.o solve.o
OBJS0 = puzzle.o
>>>>>>> b8685109feb43b399b4a849be4aee2a1e23d043b
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
solve.o: solve.h

.PHONY: test graphics clean

<<<<<<< HEAD
test: $(PUZZTEST)
	./$(PUZZTEST)
	#./sudoku create
=======
test: ./testing.sh
	./testing.sh &> testing.out
	cat testing.out

graphics: 
	gcc `pkg-config --cflags gtk+-3.0` puzzle.c solve.c create.c -o graphics graphics.c `pkg-config --libs gtk+-3.0`
	./graphics
>>>>>>> b8685109feb43b399b4a849be4aee2a1e23d043b

clean:
	rm -f $(PROG)
	rm -f *~ *.o
	rm -rf *.dSYM