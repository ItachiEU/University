#!/bin/bash

for ((i=9; i > 0; i--))
   do
   for ((j = 1; j < i; j++))
      do
      printf $'\e[K'
      echo -n $i
   done
   sleep 1
   echo -en "\r"
done