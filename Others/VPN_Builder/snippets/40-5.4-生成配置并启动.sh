bash <<'SCRIPT'
set -a; . /root/vpn/params.env; set +a

# 生成两个强随机密码（用 hex，不用 base64：
# base64 会产生 / + = 三种字符，/ 会截断路径、+ 在 URI 里会被解成空格，写 YAML/URI 都很容易出坑）
HY2_AUTH=$(openssl rand -hex 24)
HY2_OBFS=$(openssl rand -hex 24)
echo "auth 密码: $HY2_AUTH"
echo "obfs 密码: $HY2_OBFS"

cp /etc/hysteria/config.yaml /etc/hysteria/config.yaml.bak 2>/dev/null

cat > /etc/hysteria/config.yaml <<EOF
listen: ${HY2_LISTEN}

acme:
  domains:
    - ${DOMAIN}
  email: ${MAILTO}

auth:
  type: password
  password: "${HY2_AUTH}"

obfs:
  type: salamander
  salamander:
    password: "${HY2_OBFS}"

masquerade:
  type: proxy
  proxy:
    url: ${HY2_MASQ}
    rewriteHost: true

bandwidth:
  up: ${HY2_UP}
  down: ${HY2_DOWN}
EOF

# 把密码回写进 params.env，后面生成客户端配置要用
sed -i "s|^HY2_AUTH=.*|HY2_AUTH=\"${HY2_AUTH}\"|" /root/vpn/params.env
sed -i "s|^HY2_OBFS=.*|HY2_OBFS=\"${HY2_OBFS}\"|" /root/vpn/params.env

systemctl enable --now hysteria-server
systemctl restart hysteria-server
systemctl status hysteria-server --no-pager
journalctl -u hysteria-server -n 50 --no-pager

ss -ulpen | grep -E ':443[[:space:]]'
SCRIPT
