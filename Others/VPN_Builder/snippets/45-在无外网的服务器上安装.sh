install -Dm755 hysteria-linux-amd64 /usr/local/bin/hysteria
id -u hysteria >/dev/null 2>&1 || useradd -r -d /var/lib/hysteria -m hysteria
mkdir -p /etc/hysteria

cat > /etc/systemd/system/hysteria-server.service <<'EOF'
[Unit]
Description=Hysteria Server Service
After=network.target

[Service]
Type=simple
ExecStart=/usr/local/bin/hysteria server --config /etc/hysteria/config.yaml
WorkingDirectory=~
User=hysteria
Group=hysteria
Environment=HYSTERIA_LOG_LEVEL=info
CapabilityBoundingSet=CAP_NET_ADMIN CAP_NET_BIND_SERVICE CAP_NET_RAW
AmbientCapabilities=CAP_NET_ADMIN CAP_NET_BIND_SERVICE CAP_NET_RAW
NoNewPrivileges=true

[Install]
WantedBy=multi-user.target
EOF

systemctl daemon-reload
systemctl enable --now hysteria-server
