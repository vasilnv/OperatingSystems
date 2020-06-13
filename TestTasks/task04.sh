#!/bin/bash
file1=$1
file2=$2

numOfLines1=$(cat $file1 | wc -l)
numOfLines2=$(cat $file2 | wc -l)

if [ $numOfLines1 -ge $numOfLines2 ]
then
	winner=$file1
else
	winner=$file2
fi

newLines=$(cat $winner | cut -d '.' -f 2- | cut -d '-' -f 2- | sed 's/ //' | sort)
resFileName=$(echo "${winner}.songs")
touch ${resFileName}
echo "$newLines" > ${resFileName} 
