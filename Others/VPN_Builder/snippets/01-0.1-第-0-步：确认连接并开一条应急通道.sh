ssh root@<服务器IP> 'echo "== SSH 连通 =="; echo -n "服务器出口 IP: "; curl -s --max-time 8 https://api.ipify.org; echo'
