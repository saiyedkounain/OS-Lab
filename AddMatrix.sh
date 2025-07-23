#!/bin/bash

declare -A X
declare -A Y
declare -A Z

echo "Enter 3X3 matrix 1: "

for ((i=0;i<3;i++))
do
    for ((j=0;j<3;j++))
    do 
        read X[$i,$j]
    done
done

echo "Enter 3X3 matrix 2: "

for ((i=0;i<3;i++))
do
    for ((j=0;j<3;j++))
    do 
        read Y[$i,$j]
    done
done

echo "Your first matrix is: "
for ((i=0;i<3;i++))
do
    for ((j=0;j<3;j++))
    do 
        echo "${X[$i,$j]}"
    done
done

echo "Your second matrix is: "
for ((i=0;i<3;i++))
do
    for ((j=0;j<3;j++))
    do 
        echo "${X[$i,$j]}"
    done
done

echo "Your resultant matrix is: "
for ((i=0;i<3;i++))
do
    for ((j=0;j<3;j++))
    do
        Z[$i,$j]=$((X[$i,$j] + Y[$i,$j]))
        echo "${Z[$i,$j]}"
    
    done

done