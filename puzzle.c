/* 
 * puzzle.c - CS50 puzzle module
 *
 * see puzzle.h for more information
 *
 * Author: Piper Stacey, 2020
 * Teammates: Matt Keating, Sarah Korb, Marlee Montella
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "puzzle.h"

/**************** file-local global variables ****************/
/* none */

/**************** global types ****************/
typedef struct puzzle{
    int grid[9][9];
}puzzle_t;

/**************** puzzle_new ****************/
puzzle_t *puzzle_new(){
    puzzle_t * p = (puzzle_t *)malloc(9*9*sizeof(puzzle_t*));
    if(p != NULL){
        // fill grid with all zeroes
        for(int i = 0; i < 9; i++){
            for(int j = 0; j < 9; j++){
                (p->grid)[i][j] = 0;
            }
        }
        return p;
    }
    else return NULL;
}

/**************** puzzle_set ****************/
bool puzzle_set(puzzle_t *p, const int row, const int col, const int value){
    if(p != NULL){
        if(row >= 0 && row < 9){
            if(col >= 0 && col < 9){
                (p->grid)[row][col] = value;
                return true;
            }
            else{
                printf("[puzzle_set] error: invalid col\n");
                return NULL;
            }
        }
        else{
            printf("[puzzle_set] error: invalid row\n");
            return NULL;
        }
    }
    else{
        printf("[puzzle_set] error: invalid puzzle\n");
        return NULL;
    }
}

/**************** puzzle_getValue ****************/
const int puzzle_getValue(puzzle_t * p, const int row, const int col){
    if(p != NULL){
        if(row >= 0 && row < 9){
            if(col >= 0 && col < 9){
                return (p->grid)[row][col];
            }
            else{
                printf("[puzzle_getValue] error: invalid col\n");
                return -1;
            }
        }
        else{
            printf("[puzzle_getValue] error: invalid row\n");
            return -1;
        }
    }
    else{
        printf("[puzzle_getValue] error: invalid puzzle\n");
        return -1;
    }
}

/**************** puzzle_getRow ****************/
int * puzzle_getRow(puzzle_t * p, const int r){
    if(p != NULL){
        if(r >= 0 && r < 9){
            return (p->grid)[r];
        }
        else{
            printf("[puzzle_getRow] error: invalid row\n");
            return NULL;
        }
    }
    else{
        printf("[puzzle_getRow] error: invalid puzzle\n");
        return NULL;
    }
}

/**************** puzzle_getCol ****************/
int * puzzle_getCol(puzzle_t * p, const int col){
    if(p != NULL){
        if(col >= 0 && col < 9){
            int * column = calloc(9, sizeof(int));
            for(int i = 0; i < 9; i++){
                 column[i] = (p->grid)[i][col];
            }
            return column;
        }
        else{
            printf("[puzzle_getCol] error: invalid row\n");
            return NULL;
        }
    }
    else{
        printf("[puzzle_getCol] error: invalid puzzle\n");
        return NULL;
    }
}

/**************** puzzle_write ****************/
void puzzle_write(puzzle_t *p){
    if(p != NULL){
        for(int i = 0; i < 9; i++) {
            for(int j = 0; j < 9; j++) {
                printf("%d ", (p->grid)[i][j]);
            }
            printf("\n");
        }
    }
    else{
        printf("[puzzle_write] error: null puzzle as parameter\n");
    }
}

/**************** puzzle_delete ****************/
void puzzle_delete(puzzle_t *p){
    if(p != NULL){
        free(p);
    }
}