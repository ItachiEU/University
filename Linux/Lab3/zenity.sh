#!/bin/bash
IFS=$'\n'

index=0
track_list=$(find . -type f -name *.mp3)
for var in $track_list
do
    index=$((index+1))
    tracks[$index]=$(mp3info -p "%l (%a): %t" "$var")
    track_paths[$index]=$var
done

args=("Search by title" "")
index=0
for item in "${tracks[@]}"; do
    index=$((index+1))
    args+=("$index" "$item")
done

while [ 1 ]
do
    CHOICE=$(zenity --list --title="Music Player" --width=800 --height=400 --column="Number" --column="Description" "${args[@]}" &)
    if [[ $CHOICE == "Search by title" ]]; then
        SEARCH=$(zenity --forms --title="Search songs" --add-entry="Type title" --width=800 --height=400)
        args=("Search by title" "")
        index=0
        for item in "${tracks[@]}"; do
            index=$((index+1))
            matchtile=$(echo $item | sed 's/.*)//')
            if [[ $matchtile == *"$SEARCH"* ]]; then
            args+=("$index" "$item")
            fi 
        done
        continue
    fi
    if [[ "$CHOICE" == "" ]]
    then
        exit 0
    fi
    if [ "$CHOICE" -ge 1 ] && [ "$CHOICE" -le $index ]
    then 
        mplayer ${track_paths[$CHOICE]} 2>/dev/null && continue
    fi
done