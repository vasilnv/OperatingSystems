#!/bin/bash
myProgram=$1
scope=$(cat $myProgram | sed "s/[^{}]//g" | tr -s "\n" " " | tr -d " " | sed "s/}{//g")
res=$((${#scope}/2)) 
echo $res
