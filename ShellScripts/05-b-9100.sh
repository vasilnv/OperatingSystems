#!/bin/bash
SOURCE=$1
DESTINATION=$2

files=$(find "$SOURCE" -type f -printf "%f \n")

echo "$files"
while read file
do
	
	dest="$DESTINATION""/""$(echo $file | cut -d '.' -f2)"
	echo "$dest"
	echo "$file"	
	if [ ! -d "$dest" ]
	then 
		mkdir "$dest"
	fi
	cp ""$SOURCE""/""$file"" "$dest"
done<<<$(echo "$files")
