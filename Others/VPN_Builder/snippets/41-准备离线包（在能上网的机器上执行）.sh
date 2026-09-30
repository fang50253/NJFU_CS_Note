mkdir -p offline-pkg && cd offline-pkg

# Xray：zip 本身就含 xray 二进制 + geoip.dat + geosite.dat
XVER=v26.3.27
curl -fLO "https://github.com/XTLS/Xray-core/releases/download/${XVER}/Xray-linux-64.zip"
curl -fLO "https://github.com/XTLS/Xray-core/releases/download/${XVER}/Xray-linux-64.zip.dgst"

# Hysteria 2（文件名格式：hysteria-linux-amd64，无扩展名）
curl -fLO "https://github.com/apernet/hysteria/releases/download/app/v2.8.2/hysteria-linux-amd64"
chmod +x hysteria-linux-amd64

# 客户端也一并准备好（第三节要用）
curl -fLO "https://github.com/2dust/v2rayN/releases/latest/download/v2rayN-With-Core.zip"

# 校验（务必做）
sha256sum -c Xray-linux-64.zip.dgst
ls -lh
