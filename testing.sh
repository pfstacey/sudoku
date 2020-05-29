#Bash script for testing 

##### THESE TESTS SHOULD FAIL ######


# No arguments given to ./sudoku

./sudoku

# incorrect argument given to ./sudoku

./sudoku NotAnArgument

##### THESE TESTS SHOULD WORK ######

# Create a puzzle

./sudoku create 

#Pipeline puzzle to solve

cat board | ./sudoku solve











