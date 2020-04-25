#!/bin/bash
find . -type f -printf "%n %p\n" | sort -n | head -n 5 | awk -F ' ' '{print $2}'
