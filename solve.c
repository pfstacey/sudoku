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

        //executed ONLY if puzzle is UNSOLVABLE
        return false;
} 


bool backtrack_optimized(puzzle_t *puzzle, int row, int column){

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

        //executed ONLY if puzzle is UNSOLVABLE
        return false;
} 
