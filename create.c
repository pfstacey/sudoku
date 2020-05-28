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
#include <string.h>
#include <stdlib.h>
#include "create.h"
#include "puzzle.h"

int rand_num(void);
bool already_tested(int checked[], int num);
bool valid_num(int num, int r, int c, puzzle_t *p);

/**************** global functions ****************/

/**************** build_puzzle() ****************/
void build_puzzle(puzzle_t *puzzle)
{
    int num, k, check;
    bool added = false;
    int checked[9] = {0};
    for (int i = 0; i < 9; i ++){ // iterate over rows
        for (int j = 0; j < 9; j++){ // iterate over columns
            num = rand_num(); // start with a random number
            added = false;
            while(!added){
                if (!valid_num(num,i,j,puzzle)) num = rand_num();
                else {
                    puzzle_set(puzzle,i,j,num);
                    added = true;
                }
            }
        }
    }
}

/**************** rand_init() ****************/
void rand_init(void){
    time_t t;
    srand((unsigned) time(&t));
}



/**************** local functions ****************/

/**************** rand_num() ****************/
int rand_num(void){
    long x;
    long y;

    x = rand() % 9; // random number 0-8
    y = (int) x + 1; // integer 1-9
    return y;
}
/**************** already_tested() ****************/
bool already_tested(int checked[], int num)
{
    int i = 0;
    for (i = 0; i < 9; i++){
        if (num == checked[i]){
            return true;
        }
    }
    return false;
}

/**************** valid_num() ****************/
bool valid_num(int num, int r, int c, puzzle_t *p)
{
    int i = 0;
    int *row = puzzle_getRow(p,r);
    int *column = puzzle_getCol(p,c);
    // printf("col: ");
    // for (int j = 0; j < 9; j++){
    //     printf("%d ", column[j]);
    // }
    // printf("\n");
    //int *grid = 
    // while (i < 9 && row[i] != num && column[i] != num){
    while (i < 9 && row[i] != num){
        i++;
    }
    if (i == 9) return true; // number doesnt appear in the row 
    else return false; // number appears in the row
}
