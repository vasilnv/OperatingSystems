#!/bin/bash
unknownNumber=$((RANDOM % 100))
tries=0
echo "$unknownNumber"
while true 
do
	read -p "enter your number: " number
	tries=$((tries + 1))
	if [ "$number" -eq "$unknownNumber" ]
	then 
		echo Congratulations! you managed to find the number with "$tries" tries
	exit 0
	fi
	if [ "$number" -gt "$unknownNumber" ]
	then
		echo down
	else
		echo up
	fi
done
