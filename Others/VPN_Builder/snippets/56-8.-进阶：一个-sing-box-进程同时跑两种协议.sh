# 安装
curl -fsSL https://sing-box.app/install.sh | sh
# 或 Debian/Ubuntu 用官方源
# sudo mkdir -p /etc/apt/keyrings
# sudo curl -fsSL https://sing-box.app/gpg.key -o /etc/apt/keyrings/sagernet.asc
# echo 'Types: deb\nURIs: https://deb.sagernet.org/\nSuites: *\nComponents: *\nEnabled: yes\nSigned-By: /etc/apt/keyrings/sagernet.asc' | sudo tee /etc/apt/sources.list.d/sagernet.sources
# sudo apt-get update && sudo apt-get install sing-box

sing-box version
sing-box generate reality-keypair      # 生成 REALITY 密钥对
sing-box check -c /etc/sing-box/config.json   # 校验配置
systemctl enable --now sing-box
