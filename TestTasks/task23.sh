#!/bin/bash
dir=$1
string=$2
files=$(find $dir -type f | grep -E "vmlinuz-[0-9]+\.[0-9]+\.[0-9]+-*" | grep -E "*${string}$" | cut -d '/' -f 2) 
maxNum=$(echo "$files" | cut -d '-' -f2 | sort -V | tail -n 1)
echo $(echo "$files" | grep -E "vmlinuz-${maxNum}")

