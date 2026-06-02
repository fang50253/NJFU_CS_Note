---

# Lab Assignment 6

## Network Configuration, Services, and Network Tools (Chapters 9-10)

---

## Objective

By completing this lab, you will learn how to:

* Calculate IPv4 network information from CIDR notation
* Query interface addresses and kernel routing decisions with `ip`
* Resolve hostnames through the system name service configuration
* Read service-to-port mappings from `/etc/services`
* Inspect listening TCP and UDP sockets with `ss`
* Use `curl` to test HTTP/HTTPS services from shell scripts
* Inspect active SSH server configuration files
* Inspect SSH server settings from real configuration files

---

## Lab Setup

Create your lab directory:

```bash
mkdir -p ~/labs/lab6
cd ~/labs/lab6
```

---

## General Requirements (VERY IMPORTANT)

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
   task8.sh
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
   * Print prompts, explanations, debug logs, or error messages

6. Output formatting is STRICT:

   * No extra spaces
   * No extra blank lines
   * Exact field order must be preserved
   * Sort output where required

The teacher solutions and student scripts will run on the same machine, so use the real system files and commands described in each task.

---

## Assignment Tasks

---

### Task 1 - Calculate IPv4 CIDR Details

#### Input:

Multiple IPv4 addresses in CIDR notation, one per line:

```text
192.168.10.25/24
10.20.30.40/27
172.16.5.9/30
```

#### Task:

For each input line, calculate:

* network address
* dotted-decimal netmask
* first usable host address
* last usable host address
* number of usable host addresses

You may assume the prefix length is between `1` and `30`.

#### Output:

```text
<ip>/<prefix> <network> <netmask> <first_host> <last_host> <usable_count>
```

#### Example:

```text
192.168.10.25/24 192.168.10.0 255.255.255.0 192.168.10.1 192.168.10.254 254
```

---

### Task 2 - Show IPv4 Addresses for Interfaces

#### Input:

Multiple network interface names, one per line:

```text
lo
eth0
fake0
```

#### Task:

For each interface, use `ip -o -4 address show dev <interface>` to find IPv4 addresses assigned to that interface.

#### Output:

If the interface has one or more IPv4 addresses, print one line per address:

```text
<interface> <address>/<prefix>
```

If the interface does not exist or has no IPv4 address, print:

```text
<interface> NOTFOUND
```

If multiple addresses exist for one interface, print them in the order shown by `ip`.

---

### Task 3 - Query Kernel Routes

#### Input:

Multiple destination IP addresses, one per line:

```text
127.0.0.1
8.8.8.8
```

#### Task:

For each destination, run:

```bash
ip route get <destination>
```

Extract:

* output interface after `dev`
* source address after `src`
* gateway after `via`, if present

#### Output:

```text
<destination> dev=<interface> src=<source|NONE> via=<gateway|DIRECT>
```

If no route can be found, print:

```text
<destination> UNREACHABLE
```

---

### Task 4 - Resolve Hostnames with System Configuration

#### Input:

Multiple hostnames, one per line:

```text
localhost
example.org
no-such-host.invalid
```

#### Task:

Use `getent hosts <hostname>` to resolve each hostname through the system name service configuration.

#### Output:

If one or more addresses are found, print all unique addresses as a comma-separated list:

```text
<hostname> <addr1,addr2,...>
```

If the hostname cannot be resolved, print:

```text
<hostname> NOTFOUND
```

Keep the address order produced by `getent`.

---

### Task 5 - Look Up Service Ports

#### Input:

Multiple service/protocol pairs, one per line:

```text
ssh tcp
domain udp
http tcp
```

#### Task:

Search `/etc/services` for the first non-comment entry whose service name and protocol match the input.

#### Output:

```text
<service>/<protocol> <port>
```

If no matching entry exists, print:

```text
<service>/<protocol> NOTFOUND
```

#### Example:

```text
ssh/tcp 22
```

---

### Task 6 - Check Listening TCP and UDP Ports

#### Input:

Multiple protocol/port pairs, one per line:

```text
tcp 22
udp 53
tcp 65000
```

#### Task:

Use `ss` to determine whether the local machine is listening on each requested port.

* For TCP, inspect listening TCP sockets.
* For UDP, inspect listening UDP sockets.
* Match numeric ports only.

#### Output:

```text
<protocol>/<port> <yes|no>
```

---

### Task 7 - Test HTTP or HTTPS URLs with curl

#### Input:

Multiple URLs, one per line:

```text
https://example.org/
http://127.0.0.1/
```

#### Task:

For each URL, use `curl` to report the HTTP status code.

Use these curl behaviors:

* silent mode
* discard the response body
* maximum time of 5 seconds
* print only the HTTP status code

If `curl` cannot connect or the request fails, curl will report status code `000`; print that value.

#### Output:

```text
<url> <http_code>
```

If the `curl` command is not installed, print:

```text
<url> TOOL_MISSING
```

---

### Task 8 - Inspect Active SSH Server Configuration

#### Input:

Multiple SSH server configuration keywords, one per line:

```text
Port
PermitRootLogin
X11Forwarding
```

#### Task:

Read active, non-comment settings from:

* `/etc/ssh/sshd_config`
* readable files matching `/etc/ssh/sshd_config.d/*.conf`

For each keyword, find the last active matching assignment. Matching is case-insensitive. Ignore blank lines and lines beginning with `#`.

#### Output:

If an active setting is found:

```text
<Keyword> <value>
```

If no active setting is found:

```text
<Keyword> NOTFOUND
```

Preserve the keyword spelling from the input.

---

## Testing

You can test each script locally using:

```bash
bash taskN.sh < taskN.in
```

---

## Grading

Your work will be graded by comparing your script output against expected results generated from the teacher solutions.

Make sure your scripts:

* follow the exact filenames
* read from standard input
* print exact output with no extra text
* use the real system commands and files requested by each task
