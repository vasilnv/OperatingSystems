#!/bin/bash
option=$1
while true
do
	if [ "$option" == "-r" ] 
	then
		read -p "enter string: " string
		echo -e "\033[0;31m $string"
		
		read -p "enter string: " string
        	echo -e "\033[0;32m $string"
			
		read -p "enter string: " string
       		echo -e "\033[0;34m $string"
	elif [ "$option" == "-g" ]
	then
		read -p "enter string: " string
        	echo -e "\033[0;32m $string"
        
        	read -p "enter string: " string
        	echo -e "\033[0;34m $string"
        
        	read -p "enter string: " string
        	echo -e "\033[0;31m $string"
	elif [ "$option" == "-b" ]
       	then
		read -p "enter string: " string
       		echo -e "\033[0;34m $string"

       		read -p "enter string: " string
        	echo -e "\033[0;31m $string"
       
        	read -p "enter string: " string
        	echo -e "\033[0;32m $string"
    	elif [ "$option" == "-x" ]
    	then
	 	read -p "enter string: " string
	 	echo "$string"
  fi
	
done
