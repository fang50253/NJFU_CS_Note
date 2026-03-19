## Linux Shell Commands for Configuration Files

```bash
# 1. List all files in /etc that contain "conf" in their name
ls /etc | grep "conf"

# 2. Save the list to conf_files.txt
ls /etc | grep "conf" > conf_files.txt

# 3. Count how many such files
wc -l conf_files.txt

# 4. Show first 3 and last 3 lines
echo "First 3 lines:"
head -n 3 conf_files.txt
echo ""
echo "Last 3 lines:"
tail -n 3 conf_files.txt

# 5. Sort alphabetically and view with less
sort conf_files.txt | less

# Bonus: Redirect error messages to separate file
ls /etc 2> error.log | grep "conf" > conf_files.txt
```

### Complete Script Version

```bash
cat > list_conf_files.sh << 'EOF'
#!/bin/bash
# Script to find and process configuration files

# Define output files
CONF_FILE="conf_files.txt"
ERROR_FILE="error.log"

echo "Searching for files containing 'conf' in /etc..."

# List files and filter, redirecting errors
ls /etc 2> "$ERROR_FILE" | grep "conf" > "$CONF_FILE"

# Check if any errors occurred
if [ -s "$ERROR_FILE" ]; then
    echo "Errors encountered (see $ERROR_FILE):"
    cat "$ERROR_FILE"
fi

# Display results
echo ""
echo "Files found:"
echo "----------------------------------------"
cat "$CONF_FILE"
echo "----------------------------------------"

# Count files
COUNT=$(wc -l < "$CONF_FILE")
echo "Total files containing 'conf': $COUNT"

# Show first and last 3
echo ""
echo "First 3 files:"
head -n 3 "$CONF_FILE"

echo ""
echo "Last 3 files:"
tail -n 3 "$CONF_FILE"

# Create sorted version
sort "$CONF_FILE" > "${CONF_FILE%.txt}_sorted.txt"
echo ""
echo "Sorted list saved to conf_files_sorted.txt"
EOF

chmod +x list_conf_files.sh
```

### One-Liner Commands

```bash
# 1. List conf files
ls /etc | grep conf

# 2. Save to file
ls /etc | grep conf > conf_files.txt

# 3. Count files
wc -l conf_files.txt

# 4. First 3 and last 3
head -3 conf_files.txt; echo "---"; tail -3 conf_files.txt

# 5. Sort and view
sort conf_files.txt | less

# Bonus: With error redirection
ls /etc 2> errors.txt | grep conf > conf_files.txt
```

### Expected Output Example

```bash
# After running the commands:
$ ls /etc | grep conf
adduser.conf
apg.conf
apparmor.conf
...
wgetrc
wodim.conf
xpdf.conf

$ wc -l conf_files.txt
42 conf_files.txt

$ head -3 conf_files.txt
adduser.conf
apg.conf
apparmor.conf

$ tail -3 conf_files.txt
wgetrc
wodim.conf
xpdf.conf
```

### Error Handling Bonus

```bash
# Try listing a non-existent directory with error redirection
ls /nonexistent 2> errors.txt | grep conf > conf_files.txt

# View errors
cat errors.txt
# Output: ls: cannot access '/nonexistent': No such file or directory
```

### Key Commands Explained

| Command | Purpose | Example |
|---------|---------|---------|
| `ls /etc` | List files in /etc | `ls /etc` |
| `grep "conf"` | Filter lines containing "conf" | `grep "conf"` |
| `\|` (pipe) | Send output to next command | `ls \| grep` |
| `>` | Redirect output to file | `> conf_files.txt` |
| `2>` | Redirect errors | `2> error.log` |
| `wc -l` | Count lines | `wc -l file.txt` |
| `head -3` | Show first 3 lines | `head -3 file.txt` |
| `tail -3` | Show last 3 lines | `tail -3 file.txt` |
| `sort` | Sort alphabetically | `sort file.txt` |
| `less` | View page by page | `sort file.txt \| less` |

These commands demonstrate basic Linux shell operations including pipes, redirections, and text processing.