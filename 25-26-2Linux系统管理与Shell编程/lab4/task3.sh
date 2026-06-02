#!/bin/bash
# task3.sh - Query user records from /etc/passwd

while read username; do
    if grep -q "^$username:" /etc/passwd; then
        entry=$(grep "^$username:" /etc/passwd)
        uid=$(echo "$entry" | cut -d: -f3)
        gid=$(echo "$entry" | cut -d: -f4)
        home=$(echo "$entry" | cut -d: -f6)
        shell=$(echo "$entry" | cut -d: -f7)
        echo "$username $uid $gid $home $shell"
    else
        echo "$username NOTFOUND"
    fi
done
