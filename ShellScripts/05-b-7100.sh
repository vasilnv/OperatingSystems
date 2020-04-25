#!/bin/bash
dir=$1
number=$2

files=$(find "$dir" -type f -printf "%f %s\n")
echo "$files"
echo "$files" | while read i
do
	name=$(echo "$i" | cut -d ' ' -f1)
	num=$(echo "$i" | cut -d ' ' -f2)
	if [ "$num"  -gt "$number" ]
	then
		echo $name
	fi
done
