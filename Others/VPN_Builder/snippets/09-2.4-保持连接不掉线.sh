ssh -fN -D 1080 vps      # 开 SOCKS5
autossh -M 0 -fN -D 1080 vps   # 有 autossh 的话会自动重连
