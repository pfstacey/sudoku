---
layout: page
title: Sudoku Design Spec
Authors: Sarah Korb, Matt Keating, Marlee Montella, Piper Stacey
Dates: May 25 - June 3, 2020
---
 
Recall the [Sudoku Requirements Spec](REQUIREMENTS.html); the **create** creates and solves a sudoku puzzle.
The **solve** takes a 9X9 sudoku array and solves the array for the user, printing the unique solution to the user. 
 
This Design Spec contains:
 
* User interface
* Inputs and Outputs
* Functional decomposition into modules
* Pseudo code for logic/algorithmic flow
* Dataflow through modules
* Major data structures
* Testing plan
 
### User interface
 
The sudoku solve and create methods are currently run with a command line interface with one argument, either create or solve. In future designs we hope to implement a graphical user interface.
 
```
sudoku (create/solve)
```
 
For example:
 
``` bash
$ ./sudoku create
$ cat board | ./sudoku solve
```
Note: The file *board* is the output of the sudoku creator. It will be formatted as 9 lines of test, each with 9 numbers separated by white space. Blank spaces will be represented by a 0. 
 
### Inputs and outputs
 
#### create
Input: the only inputs are command-line parameters; see the User Interface above.
 
Output: We output an unsolved sudoku board in the form of a 9x9 number array with at least 40 0’s indicating the empty spaces
 
#### solve 
 
Input: 
 
Output: We output the solved 9x9 sudoku array. The solution is unique. 
 
 
### Functional decomposition into modules
 
We anticipate the following modules or functions:
 
1. *main*, which parses arguments and initializes other modules
2. *solve*, which calls backtrace to generate puzzle solution
3. *create*, which generates a pseudo random puzzle and removes at least 40 spots
4. *backtrack*, implements backtracking algorithm given a 9x9 array as a parameter
4. *check_solution*, which verifies that a puzzle is a valid sudoku solution.
 
### Pseudo code for logic/algorithmic flow
 
The crawler will run as follows:
 
1. execute from a command line as shown in the User Interface
2. parse the command line, validate parameters, initialize other modules
3. make a *webpage* for the `seedURL`, marked with depth=0
4. add that page to the *bag* of webpages to crawl
5. add that URL to the *hashtable* of URLs seen
3. while there are more webpages to crawl,
   5. extract a webpage (URL,depth) item from the *bag* of webpages to be crawled,
   4. pause for at least one second,
   6. use *pagefetcher* to retrieve a webpage for that URL,
   5. use *pagesaver* to write the webpage to the `pageDirectory` with a unique document ID, as described in the Requirements.
   6. if the webpage depth is < `maxDepth`, explore the webpage to find links:
       7. use *pagescanner* to parse the webpage to extract all its embedded URLs;
       7. for each extracted URL,
           8. 'normalize' the URL (see below)
           9. if that URL is not 'internal' (see below), ignore it;
           9. try to insert that URL into the *hashtable* of URLs seen
               10. if it was already in the table, do nothing;
               11. if it was added to the table,
                   12. make a new *webpage* for that URL, at depth+1
                   13. add the new webpage to the *bag* of webpages to be crawled
 
**normalize the URL** means to convert it into a clean, canonical form.
 
**internal** means the URL stays within the CS50 playground http://old-www.cs.dartmouth.edu/.
 
A good implementation will not necessarily encode all the above code in a single, deeply-nested function; part of the Implementation Spec is to break the pseudocode down into a cleanly arranged set of functions.
 
Notice that our pseudocode says nothing about the order in which it crawls webpages; since it presumably pulls them out of a *bag*, and a *bag* abstract data structure explicitly denies any promise about the order of items removed from a bag, we can't expect any particular crawl order.
That's ok.
The result may or may not be a Breadth-First Search, but for the crawler we don't care about the order as long as we explore everything within the `maxDepth` neighborhood.
 
The crawler completes and exits when it has nothing left in its bag - no more pages to be crawled.
The maxDepth parameter indirectly determines the number of pages that the crawler will retrieve.
 
 
### Dataflow through modules
 
1. *main* parses parameters and passes them to either the solve or create.
2. *solve* loads the puzzle into a puzzle struct and calls *backtrack* to solve the file.
3. *create* generates the puzzle using *backtrack*.
4. *backtrack* takes in a puzzle struct from *solve* or *create* and uses a backtracking algorithm while verifying a solution with *check_solution*
4. *check_solution* gets a puzzle struct from *check_solution* and returns a boolean.
 
### Major data structures
 
Puzzle: a 9x9 integer array.
 
### Testing plan
 
*Unit testing*.  A small test program in `testing.sh` to test each module to make sure it does what it's supposed to do.
 
*Integration testing*.  Assemble the crawler and test it as a whole using `testing.sh`.
In each case, examine the output files carefully to be sure they have the contents of the correct page, with the correct URL, and the correct depth.
Ensure that no pages are missing or duplicated.
Print "progress" indicators from the crawler as it proceeds (e.g., print each URL explored, and each URL found in the pages it explores) so you can watch its progress as it runs.
 
0. Test the program with various forms of incorrect command-line arguments to ensure that its command-line parsing, and validation of those parameters, works correctly.
 
0. Test the crawler with a `seedURL` that points to a non-existent server.
 
0. Test the crawler with a `seedURL` that points to a non-internal server.
 
0. Test the crawler with a `seedURL` that points to a valid server but non-existent page.
 
1. Crawl a simple, closed set of cross-linked web pages to crawl.
Ensure that some page(s) are mentioned multiple times within a page, and multiple times across the set of pages.
Ensure there is a loop (a cycle in the graph of pages).
In such a little site, you know exactly what set of pages should be crawled, at what depths, and you know where your program might trip up.
 
2. Point the crawler at a page in that site, and explore at depths 0, 1, 2, 3, 4, 5.
Verify that the files created match expectations.
 
2. Repeat with a different seed page in that same site.
If the site is indeed a graph, with cycles, there should be several interesting starting points.
 
3. Point the crawler at our Wikipedia playground.
Explore at depths 0, 1, 2.
(It takes a long time to run at depth 2 or higher!) Verify that the files created match expectations.
 
5. When you are confident that your crawler runs well, test it on a part of our playground or with a greater depth - but be ready to kill it if it seems to be running amok.
