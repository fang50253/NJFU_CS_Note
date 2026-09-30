# Xray（官方脚本，升级时会保留配置）
bash -c "$(curl -L https://github.com/XTLS/Xray-install/raw/main/install-release.sh)" @ install
xray version && systemctl restart xray

# Hysteria 2（重跑安装脚本即可，会自动重启运行中的服务）
bash <(curl -fsSL https://get.hy2.sh/)
systemctl status hysteria-server

# sing-box
curl -fsSL https://sing-box.app/install.sh | sh
systemctl restart sing-box
