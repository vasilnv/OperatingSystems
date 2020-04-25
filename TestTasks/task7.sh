#!/bin/bash
cat myPasswd | grep ^s[1-9] | cut -d: -f1,5 | cut -d, -f 1 | grep a$ | cut -d : -f1 | cut -c 3,4 | uniq -c | tr -s "  " " " | sed 's/ //' | head -n +1
