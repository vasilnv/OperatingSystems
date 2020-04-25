#!/bin/bash
file=$1
lines=$(cat "$file" | grep -v [a-w] | grep [02468] | wc -l)
echo "Number of lines is $lines" 
