#!/bin/bash
filesWithInode=$(find . -type f -inum $(find . -type f -printf "%As %p %i\n" | sort -nr | head -n +1 | awk -F " " '{printf $3}'))
allCounts=''
while read line
do
	counterOfDepth=$(echo $line | sed -r 's/(.)/\1\n/g' | uniq -c | grep / | wc -l)
	allCounts=$(echo $allCounts $counterOfDepth) 	
done< <(echo "$filesWithInode")
echo "$allCounts" | sed -s 's/ /\n/g' | sort -n | head -n 1

