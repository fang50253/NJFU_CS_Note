# references/ —— 官方一手资料存档

本目录由 `fetch_references.py` 自动抓取，内容是《VLESS + Hysteria2 自建节点部署指南》引用的**官方原文**，用于离线查阅与直接复制配置。

- 抓取日期：2026-09-30
- 文件数：33
- 完整校验值见 [`MANIFEST.json`](MANIFEST.json)（SHA256 + 字节数），或运行 `python3 fetch_references.py --verify`

> ⚠️ 上游文档会更新。本目录是**快照**，不是镜像；要最新内容请以表中 URL 为准。表里的 `commit` 是抓取时该文件的上游 commit，可以直接拿来对比差异。

> 许可证：各文件版权归原作者/原项目所有，本目录仅作学习存档。Xray/REALITY 为 MPL-2.0，Hysteria/sing-box 为 GPL-3.0，转载或再分发请遵循各自许可证。

## 目录

### Hysteria 2 官方文档（3 个）

| 文件 | 内容 | 指南中对应章节 | 大小 | SHA256（前 12） |
|---|---|---|---|---|
| [`hysteria/Server.md`](hysteria/Server.md) | Hysteria 2 服务端部署 | §5.1 部署 Hysteria 2 服务端 | 5 KB | `71e362714564` |
| [`hysteria/Full-Server-Config.md`](hysteria/Full-Server-Config.md) | Hysteria 2 完整服务端配置（全部字段） | §5.2 服务端 config.yaml 逐字段说明 | 30 KB | `f34207b4b1a4` |
| [`hysteria/Port-Hopping.md`](hysteria/Port-Hopping.md) | Hysteria 2 端口跳跃 | §7.2 端口跳跃（Port Hopping） | 3 KB | `c6126a6590d9` |

<details><summary>来源 URL 与 commit</summary>

- `hysteria/Server.md` ← <https://v2.hysteria.network/docs/getting-started/Server/>
- `hysteria/Full-Server-Config.md` ← <https://v2.hysteria.network/docs/advanced/Full-Server-Config/>
- `hysteria/Port-Hopping.md` ← <https://v2.hysteria.network/docs/advanced/Port-Hopping/>

</details>

### sing-box 官方文档（含官方中文版）（8 个）

| 文件 | 内容 | 指南中对应章节 | 大小 | SHA256（前 12） |
|---|---|---|---|---|
| [`sing-box/vless.md`](sing-box/vless.md) | sing-box VLESS 出站（英文原文） | §8.1 sing-box 客户端配置 | 1 KB | `9a3b3bcf9a2e` |
| [`sing-box/vless.zh.md`](sing-box/vless.zh.md) | sing-box VLESS 出站（官方中文版） | §8.1 字段对照 | 1 KB | `ebb200dea969` |
| [`sing-box/hysteria2.md`](sing-box/hysteria2.md) | sing-box Hysteria2 出站（英文原文） | §8.2 sing-box Hysteria2 出站 | 6 KB | `5af71322fe85` |
| [`sing-box/hysteria2.zh.md`](sing-box/hysteria2.zh.md) | sing-box Hysteria2 出站（官方中文版） | §8.2 字段对照 | 6 KB | `a3dee0db31c4` |
| [`sing-box/tls.md`](sing-box/tls.md) | sing-box TLS / REALITY / uTLS 共享字段（英文原文） | §8.3 reality_opts / utls 字段 | 21 KB | `6f198183c73b` |
| [`sing-box/tls.zh.md`](sing-box/tls.zh.md) | sing-box TLS / REALITY / uTLS 共享字段（官方中文版） | §8.3 字段对照 | 20 KB | `bf0b1eeafa2c` |
| [`sing-box/package-manager.md`](sing-box/package-manager.md) | sing-box 安装（包管理器） | §8.0 安装 sing-box | 8 KB | `9764820802ae` |
| [`sing-box/package-manager.zh.md`](sing-box/package-manager.zh.md) | sing-box 安装（官方中文版） | §8.0 安装 sing-box | 8 KB | `d31b1aa3faee` |

