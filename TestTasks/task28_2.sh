#!/bin/bash
if [ $# -ne 1 ]
then
	echo wrong number of parameters
fi
input=$1

nums=$(cat ${input} | egrep "^[-0-9]+$" | sort | uniq)
anums=$(echo "${nums}" | tr -d '-')

max=0
maxnum=$(echo "${anums}" | head -n 1)
while read num
do
	digits=$(echo ${num} | egrep -o .)
	count=0
	while read dig
	do
		count=$((count+$dig))
	done < <(echo "${digits}")
	
	if [ ${count} -gt ${max} ]
	then
		max=${count}
		maxnum=${num}
	elif [ ${count} -eq ${max} ]
	then
		realnum=$(echo "$nums" | grep ${num} | sort -n | head -n 1)
		realmax=$(echo "$nums" | grep ${maxnum} | sort -n | head -n 1)
		if [ ${realnum} -lt ${realmax} ]
		then
			maxnum=${num}
		fi	
	fi
done < <(echo "${anums}")
res=$(echo "${nums}" | grep "${maxnum}" | sort -n | head -n 1)
echo "${res}"
