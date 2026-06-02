#!/bin/bash
# task5.sh
while read cmd; do
    # 获取 PID 最小的进程的线程数
    thcount=$(ps -C "$cmd" -o pid,thcount --sort=pid | awk 'NR==2 {print $2}')
    
    if [ -z "$thcount" ]; then
        echo "$cmd NOTFOUND"
    elif [ "$thcount" -gt 1 ]; then
        echo "$cmd multithreaded"
    else
        echo "$cmd single-threaded"
    fi
done