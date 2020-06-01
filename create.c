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
        remove_values(puzzle, 40);
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
                if (check_array(checked,num,k)) num = rand_num();
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
            if (!added) printf("frik\n");
            free(checked);
        }
    }
}

/**************** check_array() ****************/
bool check_array(int checked[], int num, int pos)
{
    int i = 0;
    for (i = 0; i < pos; i++){
        if (num == checked[i]){
            return true;
        }
    }
    return false;
}

/**************** valid_num() ****************/
bool valid_num(int num, int r, int c, puzzle_t *p)
{
    int i, j;

    //check if a value is in the same block
    for (i = 0; i < 9; i++) {
        for (j = 0; j < 9; j++) {
            if ((i!= r || (j!= c))){
                if((((int) i/3) == ((int) r/3)) && (((int) j/3) == ((int) c/3))) {
                    if (puzzle_getValue(p, i, j) == num){
                        return false;
                    }
                }
            }
        }
    }

    // Chekc if in same row
    for (i = 0; i < 9; i++) {
        if (i!= c) {
            if (puzzle_getValue(p, r, i) == num){
                return false;
            }
        }
    }

    // check if in same column
    for (i = 0; i < 9; i++) {
        if (i!= r) {
            if (puzzle_getValue(p, i, c) == num){
                return false;
            }
        }
    }

    return true;

    /*
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
    */
}

/**************** fill_others() ****************/
bool fill_others(puzzle_t *p, int r, int c)
{
    /*
   if (r == 9){
        r = 0;
        c++;
    }

    if (c == 9) return true;

    if (puzzle_getValue(p, r, c) != 0) return fill_others(p,r+1,c);*/

/*
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
    */

    int start = (rand())%9;
    srand(rand()+(r*9)+c); // For recursion
    int k = 0, puzzleVal = 0;
    for (k = start; k < start + 9; k++){
        puzzleVal = (k%9) + 1;
        if(!valid_num(puzzleVal, r, c, p)){
            //printf("hi");
            continue;
        }
        puzzle_set(p, r, c, puzzleVal);


        //recursive assignment
        int nextr, nextc;
        get_next_cell(r, c, &nextr, &nextc, p);

            if (nextr == -1 && nextc == -1) {
                //printf("hi");
                return true;
            }
            else {
                if (fill_others(p, nextr, nextc)) {
                    return true;
                }
                puzzle_set(p, r, c, 0);
            }
    }
    return false;
}
        
        

/*
    }
    while(k < 9){ // iterate through the randomly ordered array
        puzzleVal = random[k];
        if(valid_num(puzzleVal, r, c, p)){
            puzzle_set(p, r, c, puzzleVal);
            
            printf("%d vs %d\n", puzzleVal, puzzle_getValue(p, r, c));
            int nextr, nextc;
            get_next_cell(r, c, &nextr, &nextc, p);

            if (nextr == -1 && nextc == -1) {
                printf("hi");
                return true;
            }
            else {
                if (fill_others(p, nextr, nextc)) {
                    return true;
                }
                //puzzle_set(p, r, c, 0);
            }

            if(fill_others(p, r + 1, c)){
                return true;
            }
            else{
                if (r !=0) fill_others(p,r-1,c);
                else if(c != 0) fill_others(p,r,c-1);
                else puzzle_set(p, r, c, 0);
            }
        }
        k++;
    }
    return false;
} */

void get_next_cell(int r, int c, int *nextr, int *nextc, puzzle_t *p) {
    int i, j;  // Next cells
    for (i = r; i < 9; i++) {
        int begin;
        if (i == r) {
            begin = c;
        }
        else {
            begin = 0;
        }
        for (j = begin; j < 9; j++) {
            if (puzzle_getValue(p, i, j) == 0) {
                *nextr = i;
                *nextc = j;
                return;
            }
        }
    }
    *nextr = -1;
    *nextc = -1;
    return;
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