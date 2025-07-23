#!bin/bash

read -p "Enter num 1: " n1
read -p "Enter num 2: " n2
read -p "Enter num 1: " n3

if [[ $n1 -gt $n2 ]]
then
    largest=$n1
else
    largest=$n2
fi

if [[ $n3 -gt $largest ]]
then
    largest=$n3
fi

echo "$largest is largest"