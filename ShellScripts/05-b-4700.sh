#!/bin/bash
delimiter=' '
if [ $# -eq 2 ] ; 
then
	delimiter=$2
	num="$(echo "$1" | rev | sed -r "s/(...)/\1"$delimiter"/g" | rev)"
	check="$(echo "$num" | grep "^["$delimiter"]")"
	if [ -n "$check" ] 
	then
		num="$(echo "$num" | sed "s/"$delimiter"//")"
	fi  
	echo "$num"
	exit 0
else
    num="$(echo "$1" | rev | sed -r 's/(...)/\1 /g' | rev)"
    check="$(echo "$num" | grep "^[' ']")"
    if [ -n "$check" ]
    then
        num="$(echo "$num" | sed "s/ //")"
    fi
    echo "$num"
    exit 0
fi
