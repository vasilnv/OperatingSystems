#!/bin/bash
if [ $# -ne 2 ]
then
	echo wrong number of parameters
	exit 1
fi

if [ ! -f $1 ] || [ ! -r $1 ]
then
	echo first parameter should be readable file
fi

input=$1
dst=$2

touch b.csv
allInfo=$(cat ${input} | cut -d, -f2- | sort | uniq)

while read line
do
	cat "${input}" | grep "${line}" | sort -n -t, -k1 | head -n 1 >> "${dst}"
done < <(echo "${allInfo}")