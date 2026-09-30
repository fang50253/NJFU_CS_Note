# 一次性
export ALL_PROXY=socks5h://127.0.0.1:1080

# apt
cat > /etc/apt/apt.conf.d/99proxy <<'EOF'
Acquire::http::Proxy  "socks5h://127.0.0.1:1080";
Acquire::https::Proxy "socks5h://127.0.0.1:1080";
EOF

# git
git config --global http.proxy socks5h://127.0.0.1:1080

# pip
pip config set global.proxy socks5h://127.0.0.1:1080
