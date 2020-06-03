# SUDOKU IMPLEMENTATION
authors: Piper Stacey, Matt Keating, Marlee Montella, Sarah Korb
date: May - June, 2020
---

### Sudoku
Sudoku can both create and solve puzzles. 
A Sudoku puzzle is a 9 by 9 grid filled with the numbers one through 9
The requirements of the game are:
1. each row must have one instance of each of the numbers between 1 and 9 
2. each column must have one instance of each of the numbers between 1 and 9
3. each 3 by 3 subgrid must have one instance of each of the numbers between 1 and 9

## User Interface:
#### to create a puzzle:
./sudoku create
#### to solve an existing puzzle (where puzzlefile is a file holding a puzzle):
./sudoku solve | puzzlefile 

## Sudoku Pseudo code
1. if create
    2. generate a fully solved puzzle 
    3. remove 40 of the numbers from the puzzle
    4. write the puzzle out
5. if solve
    6. load in the given puzzle 
    7. work through the puzzle using recursion to fill the empty slots with numbers
    8. write the solved puzzle out

## Major data structures
Inside sudoku, we use three helper modules.
`puzzle.h` module
We use it store, get, load, and write puzzles (9 by 9 grids). 
`create.h` module
We use it to generate a fully solved puzzle and remove 40 spaces from that puzzle to generate a puzzle with a unique solution. 
`solve.h` module
We use it to take a half filled puzzle and solve for the empty spaces. 
#### Below is the implementation of `puzzle`.
/**************** puzzle_new ****************/
/* Create a new (empty) sudoku puzzle board.
 *
 * We return:
 *   pointer to the new index; return NULL if error.
 * We guarantee:
 *   puzzle is initialized with all zeros (calloced).
 * Caller is responsible for:
 *   later calling puzzle_delete.
 */
/**************** puzzle_new ****************/
puzzle_t *puzzle_new();

/**************** puzzle_set ****************/
/* Sets a cell in the puzzle grid at the row, col point to the value
 *
 * Caller provides:
 *   valid pointer to puzzle, int row, int col, int value.
 * We return:
 *   false if any parameter is NULL, or error;
 *   true if new value was inserted.
 */
bool puzzle_set(puzzle_t *p, const int row, const int col, const int value);

/**************** puzzle_getValue ****************/
/* Returns the int at the specified row, col
 *
 * Caller provides:
 *   valid pointer to puzzle, int row, int col
 * We return:
 *   NULL the row, col doesn't exist in the puzzle
 *   the value associated with the row, col if it exists
 * Notes:
 *   does not remove the value at row, col from the puzzle, just returns it 
 */
const int puzzle_getValue(puzzle_t * p, const int row, const int col);

/**************** puzzle_getRow ****************/
/* Returns the specified row
 *
 * Caller provides:
 *   valid pointer to puzzle, int row
 * We return:
 *   NULL the row doesn't exist in the puzzle
 *   the values associated with the row if it exists
 * Notes:
 *   does not remove the row from the puzzle, just returns it 
 */
int * puzzle_getRow(puzzle_t * p, const int row);

/**************** puzzle_getCol ****************/
/* Returns the specified col
 *
 * Caller provides:
 *   valid pointer to puzzle, int col
 * We return:
 *   NULL the col doesn't exist in the puzzle
 *   the values associated with the col if it exists
 * Notes:
 *   does not remove the col from the puzzle, just returns it 
 */
int * puzzle_getCol(puzzle_t * p, const int col);

/**************** puzzle_getMiniGrid ****************/
/* Returns an array of the values in the mini grid
 *
 * Caller provides:
 *   valid pointer to puzzle, int which minigrid they want
 * We return:
 *   NULL if the minigrid doesn't exist in the puzzle
 *   the values associated with the minigrid if it exists
 * Notes:
 *   does not remove the minigrid from the puzzle, just returns it 
| ----- | ----- | ----- |
|   0   |   1   |   2   |
| ----- | ----- | ----- |
|   3   |   4   |   5   | 
| ----- | ----- | ----- |
|   6   |   7   |   8   | 
| ----- | ----- | ----- |
 */
int * puzzle_getMiniGrid(puzzle_t * p, const int row, const int col);

/**************** puzzle_write ****************/
/* writes the whole puzzle into the stdin
 * 
 * Caller provides:
 *   valid pointer to puzzle
 * We print:
 *   "(null)" if NULL puzzle.
 *   a 9x9 grid of ints if the puzzle exists 
 * Note:
 *   the puzzle and its contents are not changed by this function,
 */
void puzzle_write(puzzle_t *p);

/**************** puzzle_load ****************/
/*load puzzle from standard input
*
*Caller provides:
*
*We do:
*Create a new, empty puzzle
*Read Standard Input and load the displayed values into puzzle structure
*Return filled puzzle
*Note:
*   The puzzle is expected to be displayed (via 'cat') in the stdin 
*   
*/
puzzle_t *puzzle_load(FILE *fp);

/**************** puzzle_delete ****************/
/* Delete puzzle
 *
 * Caller provides:
 *   valid index puzzle
 * We do:
 *   if puzzle==NULL, do nothing.
 *   otherwise, free the puzzle itself.
 * Notes:
 *   (the ints within the puzzle don't need to freed)
 */
void puzzle_delete(puzzle_t *p);

#### Below is the implementation of `create`.
/**************** build_puzzle() ****************/
/* Builds a sudoku puzzle that is ready to be solved
 *
 * Caller provides:
 *   valid pointer 
 * We return:
 *   true if puzzle is completed
 *   false if puzzle is unable to be built
 * 
 */
