#!/bin/bash
file=$1
str1=$2
str2=$3

row1=$(cat ${file} | egrep "^${str1}=")
row2=$(cat ${file} | egrep "^${str2}=")

if [ -z "${row2}" ]
then
	echo ${row2}
	exit 0
fi

args1=$(echo "${row1}" | cut -d= -f2 | tr " " "\n")
args2=$(echo "${row2}" | cut -d= -f2 | tr " " "\n")

all=$(echo -e "${args1}\n${args2}" | sort | uniq -c | tr -s " " | sed "s/ //" | grep -v ^1 | cut -d ' ' -f2) 

str3=$(echo "${row2}" | cut -d= -f2)

while read arg
do
	echo arg=${arg}
	res=$(echo "${str3}" | tr -d "${arg}")
done < <(echo "${all}")

alines=$(cat ${file})
echo > ${file}
while read line
do
	if [ "${line}" = "${row2}" ]
	then
		echo i am here
		key=$(echo "${str2}" | cut -d= -f1)
		echo "${key}=${res}" >> ${file}
	else
		echo "${line}" >> ${file}
	fi
done < <(echo "${alines}")

