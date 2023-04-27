#!/bin/bash
filename="hi.txt"
filename2="hi2.txt"

flags=(
    ""
    "-b" 
    "-e"
    "-n"
    "-s"
    "-t"
    "-be"
    "-bn"
    "-b -s"
    "-n -s"
)
make
n=0
successes=0
# tests for one file
for flags_comb in "${flags[@]}"
    do
        n=$[ $n + 1]
    echo "\nTEST № $n ---------"
    echo "cat $flags_comb $filename"
    ./s21_cat $flags_comb "$filename">my_result.txt
    # echo "\n\nTEST № $n \n---------\n"
    cat $flags_comb "$filename">real_result.txt

    if diff my_result.txt real_result.txt
    then 
        echo SUCCESS
        successes=$[ $successes + 1]
    else 
        echo FAIL
    fi 


    # tests for multiple files
    n=$[ $n + 1]
    echo "\nTEST № $n ---------"
    echo "cat $flags_comb $filename $filename2"
    ./s21_cat $flags_comb "$filename" $filename2>my_result.txt
    # echo "\n\nTEST № $n \n---------\n"
    cat $flags_comb "$filename" $filename2>real_result.txt

    if diff my_result.txt real_result.txt
    then 
        echo SUCCESS
        successes=$[ $successes + 1]
    else 
        echo FAIL
    fi 

done


if [ "$n" -eq "$successes" ]
then 
    echo "\n\n ALL SUCCESSES"
else
    fails=$[ $n - $successes]
    echo "\n\n $fails FAILS"
fi