#!/bin/bash
pattern="hi"
filename="hi.txt"
filename2="hi2.txt"
filename3="regexes.txt"

flags=(
    ""
    "-e" 
    "-i" 
    "-v"
    "-c"
    "-l"
    "-n"
    "-s"
    "-o"
    "-h"
    "-in"
    "-nv"
    "-cv"
    "-iv"
    "-hv"
)
flags_mul_files=(
    ""
    "-v"
    "-l"
    "-h"
    "-lv"
    "-ho"
)

make
n=0
successes=0
# tests for one file
for flags_comb in "${flags[@]}"
    do
        n=$[ $n + 1]
    echo "\nTEST № $n ---------"
    echo "grep $flags_comb $pattern $filename"
    ./s21_grep $flags_comb "$pattern" "$filename">my_result.txt
    # echo "\n\nTEST № $n \n---------\n"
    grep $flags_comb "$pattern" "$filename">real_result.txt

    if diff my_result.txt real_result.txt
    then 
        echo SUCCESS
        successes=$[ $successes + 1]
    else 
        echo FAIL
    fi 
done

# tests for multiple files
for flags_comb in "${flags_mul_files[@]}"
    do
        n=$[ $n + 1]
    echo "\nTEST № $n ---------"
    echo "grep $flags_comb $pattern $filename $filename2"
    ./s21_grep $flags_comb "$pattern" "$filename" "$filename2">my_result.txt
    # echo "\n\nTEST № $n \n---------\n"
    grep $flags_comb "$pattern" "$filename" "$filename2">real_result.txt

    if diff my_result.txt real_result.txt
    then 
        echo SUCCESS
        successes=$[ $successes + 1]
    else 
        echo FAIL
    fi 
done

# tests for -f flag
 n=$[ $n + 1]
echo "\nTEST № $n ---------"

echo "grep -f  $filename"
./s21_grep -f "$filename3" "$filename">my_result.txt
# echo "\n\nTEST № $n \n---------\n"
grep -f "$filename3" "$filename">real_result.txt

if diff my_result.txt real_result.txt
then 
    echo SUCCESS
    successes=$[ $successes + 1]
else 
    echo FAIL
fi 

n=$[ $n + 1]
echo "\nTEST № $n ---------"
echo "grep -inf  $filename"
./s21_grep -inf "$filename3" "$filename">my_result.txt
# echo "\n\nTEST № $n \n---------\n"
grep -inf "$filename3" "$filename">real_result.txt

if diff my_result.txt real_result.txt
then 
    echo SUCCESS
    successes=$[ $successes + 1]
else 
    echo FAIL
fi 

if [ "$n" -eq "$successes" ]
then 
    echo "\n\n ALL SUCCESSES"
else
    fails=$[ $n - $successes]
    echo "\n\n $fails FAILS"
fi