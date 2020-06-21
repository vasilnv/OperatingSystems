#!/bin/bash
searched=$1
left=$2
right=$3
for i in $@ 
do 
	if ! [[ $i =~ ^[0-9]+$ ]] 
		then
		echo not a number
		exit 3
	fi
done

if [ $left -gt $right ]
then
	echo argument 2 should be less or equal to argument 3
	exit 2
fi

if [ $searched -lt $left ] || [ $searched -gt $right ]
then 
	echo not in interval
	exit 1
else 
	echo in interval
	exit 0
fi
