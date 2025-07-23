#!/bin/bash

read -p "Enter n:" n

declare -A arr
echo "Enter array elements:"
for ((i=0;i<n;i++))
do
    read arr["$i"]
done

max=${arr[0]}

for ((i=1;i<n;i++))
do 
    if [[ $max < ${arr[$i]} ]]
    then
        max=${arr[$i]}
    fi
done

echo "Max is $max"