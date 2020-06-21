#!/bin/bash

checkRecursive="do not delete"
echo "${BACKUP_DIR}"
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
		xz "$i" > "${BACKUP_DIR}/${name}_${time}"
		rm "$i".xz
	elif [ -d "$i" ] 
	then
		numOfFiles=$(ls -l "$i"| wc -l)
		time=$(date +"%Y-%m-%d-%H-%M-%S")
		if [ $numOfFiles -eq 1 ] 
		then
			tar -cvf "${BACKUP_DIR}/${name}_${time}.tar" "$i"
			xz "${BACKUP_DIR}/${name}_${time}.tar"
			rmdir "$i" 
		else
			tar -cvf "${BACKUP_DIR}/${name}_${time}.tar" "$i"
			xz "${BACKUP_DIR}/${name}_${time}.tar"
			if [ "$checkRecursive" == "delete" ] 
			then
				rm -r "$i"
			fi
		fi
	else
		echo mistake
	fi
done
