set -a; source /root/vpn/params.env; set +a

echo "=============================================="
echo " 1) VLESS+REALITY 分享链接（v2rayN/v2rayNG/Shadowrocket 都能扫）"
echo "=============================================="
cat <<EOF
vless://${REALITY_UUID}@${SERVER_IP}:${VLESS_PORT}?encryption=none&flow=xtls-rprx-vision&security=reality&sni=${REALITY_SNI}&fp=chrome&pbk=${REALITY_PASSWORD}&sid=${REALITY_SHORT_ID}&type=tcp&headerType=none#REALITY-${SERVER_IP}
EOF

echo
echo "=============================================="
echo " 2) Hysteria2 分享链接"
echo "=============================================="
cat <<EOF
hysteria2://${HY2_AUTH}@${DOMAIN}:443?sni=${DOMAIN}&insecure=0&obfs=salamander&obfs-password=${HY2_OBFS}#HY2-${DOMAIN}
EOF

echo
echo "=============================================="
echo " 3) sing-box 客户端 outbound（VLESS + REALITY）"
echo "=============================================="
cat <<EOF
{
  "type": "vless",
  "tag": "proxy-reality",
  "server": "${SERVER_IP}",
  "server_port": ${VLESS_PORT},
  "uuid": "${REALITY_UUID}",
  "flow": "xtls-rprx-vision",
  "packet_encoding": "xudp",
  "tls": {
    "enabled": true,
    "server_name": "${REALITY_SNI}",
    "utls": { "enabled": true, "fingerprint": "chrome" },
    "reality": {
      "enabled": true,
      "public_key": "${REALITY_PASSWORD}",
      "short_id": "${REALITY_SHORT_ID}"
    }
  }
}
EOF

echo
echo "=============================================="
echo " 4) sing-box 客户端 outbound（Hysteria2）"
echo "=============================================="
cat <<EOF
{
  "type": "hysteria2",
  "tag": "proxy-hy2",
  "server": "${DOMAIN}",
  "server_port": 443,
  "password": "${HY2_AUTH}",
  "obfs": { "type": "salamander", "password": "${HY2_OBFS}" },
  "up_mbps": 100,
  "down_mbps": 500,
  "tls": { "enabled": true, "server_name": "${DOMAIN}", "insecure": false }
}
EOF
