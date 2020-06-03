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

/**************** build_puzzle() ****************/
bool build_puzzle(puzzle_t *puzzle)
{
    // fill diagonal 3x3 matrices
    for (int i = 0; i < 3; i++){
        fill_miniGrid(puzzle,i*3,i*3);
    }
    // recursively fill the rest of the spaces
    if(fill_others(puzzle,0,3)) { // if successful, remove 40 values 
        remove_values(puzzle, 40);
        return true;
    }
    else return false;
}

/**************** rand_init() ****************/
void rand_init(void){
    time_t t;
    srand((unsigned) time(&t)); // initialize ransom number generator
}

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
    for (int i = row; i < row+3; i++){ // 3 rows
        for (int j = column; j < column+3; j++){ // 3 columns per row
            num = rand_num(); // get a random number
            int *checked = (int *)calloc(9,sizeof(int)); // initialize checked array
            k = 0; // array index tracker
            added = false; 
            while(!added && k < 9){ // until number 1-9 have been checked or the spot has not been filled
                if (check_array(checked,num,k)){ // check if the number has already been tested
                    checked[k] = num; // mark the number as checked
                    num = rand_num(); // generate a new random number
                } 
                else if (!valid_num(num,i,j,p)){ // if the number is not valid (conflict in row/column/mini grid)
                    checked[k] = num; // mark as checked
                    k++; // increment the checked array
                    num = rand_num(); // generate new random number
                }
                else{ // if the number has not been checked and it is valid, fill the space
                    puzzle_set(p,i,j,num);
                    added = true; // exit while loop
                }
            }
            free(checked); // reset checked array
        }
    }
}

/**************** check_array() ****************/
bool check_array(int checked[], int num, int pos)
{
    if (pos == 0) return false; // nothing has been checked
    else{
        for (int i = 0; i < pos; i++){ // for each number in the array
            if (num == checked[i]){ // if it equals the num parameter, true
                return true;
            }
        }
    }
    return false; // no matches, return false
}

/**************** valid_num() ****************/
bool valid_num(int num, int r, int c, puzzle_t *p)
{
    int i = 0;
    int *row = puzzle_getRow(p,r); // array of number in row
    int *column = puzzle_getCol(p,c); // array of number in column
    int *grid = puzzle_getMiniGrid(p,r,c);  // array of number in mini grid
    while (i < 9){ // checking each number in the arrays
        if (row[i] != num && column[i] != num && grid[i] != num) i++; // no matches, check next index
        else break; // if there is a match, exit the while loop
    }
    free(row);
    free(column);
    free(grid);
    if (i == 9) return true; // number does not appear in the row/column/grid 
    else return false; // number appears in the row/column/grid 
    
}

/**************** fill_others() ****************/
bool fill_others(puzzle_t *p, int r, int c)
{
    int start = (rand())%9; //start with a random value between 0-8
    srand(rand()+(r*9)+c); // For recursion
    int k = 0, puzzleVal = 0;
    for (k = start; k < start + 9; k++){ 
        puzzleVal = (k%9) + 1; //Generate possible values between 1-9
        if(!valid_num(puzzleVal, r, c, p)){ //If it's a valid number, set the cell to this value
            continue;
        }
        puzzle_set(p, r, c, puzzleVal);


        //recursive assignment
        int nextr, nextc;
        get_next_cell(r, c, &nextr, &nextc, p);

            if (nextr == -1 && nextc == -1) { //If the values of nextr/nextc are -1, we have reached the last cell, so return
                return true;
            }
            else {
                if (fill_others(p, nextr, nextc)) { //otherwise we continue recursing on this next cell
                    return true;
                }
                puzzle_set(p, r, c, 0); //If the recursive call returns false, we made a mistake so set this cell to 0;
            }
    }
    return false;
}

void get_next_cell(int r, int c, int *nextr, int *nextc, puzzle_t *p) {
    int i, j;  // Next cells
    for (i = r; i < 9; i++) { 
        int begin;
        if (i == r) { //start with our current location
            begin = c;
        }
        else {
            begin = 0;
        }
        for (j = begin; j < 9; j++) { //look around for possible emty spaces around our current cell 
            if (puzzle_getValue(p, i, j) == 0) { //if the next cell is an empty space, we set it's coordinates as nextr, nextc
                *nextr = i;
                *nextc = j;
                return;
            }
        }
    }
    *nextr = -1; //otherwise this cell is not an option -> set coordinates to -1
    *nextc = -1; 
    return;
}

/*************remove_values************/
void remove_values(puzzle_t *p, int count){
    while(count != 0){ // number of spaces to remove
        // generate random coordinates on the board
        int r = rand()%9; 
        int c = rand()%9;
        if(puzzle_getValue(p,r,c) != 0){ // if there is a value, set to 0
            puzzle_set(p, r, c, 0);
            count --;
        }
        // otherwise, get a new set of coordinates
    }
}

#ifdef TEST
int main(void){
    printf("------------------------------------------------------\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("    Testing the functionality of creating puzzles!\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

    puzzle_t * test = puzzle_new();

    printf("Initializing a new puzzle: \n");
    puzzle_write(test);
    printf("\n");

    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

    printf("Filling first mini grid:\n");
    fill_miniGrid(test, 0, 0);
    puzzle_write(test);
    printf("\n");

    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("Filling center mini grid:\n");
    fill_miniGrid(test, 3, 3);
    puzzle_write(test);
    printf("\n");

    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("Filling last mini grid:\n");
    fill_miniGrid(test, 6, 6);
    puzzle_write(test);
    printf("\n");

    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("Filling the other mini grids:\n");
    fill_others(test, 0,3);
    puzzle_write(test);
    printf("\n");

    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

    printf("Test valid_num using arbitrary integer: 1\n");
    printf("checking for 1 in row 0, column 0\n");
    if (valid_num(1,0,0,test)){
        printf("1 is not found in column 0, row 0 or in the first minigrid!\n");
    }else{
          printf("1 found in column 0/row 0/in the first minigrid. Not a valid number!\n");
    }
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("Now we have filled the puzzle! Next, we'll delete 40 \nitems from the puzzle and will be all good to go!\n");
    remove_values(test, 40);
    puzzle_write(test);
    printf("\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("             Now let's put it all together! \n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("Using build_puzzle to generate new,sudoku board\n");
    puzzle_t *test2 = puzzle_new();
    build_puzzle(test2);
    printf("Here's the final puzzle: \n");
    puzzle_write(test2);
    printf("\n");

    puzzle_delete(test2);
    puzzle_delete(test);
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("------------------------------------------------------\n");
    return 0;

}
#endif