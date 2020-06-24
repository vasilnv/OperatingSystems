#!/bin/bash

processes=$(ps -e -o user, -o pid, -o times --no-headers | sort -k1) 

users=$(echo "${processes}" | cut -d ' ' -f1 | uniq)
user=$1
userProcessCounter=$(echo "${processes}" | grep "${user}" | wc -l)

if [ -z "${userProcessCounter}" ]; then
	userProcessCounter=0
fi


while read line
do
    processCounter=$(echo "$processes" | grep "$line" | wc -l)

    if [ "$processCounter" -gt "$userProcessCounter" ]; then
    	echo "$line"	
    fi
done < <(echo "${users}")

AVERAGE=$(echo "$processes" | tr -s "  " " " |  awk -F ' ' '{t+=$3;cnt++} END {printf "%d", t/cnt}')

echo "$AVERAGE"

userProcesses=$(echo "$processes")
timecheck=$(expr 2 "*" ${AVERAGE})
while read line
do
	currProcessTime=$(echo "$line" | tr -s "  " " " | cut -d ' ' -f3)
	if [ ${currProcessTime} -gt ${AVERAGE} ]
	then
		echo gona kill $line
	fi 

done < <(echo "$userProcesses")