<details><summary>来源 URL 与 commit</summary>

- `sing-box/vless.md` ← <https://raw.githubusercontent.com/SagerNet/sing-box/testing/docs/configuration/outbound/vless.md>
- `sing-box/vless.zh.md` ← <https://raw.githubusercontent.com/SagerNet/sing-box/testing/docs/configuration/outbound/vless.zh.md>
- `sing-box/hysteria2.md` ← <https://raw.githubusercontent.com/SagerNet/sing-box/testing/docs/configuration/outbound/hysteria2.md>
- `sing-box/hysteria2.zh.md` ← <https://raw.githubusercontent.com/SagerNet/sing-box/testing/docs/configuration/outbound/hysteria2.zh.md>
- `sing-box/tls.md` ← <https://raw.githubusercontent.com/SagerNet/sing-box/testing/docs/configuration/shared/tls.md>
- `sing-box/tls.zh.md` ← <https://raw.githubusercontent.com/SagerNet/sing-box/testing/docs/configuration/shared/tls.zh.md>
- `sing-box/package-manager.md` ← <https://raw.githubusercontent.com/SagerNet/sing-box/testing/docs/installation/package-manager.md>
- `sing-box/package-manager.zh.md` ← <https://raw.githubusercontent.com/SagerNet/sing-box/testing/docs/installation/package-manager.zh.md>

</details>

### Xray / REALITY 官方文档（4 个）

| 文件 | 内容 | 指南中对应章节 | 大小 | SHA256（前 12） |
|---|---|---|---|---|
| [`xray/reality-transport.md`](xray/reality-transport.md) | Xray 配置文档：REALITY 传输层字段详解 | §6.2 REALITY 参数逐个解释 | 9 KB | `d6c67a5482d7` |
| [`xray/REALITY-README.md`](xray/REALITY-README.md) | XTLS/REALITY 官方仓库 README | §6 REALITY 原理与抗探测 | 8 KB | `25b411756bd9` |
| [`xray/REALITY-README.en.md`](xray/REALITY-README.en.md) | XTLS/REALITY README（英文原文） | §6 REALITY 原理与抗探测 | 8 KB | `5658a983b433` |
| [`xray/Xray-install-README.md`](xray/Xray-install-README.md) | Xray 官方安装脚本说明 | §5.5 离线安装 / §3.1 安装 Xray | 3 KB | `43dd0b852844` |

<details><summary>来源 URL 与 commit</summary>

- `xray/reality-transport.md` ← <https://raw.githubusercontent.com/XTLS/Xray-docs-next/main/docs/config/transports/reality.md>
- `xray/REALITY-README.md` ← <https://raw.githubusercontent.com/XTLS/REALITY/main/README.md>
- `xray/REALITY-README.en.md` ← <https://raw.githubusercontent.com/XTLS/REALITY/main/README.en.md>
- `xray/Xray-install-README.md` ← <https://raw.githubusercontent.com/XTLS/Xray-install/main/README.md>

</details>

### Xray 官方示例配置（可直接复制）（12 个）

