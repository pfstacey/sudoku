/* 
 * createtest.c - Unit testing for CS50 create module
 *
 *
 * Author:  Sarah Korb, 2020
 * Teammates: Matt Keating, Marlee Montella, Piper Stacey
 *
 */

#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include "create.h"
#include "puzzle.h"


int main(){
    puzzle_t *test = puzzle_new();

    printf("Starting with empty puzzle\n");
    puzzle_write(test);

    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

    printf("Filling first mini grid\n");
    fill_miniGrid(test, 0, 0);
    puzzle_write(test);

    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("Filling center mini grid\n");
    fill_miniGrid(test, 3, 3);
    puzzle_write(test);

    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("Filling last mini grid\n");
    fill_miniGrid(test, 6, 6);
    puzzle_write(test);

    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("Filling others\n");
    fill_others(test, 0,3);
    puzzle_write(test);
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

    printf("Test valid_num using arbitrary integer: 1\n");
    printf("checking for 1 in column 0, row 0\n");
    if (valid_num(1,0,0,test)){
        printf("1 is not found in column 0, row 0 or in the first minigrid \n");
    }else{
          printf("1 found in column 0/row 0/in the first minigrid. Not a valid number\n");
    }
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("Removing values: Should leave 40 spaces open\n");
    remove_values(test, 40);
    puzzle_write(test);
    
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("Using build_puzzle to generate new,sudoku board\n");
    puzzle_t *test2 = puzzle_new();
    build_puzzle(test2);
    puzzle_write(test2);

    puzzle_delete(test2);
    puzzle_delete(test);

    return 0;



}