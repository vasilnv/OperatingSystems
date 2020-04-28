#!/bin/bash
if [ $# -ne 1 ]
then
	echo "Invalid number of arguments"
	exit 1
fi

if [ $(whoami) == "root" ] 
then
	processes=$(ps -e -o uid -o pid -o rss --no-header)
fi

counterRss=0

while read line
do
	currentRss=$(echo "$line" | tr -s "  " " " | cut -d ' ' -f3)
	counterRss=$((counterRss+$currentRss))
done < <(echo "$processes")

if [ $counterRss -gt $1 ] 
then
	#next command will print the pid we want to kill
	echo "$processes" | sort -nrk 3 | head -n 1 | tr -s "  " " " | cut -d ' ' -f2
	echo "I can kill this process by making last command as a subcommand and kill before it"	
fi 

