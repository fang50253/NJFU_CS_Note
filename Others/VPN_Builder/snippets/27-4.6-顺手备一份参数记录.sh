set -a; . /root/vpn/params.env; set +a

cat > /root/vpn/creds.txt <<EOF
# 私人文件，chmod 600，**不要发给任何人**
VLESS 地址    : ${SERVER_IP}
VLESS 端口    : ${VLESS_PORT}
UUID          : ${REALITY_UUID}
Flow          : xtls-rprx-vision
传输          : raw
安全          : reality
SNI           : ${REALITY_SNI}
公钥(pbk/password) : ${REALITY_PASSWORD}
ShortId(sid)  : ${REALITY_SHORT_ID}
Fingerprint   : chrome
EOF
chmod 600 /root/vpn/creds.txt
cat /root/vpn/creds.txt
