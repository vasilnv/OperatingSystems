#!/bin/bash
dir=$1
if [ $# -eq 2 ]
then
	cpDir=$2
elif [ $# -eq 1 ]
then
	cpDir=$(date)
else
	echo wrong number of parameters
fi
mkdir "$cpDir"
find $dir -type f -mmin -45 -exec cp {} "$cpDir" \;