| 文件 | 内容 | 指南中对应章节 | 大小 | SHA256（前 12） |
|---|---|---|---|---|
| [`examples/XTLS-REALITY/README.md`](examples/XTLS-REALITY/README.md) | 示例：VLESS-TCP-XTLS-Vision-REALITY（中文） | §6.3 服务端/客户端配置 | 0.4 KB | `ad70a77ee96e` |
| [`examples/XTLS-REALITY/REALITY.ENG.md`](examples/XTLS-REALITY/REALITY.ENG.md) | 示例：VLESS-TCP-XTLS-Vision-REALITY 说明（英文详解） | §6.2 REALITY 的 dest / serverNames 怎么选 | 6 KB | `93d8d9043a4b` |
| [`examples/XTLS-REALITY/config_server.jsonc`](examples/XTLS-REALITY/config_server.jsonc) | 示例：REALITY 服务端配置 | §6.3.1 服务端 config.json | 2 KB | `da6247846507` |
| [`examples/XTLS-REALITY/config_client.jsonc`](examples/XTLS-REALITY/config_client.jsonc) | 示例：REALITY 客户端配置 | §6.3.2 客户端 config.json | 1 KB | `0e1880a651b0` |
| [`examples/VLESS-TCP-XTLS-Vision/README.md`](examples/VLESS-TCP-XTLS-Vision/README.md) | 示例：VLESS-TCP-XTLS-Vision（无 TLS，直连） | §6.4 对比：Vision 裸 TCP 与 REALITY 的差别 | 2 KB | `fbed9e61d563` |
| [`examples/VLESS-TCP-XTLS-Vision/config_server.jsonc`](examples/VLESS-TCP-XTLS-Vision/config_server.jsonc) | 示例：Vision 服务端配置 | §6.4 对比实验 | 3 KB | `b6cdd4e34e91` |
| [`examples/VLESS-TCP-XTLS-Vision/config_client.jsonc`](examples/VLESS-TCP-XTLS-Vision/config_client.jsonc) | 示例：Vision 客户端配置 | §6.4 对比实验 | 3 KB | `652593778fff` |
| [`examples/VLESS-TCP-REALITY/README.md`](examples/VLESS-TCP-REALITY/README.md) | 示例：VLESS-TCP-REALITY（防 RST 偷取） | §6.5 防 RST 攻击 | 0.5 KB | `05e9a6ceb7ca` |
| [`examples/VLESS-TCP-REALITY/config_server.jsonc`](examples/VLESS-TCP-REALITY/config_server.jsonc) | 示例：防 RST 服务端配置 | §6.5 防 RST 攻击 | 3 KB | `6d4a5b5e70e5` |
| [`examples/VLESS-TCP-REALITY/config_client.jsonc`](examples/VLESS-TCP-REALITY/config_client.jsonc) | 示例：防 RST 客户端配置 | §6.5 防 RST 攻击 | 1 KB | `2d8c9d8e8fcb` |
| [`examples/Hysteria2/README.md`](examples/Hysteria2/README.md) | 示例：Xray 作为 Hysteria2 客户端 | §9.2 让 Xray 也走 Hysteria2 | 0.4 KB | `02b0d326ca22` |
| [`examples/Hysteria2/client.jsonc`](examples/Hysteria2/client.jsonc) | 示例：Xray Hysteria2 客户端 outbound | §9.2 让 Xray 也走 Hysteria2 | 1 KB | `6f3db9b85407` |

<details><summary>来源 URL 与 commit</summary>

- `examples/XTLS-REALITY/README.md` ← <https://raw.githubusercontent.com/XTLS/Xray-examples/main/VLESS-TCP-XTLS-Vision-REALITY/README.md>
- `examples/XTLS-REALITY/REALITY.ENG.md` ← <https://raw.githubusercontent.com/XTLS/Xray-examples/main/VLESS-TCP-XTLS-Vision-REALITY/REALITY.ENG.md>
- `examples/XTLS-REALITY/config_server.jsonc` ← <https://raw.githubusercontent.com/XTLS/Xray-examples/main/VLESS-TCP-XTLS-Vision-REALITY/config_server.jsonc>
- `examples/XTLS-REALITY/config_client.jsonc` ← <https://raw.githubusercontent.com/XTLS/Xray-examples/main/VLESS-TCP-XTLS-Vision-REALITY/config_client.jsonc>
- `examples/VLESS-TCP-XTLS-Vision/README.md` ← <https://raw.githubusercontent.com/XTLS/Xray-examples/main/VLESS-TCP-XTLS-Vision/README.md>
- `examples/VLESS-TCP-XTLS-Vision/config_server.jsonc` ← <https://raw.githubusercontent.com/XTLS/Xray-examples/main/VLESS-TCP-XTLS-Vision/config_server.jsonc>
- `examples/VLESS-TCP-XTLS-Vision/config_client.jsonc` ← <https://raw.githubusercontent.com/XTLS/Xray-examples/main/VLESS-TCP-XTLS-Vision/config_client.jsonc>
- `examples/VLESS-TCP-REALITY/README.md` ← <https://raw.githubusercontent.com/XTLS/Xray-examples/main/VLESS-TCP-REALITY%20%28without%20being%20stolen%29/README.md>
- `examples/VLESS-TCP-REALITY/config_server.jsonc` ← <https://raw.githubusercontent.com/XTLS/Xray-examples/main/VLESS-TCP-REALITY%20%28without%20being%20stolen%29/config_server.jsonc>
- `examples/VLESS-TCP-REALITY/config_client.jsonc` ← <https://raw.githubusercontent.com/XTLS/Xray-examples/main/VLESS-TCP-REALITY%20%28without%20being%20stolen%29/config_client.jsonc>
- `examples/Hysteria2/README.md` ← <https://raw.githubusercontent.com/XTLS/Xray-examples/main/Hysteria2/README.md>
- `examples/Hysteria2/client.jsonc` ← <https://raw.githubusercontent.com/XTLS/Xray-examples/main/Hysteria2/client.jsonc>

