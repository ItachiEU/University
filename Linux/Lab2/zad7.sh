#!/bin/bash

size_sum=0

for var in "$@"
do
    size_sum=$(($(du -ack "$var" | sed '$!d' | awk '{ print $1 }')+size_sum))
done

echo "Your files will fit in these filesystems:"
df -k | sed '1d' | awk -v sum=$size_sum '{if(sum<=$4) print $6; }'
