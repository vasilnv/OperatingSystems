#!/bin/bash
file=$1
counter=1
newLines=$(while read line
do
    newLine=$(echo ${line} | cut -d '-' -f2-)
    echo ${counter}. ${newLine} 
    counter=$((counter+1))
done <<< $(cat $file))
sortedLines=$(echo "$newLines" | cut -d ' ' -f2- | sort)
while read line
do
    echo "$newLines" | grep -e "$line"
done <<< $(echo "$sortedLines")
