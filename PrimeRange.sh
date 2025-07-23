#!/bin/bash

read -p "Lower bound" n1
read -p "Upper bound" n2

for ((i=n1;i<n2;i++))
do
    flag=0
    for ((j=2;j<$i/2;j++))
    do
        if [[ $((i%j)) == 0 ]] then
            flag=1 
        fi
    done
    
    if [[ $flag == 0 ]] then
        echo -ne "$i "
    fi

done