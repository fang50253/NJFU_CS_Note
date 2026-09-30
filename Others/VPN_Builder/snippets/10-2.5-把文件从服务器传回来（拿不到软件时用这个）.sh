# 方式一：scp，最简单
scp root@<服务器IP>:/root/offline-pkg/v2rayN.zip ~/Downloads/

# 方式二：服务器起临时 HTTP 服务，本地浏览器直接下载
#   服务器上（只监听回环，安全性最好）
cd /root/offline-pkg && python3 -m http.server 8000 --bind 127.0.0.1
#   本地另开一个终端做端口转发
ssh -fN -L 8000:127.0.0.1:8000 root@<服务器IP>
#   然后浏览器访问 http://127.0.0.1:8000/
