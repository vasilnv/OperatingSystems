#!/bin/bash
find /home/SI -type d -printf "%p %As\n" | awk -F " " '$2 > 1551168000 && $2 < 1551176100 {print $1}'