bool build_puzzle(puzzle_t *puzzle);

/**************** rand_init() ****************/
/* 
 *  Provides seed to use random number generator function rand()
 */

void rand_init(void);


/**************** rand_num() ****************/
/* Generates random integer from 1-9
 *
 * Caller provides:
 *   no parameters
 * We return:
 *   random integer between 1-9
 */ 
int rand_num(void);

/**************** fill_miniGrid() ****************/
/* fills 3x3 minigrid of 9x9 board
 *
 * Caller provides:
 *   valid pointer to puzzle, int row, int col
 * We return:
 *  n/a
 */
void fill_miniGrid(puzzle_t *p, int row, int column);

/**************** check_array() ****************/
/* Checks integer array for a given value
 *
 * Caller provides:
 *   integer array, int number, int position/index
 * We return:
 *  true if the number exists within the array
 *  false if number is not in array
 */
bool check_array(int checked[], int num, int pos);

/**************** valid_num() ****************/
/* Checks to see if number can be inserted in a given row, column and grid
 *
 * Caller provides:
 *   valid pointer to puzzle, int row, int col, int value.
 * We return:
 *   false number appears in the row/column/grid
 *   true if nuber does not appezr in the row/column/grid
 */
bool valid_num(int num, int r, int c, puzzle_t *p);

/**************** fill_others() ****************/
/* Fills remaining spaces in sudoku grid
 *
 * Caller provides:
 *   valid pointer to puzzle, int row, int col
 * We return
 *   true if grid was successfully filled
 *   false in the case of backtracking
 * 
 * Notes:
 *  recursive function: calls itself within function body
 */
bool fill_others(puzzle_t *p, int row, int column);

/**************** remove_values() ****************/
/* removes a set number of values in the sudoku grid
 *
 * Caller provides:
 *   valid pointer to puzzle, int num
 * We return:
 *   n/a
 * 
 * Note:
 *  Removed numbers are set to 0, representing an empty space
 */
void remove_values(puzzle_t *p, int count);

/**************** ger_next_cell() ****************/
/* removes a set number of values in the sudoku grid
 *
 * Caller provides:
 *   row and column, pointer to next row and column, valid pointer to puzzle
 * We return:
 *   n/a
 */
void get_next_cell(int r, int c, int *nextr, int *nextc, puzzle_t *puzzleVal);

#### Below is the implementation of `solve`.
/**************** init() ****************/
/* initializes rows, columns, and grids in a set
 * these rows, columns, and grids represent the rows, columns, and minigrids 
 * of the given puzzle. By making them an instance variable,
 * we only have to initialize them once instead of every call of valid_puzzle()
 *
 * Caller provides:
 *   valid pointer to puzzle
 */
void init(puzzle_t *puzzle);

/**************** clean() ****************/
/* deletes the set of rows, columns, subgrids
 *
 * Caller provides:
 *   n/a
 * 
 * Note:
 *  this does not delete the initial puzzle
 */
void clean();

/**************** get_subarray() ****************/
/* gets the array within the set of rows, columns, and subgrids
 *
 * Caller provides:
 *   an int representing whether they want the row, column, or subgrid
 *      1 = row
 *      2 = column
 *      3 = minigrid
 *   the row and column numbers for which they would like to receive the subarray
 *   
 * We return:
 *   an int array
 * 
 * Note:
 *  We do not change anything within the subarray
 */
int * get_subarray(int type, int row, int col);

/*
 * boolean method that returns true if an integer val is contained in array arr
 */
bool contains(int * arr, int val);

/**************** optimized_valid_puzzle() ****************/
/* checks whether a puzzle is valid in an optimized manner
 *
 * Caller provides:
 *   valid pointer to puzzle, int row, int column, int puzzleVal
 * We return:
 *   true if the puzzle is valid
 *   false if the puzzle is not valid
 * 
 */
bool optimized_valid_puzzle(puzzle_t *puzzle, int row, int column, int puzzleVal);

/**************** backtrack() ****************/
/* recurses through the puzzle attempting to insert numbers and then calls optimized_valid_puzzle to check if valid
 *
 * Caller provides:
 *   valid pointer to puzzle, int row, int column (the starting coordinates)
 * We return:
 *   true if puzzle can be solved and is solved
 *   false if puzzle cannot be solved
 */
bool backtrack(puzzle_t *puzzle, int row, int column);

/**************** original_num() ****************/
/* keeps track of the original numbers in the puzzle to be used during optimization
 *
 * Caller provides:
 *   valid pointer to puzzle
 * We return:
 *   a grid of original numbers and -1s where the zeros used to be
 */
int** original_num(puzzle_t *p);

/**************** backtrack_optimized() ****************/
/* recurses through the puzzle attempting to insert numbers and then calls optimized_valid_puzzle to check if valid
 * optimizes by not reallocating space for each row and column and also using the original num arrays to only
 * check the validity of numbers that aren't in the original row/column/minigrid
 *
 * Caller provides:
 *   valid pointer to puzzle, int row, int column (the starting coordinates), int ** original_num
 * We return:
 *   true if puzzle can be solved and is solved
 *   false if puzzle cannot be solved
 */
bool backtrack_optimized(puzzle_t *puzzle, int row, int column, int ** original);


## Check for memory leak
All the valid outputs are demonstrated in testing.sh shell script. The ouput of the testing can be found in testing.out In order to access testing.out type make test . Memory leaks can be checked in testing.sh and testing.out

## Compilation
To compile, type make 
To test, type make test
To clean, type make clean
