#!/bin/bash
if [ $# -ne 2 ]
then
	echo "wrong number of parameters"
	exit 1
fi

file=$1
dir=$2

if [ ! -f "${file}" ] || [ ! -r "${file}" ]
then
	echo "first parameter should be a readable file"
	exit 1
fi

if [ ! -d "${dir}" ] || [ ! -r "${file}" ]
then
	echo "second parameter should be a readable directory"
	exit 1
fi

dirok=$(find "${dir}" -type f | wc -l)
if [ ${dirok} -ne 0 ]
then
	echo "dir should be empty"
	exit 1
fi

dict="${dir}"dict.txt
touch "${dict}"

redact=$(cat "${file}" | cut -d ' ' -f 1,2 | cut -d: -f1 | sort | uniq)

count=1
while read line
do
	echo "${line}"';'"${count}" >>"${dict}"
	count=$(expr ${count} "+" 1)
done < <(echo "${redact}")


cat "$dict"
while read line
do
	num=$(echo "${line}" | cut -d ';' -f2)
	touch "${dir}""${num}"".txt"
	name=$(echo "${line}" | cut -d ';' -f1)
	cat "${file}" | grep "${name}" >> "${dir}""${num}"".txt"
done < <(cat "${dict}")

