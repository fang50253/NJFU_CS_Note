cat > /etc/sysctl.d/99-bbr.conf <<'EOF'
net.core.default_qdisc = fq
net.ipv4.tcp_congestion_control = bbr
net.ipv4.tcp_fastopen = 3
# hy2 / QUIC 建议调大 UDP 缓冲
net.core.rmem_max = 16777216
net.core.wmem_max = 16777216
EOF
sysctl --system

# 确认生效
sysctl net.ipv4.tcp_congestion_control net.core.default_qdisc
