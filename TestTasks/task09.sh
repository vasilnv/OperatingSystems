#!/bin/bash
find /home/grade -type f -printf "%i %T@ %n\n" | sort -t ' ' -k2 -nr | awk -F ' ' '{if($3 > 1) {print $1}}' | uniq | head -n 1