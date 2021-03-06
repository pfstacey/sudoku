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

#ifdef TEST
int main(void){
        printf("---------------------------------------------------\n");
        printf("              Testing the solve class...\n");
        printf("---------------------------------------------------\n");
	puzzle_t *t = puzzle_new();
	puzzle_write(t);
        printf("\n");

        printf("Backtracking through the puzzle now...\n");
	backtrack(t, 0, 0);

        printf("Here's the new puzzle...\n");
	puzzle_write(t);
        printf("\n");
        
	puzzle_delete(t);

        printf("Here's the original puzzle... we'll fill it in a second\n");
	puzzle_t *test = puzzle_new();

        printf("Filling the puzzle...\n");
        printf("It should look like this:\n");
        printf("* * * * * * * * * * *\n* 1 6 0 0 0 3 0 0 0 *\n* 2 0 0 7 0 6 0 1 4 *\n* 0 4 5 0 8 1 0 0 7 *\n* 5 0 8 4 0 0 0 0 0 *\n* 0 0 4 3 0 8 9 0 0 *\n* 0 0 0 0 0 7 2 0 8 *\n* 8 0 0 6 3 0 1 9 0 *\n* 6 3 0 1 0 5 0 0 2 *\n* 0 0 0 8 0 0 0 3 6 *\n* * * * * * * * * * *\n");
	puzzle_set(test, 0, 0, 1);
	puzzle_set(test, 0, 1, 6);
	puzzle_set(test, 0, 5, 3);
	puzzle_set(test, 1, 0, 2);
	puzzle_set(test, 1, 3, 7);
	puzzle_set(test, 1, 5, 6);
	puzzle_set(test, 1, 7, 1);
	puzzle_set(test, 1, 8, 4);
	puzzle_set(test, 2, 1, 4);
	puzzle_set(test, 2, 2, 5);
	puzzle_set(test, 2, 4, 8);
	puzzle_set(test, 2, 5, 1);
	puzzle_set(test, 2, 8, 7);
	puzzle_set(test, 3, 0, 5);
	puzzle_set(test, 3, 2, 8);
	puzzle_set(test, 3, 3, 4);
	puzzle_set(test, 4, 2, 4);
	puzzle_set(test, 4, 3, 3);
	puzzle_set(test, 4, 5, 8);
	puzzle_set(test, 4, 6, 9);
	puzzle_set(test, 5, 5, 7);
	puzzle_set(test, 5, 6, 2);
	puzzle_set(test, 5, 8, 8);
	puzzle_set(test, 6, 0, 8);
	puzzle_set(test, 6, 3, 6);
	puzzle_set(test, 6, 4, 3);
	puzzle_set(test, 6, 6, 1);
	puzzle_set(test, 6, 7, 9);
	puzzle_set(test, 7, 0, 6);
	puzzle_set(test, 7, 1, 3);
	puzzle_set(test, 7, 3, 1);
	puzzle_set(test, 7, 5, 5);
	puzzle_set(test, 7, 8, 2);
	puzzle_set(test, 8, 3, 8);
	puzzle_set(test, 8, 7, 3);
	puzzle_set(test, 8, 8, 6);

        printf("Here's what the manually filled puzzle is...\n");
	puzzle_write(test);

        printf("Now, we'll solve it!\n");
        printf("First, we'll store all the rows, columns, and minigrids\n");
	init(test);
        printf("Next, we'll check which number can be added at which places\n");
	int ** originals = original_num(test);  //comment these out if needed 
        printf("Then, we'll solve the puzzle using backtrack recursion\n");
	backtrack_optimized(test, 0, 0, originals);
	clean();
	free(originals);

        printf("All done! Here's the solved puzzle...\n");
	puzzle_write(test);

        printf("This is what we expected:\n");
        printf("* * * * * * * * * * *\n* 1 6 7 5 4 3 8 2 9 *\n* 2 8 3 7 9 6 5 1 4 *\n* 9 4 5 2 8 1 3 6 7 *\n* 5 9 8 4 1 2 6 7 3 *\n* 7 2 4 3 6 8 9 5 1 *\n* 3 1 6 9 5 7 2 4 8 *\n* 8 7 2 6 3 4 1 9 5 *\n* 6 3 9 1 7 5 4 8 2 *\n* 4 5 1 8 2 9 7 3 6 *\n* * * * * * * * * * *\n");
        printf("Cleaning up...\n");
	puzzle_delete(test);
        printf("---------------------------------------------------\n");
        return 0;
}
#endif