#!/bin/bash
# Program to read two 3x3 matrices and find their sum

declare -A X
declare -A Y
declare -A Z

# Read first matrix
echo "Enter the elements of the first 3x3 matrix:"
for ((i=0; i<3; i++))
do
    for ((j=0; j<3; j++))
    do
        read X[$i,$j]
    done
done

# Read second matrix
echo "Enter the elements of the second 3x3 matrix:"
for ((i=0; i<3; i++))
do
    for ((j=0; j<3; j++))
    do
        read Y[$i,$j]
    done
done

# Print first matrix
echo "The first matrix is:"
for ((i=0; i<3; i++))
do
    for ((j=0; j<3; j++))
    do
        echo -ne "${X[$i,$j]}\t"
    done
    echo
done

# Print second matrix
echo "The second matrix is:"
for ((i=0; i<3; i++))
do
    for ((j=0; j<3; j++))
    do
        echo -ne "${Y[$i,$j]}\t"
    done
    echo
done

# Calculate and print resultant matrix
echo "The resultant matrix (sum) is:"
for ((i=0; i<3; i++))
do
    for ((j=0; j<3; j++))
    do
        Z[$i,$j]=$(( X[$i,$j] + Y[$i,$j] ))
        echo -ne "${Z[$i,$j]}\t"
    done
    echo
done
