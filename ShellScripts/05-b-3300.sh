#!/bin/bash
read -p "Enter directory: " directory
echo 'num of folders is: '
find $directory -type f | wc -l
echo "num of directories is: "
find $directory -type d | wc -l
grade@buster:~/05zadachi$ cat 05-b-3300.sh
#!/bin/bash
read -p "enter three file names: " first second third
f1=$(cat $first)
f2=$(cat $second)
sort $first $second > $third
