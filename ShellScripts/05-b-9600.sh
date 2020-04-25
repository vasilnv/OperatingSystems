#!/bin/bash

checkRecursive="do not delete"

for i in "$@" 
do
	if [ "$i" == '-r' ]
	then 
		checkRecursive="delete"
		continue
	fi
	name=$(echo $i | rev | cut -d '/' -f1 | rev)
	if [ -f "$i" ] 
	then
		time=$(date +"%Y-%m-%d-%H-%M-%S")
		gzip -f "$i" > "${BACKUP_DIR}/${name}_${time}.gz"
	elif [ -d "$i" ] 
	then
		numOfFiles=$(ls -l "$i"| wc -l)
		time=$(date +"%Y-%m-%d-%H-%M-%S")
		if [ $numOfFiles -eq 1 ] 
		then
			tar -czf "${BACKUP_DIR}/${name}_${time}.tgz" "$i"
			rmdir "$i" 
		else
			tar -czf "${BACKUP_DIR}/${name}_${time}.tgz" "$i"
			if [ "$checkRecursive" == "delete" ] 
			then
				rm -r "$i"
			fi
		fi
	else
		echo mistake
	fi
done
