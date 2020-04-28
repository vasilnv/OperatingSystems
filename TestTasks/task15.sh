#!/bin/bash
if [ $# -ne 0 ]
then
	echo "No parameters needed" 
fi

if [ $EUID -ne 0 ]
then 
	echo "This script should be executed by root"
	exit 1
fi

#no home dirs
cat /etc/passwd | grep -v /home

#home directories that don't exist
usersWithHomeDirs=$(cat /etc/passwd | grep /home)
while read line
do
	user=$(echo "$line" | tr -s "  " " " | cut -d ':' -f 1,7)
	currentDir=$(echo "$user" | cut -d ':' -f2)
	if [ ! -d currentDir ] 
	then
		echo "$line"
	fi
done < <(echo "$usersWithHomeDirs")
