#!/bin/bash
find /home/$whoami -type f -printf "%f %s\n" | sort -t ' ' -k2 -nr | head -n 5 | cut -d ' ' -f 1 | xargs rm 
