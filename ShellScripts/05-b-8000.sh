#!/bin/bash
user=$1

ps -eo euser -o rss -o vsz -o cmd | grep "$user" | tr -s " " |sort -nr -t" " -k3 | awk -F ' ' '{if($3 != 0) {printf "%s %.2f\n", $4, $2/$3}}'

