#!/bin/bash
if [ $# -ne 1 ]
then
	echo "Invalid number of arguments"
	exit 1
fi

if [ ! -d $1 ]
then
	echo "You should add a directory as parameter"
	exit 1
fi

directory=$1

files=$(ls -lR /home | grep ^l | tr -s "  " " " | cut -d " " -f 9,11)
while read line
do
	symLinkFile=$(echo "$line" | cut -d " " -f2)
	if [ -f "$symLinkFile" ]
	then
		echo $directory/$(echo "$line" | cut -d " " -f1)
	fi
done < <(echo "$files")
