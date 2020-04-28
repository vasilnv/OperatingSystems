#!/bin/bash
if [ $# -ne 3 ] 
then
	echo wrong number of parameters
fi

file=$1
string1=$2
string2=$3

#checkString1=$(cat $file | grep "${string1}=")
line="${string1}="$(cat $file | grep "${string1}=" | tr -d " " | cut -d '=' -f2 | sed -r 's/(.)/\1\n/g' | sort -n | uniq -c | tr -s "  " " " | sed 's/ //' | sort -nr | awk -F ' ' '{printf $2} END {printf "\n"}' | sed -r 's/(.)/\1 /g')

cat $file | sed "s/$(cat $file | grep "${string1}=")/${line}/" > $file
checkString2=$(cat $file | grep "${string2}=")
#echo $checkString2
if [ -z "$checkString2" ] 
then 
	echo i am here
	exit 0
fi

line="${string2}="$(cat $file | grep "${string2}=" | tr -d " " | cut -d '=' -f2 | sed -r 's/(.)/\1\n/g' | sort -n | uniq -c | tr -s "  " " " | sed 's/ //' | sort -nr | awk -F ' ' '{printf $2} END {printf "\n"}' | sed -r 's/(.)/\1 /g')

cat $file | sed "s/$(cat $file | grep "${string2}=")/${line}/" > $file

charsFromString1=$(cat $file | grep "${string1}=" | tr -d " " | cut -d '=' -f2 | sed -r 's/(.)/\1\n/g' | sort -n | uniq -c | tr -s "  " " " | sed 's/ //' | sort -nr | awk -F ' ' '{printf $2} END {printf "\n"}' | sed -r 's/(.)/\1 /g')
charsFromString2=$(cat $file | grep "${string2}=" | tr -d " " | cut -d '=' -f2 | sed -r 's/(.)/\1\n/g' | sort -n | uniq -c | tr -s "  " " " | sed 's/ //' | sort -nr | awk -F ' ' '{printf $2} END {printf "\n"}' | sed -r 's/(.)/\1 /g')

allCharacters="$charsFromString1 $charsFromString2"

commonChars=$(echo $allCharacters | tr -d ' ' | sed -r 's/(.)/\1\n/g' | sort -n | uniq -c | tr -s "  " " " | sed 's/ //' | sort -nr | grep -v '1 ' | awk -F ' ' '{printf $2}END {printf "\n"}')
#echo $commonChars

finalLine="${string2}="$(cat $file | grep "${string2}=" | tr -d " " | cut -d '=' -f2 | tr -d "$commonChars" | tr -d ' ' | sed -r 's/(.)/\1 /g') 
cat $file | sed "s/$(cat $file | grep "${string2}=")/${finalLine}/" > $file
