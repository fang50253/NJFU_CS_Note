#!/bin/bash
# task6.sh - Convert epoch time in a given time zone

# Read timezone
read timezone

# Convert each epoch timestamp
while read epoch; do
    if [ -n "$epoch" ]; then
        TZ="$timezone" date -d "@$epoch" "+%Y-%m-%d %H:%M:%S %Z"
    fi
done
