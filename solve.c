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
        for(int i = 0; i < sizeof(arr)/sizeof(int); i++){
                if(arr[i] == val){
                        return true;
                }
        }

        return false;
}

bool is_valid(puzzle_t *puzzle, int row, int column, int puzzleVal){
        int * row = puzzle_getRow(puzzle, row);
        int * col = puzzle_getCol(puzzle, column);
        int * sub = puzzle_getMiniGrid(puzzle, row, column);

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
                        if(solve(puzzle, row + 1, column)){
                                return true;
                        }
                        else{
                                puzzle[row][column] = 0;
                        }
                }
                puzzleVal++;
        }

        //executed ONLY if puzzle is UNSOLVABLE
        return false;
} 
