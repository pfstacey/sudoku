//Unit Testing for puzzle.c module 
//Author: Piper Stacey
//Teammates: Matt Keating, Sarah Korb, Marlee Montella

#include <stdio.h>
#include <stdlib.h>
#include "puzzle.h"
int main(void){
    puzzle_t * piper = puzzle_new();
    puzzle_set(piper, 0, 0, 1);
    puzzle_set(piper, 1, 1, 2);
    puzzle_set(piper, 2, 2, 3);
    puzzle_set(piper, 3, 3, 4);
    puzzle_set(piper, 4, 4, 5);
    puzzle_set(piper, 5, 5, 6);
    puzzle_set(piper, 6, 6, 7);
    puzzle_set(piper, 7, 7, 8);
    puzzle_set(piper, 8, 8, 9);

    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

    puzzle_write(piper);

    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

    printf("getting minigrid 0 as a test:\n");
    int * array = puzzle_getMiniGrid(piper, 0,1);
    for(int i = 0; i < 9; i++){
        printf("%d ", array[i]);
        if((i%3 == 2)){
            printf("\n");
        }
    }
    printf("\n");

    printf("getting row 0 as a test:\n");
    int * row0 = puzzle_getRow(piper, 0);
    for(int i = 0; i < 9; i++){
        printf("%d ", row0[i]);
    }
    printf("\n\n");

    printf("getting col 0 as a test:\n");
    int * col0 = puzzle_getCol(piper, 0);
    for(int i = 0; i < 9; i++){
        printf("%d\n", col0[i]);
    }
    printf("\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

    free(row0);
    free(col0);

    free(array);
    puzzle_delete(piper);
    return 0;
}




