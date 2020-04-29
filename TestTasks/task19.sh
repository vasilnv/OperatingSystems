#!/bin/bash

if [ $# -eq 2 ] 
then
	dir=$1
	checkNum=$2
	files=$(find $dir -type f -printf "%p %n\n")
	while read line
	do
		fileHardLinks=$(echo "$line" | cut -d ' ' -f2)
		if [ $fileHardLinks -ge $checkNum ]
		then
			echo $line | cut -d ' ' -f1
		fi
	done < <(echo "$files")
elif [ $# -eq 1 ]
then
	dir=$1
	fileSymLinks=$(ls -l | grep ^l | tr -s "  " " " | cut -d ' ' -f9-)
	dirInSymLink=$(echo "$fileSymLinks" | cut -d '>' -f2 | sed 's/ //')
	
	echo $dirInSymLink
	if [ -d $dirInSymLink ]
	then 
		echo broken link
	fi
else
	echo wrong number of parameters
fi
