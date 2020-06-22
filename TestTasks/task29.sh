#!/bin/bash
if [ $# -lt 1 ]
then
	echo at least 1 argument expected
fi

N=10

if [ $1 = "-n" ]
then
	N=$2
fi

for i in "$@"
do
	if [ $i = "-n" ]
	then
		continue
	fi
	
	if [[ "$i" =~ ^[0-9]+$ ]]
	then
		continue
	fi

	idf=$(echo "$i" | cut -d. -f1)
	lines=$(cat $i | tail -n ${N})

	while read line
	do	
		timest=$(echo "${line}" | cut -d ' ' -f1,2)
		data=$(echo "${line}" | cut -d ' ' -f3-)
		echo "${timest} ${idf} ${data}"
	done < <(echo "$lines") 
done 
