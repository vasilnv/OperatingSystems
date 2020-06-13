#!/bin/bash
find . -type f -printf "%s %f\n" | sort -nr | cut -d ' ' -f2 | head -n +2 | xargs rm 
