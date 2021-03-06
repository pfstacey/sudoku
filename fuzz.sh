# Title: fuzz.sh
# Date: 6/1/2020
# Description: sudoku fuzz testing

#!/bin/bash
 
if [ "$@" -ne "$@" ]
then
    echo 'Run with command: ./fuzz.sh number'
else
    make clean
    make all
    rm -f board
    echo 'Generating ' $i ' random boards:'
    for (( i=1; i<=$@; i++ ))
    do 
        sleep 1
        ./sudoku create > hold
        echo 'Puzzle' $i ' original:'
        cat hold
        echo $'\n'
        cat hold | tee -a board >/dev/null
        rm hold
    done
    echo $'Solving...\n'
    cat board | ./sudoku solve
    rm -f board hold
fi