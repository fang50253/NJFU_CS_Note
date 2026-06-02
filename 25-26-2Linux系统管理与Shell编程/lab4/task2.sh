#!/bin/bash
# task2.sh - Filter journal units by prefix

read prefix

if command -v journalctl &> /dev/null; then
    journalctl -F _SYSTEMD_UNIT 2>/dev/null | grep "$prefix" | sort -u
fi
