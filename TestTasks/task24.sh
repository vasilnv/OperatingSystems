#!/bin/bash

rss=$(ps -eo euser -o rss | grep ^root | tr -s "  " " "  | awk -F ' ' '{total+=$2} END {print total}')

users=$(cat /etc/passwd | cut -d ':' -f1,6)

while read line
do
	user=$(echo $line | cut -d ':' -f1)
	echo this is my user: $user
	dir=$(echo $line | cut -d ':' -f2)

	if [ ! -d $dir ]
	then
		user_rss=$(ps -eo euser -o rss | grep ^${user} | tr -s "  " " " | awk -F ' ' 'BEGIN {total=0} {total+=$2} END {print total}')
	elif [ "$(stat -c "%U" $dir)" != "$user" ]
	then
		user_rss=$(ps -eo euser -o rss | grep ^${user} | tr -s "  " " " | awk -F ' ' 'BEGIN {total=0} {total+=$2} END {print total}')
	elif [ "$(stat -c "%A" $dir | cut -c3)" != "w" ] 
	then
		 user_rss=$(ps -eo euser -o rss | grep ^${user} | tr -s "  " " " | awk -F ' ' 'BEGIN {total=0} {total+=$2} END {print total}')
	else
		echo i continue
		continue
	fi
	echo this is userRss: $user_rss
	echo this is totalRss: $rss
	if [ $user_rss -gt $rss ]
	then 
		echo kill by user
	fi

done < <(echo "$users")

