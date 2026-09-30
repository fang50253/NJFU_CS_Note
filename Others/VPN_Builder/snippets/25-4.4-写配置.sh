bash <<'SCRIPT'
set -a; . /root/vpn/params.env; set +a

# 校验必填项，别带着空值往下走
missing=""
for v in SERVER_IP VLESS_PORT REALITY_SNI REALITY_TARGET \
         REALITY_UUID REALITY_PRIVATE_KEY REALITY_PASSWORD REALITY_SHORT_ID; do
  eval "val=\$$v"
  [ -n "$val" ] || missing="$missing $v"
done
if [ -n "$missing" ]; then
  echo "❌ params.env 里这些项还是空的：$missing"
  echo "   请先编辑 /root/vpn/params.env 填好再重跑本段。"
  exit 1
fi

cp /usr/local/etc/xray/config.json /usr/local/etc/xray/config.json.bak 2>/dev/null

cat > /usr/local/etc/xray/config.json <<EOF
{
  "log": {
    "loglevel": "warning",
    "access": "/var/log/xray/access.log",
    "error": "/var/log/xray/error.log"
  },
  "inbounds": [
    {
      "tag": "vless-reality-in",
      "listen": "0.0.0.0",
      "port": ${VLESS_PORT},
      "protocol": "vless",
      "settings": {
        "clients": [
          {
            "id": "${REALITY_UUID}",
            "flow": "xtls-rprx-vision",
            "email": "main"
          }
        ],
        "decryption": "none"
      },
      "streamSettings": {
        "network": "raw",
        "security": "reality",
        "realitySettings": {
          "show": false,
          "target": "${REALITY_TARGET}",
          "xver": 0,
          "serverNames": ["${REALITY_SNI}"],
          "privateKey": "${REALITY_PRIVATE_KEY}",
          "shortIds": ["${REALITY_SHORT_ID}"]
        }
      },
      "sniffing": {
        "enabled": true,
        "destOverride": ["http", "tls", "quic"],
        "routeOnly": true
      }
    }
  ],
  "outbounds": [
    { "tag": "direct", "protocol": "freedom", "settings": {} },
    { "tag": "block",  "protocol": "blackhole", "settings": {} }
  ],
  "routing": {
    "domainStrategy": "IPIfNonMatch",
    "rules": [
      { "type": "field", "ip": ["geoip:private"], "outboundTag": "block" },
      { "type": "field", "protocol": ["bittorrent"], "outboundTag": "block" },
      { "type": "field", "ip": ["geoip:cn"], "outboundTag": "block" }
    ]
  }
}
EOF

echo "✅ 已写入 /usr/local/etc/xray/config.json"
SCRIPT
