mkdir -p /etc/hysteria
# -pkeyopt ec_paramgen_curve:P-256 直接生成 P-256 曲线（OpenSSL 1.1.1+ / 3.x 均可）
# 不要用 ec:<(openssl ecparam ...) 这种进程替换写法 —— 它依赖 bash，且在部分发行版上会失败
openssl req -x509 -nodes -newkey ec -pkeyopt ec_paramgen_curve:P-256 \
  -keyout /etc/hysteria/server.key \
  -out    /etc/hysteria/server.crt \
  -subj   "/CN=bing.com" \
  -addext "subjectAltName=DNS:bing.com" \
  -days 36500
chown -R hysteria:hysteria /etc/hysteria
chmod 600 /etc/hysteria/server.key

# 确认 SAN 真的写进去了（现代 TLS 客户端只看 SAN，不认 CN）
openssl x509 -in /etc/hysteria/server.crt -noout -text | grep -A1 "Alternative"
