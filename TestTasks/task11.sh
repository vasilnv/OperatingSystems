#!/bin/bash
find /home/SI -type d -printf "%p %Cs\n" | awk -F ' ' '$2 > 1551168000 && $2 < 1551176100 {print $1}'