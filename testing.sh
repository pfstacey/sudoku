#Bash script for testing 

##### THESE TESTS SHOULD FAIL ######
echo $'\n~~~~~~~~~~~~~~~~~~~~~~'
echo $'Error Testing...'

# No arguments given to ./sudoku
echo $'\nNo Arguments:'
./sudoku

# incorrect argument given to ./sudoku
echo $'\nIncorrect Argument:'
./sudoku NotAnArgument

# multiple arguments given to ./sudoku
echo $'\nMultiple Arguments:'
./sudoku create solve

##### THESE TESTS SHOULD WORK ######

# Create a puzzle
echo $'\n~~~~~~~~~~~~~~~~~~~~~~'
echo $'Functionality Testing...'
./sudoku create > board
echo $'\nOriginal Puzzle:'
cat board

#Pipeline puzzle to solve
echo $'\nSolved Puzzle:'
cat board | ./sudoku solve > solved
cat solved

