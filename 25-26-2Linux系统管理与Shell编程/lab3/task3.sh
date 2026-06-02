#!/bin/bash
read prefix
mount | awk -v p="$prefix" '$1 ~ "^" p {print $1, $3}' | sort -u
