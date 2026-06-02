#!/bin/bash
# task4.sh - Classify login capability

while read username; do
    if ! grep -q "^$username:" /etc/passwd; then
        echo "$username NOTFOUND"
    else
        shell=$(grep "^$username:" /etc/passwd | cut -d: -f7)
        if [[ "$shell" == "/bin/false" ]] || [[ "$shell" == *nologin* ]]; then
            echo "$username no-login"
        else
            echo "$username login"
        fi
    fi
done
