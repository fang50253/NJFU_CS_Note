cd /root/offline-pkg
# 顺便把 systemd 单元一起装上
curl -fsSL https://get.hy2.sh/ 2>/dev/null > /dev/null || true   # 无网时跳过，改用手写单元
bash install_server.sh --local ./hysteria-linux-amd64
