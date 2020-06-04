# CS50 Sudoku Puzzle testing
## Matt Keating, Marlee Montella, Sarah Korb, Piper Stacey, 2020
### Usage

/~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ how the tests were run ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~/

testing.sh holds all the black box tests and descriptions of each
calling make test compiles each class with a macro flag that allows the white box testing to take place
testing.out is an empty file
# to run : 
make test > testing.out

/~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Sudoku ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~/

Tests run:
1. too few arguments
2. too many arguments
3. proper functionality

To run white box testing, run `make test`:
[marleemontella@moose ~/cs50/labs/sudoku]$ make test/
./testing.sh &> testing.out/
cat testing.out/

~~~~~~~~~~~~~~~~~~~~~~/
Error Testing...

No Arguments:/
Error: input one argument.

Incorrect Argument:/
Error: enter 'create' or 'solve'.

Multiple Arguments:/
Error: input one argument.

~~~~~~~~~~~~~~~~~~~~~~/
Functionality Testing...

Original Puzzle:/
0 0 2 0 0 4 0 7 0 /
0 9 4 6 7 1 0 0 0 /
7 0 3 0 0 8 9 4 1 /
0 0 0 4 9 0 8 0 2 /
4 0 0 0 0 0 7 0 0 /
9 0 8 2 6 7 0 5 4 /
0 5 0 0 0 6 0 1 9 /
0 4 6 0 5 0 0 8 7 /
1 8 0 7 0 0 5 0 3 /

Solved Puzzle:

Puzzle 1 solved: /
5 1 2 9 3 4 6 7 8 /
8 9 4 6 7 1 3 2 5 /
7 6 3 5 2 8 9 4 1 /
6 7 1 4 9 5 8 3 2 /
4 2 5 8 1 3 7 9 6 /
9 3 8 2 6 7 1 5 4 /
2 5 7 3 8 6 4 1 9 /
3 4 6 1 5 9 2 8 7 /
1 8 9 7 4 2 5 6 3 

/~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Fuzz Testing ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~/

`fuzz.sh` allows the user to generate x number of random sudoku boards, and will print the original and solved baords. To run, use the command `./fuzz.sh number` 

Generating   random boards:\
Puzzle 1  original:\
0 3 8 6 0 0 0 0 0 \
1 6 9 0 5 4 0 0 0 \
0 2 4 9 0 0 0 0 1 \
8 4 0 7 0 5 0 0 9 \
0 5 0 8 4 0 0 0 7 \
0 0 0 1 0 0 8 5 4 \
0 1 2 0 9 0 0 0 0 \
3 0 5 4 2 0 1 0 6 \
6 9 7 0 1 0 4 2 5 


Puzzle 2  original: \
4 0 8 0 3 0 0 6 0 \
6 2 0 0 8 4 0 1 0 \
0 1 0 9 0 0 4 0 8 \
3 4 7 0 2 1 8 9 5 \
8 6 0 0 0 0 0 7 0 \
0 5 2 3 7 8 0 0 0 \
0 0 9 5 1 0 6 0 0 \
5 0 4 0 0 6 0 0 1 \
0 0 0 8 4 0 0 2 9 


Puzzle 3  original: \
5 9 0 0 0 4 0 0 8 \
8 0 0 0 0 0 0 5 0 \
0 0 4 7 0 0 0 1 0 \
0 5 0 0 4 6 0 9 0 \
0 0 0 0 0 0 4 0 5 \
6 0 2 5 7 9 8 0 0 \
4 0 5 8 0 3 1 2 9 \
0 2 3 4 1 7 5 0 6 \
1 8 0 0 2 5 3 0 7 


Solving...


Puzzle 1 solved: \
5 3 8 6 7 1 9 4 2 \
1 6 9 2 5 4 3 7 8 \
7 2 4 9 8 3 5 6 1 \
8 4 1 7 6 5 2 3 9 \
2 5 3 8 4 9 6 1 7 \
9 7 6 1 3 2 8 5 4 \
4 1 2 5 9 6 7 8 3 \
3 8 5 4 2 7 1 9 6 \
6 9 7 3 1 8 4 2 5 

Puzzle 2 solved: \
4 0 8 0 3 0 0 6 0 \
6 2 0 0 8 4 0 1 0 \
0 1 0 9 0 0 4 0 8 \
3 4 7 0 2 1 8 9 5 \
8 6 0 0 0 0 0 7 0 \
0 5 2 3 7 8 0 0 0 \
0 0 9 5 1 0 6 0 0 \
5 0 4 0 0 6 0 0 1 \
0 0 0 8 4 0 0 2 9 

Puzzle 3 solved: \
5 9 1 2 3 4 6 7 8 \
8 3 7 6 9 1 2 5 4 \
2 6 4 7 5 8 9 1 3 \
3 5 8 1 4 6 7 9 2 \
7 1 9 3 8 2 4 6 5 \
6 4 2 5 7 9 8 3 1 \
4 7 5 8 6 3 1 2 9 \
9 2 3 4 1 7 5 8 6 \
1 8 6 9 2 5 3 4 7 