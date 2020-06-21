#!/bin/bash
if [ $# -ne 2 ]
then
	echo "wrong number of parameters"
fi
file=$1
dir=$2
if [ ! -f "${file}" ]
then
	echo "first parameter should be file"
fi

if [ ! -d "${dir}" ]
then
	echo "second parameter should be directory"
fi

dict="${dir}"dict.txt
touch "${dict}"

redact=$(cat "${file}" | cut -d ' ' -f 1,2 | cut -d : -f1  | sort | uniq)
echo "$redact"
count=1
while read line
do
	echo "${line}"';'"${count}" >>"${dict}"
	count=$((count+1))
done < <(echo "${redact}")


cat "$dict"
while read line
do
	num=$(echo "${line}" | cut -d ';' -f2)
	touch "${dir}""${num}"".txt"
	name=$(echo "${line}" | cut -d ';' -f1)
	cat "${file}" | grep "${name}" >> "${dir}""${num}"".txt"
done < <(cat "${dict}")
