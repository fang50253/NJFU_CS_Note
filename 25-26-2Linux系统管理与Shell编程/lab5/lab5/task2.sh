#!/bin/bash
# task2.sh
while read cmd; do
    # 获取 PID 最小的进程的 NI 值
    result=$(ps -C "$cmd" -o pid,ni --sort=pid | awk 'NR==2 {print $2}')
    if [ -z "$result" ]; then
        echo "$cmd NOTFOUND"
    else
        echo "$cmd $result"
    fi
done