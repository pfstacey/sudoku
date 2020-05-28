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
void build_puzzle(puzzle_t *puzzle);

void rand_init(void);

#endif