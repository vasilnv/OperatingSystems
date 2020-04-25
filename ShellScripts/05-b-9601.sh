#!/bin/bash
#05-b-9601.sh
destination="."
if [ "$1" == "-l" ]
then
	allNames=$(echo $BACKUP_DIR | ls -l)
	echo "$allNames"
	dir=$2
	if [ $# -eq 3 ] 
	then
		destination=$3
	fi
else
	dir=$1
    if [ $# -eq 2 ] 
    then
        destination=$2
    fi
fi

name=$(ls $BACKUP_DIR | grep "$dir")
echo $name
if [ "$name" == "*.tgz" ]
then
	tar -xvf "${BACKUP_DIR}/${name}" -C $destination
else
	mv "${BACKUP_DIR}/${name}" "$destination"
	echo "${destination}/${name}"
	gzip -d "${destination}/${name}"
fi
