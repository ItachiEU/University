#!/bin/bash

if [ $# -ne 1 ]
then
    echo "Please provide one mount point."
    exit 1
fi

lookup=$(echo $1 | sed 's/\/*$//' )

if [ "$lookup" == "" ]
then
	lookup="/"
fi

fstab=$( cat /etc/fstab | sed 's/^#.*$/#/' | awk -v var="$lookup" '$2 ~ var' )
dev=$(echo $fstab | awk '{print $1}')
fs=$(echo $fstab | awk '{print $3}')
mntopt=$(echo $fstab | awk '{print $4}')
dmpfreq=$(echo $fstab | awk '{print $5}')
fsckpass=$(echo $fstab | awk '{print $6}')

printf "Device: $dev\nFilesystem type: $fs\nMount options: $mntopt\nDump frequency: $dmpfreq\nFsck pass number:$fsckpass\n"
