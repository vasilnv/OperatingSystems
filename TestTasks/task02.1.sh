#!/bin/bash
file=$1
i=1
notSorted=$(cat $file | cut -d '-' -f 2- | sed "s/ //")
new=$(while read line
do 
	echo "$i. $line"
	i=$((i+1))
done <<< $(echo "$notSorted"))
sorted=$(echo "$new" | sort -t. -k2)
echo "$sorted"
