# ---- 在服务器上执行（它有墙外网络，随便下）----
mkdir -p /root/offline-pkg/clients && cd /root/offline-pkg/clients
curl -fLO "https://github.com/2dust/v2rayN/releases/latest/download/v2rayN-With-Core.zip"
ls -lh   # 确认文件大小正常，不是 0 字节或错误页
