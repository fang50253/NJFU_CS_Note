#!/bin/bash
read procfile
grep -c "^processor" "$procfile"
