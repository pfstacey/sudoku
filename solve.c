/*
 * Sudoku solve
 *
 * provies backtracking algorithm
 *
 * Author: Matt Keating
 * Teammates: Piper Stacey, Sarah Korb, Marlee Montella
 */

#include "solve.h"

set_t *all_r_c_m;

void init(puzzle_t *puzzle){
	all_r_c_m = set_new();

	for(int i = 0; i < 9; i++){
		char *name = malloc(3 * sizeof(char));

		sprintf(name, "r%d", i);

		set_insert(all_r_c_m, name, puzzle_getRow(puzzle, i));
	}

	for(int i = 0; i < 9; i++){
		char *name = malloc(3 * sizeof(char));

		sprintf(name, "c%d", i);

		set_insert(all_r_c_m, name, puzzle_getCol(puzzle, i));
	}

	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			char *name = malloc(4 * sizeof(char));

			sprintf(name, "m%d%d", i, j);

			set_insert(all_r_c_m, name, puzzle_getMiniGrid(puzzle, i, j));
		}
	}
}

/******************** CLEAN ******************
 * deletes the set from memory - please call this
 */
void itemdelete(void *item){
	free((int *) item);
}

void clean(){
	set_delete(all_r_c_m, itemdelete);
}

int * get_subarray(int type, int row, int col){
	//get the key string for the row and column
	char *name = malloc(4 * sizeof(char));

	if(type == 1){
		sprintf(name, "r%d", row);
	}
	else if(type == 2){
		sprintf(name, "c%d", col);
	}
	else if(type == 3){
		sprintf(name, "m%d%d", row, col);
	}
	else{
		fprintf(stderr, "Invalid method call, make type [1, 3]");
		return NULL;
	}

	return set_find(all_r_c_m, name);
}

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

bool optimized_valid_puzzle(puzzle_t *puzzle, int r, int c, int puzzleVal){
        int * row = get_subarray(1, r, c);
        int * col = get_subarray(2, r, c);
        int * sub = get_subarray(3, r, c);

        if(contains(row, puzzleVal) || contains(col, puzzleVal) || contains(sub, puzzleVal)){
                return false;
        }

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
		if(valid_num(puzzleVal, row, column, puzzle)){
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
                        if(optimized_valid_puzzle(puzzle, row, column, puzzleVal)){
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

		    int val = puzzle_getValue(p, i, j);

                    if (val != 0){ //if the puzzle has a value there we know it must be permanent
                            originals[i][val - 1] = -1; //change it in our record to something we can ignore later
                    }
                }
        }
        return originals;
}

