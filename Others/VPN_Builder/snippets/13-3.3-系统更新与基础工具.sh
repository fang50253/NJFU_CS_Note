apt update && apt full-upgrade -y
apt install -y curl wget ca-certificates openssl jq unzip tar \
               ufw nftables iptables chrony python3

timedatectl set-timezone Asia/Shanghai
systemctl enable --now chrony
timedatectl status          # 时间必须准，否则 REALITY 握手可能失败
