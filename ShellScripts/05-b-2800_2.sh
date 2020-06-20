#!/bin/bash
param=$1

comp=$(echo "$param" | sed -r "s/[^0-9A-Za-z]//g") 
print=$(echo "$param" | sed "s/[0-9A-Za-z]//g")

if [[ $param == $comp ]]
then
	echo "contains everything we want"
else
	echo "contains sth we dont want " "$print"  
fi
