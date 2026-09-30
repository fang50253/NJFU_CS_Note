mkdir -p /root/vpn
cat > /root/vpn/params.env <<'EOF'
# ===== 基础 =====
SERVER_IP="1.2.3.4"            # ← 改：服务器公网 IPv4
DOMAIN="hy2.example.com"       # ← 改：你的域名（只有 hy2 需要）
MAILTO="you@example.com"       # ← 改：ACME 注册邮箱

# ===== VLESS + REALITY =====
VLESS_PORT=443
REALITY_SNI="www.microsoft.com"                        # ← 改：伪装目标域名
REALITY_TARGET="www.microsoft.com:443"
REALITY_UUID=""                                       # ← 填 xray uuid 的输出
REALITY_PRIVATE_KEY=""                                 # ← 填 xray x25519 的 PrivateKey
REALITY_PASSWORD=""                                    # ← 填 xray x25519 的 Password (PublicKey)
REALITY_SHORT_ID=""                                    # ← 填 shortId

# ===== Hysteria 2 =====
HY2_LISTEN=":443"          # 端口跳跃时改成 ":20000-20100"
HY2_AUTH=""                # ← 填 auth 密码
HY2_OBFS=""                # ← 填 obfs 密码
HY2_MASQ="https://www.bing.com/"
HY2_UP="100 mbps"          # VPS 上传给客户端
HY2_DOWN="500 mbps"        # 客户端传给 VPS
EOF
