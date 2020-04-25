#!/bin/bash
file=$1
userReceiver=$2
realReceiverUsername=$(cat $file | grep $userReceiver | cut -d " " -f 1-2)
write $realReceiverUsername<<< "ooooo\n EOF"
exit 0
