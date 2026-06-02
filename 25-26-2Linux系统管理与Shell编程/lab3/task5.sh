#!/bin/bash
free -b | awk '/^Swap:/ {print $2, $3}'
