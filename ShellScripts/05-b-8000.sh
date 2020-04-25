#!/bin/bash
user=$1

ps -eo euser -o rss -o vsz -o cmd | grep "$user" | tr -s "  " " " | awk -F ' ' '{printf ""$4" %.2f\n", $2/$3}'
