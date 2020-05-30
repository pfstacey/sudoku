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

/**************** create_puzzle() ****************/
/* 
 *
 * 
 * 
 * 
 * 
 */
bool build_puzzle(puzzle_t *puzzle);

void rand_init(void);

void fill_miniGrid(puzzle_t *p, int row, int column);
bool check_array(int checked[], int num, int pos);
bool valid_num(int num, int r, int c, puzzle_t *p);
bool fill_others(puzzle_t *p, int row, int column);

#endif