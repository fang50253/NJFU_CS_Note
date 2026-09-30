ufw default deny incoming
ufw default allow outgoing

ufw allow 22/tcp        # 或你的新 SSH 端口
ufw allow 443/tcp       # VLESS + REALITY
ufw allow 443/udp       # Hysteria 2
ufw allow 80/tcp        # 仅 ACME HTTP-01 需要；用 DNS-01 可不开

ufw enable
ufw status verbose
