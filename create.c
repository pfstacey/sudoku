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
void fill_miniGrid(puzzle_t *p, int row, int column);
bool check_array(int checked[], int num, int pos);
bool valid_num(int num, int r, int c, puzzle_t *p);
bool fill_others(puzzle_t *p, int row, int column);

/**************** global functions ****************/
/**************** rand_init() ****************/
void rand_init(void){
    time_t t;
    srand((unsigned) time(&t));
}
/**************** build_puzzle() ****************/
bool build_puzzle(puzzle_t *puzzle)
{
    // fill diagonal 3x3 matrices
    for (int i = 0; i < 3; i++){
        fill_miniGrid(puzzle,i*3,i*3);
    }
    if(fill_others(puzzle,0,3)) {
        return true;
    }
    else return false;
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
/**************** fill_minigrid() ****************/
void fill_miniGrid(puzzle_t *p, int row, int column)
{
    int num,k;
    bool added;
    for (int i = row; i < row+3; i++){
        for (int j = column; j < column+3; j++){
            num = rand_num();
            int *checked = (int *)calloc(9,sizeof(int));
            k = 0;
            added = false;
            while(!added && k < 9){
                if (check_array(checked,num,k)){
                    checked[k] = num;
                    num = rand_num();
                } 
                else if (!valid_num(num,i,j,p)){
                    checked[k] = num;
                    k++;
                    num = rand_num();
                }
                else{
                    puzzle_set(p,i,j,num);
                    added = true;
                }
            }
            free(checked);
        }
    }
}

/**************** check_array() ****************/
bool check_array(int checked[], int num, int pos)
{
    if (pos == 0) return false;
    else{
        for (int i = 0; i < pos; i++){
            if (num == checked[i]){
                return true;
            }
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
    int *grid = puzzle_getMiniGrid(p,r,c);
    while (i < 9){
        if (row[i] != num && column[i] != num && grid[i] != num) i++;
        else break;
    }
    free(row);
    free(column);
    free(grid);
    if (i == 9) return true; // number doesnt appear in the row/column/grid 
    else return false; // number appears in the row/column/grid 
}

/**************** fill_others() ****************/
bool fill_others(puzzle_t *p, int r, int c)
{
    if (r == 9){
        r = 0;
        c++;
    }

    if (c == 9) return true;

    if (puzzle_getValue(p, r, c) != 0) return fill_others(p,r+1,c);

    int random[9];
    int i = 0, num = 0;
    while(i < 9){ // fill an array of random numbers
        num = rand_num();
        if (check_array(random,num,i)) num = rand_num();
        else {
            random[i] = num;
            i++;
        }
    }

    int k = 0, puzzleVal = 0;
    while(k < 9){ // iterate through the randomly ordered array
        puzzleVal = random[k];
        if(valid_num(puzzleVal, r, c, p)){
            puzzle_set(p, r, c, puzzleVal);
            if(fill_others(p, r + 1, c)){
                return true;
            }
            // else{
            //     if (r !=0) fill_others(p,r-1,c);
            //     else if(c != 0) fill_others(p,r,c-1);
            //     else puzzle_set(p, r, c, 0);
            // }
        }
        k++;
    }
    return false;
} 

/*************remove_values************/

void remove_values(puzzle_t *p, int count){
    while(count != 0){
        int r = rand()%9;
        int c = rand()%9;
        if(puzzle_getValue(p,r,c) != 0){
            puzzle_set(p, r, c, 0);
            count --;
        }

    }
}