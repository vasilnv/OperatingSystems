#!/bin/bash
if [ $# -gt 2 ] && [ $# -eq 1 ]
then
	echo wrong number of parameters
fi

if [ ! -d $1 ]
then 
	echo first argument should be axisting dir
	exit 1
fi

if [ ! -r $1 ]
then
	echo dir should be readable
	exit 1
fi

dir=$1

if [ $# -eq 2 ]
then
	if [[ "$2" =~ ^[0-9]+$ ]]
	then
		slinks=$2
		all=$(find ${dir} -type f -printf "%p %n\n")
		
		while read line
		do
			numlink=$(echo ${line} | rev | cut -d' ' -f1 | rev)
			if [ ${numlink} -ge ${slinks} ]
			then
				echo "${line}" | cut -d ' ' -f1
			fi
		done < <(echo "${all}")
	fi	
else
	echo i am here
	find ${dir} -type l -printf "%Y %p\n" | grep ^N 
fi
