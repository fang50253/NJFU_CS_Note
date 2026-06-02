---

# 🧪 Lab Assignment

## Linux System Configuration, Time, Scheduled Jobs, and Users (Chapter 7)

---

## 🎯 Objective

By completing this lab, you will learn how to:

* Inspect Linux logging components and journal metadata
* Read and parse user and group information from `/etc/passwd` and `/etc/group`
* Distinguish regular accounts from pseudo-users based on login shells
* Work with epoch timestamps and time zones
* Analyze system crontab entries
* Write robust, non-interactive shell scripts for system administration tasks

---

## 📁 Lab Setup

Create your lab directory:

```bash
mkdir -p ~/labs/lab4
cd ~/labs/lab4
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

	* Read input from **stdin**
	* Write output to **stdout**

5. DO NOT:

	* Use interactive input
	* Hardcode answers
	* Print extra text such as prompts or debug logs

6. Output formatting is STRICT:

	* No extra spaces
	* No extra blank lines
	* Exact field order must be preserved
	* Sort output where required

---

## 📝 Assignment Tasks

---

### ✅ Task 1 — Detect Logging Components

#### Input:

Multiple lines, each containing one logging component name:

```
journald
rsyslog
syslog-ng
```

#### Task:

For each input line, detect whether the component is available on the current system:

* `journald` means `journalctl` can be executed successfully
* `rsyslog` means `/etc/rsyslog.conf` exists
* `syslog-ng` means `/etc/syslog-ng` exists

#### Output:

Print one line per component in this format:

```
<name> <yes|no>
```

#### Example:

```
journald yes
rsyslog no
syslog-ng no
```

---

### ✅ Task 2 — Filter Journal Units by Prefix

#### Input:

One line containing a prefix string:

```
ssh
```

#### Task:

* Use `journalctl -F _SYSTEMD_UNIT` to list unit names known to the journal
* Print only the units whose names contain the given prefix

#### Output:

One matching unit per line

#### Requirement:

* Output must be **sorted**
* Output must be **unique**
* If there is no match, print nothing

---

### ✅ Task 3 — Query User Records from `/etc/passwd`

#### Input:

Multiple usernames, one per line:

```
root
nobody
alice
```

#### Task:

For each username, search `/etc/passwd` and extract:

* username
* UID
* GID
* home directory
* login shell

If the username does not exist, print `NOTFOUND` after the username.

#### Output:

Use one of the following formats:

```
<username> <uid> <gid> <home> <shell>
<username> NOTFOUND
```

#### Example:

```
root 0 0 /root /bin/bash
ghost NOTFOUND
```

---

### ✅ Task 4 — Classify Login Capability

#### Input:

Multiple usernames, one per line:

```
root
daemon
nobody
```

#### Task:

Determine whether each user is a likely interactive login account based on the shell field in `/etc/passwd`.

Use these rules:

* If the shell is `/bin/false` or contains `nologin`, print `no-login`
* Otherwise, print `login`
* If the user does not exist, print `NOTFOUND`

#### Output:

```
<username> <login|no-login|NOTFOUND>
```

#### Example:

```
root login
daemon no-login
ghost NOTFOUND
```

---

### ✅ Task 5 — Summarize Group Information

#### Input:

Multiple group names, one per line:

```
root
sudo
students
```

#### Task:

For each group in `/etc/group`, extract:

* group name
* GID
* number of listed members

If a group does not exist, print `NOTFOUND` after the group name.

#### Output:

Use one of the following formats:

```
<group> <gid> <member_count>
<group> NOTFOUND
```

#### Notes:

* The member list is the fourth field of `/etc/group`
* An empty member list means `0`

---

### ✅ Task 6 — Convert Epoch Time in a Given Time Zone

#### Input:

The first line is a time zone name.
Each remaining line is an epoch timestamp.

Example input:

```
US/Central
0
3600
86400
```

#### Task:

For each epoch value:

* Set the time zone using `TZ`
* Convert the epoch to local time using `date`

#### Output:

Print one converted timestamp per line using this format:

```
YYYY-MM-DD HH:MM:SS TZ
```

#### Example:

```
1969-12-31 18:00:00 CST
1969-12-31 19:00:00 CST
1970-01-01 18:00:00 CST
```

---

### ✅ Task 7 — Extract Commands from a System Crontab

#### Input:

Two lines:

1. Path to a **system-style crontab file**
2. Username to filter

Example input:

```
/etc/crontab
root
```

#### Task:

Parse the crontab file and print all active commands assigned to the given user.

Assume the crontab uses the **system crontab format**:

```
minute hour day month weekday user command
```

#### Requirement:

* Ignore blank lines
* Ignore lines beginning with `#`
* Match the username in the sixth field
* Print only the command portion

#### Output:

One command per line

#### Example:

If the crontab contains:

```text
17 *    * * *   root    cd / && run-parts --report /etc/cron.hourly
25 6    * * *   backup  /usr/local/bin/backup-home
47 6    * * 7   root    test -x /usr/sbin/anacron || run-parts --report /etc/cron.weekly
```

and the input user is `root`, the output should be:

```text
cd / && run-parts --report /etc/cron.hourly
test -x /usr/sbin/anacron || run-parts --report /etc/cron.weekly
```

---

## 🧪 Testing

You can test each script locally using:

```bash
bash taskN.sh < taskN.in
```

---

## 📊 Grading

Your work will be graded by comparing your script output against expected results generated from the teacher solutions.

Make sure your scripts:

* follow the exact filenames
* read from standard input
* print exact output with no extra text

