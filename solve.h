#include<stdlib.h>
#include<stdio.h>
#include "set.h"
#include "puzzle.h"
#include "create.h"

void init(puzzle_t *puzzle);

void clean();

int * get_subarray(int type, int row, int col);

/*
 * boolean method that returns true if an integer val is contained in array arr
 */
bool contains(int * arr, int val);

bool optimized_valid_puzzle(puzzle_t *puzzle, int row, int column, int puzzleVal);

bool backtrack(puzzle_t *puzzle, int row, int column);

int** original_num(puzzle_t *p);

bool backtrack_optimized(puzzle_t *puzzle, int row, int column, int ** original);
