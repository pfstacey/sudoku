# SUDOKU IMPLEMENTATION
author: Piper Stacey
date: May, 2020
---

### QUERIER
Querier parses a given line, ensures it can be queried and queries it 
given a directory of crawler output files and a written out index file.

## Boot up Querier:
querier pageDirectory indexFilename

## User Interface: 
```
***** ~ Querier ~ *****
>type your query
whatever you would like to search
```

## Querier Pseudo code
# parse_line:
// walk through line and put each word into an array of words by spliting at spaces
    // alter the size to accurately reflect the size of the filled word array
# check_line:
// take the words array and sort through it
    // check if and/or is next to and/or
    // check if and/or is first or last
    // if all good, return a bool of true
# AND_scores
// given two counters, put the common docIDs into the first counter and alter the score to reflect whichever score is lower
# AND_iteration_helper
// called in AND_scores to help with the iteration and puting the counters together
# OR_scores
// given two counters, put all the docIDs into the first counter and alter common scores to reflect the addition of the 2 original scores
# OR_iteration_helper
// called in OR_scores to help with the iteration and puting the counters together
# calculate_scores
// finds the word within the given index and fills the counter result_temp
    // checks if the next word is not or
        // if true, combines result_temp with the counter that's the AND accumulator
        // if untrue, combines result_temp with the counter that's the OR accumulator
# getCounterSize
// finds the counter size by iterating through it (serves as an iteration helper)
# fillPairs
// takes a given array of pairs, fills it with pairs made from the now unique docIDs and their calculated scores
# insertionSort
// sorts an array of pairs
# print_Urls_Scores
// prints the scores, their docID, and their url

## Major data structures
Inside the crawler, I use two helper modules.
`pair.h` module
I use it to initialize, insert, extract, and free.
`word.h` module
I use it to normalize words (make them lowercase) within my parse_line method.
Below is the implementation of `pair`.

/**************** pair_new ****************/
/* Create a new (empty) pair.
 *
 * Caller provides:
 *   number of slots to be used for the hashtable within pair (must be > 0).
 * We return:
 *   pointer to the new pair; return NULL if error.
 * We guarantee:
 *   pair is initialized empty.
 * Caller is responsible for:
 *   later calling pair_delete.
 */
/**************** pair_new ****************/
pair_t *pair_new();

/**************** pair_insert ****************/
/* Insert two ints into the pair (docID, score).
 *
 * Caller provides:
 *   valid pointer to pair, ints for docID and score
 * We return:
 *   false if pair is full
 *   true if new docID and key was inserted.
 * Notes:
 *   if the key already exists, the counter within the key's item will increment
 */
bool pair_insert(pair_t *p, int docID, int score);

/**************** pair_docID ****************/
/* returns the docID of the pair
 *
 * Caller provides:
 *   valid pointer to pair
 * We return:
 *   -1 if the pointer doesn't exist
 *   otherwise the docID as an int
 * Notes:
 *   does not remove the docID from the pair, just returns it 
 */
int pair_docID(pair_t *p);

/**************** pair_Score ****************/
/* returns the score of the pair
 *
 * Caller provides:
 *   valid pointer to pair
 * We return:
 *   -1 if the pointer doesn't exist
 *   otherwise the score as an int
 * Notes:
 *   does not remove the score from the pair, just returns it 
 */
int pair_Score(pair_t *p);

/**************** pair_delete ****************/
/* Delete the pair
 *
 * Caller provides:
 *   valid pair pointer,
 *   valid pointer to function that handles one item (may be NULL).
 * We do:
 *   if pair==NULL, do nothing.
 *   otherwise, free the pair.
 */
void pair_delete(pair_t *p);

Below is the implementation of `word`.
/**************** normalizeWord ****************/
/* Returns the input word but in lowercase */
void normalizeWord(char * word);

## Assumption
Creating a directory and indexFilename before compiling or running is essential.

## Check for memory leak
All the valid outputs are demonstrated in testing.sh shell script. The ouput of the testing can be found in testing.out In order to access testing.out type make test &> testing.out Memory leaks can be checked in testing.sh and testing.out

## Compilation
To compile, type make 
To clean, type make clean
