#!/bin/bash
for i in "$@"
do
	if [ -f "$i" ] 
	then
		echo "removed file $i" >> logs.txt
		rm "$i"	
	fi
	if [ -d "$i" ]
	then
		count=$(ls -l "$i" | wc -l)
		if [ $count -eq 1 ] 
		then
			# we check $count == 1 because ls -l will print total 0 if dir is empty
			echo "removed dir $i" >> logs.txt
			rmdir "$i"
		fi
	fi
done
