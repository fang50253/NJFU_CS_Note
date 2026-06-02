#!/bin/bash
# task7.sh
while read cmd; do
    # 获取 PID 最小的进程的用户
    user=$(ps -C "$cmd" -o pid,user --sort=pid | awk 'NR==2 {print $2}')
    
    if [ -z "$user" ]; then
        echo "$cmd NOTFOUND"
    else
        echo "$cmd $user"
    fi
done