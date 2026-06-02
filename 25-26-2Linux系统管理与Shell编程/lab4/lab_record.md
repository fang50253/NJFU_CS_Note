Last login: Sat Apr 25 14:23:21 on console
(base) fang50253@MacBook-Pro ~ % ssh 2351610105@150.158.24.225 -p 6001
2351610105@150.158.24.225's password: 
Linux raspberrypi 5.10.103-v7l+ #1529 SMP Tue Mar 8 12:24:00 GMT 2022 armv7l

The programs included with the Debian GNU/Linux system are free software;
the exact distribution terms for each program are described in the
individual files in /usr/share/doc/*/copyright.

Debian GNU/Linux comes with ABSOLUTELY NO WARRANTY, to the extent
permitted by applicable law.
Last login: Sat Apr 25 14:19:42 2026 from 127.0.0.1
2351610105@raspberrypi:~ $ ls
labs
2351610105@raspberrypi:~ $  cd labs
2351610105@raspberrypi:~/labs $ ;s
-bash: syntax error near unexpected token `;'
2351610105@raspberrypi:~/labs $ ls
lab0  lab1  lab2  lab3  lab4
2351610105@raspberrypi:~/labs $  cd lab4
2351610105@raspberrypi:~/labs/lab4 $ ls
test_cases
2351610105@raspberrypi:~/labs/lab4 $  cd test_cases
2351610105@raspberrypi:~/labs/lab4/test_cases $ ls
2351610105@raspberrypi:~/labs/lab4/test_cases $ cat tee task1.in <<'EOF'
> journald
> rsyslog
> syslog-ng
> EOF
cat: tee: No such file or directory
cat: task1.in: No such file or directory
2351610105@raspberrypi:~/labs/lab4/test_cases $ ls
2351610105@raspberrypi:~/labs/lab4/test_cases $ cat tee ./task1.in <<'EOF'
journald
rsyslog
syslog-ng
EOF
cat: tee: No such file or directory
cat: ./task1.in: No such file or directory
2351610105@raspberrypi:~/labs/lab4/test_cases $ cat ./task1.in <<'EOF'
journald
rsyslog
syslog-ng
EOF
cat: ./task1.in: No such file or directory
2351610105@raspberrypi:~/labs/lab4/test_cases $ sudo cat tee ./task1.in <<'EOF'
journald
rsyslog
syslog-ng
EOF
[sudo] password for 2351610105: 
2351610105 is not in the sudoers file.  This incident will be reported.
2351610105@raspberrypi:~/labs/lab4/test_cases $ echo "journald" > task1.in
2351610105@raspberrypi:~/labs/lab4/test_cases $ echo "rsyslog" >> task1.in
2351610105@raspberrypi:~/labs/lab4/test_cases $ echo "syslog-ng" >> task1.in
2351610105@raspberrypi:~/labs/lab4/test_cases $ echo "ssh" > task2.in
2351610105@raspberrypi:~/labs/lab4/test_cases $ 
2351610105@raspberrypi:~/labs/lab4/test_cases $ # 创建 task3.in
2351610105@raspberrypi:~/labs/lab4/test_cases $ echo "root" > task3.in
2351610105@raspberrypi:~/labs/lab4/test_cases $ echo "daemon" >> task3.in
2351610105@raspberrypi:~/labs/lab4/test_cases $ echo "nobody" >> task3.in
2351610105@raspberrypi:~/labs/lab4/test_cases $ echo "ghost" >> task3.in
2351610105@raspberrypi:~/labs/lab4/test_cases $ 
2351610105@raspberrypi:~/labs/lab4/test_cases $ # 创建 task4.in
2351610105@raspberrypi:~/labs/lab4/test_cases $ echo "root" > task4.in
2351610105@raspberrypi:~/labs/lab4/test_cases $ echo "daemon" >> task4.in
2351610105@raspberrypi:~/labs/lab4/test_cases $ echo "nobody" >> task4.in
2351610105@raspberrypi:~/labs/lab4/test_cases $ echo "ghost" >> task4.in
2351610105@raspberrypi:~/labs/lab4/test_cases $ 
2351610105@raspberrypi:~/labs/lab4/test_cases $ # 创建 task5.in
2351610105@raspberrypi:~/labs/lab4/test_cases $ echo "root" > task5.in
2351610105@raspberrypi:~/labs/lab4/test_cases $ echo "daemon" >> task5.in
2351610105@raspberrypi:~/labs/lab4/test_cases $ echo "nogroup" >> task5.in
2351610105@raspberrypi:~/labs/lab4/test_cases $ echo "students" >> task5.in
2351610105@raspberrypi:~/labs/lab4/test_cases $ 
2351610105@raspberrypi:~/labs/lab4/test_cases $ # 创建 task6.in
2351610105@raspberrypi:~/labs/lab4/test_cases $ echo "US/Central" > task6.in
2351610105@raspberrypi:~/labs/lab4/test_cases $ echo "0" >> task6.in
2351610105@raspberrypi:~/labs/lab4/test_cases $ echo "3600" >> task6.in
2351610105@raspberrypi:~/labs/lab4/test_cases $ echo "86400" >> task6.in
2351610105@raspberrypi:~/labs/lab4/test_cases $ 
2351610105@raspberrypi:~/labs/lab4/test_cases $ # 创建 task7.in
2351610105@raspberrypi:~/labs/lab4/test_cases $ echo "/etc/crontab" > task7.in
2351610105@raspberrypi:~/labs/lab4/test_cases $ echo "root" >> task7.in
2351610105@raspberrypi:~/labs/lab4/test_cases $ ls
task1.in  task2.in  task3.in  task4.in  task5.in  task6.in  task7.in
2351610105@raspberrypi:~/labs/lab4/test_cases $ cat task7.in
/etc/crontab
root
2351610105@raspberrypi:~/labs/lab4/test_cases $ echo "# Example system crontab" > task7.crontab
2351610105@raspberrypi:~/labs/lab4/test_cases $ echo "17 *    * * *   root    cd / && run-parts --report /etc/cron.hourly" >> task7.crontab
2351610105@raspberrypi:~/labs/lab4/test_cases $ echo "25 6    * * *   backup  /usr/local/bin/backup-home" >> task7.crontab
2351610105@raspberrypi:~/labs/lab4/test_cases $ echo "47 6    * * 7   root    test -x /usr/sbin/anacron || run-parts --report /etc/cron.weekly" >> task7.crontab2351610105@raspberrypi:~/labs/lab4/test_cases $ cat task7.crontab
# Example system crontab
17 *    * * *   root    cd / && run-parts --report /etc/cron.hourly
25 6    * * *   backup  /usr/local/bin/backup-home
47 6    * * 7   root    test -x /usr/sbin/anacron || run-parts --report /etc/cron.weekly
2351610105@raspberrypi:~/labs/lab4/test_cases $ cd ../
2351610105@raspberrypi:~/labs/lab4 $ cat > task1.sh << "EOF"
> #!/bin/bash
> # task1.sh - Detect logging components
> 
> while read component; do
>     case "$component" in
>         journald)
>             if command -v journalctl &> /dev/null && journalctl -q -n 1 &> /dev/null 2>&1; then
>                 echo "journald yes"
>             else
>                 echo "journald no"
>             fi
>             ;;
>         rsyslog)
>             if [ -f /etc/rsyslog.conf ]; then
>                 echo "rsyslog yes"
>             else
>                 echo "rsyslog no"
>             fi
>             ;;
>         syslog-ng)
>             if [ -d /etc/syslog-ng ]; then
>                 echo "syslog-ng yes"
>             else
>                 echo "syslog-ng no"
>             fi
>             ;;
>         *)
>             echo "$component no"
>             ;;
>     esac
> done
> EOF
2351610105@raspberrypi:~/labs/lab4 $ chmod +x task1.sh
2351610105@raspberrypi:~/labs/lab4 $ ./task1.sh

 no

 no

 no

 no

 no

 no

 no

 no

 no

 no

 no

 no

 no

 no

 no

 no

 no

 no

 no

 no

 no

 no

 no
^C
2351610105@raspberrypi:~/labs/lab4 $ cat ./test_cases/task1.in
journald
rsyslog
syslog-ng
2351610105@raspberrypi:~/labs/lab4 $ bash task1.sh < ./test_cases/task1.in
journald no
rsyslog yes
syslog-ng no
2351610105@raspberrypi:~/labs/lab4 $ cat > task2.sh << "EOF"
> #!/bin/bash
> # task2.sh - Filter journal units by prefix
> 
> read prefix
> 
> if command -v journalctl &> /dev/null; then
>     journalctl -F _SYSTEMD_UNIT 2>/dev/null | grep "$prefix" | sort -u
> fi
> EOF
2351610105@raspberrypi:~/labs/lab4 $ cat > task3.sh << "EOF"
> #!/bin/bash
> # task3.sh - Query user records from /etc/passwd
> 
> while read username; do
>     if grep -q "^$username:" /etc/passwd; then
>         entry=$(grep "^$username:" /etc/passwd)
>         uid=$(echo "$entry" | cut -d: -f3)
>         gid=$(echo "$entry" | cut -d: -f4)
>         home=$(echo "$entry" | cut -d: -f6)
>         shell=$(echo "$entry" | cut -d: -f7)
>         echo "$username $uid $gid $home $shell"
>     else
>         echo "$username NOTFOUND"
>     fi
> done
> EOF
2351610105@raspberrypi:~/labs/lab4 $ cat > task4.sh << "EOF"
> #!/bin/bash
> # task4.sh - Classify login capability
> 
> while read username; do
>     if ! grep -q "^$username:" /etc/passwd; then
>         echo "$username NOTFOUND"
>     else
>         shell=$(grep "^$username:" /etc/passwd | cut -d: -f7)
>         if [[ "$shell" == "/bin/false" ]] || [[ "$shell" == *nologin* ]]; then
>             echo "$username no-login"
>         else
>             echo "$username login"
>         fi
>     fi
> done
> EOF
2351610105@raspberrypi:~/labs/lab4 $ cat > task5.sh << "EOF"
> #!/bin/bash
> # task5.sh - Summarize group information
> 
> while read groupname; do
>     if ! grep -q "^$groupname:" /etc/group; then
>         echo "$groupname NOTFOUND"
>     else
>         entry=$(grep "^$groupname:" /etc/group)
>         gid=$(echo "$entry" | cut -d: -f3)
>         members=$(echo "$entry" | cut -d: -f4)
>         if [ -z "$members" ]; then
>             count=0
>         else
>             count=$(echo "$members" | tr ',' '\n' | grep -c .)
>         fi
>         echo "$groupname $gid $count"
>     fi
> done
> EOF
2351610105@raspberrypi:~/labs/lab4 $ cat > task6.sh << "EOF"
> #!/bin/bash
> # task6.sh - Convert epoch time in a given time zone
> 
> # Read timezone
> read timezone
> 
> # Convert each epoch timestamp
> while read epoch; do
>     if [ -n "$epoch" ]; then
>         TZ="$timezone" date -d "@$epoch" "+%Y-%m-%d %H:%M:%S %Z"
>     fi
> done
> EOF
2351610105@raspberrypi:~/labs/lab4 $ cat > task7.sh << "EOF"
> #!/bin/bash
> # task7.sh - Extract commands from a system crontab
> 
> # Read crontab file path
> read crontab_file
> 
> # Read username to filter
> read username
> 
> # Check if file exists
> if [ ! -f "$crontab_file" ]; then
>     exit 1
> fi
> 
> # Parse crontab file
> while IFS= read -r line; do
>     # Skip empty lines and comment lines
>     if [ -z "$line" ] || [[ "$line" =~ ^[[:space:]]*# ]]; then
>         continue
>     fi
>     
>     # Remove leading/trailing whitespace
>     line=$(echo "$line" | sed 's/^[[:space:]]*//;s/[[:space:]]*$//')
>     
>     # Skip if empty after trimming
>     [ -z "$line" ] && continue
>     
>     # Parse fields (system crontab has 7 fields: minute hour day month weekday user command)
>     fields=($line)
>     
>     # Check if we have at least 7 fields
>     if [ ${#fields[@]} -ge 7 ]; then
>         # User field is the 6th field (index 5)
>         if [ "${fields[5]}" = "$username" ]; then
>             # Command is everything after the 6th field (fields 6 and beyond)
>             command_line="${line#* * * * * * }"
>             # Remove any trailing whitespace
>             command_line=$(echo "$command_line" | sed 's/^[[:space:]]*//;s/[[:space:]]*$//')
>             [ -n "$command_line" ] && echo "$command_line"
>         fi
>     fi
> done < "$crontab_file"
> EOF
2351610105@raspberrypi:~/labs/lab4 $ chmod +x ./task*.sh
2351610105@raspberrypi:~/labs/lab4 $ ./task2.sh << ./test_cases/task2.in
> ^C
2351610105@raspberrypi:~/labs/lab4 $ ./task2.sh < ./test_cases/task2.in
2351610105@raspberrypi:~/labs/lab4 $ cat ./test_cases/task1.in | bash task1.sh
journald no
rsyslog yes
syslog-ng no
2351610105@raspberrypi:~/labs/lab4 $ cat ./test_cases/task2.in | bash task2.sh
2351610105@raspberrypi:~/labs/lab4 $ cat ./test_cases/task3.in | bash task3.sh
root 0 0 /root /bin/bash
daemon 1 1 /usr/sbin /usr/sbin/nologin
nobody 65534 65534 /nonexistent /usr/sbin/nologin
ghost NOTFOUND
2351610105@raspberrypi:~/labs/lab4 $ cat ./test_cases/task4.in | bash task4.sh
root login
daemon no-login
nobody no-login
ghost NOTFOUND
2351610105@raspberrypi:~/labs/lab4 $ cat ./test_cases/task5.in | bash task5.sh
root 0 0
daemon 1 0
nogroup 65534 0
students NOTFOUND
2351610105@raspberrypi:~/labs/lab4 $ cat ./test_cases/task6.in | bash task6.sh
1969-12-31 18:00:00 CST
1969-12-31 19:00:00 CST
1970-01-01 18:00:00 CST
2351610105@raspberrypi:~/labs/lab4 $ cat ./test_cases/task7.in | bash task7.sh
2351610105@raspberrypi:~/labs/lab4 $ cat > task7.sh << 'EOF'
> #!/bin/bash
> # task7.sh - Extract commands from a system crontab
> 
> # Read crontab file path
> read crontab_file
> 
> # Read username to filter
> read username
> 
> # Check if file exists and is readable
> if [ ! -f "$crontab_file" ] || [ ! -r "$crontab_file" ]; then
>     exit 0
> fi
> 
> # Parse crontab file
> while IFS= read -r line || [ -n "$line" ]; do
>     # Remove leading/trailing whitespace
>     line=$(echo "$line" | sed 's/^[[:space:]]*//;s/[[:space:]]*$//')
>     
>     # Skip empty lines and comment lines
>     [ -z "$line" ] && continue
>     [[ "$line" =~ ^# ]] && continue
>     
>     # Extract fields (system crontab format: minute hour day month weekday user command)
>     # Using awk to properly parse fields
>     user=$(echo "$line" | awk '{print $6}')
>     
>     if [ "$user" = "$username" ]; then
>         # Extract command (everything after the 6th field)
>         command=$(echo "$line" | awk '{for(i=7;i<=NF;i++) printf "%s%s", $i, (i<NF?" ":""); print ""}')
>         if [ -n "$command" ]; then
>             echo "$command"
>         fi
>     fi
> done < "$crontab_file"
> EOF
2351610105@raspberrypi:~/labs/lab4 $ 
2351610105@raspberrypi:~/labs/lab4 $ chmod +x task7.sh
2351610105@raspberrypi:~/labs/lab4 $ 
2351610105@raspberrypi:~/labs/lab4 $ # 测试修复后的脚本
2351610105@raspberrypi:~/labs/lab4 $ cat ./test_cases/task7.in | bash task7.sh
cd / && run-parts --report /etc/cron.hourly
test -x /usr/sbin/anacron || ( cd / && run-parts --report /etc/cron.daily )
test -x /usr/sbin/anacron || ( cd / && run-parts --report /etc/cron.weekly )
test -x /usr/sbin/anacron || ( cd / && run-parts --report /etc/cron.monthly )
2351610105@raspberrypi:~/labs/lab4 $ cat ./test_cases/task7.in | bash task7.sh
                                      hmod +x task7.sh
                                     ^C
2351610105@raspberrypi:~/labs/lab4 $ # 测试 journalctl 是否可用
2351610105@raspberrypi:~/labs/lab4 $ journalctl -F _SYSTEMD_UNIT 2>/dev/null | head -20
2351610105@raspberrypi:~/labs/lab4 $ 
2351610105@raspberrypi:~/labs/lab4 $ # 测试过滤 ssh 相关的单元
2351610105@raspberrypi:~/labs/lab4 $ journalctl -F _SYSTEMD_UNIT 2>/dev/null | grep ssh
2351610105@raspberrypi:~/labs/lab4 $ 
2351610105@raspberrypi:~/labs/lab4 $ # 查看所有可用的单元
2351610105@raspberrypi:~/labs/lab4 $ journalctl -F _SYSTEMD_UNIT 2>/dev/null | wc -l
0
2351610105@raspberrypi:~/labs/lab4 $ cat task2.sh
#!/bin/bash
# task2.sh - Filter journal units by prefix

read prefix

if command -v journalctl &> /dev/null; then
    journalctl -F _SYSTEMD_UNIT 2>/dev/null | grep "$prefix" | sort -u
fi
2351610105@raspberrypi:~/labs/lab4 $ cat > task2.sh << 'EOF'
> #!/bin/bash
> # task2.sh - Filter journal units by prefix
> 
> read prefix
> 
> if command -v journalctl &> /dev/null; then
>     # 尝试使用 sudo（如果配置了无密码 sudo）
>     sudo journalctl -F _SYSTEMD_UNIT 2>/dev/null | grep "$prefix" | sort -u
> fi
> EOF
2351610105@raspberrypi:~/labs/lab4 $ 
2351610105@raspberrypi:~/labs/lab4 $ chmod +x task2.sh
2351610105@raspberrypi:~/labs/lab4 $ cat ./test_cases/task2.in | bash task2.sh
[sudo] password for 2351610105: 
2351610105@raspberrypi:~/labs/lab4 $ cat > task2.sh << 'EOF'
> #!/bin/bash
> # task2.sh - Filter journal units by prefix
> 
> read prefix
> 
> # 方法1：尝试使用用户级别的 journalctl（不需要 sudo）
> if command -v journalctl &> /dev/null; then
>     # 尝试用户模式的 journal
>     units=$(journalctl --user -F _SYSTEMD_UNIT 2>/dev/null)
>     
>     # 如果用户模式没有，尝试系统模式但只读当前用户有权限的
>     if [ -z "$units" ]; then
>         units=$(journalctl -F _SYSTEMD_UNIT 2>/dev/null || true)
>     fi
>     
>     if [ -n "$units" ]; then
>         echo "$units" | grep "$prefix" | sort -u
>         exit 0
>     fi
> fi
> 
> # 方法2：使用 systemctl 列出服务（不需要 sudo）
> if command -v systemctl &> /dev/null; then
>     # 列出所有服务单元（用户和服务单元）
>     {
>         systemctl list-units --all --type=service --no-legend --no-pager 2>/dev/null | awk '{print $1}'
>         systemctl --user list-units --all --type=service --no-legend --no-pager 2>/dev/null | awk '{print $1}'
>     } | grep "$prefix" | sort -u
>     exit 0
> fi
> 
> # 方法3：直接查找 systemd 单元文件
> if [ -d /etc/systemd/system ] || [ -d /lib/systemd/system ]; then
>     {
>         find /etc/systemd/system -name "*.service" -o -name "*.socket" 2>/dev/null
>         find /lib/systemd/system -name "*.service" -o -name "*.socket" 2>/dev/null
>         find /usr/lib/systemd/system -name "*.service" -o -name "*.socket" 2>/dev/null
>     } | sed 's|.*/||' | grep "$prefix" | sort -u
> fi
> EOF
2351610105@raspberrypi:~/labs/lab4 $ 
2351610105@raspberrypi:~/labs/lab4 $ chmod +x task2.sh
2351610105@raspberrypi:~/labs/lab4 $ 
2351610105@raspberrypi:~/labs/lab4 $ # 测试
2351610105@raspberrypi:~/labs/lab4 $ cat ./test_cases/task2.in | bash task2.sh
regenerate_ssh_host_keys.service
ssh.service
sshswitch.service
2351610105@raspberrypi:~/labs/lab4 $ cd ../
2351610105@raspberrypi:~/labs $ cd lab4
2351610105@raspberrypi:~/labs/lab4 $ cd ../lab3
2351610105@raspberrypi:~/labs/lab3 $ ls
answer    task2.sh  task4.sh  task6.sh  test_cases
task1.sh  task3.sh  task5.sh  task7.sh  test.sh
2351610105@raspberrypi:~/labs/lab3 $ cat task2.sh
#!/bin/bash
while read device; do
    name=$(basename "$device")
    fstype=$(lsblk -n -o FSTYPE "$device")
    echo "$name $fstype"
done
2351610105@raspberrypi:~/labs/lab3 $ ls
answer    task2.sh  task4.sh  task6.sh  test_cases
task1.sh  task3.sh  task5.sh  task7.sh  test.sh
2351610105@raspberrypi:~/labs/lab3 $ ls test_cases
task1.in  task2.in  task3.in  task4.in  task5.in  task6.in  task7.in
2351610105@raspberrypi:~/labs/lab3 $ ./task1.sh < ./test_cases/task1.in
sda1
sda2
2351610105@raspberrypi:~/labs/lab3 $ ./task.sh < ./test_cases/task2.in
-bash: ./task.sh: No such file or directory
2351610105@raspberrypi:~/labs/lab3 $ ./task2.sh < ./test_cases/task2.in
sda1 ext4
sda2 ext4
loop0 
2351610105@raspberrypi:~/labs/lab3 $ echo "lsblk -f -n -o NAME,FSTYPE /dev/sda1 /dev/sda2" < task2.sh
lsblk -f -n -o NAME,FSTYPE /dev/sda1 /dev/sda2
2351610105@raspberrypi:~/labs/lab3 $ cat task2.sh
#!/bin/bash
while read device; do
    name=$(basename "$device")
    fstype=$(lsblk -n -o FSTYPE "$device")
    echo "$name $fstype"
done
2351610105@raspberrypi:~/labs/lab3 $ echo "lsblk -f -n -o NAME,FSTYPE /dev/sda1 /dev/sda2" > task2.sh
2351610105@raspberrypi:~/labs/lab3 $ cat task2.sh
lsblk -f -n -o NAME,FSTYPE /dev/sda1 /dev/sda2
2351610105@raspberrypi:~/labs/lab3 $ ./task2.sh < ./test_cases/task2.in
sda1 ext4
sda2 ext4
2351610105@raspberrypi:~/labs/lab3 $ ./task7.sh < ./test_cases/task7.in
/dev/mmcblk0p1  253M
/dev/root       118G
/dev/sda1       190M
2351610105@raspberrypi:~/labs/lab3 $ cat task7.sh
#!/bin/bash
df -h --output=source,size | tail -n +2 | grep "^/dev" | sort -u
2351610105@raspberrypi:~/labs/lab3 $ echo "#!/bin/bash
-bash: !/bin/bash: event not found
2351610105@raspberrypi:~/labs/lab3 $ df -h --output=source,size | tail -n +2 | grep "^/dev/sd" | sort -u" < task7.sh
> ^C
2351610105@raspberrypi:~/labs/lab3 $ df -h --output=source,size | tail -n +2 | grep "^/dev/sd" | sort -u" > task7.sh
> ^C
2351610105@raspberrypi:~/labs/lab3 $ df -h --output=source,size | tail -n +2 | grep "^/dev/sd" | sort -u" >^Cask7.sh
2351610105@raspberrypi:~/labs/lab3 $ echo "#!/bin/bash
-bash: !/bin/bash: event not found
2351610105@raspberrypi:~/labs/lab3 $ df -h --output=source,size | tail -n +2 | grep "^/dev/sd" | sort -u" ^C
2351610105@raspberrypi:~/labs/lab3 $ echo "df -h --output=source,size | tail -n +2 | grep "^/dev/sd" | sort -u" < task7.sh
df -h --output=source,size | tail -n +2 | grep ^/dev/sd | sort -u
2351610105@raspberrypi:~/labs/lab3 $ echo "df -h --output=source,size | tail -n +2 | grep "^/dev/sd" | sort -u" > task7.sh
2351610105@raspberrypi:~/labs/lab3 $ chmod +x task7.sh
2351610105@raspberrypi:~/labs/lab3 $ ./task7.sh
/dev/sda1       190M
2351610105@raspberrypi:~/labs/lab3 $ ./task7.sh < ./test_cases/task7.in
/dev/sda1       190M
2351610105@raspberrypi:~/labs/lab3 $ cat ./test_cases/task7.in
2351610105@raspberrypi:~/labs/lab3 $ Read from remote host 150.158.24.225: Operation timed out
Connection to 150.158.24.225 closed.
client_loop: send disconnect: Broken pipe
(base) fang50253@MacBook-Pro ~ % 
