#!/bin/bash
file=$1

allnums=$(cat "${file}" | egrep "^[-0-9]+$")
nums=$(echo "${allnums}" | tr -d '-' | sort | uniq)

max=0

while read num
do
	if [ ${num} -gt ${max} ]
	then
		max=${num}
	fi
done < <(echo "${nums}")

echo maxnums are: $(cat "${file}" | grep ${max} | sort | uniq)

minnum=$(echo "${nums}" | tail -n 1)

maxsum=0

while read line 
do
	digits=$(echo "${line}" | grep -o .)
	sum=0	
	while read digit 
	do
		sum=$(expr ${sum} "+" ${digit})
	done < <(echo "${digits}")

	if [ ${sum} -gt ${maxsum} ]
	then
		maxsum=${sum}
		minnum=$(echo "${allnums}" | grep "${line}" | sort -n | head -n 1)
	fi

	if [ ${sum} -eq ${maxsum} ]
	then 
		currnum=$(echo "${allnums}" | grep "${line}" | sort -n | head -n 1)
		if [ ${minnum} -gt ${currnum} ]
		then 
			minnum=${currnum}
		fi
	fi
done < <(echo "${nums}")

echo minnum is ${minnum}
