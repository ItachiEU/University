#!/bin/bash

while true
do
    entropy_avail=$(cat /proc/sys/kernel/random/entropy_avail)
    poolsize=$(cat /proc/sys/kernel/random/poolsize)
    printf $'\e[K'
    printf "Available entropy: $entropy_avail/$poolsize\r"
    
    if read -n 1 -s -t 1; then 
        break
    fi
done
