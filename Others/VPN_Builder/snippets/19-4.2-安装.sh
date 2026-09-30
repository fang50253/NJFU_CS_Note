bash -c "$(curl -L https://github.com/XTLS/Xray-install/raw/main/install-release.sh)" @ help
# install --beta          装预发布版
# install -u root         以 root 身份运行（需要绑定 1024 以下端口时才用）
# install --without-geodata  不装 geo 数据（脚本已装过 geoip 可用这个更快）
# install-geodata         只更新 geoip/geosite
# remove                  卸载（保留配置和日志）
# remove --purge          彻底卸载
