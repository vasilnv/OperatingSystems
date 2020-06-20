#!/bin/bash
read -p "enter three file names: " first second third
f1=$(cat $first)
f2=$(cat $second)
sort $first $second > $third
