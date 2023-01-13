#!/bin/bash

trap '' SIGHUP # If ARG is the null string each SIGNAL_SPEC is ignored by the shell
trap 'logger "SIGUSR1 received"; exit'  SIGUSR1

while true
do
	logger -s `date`
	sleep 1
done