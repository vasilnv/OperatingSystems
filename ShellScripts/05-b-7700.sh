#!/bin/bash
directory=$1
number=$2

result=1
files=$(find "$directory" -type f -printf "%f %s\n")
while read i
	do
	name=$(echo "$i" | cut -d ' ' -f1)
	size=$(echo "$i" | cut -d ' ' -f2)
	if [ "$size" -gt "$number" ] 
	then
		result="$((result+$size))"
	fi
done <<<$(echo -e "$files")
echo $result
