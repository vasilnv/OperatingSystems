#!/bin/bash
read -p "enter file name and string" file string
cat $file | grep -q "$string" 
echo $?
