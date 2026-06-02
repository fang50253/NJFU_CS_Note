#!/bin/bash
# task1.sh - Detect logging components

while read component; do
    case "$component" in
        journald)
            if command -v journalctl &> /dev/null && journalctl -q -n 1 &> /dev/null 2>&1; then
                echo "journald yes"
            else
                echo "journald no"
            fi
            ;;
        rsyslog)
            if [ -f /etc/rsyslog.conf ]; then
                echo "rsyslog yes"
            else
                echo "rsyslog no"
            fi
            ;;
        syslog-ng)
            if [ -d /etc/syslog-ng ]; then
                echo "syslog-ng yes"
            else
                echo "syslog-ng no"
            fi
            ;;
        *)
            echo "$component no"
            ;;
    esac
done
