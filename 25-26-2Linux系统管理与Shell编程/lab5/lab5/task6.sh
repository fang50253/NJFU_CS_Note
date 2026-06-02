#!/bin/bash
# task6.sh
free -k | awk '/^Mem:/ {print $2}'