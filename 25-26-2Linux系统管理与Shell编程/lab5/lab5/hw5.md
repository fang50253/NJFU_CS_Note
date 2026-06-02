---

# 🧪 Lab Assignment 5

## A Closer Look at Processes and Resource Utilization (Chapter 8)

---

## 🎯 Objective

By completing this lab, you will learn how to:

* Query memory configuration and system paging details
* Check process priorities and scheduling indices
* Diagnose file access issues by tracing system calls with `strace`
* Determine file descriptors and loaded shared libraries for user processes using `lsof`
* Analyze if running commands are multithreaded
* Measure and report physical system memory
* Script deterministic tests using Chapter 8 system tools

---

## 📁 Lab Setup

Create your lab directory:

```bash
mkdir -p ~/labs/lab5
cd ~/labs/lab5
```

---

## ⚠️ General Requirements (VERY IMPORTANT)

You MUST follow all rules below:

1. **File names (strict):**
   ```
   task1.sh
   task2.sh
   task3.sh
   task4.sh
   task5.sh
   task6.sh
   task7.sh
   ```

2. Each task must be:
   * A **separate script**
   * **Executable** (`chmod +x taskN.sh`)

3. Scripts must run as:
   ```bash
   bash taskN.sh < input.txt
   ```

4. Scripts MUST:
   * Read input from **stdin** (where applicable)
   * Write output to **stdout**

5. DO NOT:
   * Use interactive input
   * Hardcode answers
   * Print extra text such as prompts or debug logs

6. Output formatting is STRICT:
   * No extra spaces
   * No extra blank lines
   * Exact field order must be preserved

---

## 📝 Assignment Tasks

---

### ✅ Task 1 — System Page Size

#### Input:
(Input text should be ignored)

#### Task:
Retrieve the memory page size used by the system kernel. Use `getconf PAGE_SIZE`.

#### Output:
Print a single number representing the page size in bytes.

#### Example:
```
4096
```

---

### ✅ Task 2 — Check Process Priority (Nice Value)

#### Input:
Multiple process command names, one per line:
```
systemd
cron
sshd
```

#### Task:
For each command name:
* Find the matching process with the lowest PID using `ps -C <command>`.
* Extract its NI (nice) value.
* If multiple processes exist, only consider the lowest PID.
* If no process matches the command, print `NOTFOUND` after the command name.

#### Output:
```
<command> <nice>
<command> NOTFOUND
```

#### Example:
```
systemd 0
nonexistent-daemon NOTFOUND
```

---

### ✅ Task 3 — Trace Failed System Calls

#### Input:
Multiple paths to files that do not exist, one per line:
```
/tmp/not_a_file_123
/etc/shadow_fake
```

#### Task:
For each file path:
* Use `strace -e openat cat <file>` to trace the failed attempt.
* Capture standard error output and extract the exact error code constant (e.g. `ENOENT`) associated with the `openat` system call for that particular file.
* If no `ENOENT` error is found, print `NO_ENOENT`.

#### Output:
```
<filename> <ERROR_CONSTANT>
```

#### Example:
```
/tmp/not_a_file_123 ENOENT
```

---

### ✅ Task 4 — Finding Open Shared Libraries

#### Input:
Multiple library names, one per line:
```
libc.so
libtinfo.so
libfake.so
```

#### Task:
For each library name, use `lsof -p $$` to determine if your current `bash` process (the one running the script) has loaded this library. 
* Note: `$$` represents the current script's PID.
* Search for the exact library name in the `lsof` output.

#### Output:
Print one line per library in this format:
```
<library> <yes|no>
```

#### Example:
```
libc.so yes
libfake.so no
```

---

### ✅ Task 5 — Check for Multithreaded Processes

#### Input:
Multiple process command names, one per line.

#### Task:
For each command, determine whether the process with the lowest PID is single-threaded or multithreaded.
* Find the process using `ps -C <command>`.
* Count its threads (you can use `ps -o thcount`).
* If thread count > 1, it is `multithreaded`. If 1, it is `single-threaded`.
* If not found, print `NOTFOUND`.

#### Output:
```
<command> <multithreaded|single-threaded|NOTFOUND>
```

#### Example:
```
rsyslogd multithreaded
bash single-threaded
fake-daemon NOTFOUND
```

---

### ✅ Task 6 — Overall System Physical Memory

#### Input:
(Input text should be ignored)

#### Task:
Use the `free -k` command to find the total kilobytes of physical memory (`Mem:`) on the system.
* Extract just the numeric value for "total".

#### Output:
Print the total memory in kilobytes (a single number on its own line).

#### Example:
```
16234512
```

---

### ✅ Task 7 — Find the User Running a Process

#### Input:
Multiple process command names, one per line:
```
systemd
cron
sshd
```

#### Task:
For each command name:
* Find the matching process with the lowest PID using `ps -C <command>`.
* Extract the exact user (`USER` column) running that process.
* If multiple processes exist, only consider the lowest PID.
* If no process matches the command, print `NOTFOUND` after the command name.

#### Output:
```
<command> <USER>
```

#### Example:
```
systemd root
fake-daemon NOTFOUND
```
