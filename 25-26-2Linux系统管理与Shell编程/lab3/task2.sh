#!/bin/bash
while read device; do
    name=$(basename "$device")
    fstype=$(lsblk -n -o FSTYPE "$device")
    echo "$name $fstype"
done
