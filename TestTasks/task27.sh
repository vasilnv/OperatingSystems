#!/bin/bash
if [ $# -ne 1 ]
then
	echo wrong number of parameters
fi

input=$1
touch b.csv
allInfo=$(cat ${input} | cut -d, -f2-)
while read line
do
	info=$(echo "${line}" | cut -d, -f2-)
	numOfLines=$(echo "${allInfo}" | grep "^${info}$" | wc -l)
	if [ ${numOfLines} -eq 1 ]
	then
		echo "${line}" >> b.csv
	elif [ ${numOfLines} -gt 1 ]
	then
		isin=$(cat b.csv | grep "${info}" | wc -l)
		if [ "${isin}" -eq 0 ]
		then
			echo i am here
			cat "${input}" | grep "${info}" | sort -n -t, -k1 | head -n 1 >> b.csv
		fi
	fi 
done < <(cat "${input}")