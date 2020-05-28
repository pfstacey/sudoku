/* 
 * create.c - CS50 create module
 *
 * see create.h for more information
 *
 * Author:  Marlee Montella, 2020
 * Teammates: Matt Keating, Sarah Korb, Piper Stacey
 *
 */

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "create.h"
#include "puzzle.h"

/**************** create_puzzle() ****************/
void build_puzzle(puzzle_t *puzzle)
{
    int num;
    int *row;
    int *column;
    for (int i = 0; i < 9; i ++){ // iterate over rows
        for (int j = 0; j < 9; j++){ // iterate over columns
            num = rand_num();
            row = puzzle_getRow(puzzle,i);
            column = puzzle_getCol(puzzle,j);
            
            puzzle_set(puzzle,i,j,num);
        }
    }
}

void rand_init(void){
    time_t t;
    srand((unsigned) time(&t));
}

int rand_num(void){
    long x;
    long y;

    x = rand() % 9; // random number 0-8
    y = (int) x + 1; // integer 1-9
    return y;
}