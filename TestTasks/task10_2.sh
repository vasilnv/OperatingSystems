#!/bin/bash
cat my_pass | sort -t : -k3 -n | tail -n +201 | cut -d: -f 5- | cut -d, -f1,4 | tr -d , | sed "s/ //2" | sed -r "s/[0-9]//"
