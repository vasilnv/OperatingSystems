#!/bin/bash
if [ $# -lt 1 ] || [ $# -gt 2 ]
then
	echo wrong number of parameters
fi

if [ ! -d $1 ] || [ ! -r $1 ]
then 
	echo argument 1 should be readable dir
fi
dir=$1

if [ $# -eq 1 ]
then
	ok=$(find ${dir} -type l -printf "%Y %p\n" | grep ^f | cut -d ' ' -f2)

	while read line
	do
		dst=$(ls -l $(dirname ${line}) | grep $(basename ${line}) | rev | cut -d " " -f1 | rev)
	
		echo "${line} -> ${dst}"
	done< <(echo "${ok}")

	br=$(find ${dir} -type l -printf "%Y %p\n" | grep ^N | wc -l)
	
	echo broken symlinks: ${br}
else
	file=$2

	ok=$(find ${dir} -type l -printf "%Y %p\n" | grep ^f | cut -d ' ' -f2)

    while read line
    do
        dst=$(ls -l $(dirname ${line}) | grep $(basename ${line}) | rev | cut -d " " -f1 | rev)
    
        echo "${line} -> ${dst}" >> ${file}
    done< <(echo "${ok}")

    br=$(find ${dir} -type l -printf "%Y %p\n" | grep ^N | wc -l)
    
    echo broken symlinks: ${br} >> ${file}
fi
