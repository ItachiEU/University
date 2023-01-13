#!/bin/bash

PRIMES[0]=2
i=1
n=3
MAX=$1
while [ $n -le $MAX ]
do
    j=0
    while [ $((${PRIMES[$j]}*${PRIMES[$j]})) -le $n ]
    do
        if [ $((n % ${PRIMES[$j]})) -eq 0 ]; then
            n=$((n+1))
            continue 2
        fi
        j=$((j+1))
    done
    PRIMES[$i]=$n
    i=$((i+1))
    n=$((n+1))
done
echo "${PRIMES[@]}"
