/* 
 * create.h - header file for the creating puzzle
 *
 * A *puzzle* is a the datatype for a sudoku board which consists of 
 * a 9 by 9 grid of integers. Create.c handles buildig a random 9X9 puzzle
 * board with a unique solution.
 *
 * Author: Marlee Montella
 * Teammates: Matt Keating, Sarah Korb, Piper Stacey
 */

#ifndef __CREATE_H
#define __CREATE_H

#include <stdio.h>
#include <stdbool.h>
#include "puzzle.h"

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
 *
 * Caller provides:
 *   
 * We return:
 */

void rand_init(void);


/**************** rand_num() ****************/
/* Generates random integer from 1-9
 *
 * Caller provides:
 *   
 * We return:
 * integer between 1-9
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


void get_next_cell(int r, int c, int *nextr, int *nextc, puzzle_t *puzzleVal);

#endif