</details>

### Mihomo（Clash.Meta 内核）（1 个）

| 文件 | 内容 | 指南中对应章节 | 大小 | SHA256（前 12） |
|---|---|---|---|---|
| [`mihomo/README.md`](mihomo/README.md) | Mihomo（Clash.Meta 内核）README | §9.1 Mihomo 客户端配置 | 3 KB | `cdea6c96d33d` |

<details><summary>来源 URL 与 commit</summary>

- `mihomo/README.md` ← <https://raw.githubusercontent.com/MetaCubeX/mihomo/Meta/README.md>

</details>

### v2rayN（Windows 客户端）（1 个）

| 文件 | 内容 | 指南中对应章节 | 大小 | SHA256（前 12） |
|---|---|---|---|---|
| [`v2rayN/README.md`](v2rayN/README.md) | v2rayN（Windows / Linux / macOS 图形客户端）README | §9.3 图形客户端导入 | 3 KB | `2376917589f3` |

<details><summary>来源 URL 与 commit</summary>

- `v2rayN/README.md` ← <https://raw.githubusercontent.com/2dust/v2rayN/master/README.md>

</details>

### 教程中被直接执行的官方脚本（4 个）

| 文件 | 内容 | 指南中对应章节 | 大小 | SHA256（前 12） |
|---|---|---|---|---|
| [`scripts/xray-install-release.sh`](scripts/xray-install-release.sh) | Xray 官方安装脚本 install-release.sh | §3.1 安装 Xray / §5.5 离线安装 | 30 KB | `7f70c95f6b41` |
| [`scripts/sing-box-install.sh`](scripts/sing-box-install.sh) | sing-box 官方安装脚本 install.sh | §8.0 安装 sing-box | 4 KB | `528b3c77d251` |
| [`scripts/sing-box-gpg.key`](scripts/sing-box-gpg.key) | sing-box 仓库 GPG 公钥（校验 apt 源签名用） | §8.0 安装 sing-box（apt 源签名） | 3 KB | `803d5a2f09fe` |
| [`scripts/hysteria2-install.sh`](scripts/hysteria2-install.sh) | Hysteria 2 官方一键安装脚本 | §5.1 部署 Hysteria 2 服务端 | 27 KB | `2cc5d1c62f13` |

<details><summary>来源 URL 与 commit</summary>

- `scripts/xray-install-release.sh` ← <https://github.com/XTLS/Xray-install/raw/main/install-release.sh>
- `scripts/sing-box-install.sh` ← <https://sing-box.app/install.sh>
- `scripts/sing-box-gpg.key` ← <https://sing-box.app/gpg.key>
- `scripts/hysteria2-install.sh` ← <https://get.hy2.sh/>

</details>

---

## 怎么用这些文件

```bash
# 校验本地文件与抓取时一致（防篡改 / 防手动改坏）
python3 fetch_references.py --verify

# 重新抓取全部（上游更新后）
python3 fetch_references.py

# 直接看某份原文
less references/sing-box/tls.zh.md
```

**复制配置时注意**：官方示例里的 `id` / `password` / `privateKey` / `shortId` 是公开示例值，**必须换成你自己生成的**，否则等于没加密。
