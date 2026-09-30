# 语法检查（**永远先做这一步**）
xray run -test -config /usr/local/etc/xray/config.json

systemctl enable --now xray
systemctl restart xray
systemctl status xray --no-pager
journalctl -u xray -n 50 --no-pager

# 确认端口真的在监听，且只被 xray 占
ss -tulpen | grep -E ':443[[:space:]]'
