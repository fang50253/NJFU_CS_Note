#!/bin/bash
read fstabfile
grep -v "^#" "$fstabfile" | awk '{print $2}' | grep -v "^$"
