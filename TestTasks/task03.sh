#!/bin/bash

mkdir a
mkdir b
mkdir c

num1=$1
num2=$2

files=$(find . -type f -exec wc -l {} \;)

while read line
do
	numl=$(echo $line | cut -d ' ' -f 1)
	echo $numl;
	filename=$(echo $line | cut -d ' ' -f 2)
	if [ $numl -lt $num1 ]
	then
		cp $filename a
	elif [ $numl -gt $num1 ] && [ $numl -lt $num2 ]
	then
		cp $filename b
	else
		cp $filename c
	fi

done < <(echo "$files")