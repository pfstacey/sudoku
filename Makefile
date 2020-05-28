# Makefile for CS50 Sudoku

# Piper Stacey, Sarah Korb, Marlee Montella, Matt Keating - 2020

# PROG = puzzle
# OBJS = puzzle.o
# LIB = puzzle.a

# CC = gcc
# CFLAGS = -Wall -pedantic -std=c11 -ggdb 
# MAKE = make

# all: $(LIB)

# $(LIB): $(OBJS)
# 	ar cr $(LIB) $(OBJS)

# # no dependencies for puzzle.o

# .PHONY: clean sourcelist

# # list all the sources and docs in this directory.
# # (this rule is used only by the Professor in preparing the starter kit)
# sourcelist: Makefile *.md *.c *.h
# 	@echo $^

# clean:
# 	rm -f $(PROG)
# 	rm -f *~ *.o
# 	rm -rf *.dSYM

CC = gcc
MAKE = make

CFLAGS = -Wall -pedantic -std=c11 -ggdb
PROG = sudoku
OBJS = sudoku.o puzzle.o create.o

# rules
$(PROG): $(OBJS) $(CCLIBS) $(LLIBS) 
	$(CC) $(CFLAGS) $^ -o $@

sudoku.o: puzzle.o puzzle.h create.h
create.o: create.h
puzzle.o: puzzle.h

.PHONY: test clean

test:
	./sudoku create

clean:
	rm -f $(PROG)
	rm -f *~ *.o
	rm -rf *.dSYM