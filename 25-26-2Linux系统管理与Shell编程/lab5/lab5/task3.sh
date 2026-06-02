#!/bin/bash
# task3.sh
while read filepath; do
    # 捕获 strace 中 openat 的输出行
    error=$(strace -e openat cat "$filepath" 2>&1 | grep "openat.*= -1" | sed -n 's/.*-1 \([A-Z]*\).*/\1/p')
    
    if [ -z "$error" ]; then
        echo "$filepath NO_ENOENT"
    else
        echo "$filepath $error"
    fi
done