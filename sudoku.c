#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "puzzle.h"
#include "create.h"
#include "solve.h"
#include "file.h"

int main(int argc, char *argv[])
{    
    if (argc != 2) { 
        fprintf(stderr,"Error: input one argument.\n");
        return 1;
    }
    else {
        char input[10];
        sscanf(argv[1],"%s", input);
        if (strcmp(input,"create") != 0 && strcmp(input,"solve") != 0){
            fprintf(stderr,"Error: enter 'create' or 'solve'.\n");
            return 1;
        }
        else if (strcmp(input,"create") == 0){
            puzzle_t *puzzle = puzzle_new();
            if (puzzle == NULL){
                fprintf(stderr,"Error allocating memory for puzzle.\n");
                return 2;
            }
            else{
                rand_init();
                build_puzzle(puzzle);
                puzzle_write(puzzle);
                puzzle_delete(puzzle);
            }
        }
        else if (strcmp(input,"solve") == 0){
            // puzzle_t *puzzle = puzzle_load();
            // int ** originals = original_num(puzzle);  //comment these out if needed 
            // backtrack_optimized(puzzle, 0, 0, originals);
            // //backtrack(puzzle,0,0);
            // puzzle_write(puzzle);
            // puzzle_delete(puzzle);
            char input[25];
            memset(input,0,strlen(input));
            int i = 0, count = 0;
            char file[10] = "board";
            FILE *fp = fopen(file,"w");
            while((scanf("%[^\n]",input)) != EOF){
                fprintf(fp,"%s\n",input);
                scanf("%c",input);
                memset(input,0,strlen(input));
                i++;
                if (i == 9){
                    count++;
                    fclose(fp);
                    fp = fopen(file,"r");
                    puzzle_t *puzzle = puzzle_load(fp);
                    
                    init(puzzle);
                    int ** originals = original_num(puzzle);  //comment these out if needed 
                    backtrack_optimized(puzzle, 0, 0, originals);
                    clean();
                    free(originals);

                    // backtrack(puzzle,0,0);

                    printf("\nPuzzle %d: \n", count);
                    puzzle_write(puzzle);
                    puzzle_delete(puzzle);
                    fclose(fp);
                    fp = fopen(file,"w");
                    i = 0;
                }
            }
        }

    }
    return 0;
}
 
