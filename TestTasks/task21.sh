#!/bin/bash

users=$(ps -e -o user -o uid -o pid -o rss --no-header |tr -s "  " " " | sort -k1 | cut -d ' ' -f1 | uniq)
while read line
do
	echo "$line's rss is"
	ps -e -o user -o rss --no-header | grep ^$line | tr -s "  " " " | awk -F ' ' '{cnt+=$2} END {print cnt}'
	averages=$(ps -e -o user -o rss --no-header | grep ^$line | tr -s "  " " " | awk -F ' ' '{processCount+=1;cnt+=$2} END {printf "%d ", cnt/processCount}')
	userAverages+=$(echo $line $averages:)


done < <(echo "$users")

mapUsersAverages=$(echo "$userAverages" | tr -s ':' '\n') 
echo "$mapUsersAverages"
while read line
do
	user=$(echo $line | cut -d ' ' -f1)
	userRss=$(echo $line | cut -d ' ' -f2)
	processRss=$(ps -e -o user -o uid -o pid -o rss | grep ^$user | tr -s "  " " ")
	while read process
	do
		currProcessRss=$(echo $process | cut -d ' ' -f4)
		checkProcess=$((2*userRss))
		if [ $currProcessRss -gt $checkProcess ] 
		then
			echo gonna kill $process
		fi
	done < <(echo "$processRss")

done < <(echo "$mapUsersAverages")

