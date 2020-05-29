/*
 * boolean method that returns true if an integer val is contained in array arr
 */
bool contains(int * arr, int val);

bool valid_puzzle(puzzle_t *puzzle, int row, int column, int puzzleVal);

bool backtrack(puzzle_t *puzzle, int row, int column);
