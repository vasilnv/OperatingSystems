#!/bin/bash
if [ $# -ne 1 ] 
then
	echo wrong number pf parameters
fi

input=$1
nums=$(cat "${input}" | egrep "^[-0-9]+$" | sort | uniq)
anums=$(echo "${nums}" | tr -d '-' | uniq)
max=0

while read num
do
	if [ "${num}" -gt "${max}" ]
	then
		max=${num}
	fi
done< <(echo "${anums}")
res=$(echo "${nums}" | grep "${max}")
echo "${res}"
