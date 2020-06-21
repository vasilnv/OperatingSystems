#!/bin/bash
if [ $# -ne 1 ]
then
	echo wrong number of parameters
	exit 1
fi

logdir=$1

friends=$(find "${logdir}" -maxdepth 3 -mindepth 3 -type d )
touch map.txt

while read friend
do
	files=$(find "${logdir}" -type f | grep "${friend}")
	count=0
	
	while read file
	do
		new=$(cat "$file" | wc -l)
		count=$((count+$new))
	done < <(echo "${files}")
	echo "${friend}":"${count}">>map.txt
done< <(echo "${friends}")

res=$(cat map.txt | sort -n -t: -k2 -r | head -n 2)
echo "${res}"
