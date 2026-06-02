#!/bin/bash
# task7.sh - Extract commands from a system crontab

# Read crontab file path
read crontab_file

# Read username to filter
read username

# Check if file exists
if [ ! -f "$crontab_file" ]; then
    exit 1
fi

# Parse crontab file
while IFS= read -r line; do
    # Skip empty lines and comment lines
    if [ -z "$line" ] || [[ "$line" =~ ^[[:space:]]*# ]]; then
        continue
    fi
    
    # Remove leading/trailing whitespace
    line=$(echo "$line" | sed 's/^[[:space:]]*//;s/[[:space:]]*$//')
    
    # Skip if empty after trimming
    [ -z "$line" ] && continue
    
    # Parse fields (system crontab has 7 fields: minute hour day month weekday user command)
    fields=($line)
    
    # Check if we have at least 7 fields
    if [ ${#fields[@]} -ge 7 ]; then
        # User field is the 6th field (index 5)
        if [ "${fields[5]}" = "$username" ]; then
            # Command is everything after the 6th field (fields 6 and beyond)
            command_line="${line#* * * * * * }"
            # Remove any trailing whitespace
            command_line=$(echo "$command_line" | sed 's/^[[:space:]]*//;s/[[:space:]]*$//')
            [ -n "$command_line" ] && echo "$command_line"
        fi
    fi
done < "$crontab_file"
