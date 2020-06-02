# Makefile for CS50 Sudoku

# Piper Stacey, Sarah Korb, Marlee Montella, Matt Keating - 2020

CC = gcc
MAKE = make
VALGRIND = valgrind --leak-check=full --show-leak-kinds=all

CFLAGS = -Wall -pedantic -std=c11 -ggdb
PROG = sudoku
PUZZTEST = puzzletest 
CREATETEST = createtest
OBJS = sudoku.o puzzle.o create.o
PUZZOBJ = puzzle.o
CREATEOBJS = puzzle.o
OBJS = sudoku.o puzzle.o create.o solve.o
LIB = puzzle.a
TESTFLAG = -D TEST
# LLIBS = common when finished
OBJS = sudoku.o puzzle.o create.o solve.o file.o
OBJS0 = puzzle.o create.o solve.o file.o
LIB = common.a 



# rules
all: $(PROG) $(LIB) 

$(PROG): $(OBJS) $(CCLIBS) $(LIB) 
	$(CC) $(CFLAGS) $^ -o $@

$(PUZZTEST): $(PUZZOBJS) puzzle.c
	$(CC) $(CFLAGS) $(TESTFLAG) $^ -o $@

$(CREATETEST): $(CREATEOBJS) create.c
	$(CC) $(CFLAGS) $(TESTFLAG) $^ -o $@

$(LIB): $(OBJS0)
	ar cr $(LIB) $(PUZZOBJS)

sudoku.o: puzzle.o puzzle.h create.h
create.o: create.h puzzle.o puzzle.h
puzzle.o: puzzle.h
solve.o: solve.h puzzle.o puzzle.h
file.o: file.h

.PHONY: test whiteboxtest blackboxtest graphics clean

whiteboxtest: $(PUZZTEST) $(CREATETEST)
	#./$(CREATETEST)
	#./testing.sh
	#./testing.sh &>> testing.out
	./$(PUZZTEST) &>> testing.out

blackboxtest: 
	./testing.sh &>> testing.out
	cat testing.out

test:
	make whiteboxtest
	make blackboxtest

graphics: 
	gcc `pkg-config --cflags gtk+-3.0` puzzle.c solve.c create.c -o graphics graphics.c `pkg-config --libs gtk+-3.0`
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