#!/bin/bash

read -p "enter your string: " string

for i in "$@" 
do
	timesStringWasMet=$(cat "$i" | grep "$string" | wc -l )
	echo "string was met "$timesStringWasMet" times in file"
done
