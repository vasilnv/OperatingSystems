#!/bin/bash
if [[ $1 =~ ^[a-z0-9]+$ ]]; then
	echo yes
else
	echo no
fi
exit 0
