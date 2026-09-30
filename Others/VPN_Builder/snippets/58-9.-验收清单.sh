cat > /root/vpn/check.sh <<'SH'
#!/usr/bin/env bash
set -u
pass=0; fail=0
ok()   { echo "  ✅ $1"; pass=$((pass+1)); }
bad()  { echo "  ❌ $1"; fail=$((fail+1)); }
set -a; . /root/vpn/params.env; set +a

echo "== 1. 服务状态 =="
systemctl is-active --quiet xray              && ok "xray 运行中"        || bad "xray 未运行"
systemctl is-enabled --quiet xray              && ok "xray 开机自启"      || bad "xray 未设自启"
systemctl is-active --quiet hysteria-server   && ok "hysteria 运行中"    || bad "hysteria 未运行"
systemctl is-enabled --quiet hysteria-server   && ok "hysteria 开机自启"  || bad "hysteria 未设自启"

echo "== 2. 配置语法 =="
xray run -test -config /usr/local/etc/xray/config.json >/dev/null 2>&1 \
  && ok "xray 配置合法" || bad "xray 配置有语法错误"
timeout 5 hysteria server --config /etc/hysteria/config.yaml --check >/dev/null 2>&1 \
  && ok "hysteria 配置合法" || echo "  ⚠️  hysteria 无 --check 参数，跳过（看 journalctl 报错）"

echo "== 3. 端口监听 =="
# HY2_LISTEN 形如 ":443" 或 ":20000-20100"；取范围里的第一个端口来查
HY2_FIRST_PORT="${HY2_LISTEN#:}"; HY2_FIRST_PORT="${HY2_FIRST_PORT%%-*}"
ss -tlnp | grep -qE ":${VLESS_PORT}[[:space:]]"  && ok "TCP ${VLESS_PORT} 已监听 (VLESS)" || bad "TCP ${VLESS_PORT} 未监听"
ss -ulnp | grep -qE ":${HY2_FIRST_PORT}[[:space:]]" && ok "UDP ${HY2_FIRST_PORT} 已监听 (hy2)" || bad "UDP ${HY2_FIRST_PORT} 未监听"

echo "== 4. 防火墙 =="
ufw status | grep -q "${VLESS_PORT}/tcp"    && ok "ufw 放行 ${VLESS_PORT}/tcp" || bad "ufw 未放行 ${VLESS_PORT}/tcp"
# 端口跳跃时整段都要放行；单端口就是那个端口
if [ "$HY2_FIRST_PORT" = "${HY2_LISTEN#:}" ]; then
  ufw status | grep -q "${HY2_FIRST_PORT}/udp" && ok "ufw 放行 ${HY2_FIRST_PORT}/udp" || bad "ufw 未放行 ${HY2_FIRST_PORT}/udp（hy2 用）"
else
  ufw status | grep -q "${HY2_FIRST_PORT}:${HY2_LISTEN#:}/udp" && ok "ufw 放行 ${HY2_LISTEN#:} 整段 udp" || bad "ufw 未放行端口跳跃范围 ${HY2_LISTEN#:}（hy2 用）"
fi
echo "  ℹ️  别忘了确认云服务商安全组也放行了！"

echo "== 5. 出网 =="
curl -sS --max-time 8 https://api.ipify.org && echo "  ✅ 服务器出网正常（IP 如上）" || bad "服务器无法出网"

echo "== 6. REALITY 目标站 =="
xray tls ping "${REALITY_TARGET}" 2>&1 | grep -qiE 'TLS 1\.3' \
  && ok "${REALITY_SNI} 支持 TLS 1.3" || bad "${REALITY_SNI} 不支持 TLS 1.3，换个 target"

echo "== 7. 证书 =="
echo | openssl s_client -connect "${DOMAIN}:443" -servername "${DOMAIN}" 2>/dev/null \
  | openssl x509 -noout -dates 2>/dev/null | sed 's/^/     /' \
  || echo "  ⚠️  取不到证书信息（自签证书时需用 pinSHA256）"

echo "== 8. 时间同步（REALITY 硬性要求）=" 
timedatectl show -p NTPSynchronized --value | grep -q yes && ok "时间已同步" || bad "时间未同步，跑 timedatectl status 排查"

echo
echo "=========== 通过 ${pass} 项，失败 ${fail} 项 ==========="
[ "$fail" -eq 0 ]
SH

# 补一个变量给脚本用
sed -i "s/^HY2_LISTEN=.*/&\nHY2_PORT_HINT=\"443\"/" /root/vpn/params.env

chmod +x /root/vpn/check.sh
/root/vpn/check.sh
