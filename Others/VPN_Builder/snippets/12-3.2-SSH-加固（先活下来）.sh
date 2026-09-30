# 1. 先放行新端口，再改配置，最后关旧端口
NEW_SSH_PORT=42345
ufw allow ${NEW_SSH_PORT}/tcp
sed -i "s/^#\?Port .*/Port ${NEW_SSH_PORT}/" /etc/ssh/sshd_config
sshd -t && systemctl reload ssh        # 注意：reload 不是 restart，别把自己踢下线

# 2. 换到密钥登录（强烈建议）
ssh-keygen -t ed25519 -C "vps"           # 在你自己电脑上执行
#   然后把公钥内容追加到服务器的 ~/.ssh/authorized_keys
# 确认密钥能登录后，再把 PasswordAuthentication 改成 no
