#!/bin/bash
directories=$(echo $PATH | tr -s ':' '\n')

result=0
while read line
do
	numberOfFiles=$(find "$line" -type f -executable | wc -l)
	result=$((result+$numberOfFiles ))
done<<<$(echo "$directories")
echo $result
