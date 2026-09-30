apt install -y unzip          # 如果 apt 也不可用，用 busybox 或自带解压工具
cd /root/offline-pkg
unzip -o Xray-linux-64.zip
install -m 755 xray /usr/local/bin/xray
mkdir -p /usr/local/share/xray /usr/local/etc/xray /var/log/xray
install -m 644 geoip.dat geosite.dat /usr/local/share/xray/
chmod 755 geoip.dat geosite.dat

cat > /etc/systemd/system/xray.service <<'EOF'
[Unit]
Description=Xray Service
Documentation=https://github.com/XTLS/Xray-core
After=network.target nss-lookup.target

[Service]
User=nobody
CapabilityBoundingSet=CAP_NET_ADMIN CAP_NET_BIND_SERVICE
AmbientCapabilities=CAP_NET_ADMIN CAP_NET_BIND_SERVICE
NoNewPrivileges=true
ExecStart=/usr/local/bin/xray run -config /usr/local/etc/xray/config.json
Restart=on-failure
RestartPreventExitStatus=23
LimitNPROC=10000
LimitNOFILE=1000000

[Install]
WantedBy=multi-user.target
EOF

systemctl daemon-reload
systemctl enable --now xray
xray version
