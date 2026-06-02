#!/bin/bash
df -h --output=source,size | tail -n +2 | grep "^/dev" | sort -u
