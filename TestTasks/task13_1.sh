#!/bin/bash
if [ ! -d $1 ]
then
	echo parameter should be dir
	exit 1
fi

if [ ! -r $1 ]
then
	echo dir should be readable
	exit 1
fi

dir=$1

find "${dir}" -type l -printf "%Y %p\n" | grep ^[NL] | cut -d ' ' -f2
