#!/bin/bash
user="$1"
while true 
do
	sleep 1
	check=$(who |tr -s "  " " "| grep "$user")
	if [ -n "$check" ] 
	then
		echo "in"
		exit 0
	fi
done
