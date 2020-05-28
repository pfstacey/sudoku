#include <stdio.h>
#include "puzzle.h"
int main(void){
    puzzle_t * piper = puzzle_new();
    puzzle_set(piper, 0, 0, 9);
    puzzle_set(piper, 1, 1, 9);
    puzzle_set(piper, 2, 2, 9);
    puzzle_set(piper, 3, 3, 9);
    puzzle_write(piper);
    puzzle_delete(piper);
    return 0;
}




