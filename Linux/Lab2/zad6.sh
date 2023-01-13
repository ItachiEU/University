#!/bin/bash

IFS=$'\n'

if [ $# -ne 2 ]; then
    echo "Usage: $0 <path_to_files> <max_size_in_bytes>"
    exit 1
fi

sizelimit=$2
cursize=$(du -acb $1 | sed '$!d' | awk '{ print $1 }')

if [ $cursize -le $sizelimit ]; then
    echo "No cleanup necessary"
    exit 0
fi

cleanupsize=$((cursize - sizelimit))
size=0
files=$(find $1 -path '*.mp3' -printf "%Ts;%p;%s\n" | sort -r | column -t -s ';')

echo "Oldest files not within memory limit:" 
for file in $files
do
    if [ $size -ge $cleanupsize ]; then
    break
    fi 
    echo $file | awk '{print $(NF-1)}'
    size=$((size+$(echo $file | awk '{print $NF}')))
done

