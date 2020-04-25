#!/bin/bash
if [ $# -ne 2 ] 
then 
	echo i want two arguments
fi

file=$1
dir=$2
allFiles=$(find $dir -type f | tr -s "\n" " ") 

counter=0
for i in $allFiles 
do
text1=$(cat $file)
text2=$(cat $i)
	if [ "$text1" == "$text2"  ] 
	then 
		echo “$i”
		counter=$((counter+1))
	fi
done
echo [$counter]
