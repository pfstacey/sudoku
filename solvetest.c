#include<stdio.h>
#include<stdlib.h>
#include "solve.h"
#include "puzzle.h"

/*
 * test puzzle:
 * 1 6 0 0 0 3 0 0 0
 * 2 0 0 7 0 6 0 1 4
 * 0 4 5 0 8 1 0 0 7
 * 5 0 8 4 0 0 0 0 0
 * 0 0 4 3 0 8 9 0 0
 * 0 0 0 0 0 7 2 0 8
 * 8 0 0 6 3 0 1 9 0
 * 6 3 0 1 0 5 0 0 2 
 * 0 0 0 8 0 0 0 3 6
 *
 * test puzzle solution:
 * 5 3 8 1 2 9 7 6 4
 * 9 6 4 5 8 7 3 1 2
 * 1 7 2 6 3 4 8 9 5
 * 3 4 5 7 9 8 1 2 6
 * 6 8 9 2 1 5 4 7 3
 * 7 2 1 4 6 3 9 5 8
 * 8 1 3 9 5 2 6 4 7
 * 2 9 7 3 4 6 5 8 1
 * 4 5 6 8 7 1 2 3 9
 */

int main(){
	puzzle_t *test = puzzle_new();

	puzzle_set(test, 0, 0, 1);
	puzzle_set(test, 0, 1, 6);
	puzzle_set(test, 0, 5, 3);
	puzzle_set(test, 1, 0, 2);
	puzzle_set(test, 1, 3, 7);
	puzzle_set(test, 1, 5, 6);
	puzzle_set(test, 1, 7, 1);
	puzzle_set(test, 1, 8, 4);
	puzzle_set(test, 2, 1, 4);
	puzzle_set(test, 2, 2, 5);
	puzzle_set(test, 2, 4, 8);
	puzzle_set(test, 2, 5, 1);
	puzzle_set(test, 2, 8, 7);
	puzzle_set(test, 3, 0, 5);
	puzzle_set(test, 3, 2, 8);
	puzzle_set(test, 3, 3, 4);
	puzzle_set(test, 4, 2, 4);
	puzzle_set(test, 4, 3, 3);
	puzzle_set(test, 4, 5, 8);
	puzzle_set(test, 4, 6, 9);
	puzzle_set(test, 5, 5, 7);
	puzzle_set(test, 5, 6, 2);
	puzzle_set(test, 5, 8, 8);
	puzzle_set(test, 6, 0, 8);
	puzzle_set(test, 6, 3, 6);
	puzzle_set(test, 6, 4, 3);
	puzzle_set(test, 6, 6, 1);
	puzzle_set(test, 6, 7, 9);
	puzzle_set(test, 7, 0, 6);
	puzzle_set(test, 7, 1, 3);
	puzzle_set(test, 7, 3, 1);
	puzzle_set(test, 7, 5, 5);
	puzzle_set(test, 7, 8, 2);
	puzzle_set(test, 8, 3, 8);
	puzzle_set(test, 8, 7, 3);
	puzzle_set(test, 8, 8, 6);

	puzzle_write(test);

	backtrack(test, 0, 0);

	puzzle_write(test);

	puzzle_delete(test);
}
