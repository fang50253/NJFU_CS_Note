export ALL_PROXY=socks5h://127.0.0.1:1080

# 先验证代理对墙外站点确实生效
curl -s https://api.ipify.org; echo          # 应返回 VPS 的 IP

# 然后正常下载（git / wget / curl / npm / pip 都认 ALL_PROXY）
curl -fLO https://github.com/2dust/v2rayN/releases/latest/download/v2rayN-With-Core.zip
