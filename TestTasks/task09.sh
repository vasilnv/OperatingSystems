#!/bin/bash
find /home/grade -type f -printf "%Ar %i %n\n" | sort -n | awk -F ' ' '$4>=1{print $3}' | tail -n 1