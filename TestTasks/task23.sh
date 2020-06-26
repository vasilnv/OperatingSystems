#!/bin/bash
dir=$1
string=$2
files=$(find $dir -maxdepth 1 -type f -printf "%f\n" | egrep "vmlinuz-[0-9]+\.[0-9]+\.[0-9]+-[0-9A-Za-z]+" | egrep "${string}$") 
maxNum=$(echo "$files" | cut -d '-' -f2 | sort -V | tail -n 1)
echo $(echo "$files" | egrep "vmlinuz-${maxNum}")
