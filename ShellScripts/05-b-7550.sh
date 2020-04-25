#!/bin/bash
user=$1

ps -ef | grep "$user" | tr -s "  " " " | awk -F ' ' '{kill $2}'
