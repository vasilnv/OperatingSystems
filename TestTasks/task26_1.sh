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

names=$(cat "${file}" | cut -d: -f1 | cut -d ' ' -f1,2 | sort | uniq)

dict="${dir}dict.txt"
touch "${dict}"

cnt=1
while read line
do
	echo "${line};${cnt}" >> ${dict}

	touch "${dir}${cnt}.txt"
	cat "${file}" | grep "^${line}" >> "${dir}${cnt}.txt"
	
	cnt=$(expr $cnt "+" 1)
done < <(echo "${names}")

