---
layout: page
title: Sudoku Design Spec
Authors: Sarah Korb, Matt Keating, Marlee Montella, Piper Stacey
Dates: May 25 - June 3, 2020
---
 
Recall the [Sudoku Requirements Spec](REQUIREMENTS.html); the **create** creates and solves a sudoku puzzle.
The **solve** takes a 9X9 sudoku array and solves the array for the user, printing the unique solution to the user. 
 
This Design Spec contains:
 
* User interface
* Inputs and Outputs
* Functional decomposition into modules
* Pseudo code for logic/algorithmic flow
* Dataflow through modules
* Major data structures
* Testing plan
 
### User interface
 
The sudoku solve and create methods are currently run with a command line interface with one argument, either create or solve. In future designs we hope to implement a graphical user interface.
 
```
sudoku (create/solve)
```
 
For example:
 
``` bash
$ ./sudoku create
$ cat board | ./sudoku solve
```
Note: The file *board* is the output of the sudoku creator. It will be formatted as 9 lines of text, each with 9 numbers separated by white space. Blank spaces will be represented by a 0. 
 
### Inputs and outputs
 
#### create
Input: the only inputs are command-line parameters; see the User Interface above.
 
Output: We output an unsolved sudoku board in the form of a 9x9 number array with at least 40 0’s indicating the empty spaces. This is on the form of a readable file called 'board' as described above.
 
#### solve 
 
Input: We pipeline the sudoku board created in `create` into `./sudoku solve`
 
Output: We output the solved 9x9 sudoku array with graphics
 
 
### Functional decomposition into modules
 
We anticipate the following modules or functions:
 
1. *main*, which parses arguments and initializes other modules
2. *solve*, which calls backtrace to generate puzzle solution
3. *create*, which generates a pseudo random puzzle and removes at least 40 spots
4. *backtrack*, implements backtracking algorithm given a 9x9 array as a parameter
4. *check_solution*, which verifies that a puzzle is a valid sudoku solution.
 
### Pseudo code for logic/algorithmic flow

#### create.c

The `./sudoku create` commant will run as follows:

1. Take an empty sudoku puzzle created by the `puzzle.c` module. This will be a 9X9 array of all 0's.
2. For each row
    3. For each column in each row 
    4. generate a random number, and set this space to this number

#### solve.c 
 
The `./sudoku solve` commant will run as follows:
ns to convert it into a clean, canonical form.

1. Open the file titled "board" which has the puzzle printed (9 lines of 9 integers)
2. Load a puzzle object from this file.
3. Use the `backtrack` function to solve the puzzle:
    4. Starting at the top left corner...
    5. If the number in the current cell is 0, put in a valid option from 1-9, and move on to the next cell down.
    6. If there are no valid options, we made a mistake farther back. Call `backtrack` on the row above.
    7. Stop once we finish the bottom right cell
8. Write the solved puzzle to the output 

### Dataflow through modules
 
1. *main* parses parameters and passes them to either the solve or create.
2. *solve* loads the puzzle into a puzzle struct and calls *backtrack* to solve the file.
3. *create* generates the puzzle using *backtrack*.
4. *backtrack* takes in a puzzle struct from *solve* or *create* and uses a backtracking algorithm while verifying a solution with *check_solution*
4. *check_solution* gets a puzzle struct from *check_solution* and returns a boolean.
 
### Major data structures
 
Puzzle: a 9x9 integer array.
 
### Testing plan
 
*Unit testing*. Small program `puzzletest.c` focuses on testing the get() and set() methods in the puzzle moduele. Uses functions in puzzle module to create and set a 9X9 sudoku puzzle. Then uses functions in the puzzle module to print a selected 'minigrid' (or 3x3 portion of the puzzle), row 0 of the puzzle and column 0 of the puzzle. 

*Integration testing*.  Use a bash script `testing.sh` to test the capacitiy of the `./sudoku` program when creating and solving puzzles.

1. Testing incorrect command line parameters to `./sudoku`

2. Create a puzzle with `./sudoku create` and pipeline the output to `./sudoku solve` to solve for a unique solution.

