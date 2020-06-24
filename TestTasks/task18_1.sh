#!/bin/bash
homedirs=$(cat /etc/passwd | cut -d: -f6 | grep /home/)
max=0
bestAcc=""
while read line
do
	if [ ! -d "${line}" ]
	then
		echo "${line} doesnt exists"
		continue
	fi
	
	if [ ! -r "${line}" ]
	then
		echo "${line} is not readable"
		continue
	fi

	currBest=$(find "${line}" -type f -printf "%p %Ts\n" 2>/dev/null | sort -n -t ' ' -k2 | tail -n 1)
	if [ -z "${currBest}" ]
	then
		continue
	fi

	currTime=$(echo "${currBest}" | cut -d ' ' -f2)

	echo ${currBest}
	echo ${currTime}
	echo ${max}	
	if [ ${currTime} -gt ${max} ]
	then
		max=${currTime}
		bestAcc=${currBest}
	fi
done < <(echo "${homedirs}")
echo ${bestAcc}

