#!/bin/bash
cat passwd.txt | grep /home/SI | cut -d ':' -f5- | cut -d ',' -f1,4 | sed 's/, [0123456789]//'
