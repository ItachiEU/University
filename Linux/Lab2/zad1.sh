#!/bin/bash
IFS=$'\n'

index=0
track_list_raw=$(find . -type f -name *.mp3)
for tr in $track_list_raw
do
    index=$((index+1))
    tracks_parsed[$index]=$(mp3info -p "%l (%a): %t" "$tr")
    track_paths[$index]=$tr
done

PS3="Choose a number to play>"

select track in ${tracks_parsed[*]}
do
    if [ "$REPLY" -ge 1 ] && [ "$REPLY" -le $index ]
    then 
        mplayer -really-quiet ${track_paths[$REPLY]} 2>/dev/null
    else
        echo "Wrong answer"
    fi
done
