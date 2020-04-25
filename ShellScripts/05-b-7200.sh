#!/bin/bash
#05-b-7200
file=$1
if [ -f "$file" ] 
then
	echo this is readable file
	exit 0
fi

if [ -d "$file" ]
then
	echo this is directory
	otherFiles=$(find "$file" -type f -printf "%f %s\n")
	echo "$otherFiles" | while read i
	do
		name=$(echo "$i" | cut -d ' ' -f1)
		size=$(echo "$i" | cut -d ' ' -f2)
		numOfFiles=$(ls -l "$file" | wc -l) 
		if [ "$size" -lt "$numOfFiles" ]
		then 
			echo "$name"
		fi
	done
fi
