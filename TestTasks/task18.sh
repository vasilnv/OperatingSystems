#!/bin/bash
if [ $# -ne 0 ]
then
	echo no arguments expected
	exit 1
fi

find /home/ -type f -printf "%u %p %As\n" | sort -nk3 | grep ^grade | tail -n 1 | cut -d ' ' -f1,2
