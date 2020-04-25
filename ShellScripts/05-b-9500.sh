#!/bin/bash
option=$1
string=$2

if [ $option == "-r" ]
then 
	echo -e "\033[0;31m $string"
else if [ $option == "-g" ]
then
	echo -e "\033[0;32m $string"
else if [ $option == "-b" ]
then
	echo -e "\033[0;34m $string"
else 
	echo invalid first parameter
fi
fi
fi
echo -e "\033[0m"
