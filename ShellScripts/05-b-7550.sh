#!/bin/bash
processes=$(ps -e -o user -o tty -o pid | tr -s " " | grep "grade pts/1" | cut -d ' ' -f3)
while read line 
do
	kill -15 $line
done < <(echo "$processes")

#do not use kill -KILL or kill -9 because the process would not 
	#1.clean up temp files
	#2.shut down sock
	#3) inform its children that it is going away
	#4) reset its terminal characteristics
		#and so on and so on.
#Generally, send 15, and wait a second or two, and if that does not work, send 2, 
#and if that does not work send 1. If that does not work, REMOVE THE BINARY because
#the program is badly behaved!
