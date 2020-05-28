#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "puzzle.h"
#include "create.h"

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
                printf("\nfinal board:\n");
                puzzle_write(puzzle);
                puzzle_delete(puzzle);
            }
        }

    }
    return 0;
}
 
  
