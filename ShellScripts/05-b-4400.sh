#!/bin/bash
dirExtract=$1
dirTo=$2
cp $(find $dirExtract -type f -amin -45) $dirTo
exit 0
