#!/bin/bash

if [ $# -ne 3 ]
then
	echo "wrong number of parameters"
fi

sourceFile=$1
destination=$2
stringComparator=$3

filesFound=$(find $SRC -type f | grep $stringComparator)
while read line
do
	cp $line $destination
done < <(echo $filesFound)

