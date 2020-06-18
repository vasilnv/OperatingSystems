#!/bin/bash
cat my_pass | grep /home/SI/* | egrep " [[:alnum:]]+a(:|,)" | cut -c 3-4 | sort | uniq -c | tail -n 1
