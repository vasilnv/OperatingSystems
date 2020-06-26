#!/bin/bash
if [ $(id -u) -ne 1000 ]
then 
	echo should be executed by grade
fi

users=$(ps -e -o euser --no-headers | sort | uniq)
while read line
do
	rssall=$(ps -e -o euser -o rss --no-headers | grep ^${line} | tr -s " " | awk -F ' ' 'BEGIN {all=0} {all+=$2} END {print all}')
	count=$(ps -e -o euser -o rss --no-headers | grep ^${line} | wc -l)
	
	echo "${line} has ${count} processes and rss: ${rssall}"
done < <(echo "${users}")

while read line
do
    rssall=$(ps -e -o euser -o rss --no-headers | grep ^${line} | tr -s " " | awk -F ' ' 'BEGIN {all=0} {all+=$2} END {print all}')
    count=$(ps -e -o euser -o rss --no-headers | grep ^${line} | wc -l)

	if [ ${count} -eq 0 ]
	then 
		continue
	fi

	avg=$(expr 2 "*" ${rssall} "/" ${count})
	
	maxrss=$(ps -e -o user -o rss | grep ^${line} | tr -s " " | sort -n -t' ' -k2 | tail -n 1 | cut -d ' ' -f2)

	pid=$(ps -e -o user -o pid -o rss | grep ^${line} | tr -s " " | sort -n -t' ' -k3 | tail -n 1 | cut -d ' ' -f2)
	
	if [ ${maxrss} -gt ${avg} ]
	then
		echo kill -KILL ${pid}
	fi
done < <(echo "${users}")
