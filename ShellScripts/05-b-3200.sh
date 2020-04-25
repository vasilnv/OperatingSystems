#!/bin/bash
read -p "Enter directory: " directory
echo 'num of folders is: '
find $directory -type f | wc -l
echo "num of directories is: "
find $directory -type d | wc –l
