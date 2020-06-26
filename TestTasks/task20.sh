#!/bin/bash
if [ ! -d $1 ]
then
	echo first argument should be dir
fi

if [ ! -d $2 ]
then 	
	echo second argment should be dir
fi

if [ $# -ne 3 ]
then
	echo wrong number of parameters
fi

SRC=$1
DST=$2
STR=$3

dstCheck=$(find ${DST} -type f | wc -l)
if [ ${dstCheck} -ne 0 ]
then
	echo destination dir should be empty
fi

all=$(find ${SRC} -type f -printf "%p\n" | egrep "${STR}[^/]*$")

while read line
do
	extr=$(echo ${line} | cut -d/ -f2)
	echo ${extr}
	dirs=$(dirname ${extr})
	echo $dirs
	if [ "${dirs}" != '.' ]
	then
		mkdir -p ${dirs}
	fi
	
	mv ${SRC}/${extr} ${DST}/${extr}
done < <(echo "${all}")
