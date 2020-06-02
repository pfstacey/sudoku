/*
 * Sudoku solve
 *
 * provies backtracking algorithm
 *
 * Author: Matt Keating
 * Teammates: Piper Stacey, Sarah Korb, Marlee Montella
 */

#include<stdio.h>
#include<stdlib.h>
#include "puzzle.h"
 

/*
 * boolean method that returns true if an integer val is contained in array arr
 */
bool contains(int * arr, int val){
        for(int i = 0; i < 9; i++){
                if(arr[i] == val){
                        return true;
                }
        }

        return false;
}

bool valid_puzzle(puzzle_t *puzzle, int r, int c, int puzzleVal){
        int * row = puzzle_getRow(puzzle, r);
        int * col = puzzle_getCol(puzzle, c);
        int * sub = puzzle_getMiniGrid(puzzle, r, c);

        if(contains(row, puzzleVal) || contains(col, puzzleVal) || contains(sub, puzzleVal)){
                return false;
        }

        free(row);
        free(col);
        free(sub);

        return true;
}

bool backtrack(puzzle_t *puzzle, int row, int column){

        //base case
        if(row == 9){
                row = 0;
                column ++;
        }

        if(column == 9){
                return true;
        }

        //case for if the row and column already has a value from the given puzzle
        if(puzzle_getValue(puzzle, row, column) != 0){
                return backtrack(puzzle, row + 1, column);
        }

        int puzzleVal = 1;

        while(puzzleVal < 10){
                if(valid_puzzle(puzzle, row, column, puzzleVal)){
                        puzzle_set(puzzle, row, column, puzzleVal);

                        //recursive step
                        if(backtrack(puzzle, row + 1, column)){
                                return true;
                        }
                        else{
				puzzle_set(puzzle, row, column, 0);
                        }
                }
                puzzleVal++;
        }

        return false;
} 


bool backtrack_optimized(puzzle_t *puzzle, int row, int column, int ** original){

        //base case
        if(row == 9){
                row = 0;
                column ++;
        }

        if(column == 9){
                return true;
        }

        //case for if the row and column already has a value from the given puzzle
        if(puzzle_getValue(puzzle, row, column) != 0){
                return backtrack(puzzle, row + 1, column);
        }

        int i;
        int puzzleVal;

        for(i =0; i< 9; i ++){
                if (original[row][i] > 0){ //ignore negatives, they indicate values that we are sure won't work
                        puzzleVal = original[row][i];
                        if(valid_puzzle(puzzle, row, column, puzzleVal)){
                                puzzle_set(puzzle, row, column, puzzleVal);
                        
                        //recursive step
                                if(backtrack(puzzle, row + 1, column)){
                                        return true;
                                }
                                else{
				        puzzle_set(puzzle, row, column, 0);
                                }
                      }
                
                }else{
                        continue;
                }
        }
        return false;
} 

/**************original_num*******************/
int** original_num(puzzle_t *p){
        int ** originals = (int **)malloc(9 * sizeof(int *));
        //fill with options
        int i, j;
        for (i = 0; i < 9; i ++){
                originals[i] = (int *)malloc(9 * sizeof(int));
                if(originals[i] == NULL){
                    fprintf(stderr,"[puzzle_new] error: unable to allocate internal array\n");
                    return NULL;
                }      

        } //fill 9 rows with values from 1-9
        for(i = 0; i < 9; i++){  
                for(j = 0; j < 9; j++){
                        originals[i][j] = j+1;
                }
        }
        //now iterate through puzzle and check for existing numbers
        for(i = 0; i < 9; i++){
                for(j = 0; j < 9; j++){
                    if (puzzle_getValue(p, i, j) != 0){ //if the puzzle has a value there we know it must be permanent
                            originals[i][j] = -1; //change it in our record to something we can ignore later
                    }
                }
        }
        return originals;
}