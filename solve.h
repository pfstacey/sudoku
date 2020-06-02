#include<stdlib.h>
#include<stdio.h>
#include "puzzle.h"

/*
 * boolean method that returns true if an integer val is contained in array arr
 */
bool contains(int * arr, int val);

bool valid_puzzle(puzzle_t *puzzle, int row, int column, int puzzleVal);

bool backtrack(puzzle_t *puzzle, int row, int column);

int** original_num(puzzle_t *p);

bool backtrack_optimized(puzzle_t *puzzle, int row, int column, int ** original);
