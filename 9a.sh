#!/bin/bash
# Program to check if a given string/number is palindrome

echo -n "Enter the string or number to be checked: "
read str

length=${#str}
reverse=""

# Reverse the string
for (( i=length-1; i>=0; i-- ))
do
    reverse="$reverse${str:$i:1}"
done

# Compare original and reversed
if [[ "$reverse" == "$str" ]]; then
    echo " The /number \"$str\" is a palindrome"
else
    echo "The number \"$str\" is not a palindrome"
fi
