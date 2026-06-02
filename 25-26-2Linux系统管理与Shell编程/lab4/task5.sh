#!/bin/bash
# task5.sh - Summarize group information

while read groupname; do
    if ! grep -q "^$groupname:" /etc/group; then
        echo "$groupname NOTFOUND"
    else
        entry=$(grep "^$groupname:" /etc/group)
        gid=$(echo "$entry" | cut -d: -f3)
        members=$(echo "$entry" | cut -d: -f4)
        if [ -z "$members" ]; then
            count=0
        else
            count=$(echo "$members" | tr ',' '\n' | grep -c .)
        fi
        echo "$groupname $gid $count"
    fi
done
