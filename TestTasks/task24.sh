#!/bin/bash

if [ $(id -u) -ne 1000 ]
then
	echo script should be executed by grade
fi

rss=$(ps -eo user -o rss | grep ^root | tr -s " "  | awk -F ' ' '{total+=$2} END {print total}')

users=$(cat /etc/passwd | cut -d ':' -f1,6)

while read line
do
	user=$(echo $line | cut -d ':' -f1)
	dir=$(echo $line | cut -d ':' -f2)

	if [ ! -d $dir ] || [ "$(stat -c "%U" $dir)" != "$user" ] || [ "$(stat -c "%A" $dir | cut -c3)" != "w" ]
	then
		user_rss=$(ps -eo euser -o rss | grep ^${user} | tr -s "  " " " | awk -F ' ' 'BEGIN {total=0} {total+=$2} END {print total}')
	else
		continue
	fi

	if [ $user_rss -gt $rss ]
	then 
		echo killall -u "${user}" -KILL
	fi

done < <(echo "$users")
