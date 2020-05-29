#Bash script for testing 

##### THESE TESTS SHOULD FAIL ######


# No arguments given to ./sudoku

./sudoku

# incorrect argument given to ./sudoku

./sudoku NotAnArgument

##### THESE TESTS SHOULD WORK ######

# Unit test the puzzle module 

./puzzletest

# Create a puzzle

./sudoku create 

#Pipeline puzzle to solve

cat board | ./sudoku solve











