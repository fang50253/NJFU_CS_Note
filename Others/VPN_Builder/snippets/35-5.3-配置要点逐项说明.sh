# 记下证书指纹，客户端用它替代 insecure（比关校验安全得多）
openssl x509 -in /etc/hysteria/server.crt -outform der | \
  openssl dgst -sha256 -binary | openssl enc -base64
