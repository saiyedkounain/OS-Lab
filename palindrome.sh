#!/bin/bash

echo "Enter palindrome"
read num

og=$num
rev=0

while [ $num -gt 0 ]
do
    rem=$(( num % 10 ))
    rev=$(( rev * 10 + rem ))
    num=$(( num / 10 ))
done

if [ $rev -eq $og ]
then
    echo "$og is a Palindrome"
else
    echo "$og isnt a Palindrome"
fi
