# Makefile for CS50 Sudoku Common

# Piper Stacey, Sarah Korb, Marlee Montella, Matt Keating - 2020

CC = gcc
MAKE = make
VALGRIND = valgrind --leak-check=full --show-leak-kinds=all

PUZZTEST = puzzletest 
CREATETEST = createtest
SOLVETEST = solvetest
PUZZ = puzzle.c
CREATE = create.c 
SOLVE = solve.c puzzle.o
OBJS0 = puzzle.o create.o solve.o 
TESTFLAG = -D TEST
LIB = common.a
LLIBS = libcs50-given.a
CFLAGS = -Wall -pedantic -std=c11 -ggdb 


# rules
all: $(LIB) 

$(LIB): $(OBJS0) $(LLIBS)
	ar cr $(LIB) $(OBJS0) 

$(PUZZTEST): $(PUZZ)
	$(CC) $(TESTFLAG) $(CFLAGS) $^ -o $@

$(CREATETEST): $(CREATE) $(LIB) $(LLIBS)
	$(CC) $(TESTFLAG) $(CFLAGS) $^ -o $@

$(SOLVETEST): $(SOLVE) $(LIB) $(LLIBS)
	$(CC) $(TESTFLAG) $(CFLAGS) $^ -o $@


create.o: create.h
puzzle.o: puzzle.h
solve.o: solve.h create.h puzzle.h set.h

.PHONY: test graphics clean

test: $(PUZZTEST) $(CREATETEST) $(SOLVETEST)
	echo>unittesting.out
	./$(PUZZTEST) &>> unittesting.out
	./$(CREATETEST) &>>unittesting.out
	./$(SOLVETEST) &>>unittesting.out

mem:
	$(VALGRIND) ./$(PUZZTEST)
	$(VALGRIND) ./$(CREATETEST)
	$(VALGRIND) ./$(SOLVETEST)

clean:
	rm -f $(PUZZTEST)
	rm -f $(CREATETEST)
	rm -f $(SOLVETEST)
	rm -f *~ *.o
	rm -rf *.dSYM
	rm -f core
	rm -f $(LIB) *~ *.o
	rm -f board
