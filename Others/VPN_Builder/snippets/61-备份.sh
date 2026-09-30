tar czf /root/vpn-backup-$(date +%F).tar.gz \
    /usr/local/etc/xray/config.json \
    /etc/hysteria/config.yaml \
    /root/vpn/params.env \
    /var/lib/hysteria/            # hy2 的 ACME 证书
