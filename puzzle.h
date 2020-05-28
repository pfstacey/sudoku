/* 
 * puzzle.h - header file for the puzzle data type
 *
 * A *puzzle* is a the datatype for a sudoku board which consists of 
 * a 9 by 9 grid of integers
 *
 * Author: Piper Stacey
 * Teammates: Matt Keating, Sarah Korb, Marlee Montella
 */

#ifndef __PUZZLE_H
#define __PUZZLE_H

#include <stdio.h>
#include <stdbool.h>

/**************** global types ****************/
 typedef struct puzzle puzzle_t;  // opaque to users of the module

 /**************** functions ****************/

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

#endif