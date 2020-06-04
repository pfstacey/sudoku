#include<stdlib.h>
#include<stdio.h>
#include "set.h"
#include "puzzle.h"
#include "create.h"


/**************** init() ***************/ 
/* initializes rows, columns, and grids in a set

these rows, columns, and grids represent the rows, columns, and minigrids
of the given puzzle. By making them an instance variable,
we only have to initialize them once instead of every call of valid_puzzle()
Caller provides:
valid pointer to puzzle 
*/ 

void init(puzzle_t *puzzle);

/**************** clean() ***************/ 
/* deletes the set of rows, columns, subgrids 
Caller provides:
n/a
Note:
this does not delete the initial puzzle 
*/
void clean();

/**************** get_subarray() ***************/ 
/* gets the array within the set of rows, columns, and subgrids *

Caller provides:
an int representing whether they want the row, column, or subgrid
 1 = row
 2 = column
 3 = minigrid
the row and column numbers for which they would like to receive the subarray
We return:
an int array
Note:
We do not change anything within the subarray 
*/
int * get_subarray(int type, int row, int col);

/*
 * boolean method that returns true if an integer val is contained in array arr
 */
bool contains(int * arr, int val);

/**************** optimized_valid_puzzle() ***************/
/* 
checks whether a puzzle is valid in an optimized manner

Caller provides:
valid pointer to puzzle, int row, int column, int puzzleVal
We return:
true if the puzzle is valid
false if the puzzle is not valid
*/
bool optimized_valid_puzzle(puzzle_t *puzzle, int row, int column, int puzzleVal);

/**************** backtrack() ***************/ 
/* recurses through the puzzle attempting to insert numbers and then calls optimized_valid_puzzle to check if valid *

Caller provides:
valid pointer to puzzle, int row, int column (the starting coordinates)
We return:
true if puzzle can be solved and is solved
false if puzzle cannot be solved 
*/
bool backtrack(puzzle_t *puzzle, int row, int column);

/**************** original_num() ***************/ 
/* keeps track of the original numbers in the puzzle to be used during optimization *

Caller provides:
valid pointer to puzzle
We return:
a grid of original numbers and -1s where the zeros used to be 
*/
int** original_num(puzzle_t *p);

/**************** backtrack_optimized() ***************/ 
/* recurses through the puzzle attempting to insert numbers and then calls optimized_valid_puzzle to check if valid

optimizes by not reallocating space for each row and column and also using the original num arrays to only
check the validity of numbers that aren't in the original row/column/minigrid
Caller provides:
valid pointer to puzzle, int row, int column (the starting coordinates), int ** original_num
We return:
true if puzzle can be solved and is solved
false if puzzle cannot be solved 
*/
bool backtrack_optimized(puzzle_t *puzzle, int row, int column, int ** original);
