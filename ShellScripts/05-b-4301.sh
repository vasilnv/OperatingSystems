#!/bin/bash
file=$1
nameToGrep=$2
pseudonim=$3
if [ $# -ne 3 ] ; then
	echo not enough params
	exit 1
fi
username=$(cat /etc/passwd | grep $nameToGrep | cut -d ":" -f1)

if [ "$username" == "" ] ; then 
	echo username not found
	exit 1
fi

check=$(cat $file | grep $username)
if [ "$check" == "" ] ; then
	record="${username} ${pseudonim}"
	else 
	num=$(cat $file | grep $username | wc -l)
	record="${username} ${pseudonim} ${num}"
fi
echo $record>> $file
echo $record
exit 0
