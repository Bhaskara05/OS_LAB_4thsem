#!/bin/bash
# Program to generate prime numbers in a given range

echo -n "Enter the lower bound: "
read n1
echo -n "Enter the upper bound: "
read n2

echo "Prime numbers between $n1 and $n2 are:"

for ((i=n1; i<=n2; i++))
do
    if (( i < 2 )); then
        continue
    fi

    flag=0
    for ((j=2; j<=i/2; j++))
    do
        if (( i % j == 0 )); then
            flag=1
            break
        fi
    done

    if (( flag == 0 )); then
        echo -n "$i "
    fi
done

echo
