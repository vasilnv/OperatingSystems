#!/bin/bash

processes=$(ps -e -o user, -o pid, -o etimes | sort -k1) 

users=$(echo "${processes}" | cut -d ' ' -f1 | uniq)
user=$1
userProcessCounter=$(echo "${processes}" | grep $user | wc -l)

if [ -z "$userProcessCounter" ]; then
	userProcessCounter=0
fi


echo "$users" | while read line
do
    processCounter=$(echo "$processes" | grep "$line" | wc -l)

    if [ "$processCounter" -gt "$userProcessCounter" ]; then
    	echo "$line"	
    fi
done

AVERAGE=$(echo "$processes" | tr -s "  " " " |  awk -F ' ' '{cnt+=$3} END {printf cnt/2}')

echo "$AVERAGE"

userProcesses=$(echo "$processes" | grep $user)

while read line
do
	currProcessTime=$(echo "$line" | tr -s "  " " " | cut -d ' ' -f3)
	if [ $currProcessTime -gt $AVERAGE ]
	then
		echo gona kill $line
	fi 

done < <(echo "$userProcesses")
