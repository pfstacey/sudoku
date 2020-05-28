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
    int num ;
    // int nope[9];
    // int num;
    // printf("hi\n");
    // srand ( time(NULL) );
    for (int i = 0; i < 9; i ++){
        for (int j = 0; j < 9; j++){
            num = rand_num();
            puzzle_set(puzzle,i,j,num);
        }
    }
    // return puzzle;
}

void rand_init(void){
    time_t t;
    srand((unsigned) time(&t));
}

int rand_num(void){
    long x;
    long y;

    x = rand() % 9;
    y = (int) x;
    return y;
}