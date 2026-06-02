#!/bin/bash
read disk
lsblk -n -o NAME "$disk" | grep -v "^$(basename "$disk")\$" | sort
