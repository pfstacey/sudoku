# Matt Keating, Sarah Korb, Piper Stacey, and Marlee Montella
## CS50 Spring 2020, Sudoku Lab

### Required Software

In order to run the graphics, the user must have XQuartz installed. See https://www.cs.dartmouth.edu/~cs50/Resources/XQuartz/ for installation details. Additionally, the user must run
```
ssh -Y username@servername
```

### Create

Create makes a sudoku puzzle and prints it to the user. When the user inputs `./sudoku create` in the termnial, an 9x9 unsolved sudoku puzzle is displayed, with 0's representing blank spaces. It writes the puzzle into a file.

### Solve

Solves solves a sudoku puzzle. It loads a sudoku puzzle from a file and uses a backtracing funcntion to solve. It then outputs the solved puzzle to the terminal.

### Graphics
 
The graphics file allows the user to see a puzzle generated by the create function in a window. When the user presses the solve button at the bottom of the screen, the puzzle will be solved and displayed on the screen. 

### Usage

Both `create.c` and `solve.c` implement their own functions as well as the puzzle module, defined in `puzzle.h` and implemented in `puzzle.c`.

The following funcitons are exported through `puzzle.h` :

```
// Create a new (empty) sudoku puzzle board.
puzzle_t *puzzle_new();

// Sets a cell in the puzzle grid at the row, col point to the value
bool puzzle_set(puzzle_t *p, const int row, const int col, const int value);

//Returns the int at the specified row, col
const int puzzle_getValue(puzzle_t * p, const int row, const int col);


//Returns the specified row
int * puzzle_getRow(puzzle_t * p, const int row);

//Returns the specified col
int * puzzle_getCol(puzzle_t * p, const int col);

// Returns an array of the values in the mini grid
int * puzzle_getMiniGrid(puzzle_t * p, const int row, const int col);

//writes the whole puzzle into the stdin
void puzzle_write(puzzle_t *p);

//load puzzle from standard input
puzzle_t *puzzle_load(FILE *fp);

//Delete puzzle
void puzzle_delete(puzzle_t *p);

```

The following funcitons are exported through `create.h` :

```
// Builds a sudoku puzzle that is ready to be solved
bool build_puzzle(puzzle_t *puzzle);

//Provides seed to use random number generator function rand()
void rand_init(void);

//Generates random integer from 1-9
int rand_num(void);

// fills 3x3 minigrid of 9x9 board
void fill_miniGrid(puzzle_t *p, int row, int column);

//Checks integer array for a given value
bool check_array(int checked[], int num, int pos);

// Checks to see if number can be inserted in a given row, column and grid
bool valid_num(int num, int r, int c, puzzle_t *p);

//Fills remaining spaces in sudoku grid
bool fill_others(puzzle_t *p, int row, int column);

// removes a set number of values in the sudoku grid
void remove_values(puzzle_t *p, int count);


//Gets the coordinates for the next empty cell to work on
void get_next_cell(int r, int c, int *nextr, int *nextc, puzzle_t *puzzleVal);


```

The following funcitons are exported through `solve.h` :


```
//initializes rows, columns, and grids in a set
void init(puzzle_t *puzzle);

//deletes the set of rows, columns, subgrids 
void clean();

//gets the array within the set of rows, columns, and subgrids 
int * get_subarray(int type, int row, int col);

//boolean method that returns true if an integer val is contained in array arr
bool contains(int * arr, int val);

//checks whether a puzzle is valid in an optimized manner
bool optimized_valid_puzzle(puzzle_t *puzzle, int row, int column, int puzzleVal);

// recurses through the puzzle attempting to insert numbers and then calls optimized_valid_puzzle to check if valid *
bool backtrack(puzzle_t *puzzle, int row, int column);

//keeps track of the original numbers in the puzzle to be used during optimization 
int** original_num(puzzle_t *p);


//recurses through the puzzle attempting to insert numbers and then calls optimized_valid_puzzle to check if valid
bool backtrack_optimized(puzzle_t *puzzle, int row, int column, int ** original);

```

### Implementation

The sudoku puzzles are implemented as an array of 9 arrays of integers, thus forming the 9x9 grid.

The puzzle is initialised so that all the integers are all 0. 

To create/fill the puzzle, we call `build_puzzle` and pass it an empty puzzle struct;  This fills the 3 diagonal minigrids (top left, center, bottom right) first as their values will be independant from one another.

Next, `fill_others` will use a backtracing based method to fill the rest of the puzzle so that it only has 1 unique solution. 

Finally, `remove_values` will take away 40 numbers and replace them with 0's at randomly generated locations in the grid. The puzzle is ready to be solved and is printed ot the user. 

To solve, `backtrack` is used; it is a recursive funtion that begins at the coordinates passed to it. From here it checks for a valid number to place in its locaiton on the board (must be 1-9) using . If a valid number is found, it is placed in this spot and `backtrack` is called on the next row down. If no valid number can be placed in the cell, it is set to 0 and `backtrack`is called on the row before.

Solve also implements a `backtrack_optimized` function which takes the puzzle to be solved, the starting cootdinates and an array of arrays of inetgers. This `int **` array is formed by the `original_num` fucntion, which starts with a 9x9 array of numbers ordered 1-9 in every row. It takes an unsolved puzzle and at every location there is a non-zero inetger, this number is changed to -1 in its corresponding row in the `original_num` array. The `backtrack_optimized` uses this array to know which numbers are valid options to try. 


### Graphics Implementation
 
We used the gtk library to run the graphics. The layout is in a 10x9 grid, with a 9x9 section containing text cells that display the board and the last row containing a solve button. Upon pressing the solve button, the text cells are replaced with the solved text.

### Assumptions

No assumptions beyond those that are clear from the spec


### Compilation

To compile: `make`
To test: `make test`
To use graphics: `make graphics`
See [TESTING](TESTING.md) for details of testing and an example test run.
 
