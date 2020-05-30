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
    int ** grid;
}puzzle_t;

/**************** puzzle_new ****************/
puzzle_t *puzzle_new(){
    puzzle_t * p = (puzzle_t *)malloc(sizeof(puzzle_t*));
    if(p != NULL){
        // allocate space for the grid
        (p->grid) = (int **)malloc(9 * sizeof(int *));
        // allocate space for each array
        if((p->grid) != NULL){
            for(int i = 0; i < 9; i++){
                (p -> grid)[i] = (int *)malloc(9 * sizeof(int));
                if((p -> grid)[i] == NULL){
                    printf("[puzzle_new] error: unable to allocate internal array\n");
                    return NULL;
                }
            }
            // fill grid with all zeroes
            for(int i = 0; i < 9; i++){
                for(int j = 0; j < 9; j++){
                    (p->grid)[i][j] = 0;
                }
            }
            return p;
        }
        else{
            printf("[puzzle_new] error: null grid\n");
            return NULL;
        }
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
            int * row = calloc(9, sizeof(int));
            if(row != NULL){
                for(int i = 0; i < 9; i++){
                    row[i] = (p->grid)[r][i];
                }
                return row;
            }
            else{
                printf("[puzzle_getRow] error: trouble allocating column space\n");
                return NULL;
            }
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
            if(column != NULL){
                for(int i = 0; i < 9; i++){
                    column[i] = (p->grid)[i][col];
                }
                return column;
            }
            else{
                printf("[puzzle_getCol] error: trouble allocating column space\n");
                return NULL;
            }
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
/**************** puzzle_getMiniGrid ****************/
/*
| ----- | ----- | ----- |
|   0   |   1   |   2   |
| ----- | ----- | ----- |
|   3   |   4   |   5   | 
| ----- | ----- | ----- |
|   6   |   7   |   8   | 
| ----- | ----- | ----- |
 */
int * puzzle_getMiniGrid(puzzle_t * p, const int row, const int col){
    if(p != NULL){
        int * mini = malloc((sizeof(int))*9);
        if(mini != NULL){
            if( row < 3 && row >= 0 ){
                //minigrid 0, 1, or 2
                if(col < 3 && col > 0){
                    //minigrid 0
                    int index = 0; 
                    for(int i = 0; i < 3; i++){
                        for(int j = 0; j < 3; j++){
                            mini[index] = (p->grid)[i][j];
                            index++; 
                        }
                    }
                }
                else if (col < 6 && col >= 3){
                    //minigrid 1
                    int index = 0;
                    for(int i = 0; i < 3; i++){
                        for(int j = 3; j < 6; j++){
                            mini[index] = (p->grid)[i][j];
                            index++; 
                        }
                    }
                }
                else if (col < 9 && col >= 6){
                    //minigrid 1
                    int index = 0;
                    for(int i = 0; i < 3; i++){
                        for(int j = 6; j < 9; j++){
                            mini[index] = (p->grid)[i][j];
                            index++; 
                        }
                    }
                }
            }

            else if( row < 6 && row >= 3 ){
                //minigrid 0, 1, or 2
                if(col < 3 && col > 0){
                    //minigrid 3
                    int index = 0; 
                    for(int i = 3; i < 6; i++){
                        for(int j = 0; j < 3; j++){
                            mini[index] = (p->grid)[i][j];
                            index++; 
                        }
                    }
                }
                else if (col < 6 && col >= 3){
                    //minigrid 4
                    int index = 0;
                    for(int i = 3; i < 6; i++){
                        for(int j = 3; j < 6; j++){
                            mini[index] = (p->grid)[i][j];
                            index++; 
                        }
                    }
                }
                else if (col < 9 && col >= 6){
                    //minigrid 5
                    int index = 0;
                    for(int i = 3; i < 6; i++){
                        for(int j = 6; j < 9; j++){
                            mini[index] = (p->grid)[i][j];
                            index++; 
                        }
                    }
                }
            }

            else if( row < 9 && row >= 6 ){
                //minigrid 0, 1, or 2
                if(col < 3 && col > 0){
                    //minigrid 6
                    int index = 0; 
                    for(int i = 6; i < 9; i++){
                        for(int j = 0; j < 3; j++){
                            mini[index] = (p->grid)[i][j];
                            index++; 
                        }
                    }
                }
                else if (col < 6 && col >= 3){
                    //minigrid 7
                    int index = 0;
                    for(int i = 6; i < 9; i++){
                        for(int j = 3; j < 6; j++){
                            mini[index] = (p->grid)[i][j];
                            index++; 
                        }
                    }
                }
                else if (col < 9 && col >= 6){
                    //minigrid 8
                    int index = 0;
                    for(int i = 6; i < 9; i++){
                        for(int j = 6; j < 9; j++){
                            mini[index] = (p->grid)[i][j];
                            index++; 
                        }
                    }
                }
            }
            return mini;
        }
        else{
            printf("[puzzle_getMiniGrid] error: null mini array\n");
            return NULL;
        }
    }
    else{
        printf("[puzzle_getMiniGrid] error: null puzzle\n");
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

/**************** puzzle_load ****************/
puzzle_t *puzzle_load(){
    puzzle_t *p = puzzle_new();
    if(p != NULL){
        int i = 0;
        while(fscanf(stdin, "%d %d %d %d %d %d %d %d %d", 
            &(p->grid)[i][0], 
            &(p->grid)[i][1], 
            &(p->grid)[i][2], 
            &(p->grid)[i][3], 
            &(p->grid)[i][4], 
            &(p->grid)[i][5], 
            &(p->grid)[i][6], 
            &(p->grid)[i][7], 
            &(p->grid)[i][8]) == 9){
                i += 1; 
        }
        return p;
    }
    else{
        printf("[puzzle_load] error: trouble making new puzzle\n");
        return NULL;
    }
}


/**************** puzzle_delete ****************/
void puzzle_delete(puzzle_t *p){
    if(p != NULL){
        for(int i = 0; i < 9; i++){
            free((p->grid)[i]);
        }
        free((p->grid));
        free(p);
    }
}

