#!/bin/bash
# task4.sh
while read lib; do
    # lsof -p $$ 列出当前进程打开的文件
    if lsof -p $$ | grep -q "$lib"; then
        echo "$lib yes"
    else
        echo "$lib no"
    fi
done