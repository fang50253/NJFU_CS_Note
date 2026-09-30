#!/usr/bin/env python3
"""
fetch_references.py — 抓取《VLESS + Hysteria2 自建节点部署指南》引用的全部官方一手资料，
原文落盘到 references/ 目录，供读者离线查阅、直接复制配置。

两条取源策略：
  A. 有公开源码仓库的 -> 直接下 GitHub raw，拿到作者写的原始 Markdown（最权威）
  B. 只有渲染后网页的 -> 抽取正文 <article> 后用 pandoc 转成 Markdown

每个文件都会在 references/INDEX.md 里记录：来源 URL、上游 commit、字节数、SHA256、抓取日期。
文档内容可能随上游更新，commit 号就是核对依据。

用法:
    python3 fetch_references.py            # 全量抓取
    python3 fetch_references.py --verify   # 只按 INDEX.md 里记录的 SHA256 校验本地文件
"""

from __future__ import annotations

import argparse
import datetime as _dt
import hashlib
import html as html_mod
import json
import re
import subprocess
import sys
import urllib.error
import urllib.parse
import urllib.request
from pathlib import Path

ROOT = Path(__file__).resolve().parent
OUT = ROOT / "references"
UA = "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7) md-fetch/1.0"

# ─────────────────────────────────────────────────────────────────────────────
# 资源清单
#   kind: raw  = GitHub raw 原始 Markdown / 脚本 / 配置文件
#         html = 官方渲染页，抽取正文后转 Markdown
# ─────────────────────────────────────────────────────────────────────────────

RESOURCES: list[dict] = [
    # ── Hysteria 2 官方文档（无公开源码仓库，走 HTML->MD） ──────────────────
    dict(path="hysteria/Server.md", kind="html",
         url="https://v2.hysteria.network/docs/getting-started/Server/",
         title="Hysteria 2 服务端部署",
         used_in="§5.1 部署 Hysteria 2 服务端"),
    dict(path="hysteria/Full-Server-Config.md", kind="html",
         url="https://v2.hysteria.network/docs/advanced/Full-Server-Config/",
         title="Hysteria 2 完整服务端配置（全部字段）",
         used_in="§5.2 服务端 config.yaml 逐字段说明"),
    dict(path="hysteria/Port-Hopping.md", kind="html",
         url="https://v2.hysteria.network/docs/advanced/Port-Hopping/",
         title="Hysteria 2 端口跳跃",
         used_in="§7.2 端口跳跃（Port Hopping）"),

    # ── sing-box 官方文档（GitHub 源码，含官方中文版） ────────────────────
    dict(path="sing-box/vless.md", kind="raw",
         repo="SagerNet/sing-box", ref="testing", rpath="docs/configuration/outbound/vless.md",
         title="sing-box VLESS 出站（英文原文）",
         used_in="§8.1 sing-box 客户端配置"),
    dict(path="sing-box/vless.zh.md", kind="raw",
         repo="SagerNet/sing-box", ref="testing", rpath="docs/configuration/outbound/vless.zh.md",
         title="sing-box VLESS 出站（官方中文版）",
         used_in="§8.1 字段对照"),
    dict(path="sing-box/hysteria2.md", kind="raw",
         repo="SagerNet/sing-box", ref="testing", rpath="docs/configuration/outbound/hysteria2.md",
         title="sing-box Hysteria2 出站（英文原文）",
         used_in="§8.2 sing-box Hysteria2 出站"),
    dict(path="sing-box/hysteria2.zh.md", kind="raw",
         repo="SagerNet/sing-box", ref="testing", rpath="docs/configuration/outbound/hysteria2.zh.md",
         title="sing-box Hysteria2 出站（官方中文版）",
         used_in="§8.2 字段对照"),
    dict(path="sing-box/tls.md", kind="raw",
         repo="SagerNet/sing-box", ref="testing", rpath="docs/configuration/shared/tls.md",
         title="sing-box TLS / REALITY / uTLS 共享字段（英文原文）",
         used_in="§8.3 reality_opts / utls 字段"),
    dict(path="sing-box/tls.zh.md", kind="raw",
         repo="SagerNet/sing-box", ref="testing", rpath="docs/configuration/shared/tls.zh.md",
         title="sing-box TLS / REALITY / uTLS 共享字段（官方中文版）",
         used_in="§8.3 字段对照"),
    dict(path="sing-box/package-manager.md", kind="raw",
         repo="SagerNet/sing-box", ref="testing", rpath="docs/installation/package-manager.md",
         title="sing-box 安装（包管理器）",
         used_in="§8.0 安装 sing-box"),
    dict(path="sing-box/package-manager.zh.md", kind="raw",
         repo="SagerNet/sing-box", ref="testing", rpath="docs/installation/package-manager.zh.md",
         title="sing-box 安装（官方中文版）",
         used_in="§8.0 安装 sing-box"),

    # ── Xray / REALITY ────────────────────────────────────────────────────
    dict(path="xray/reality-transport.md", kind="raw",
         repo="XTLS/Xray-docs-next", ref="main", rpath="docs/config/transports/reality.md",
         title="Xray 配置文档：REALITY 传输层字段详解",
         used_in="§6.2 REALITY 参数逐个解释"),
    dict(path="xray/REALITY-README.md", kind="raw",
         repo="XTLS/REALITY", ref="main", rpath="README.md",
         title="XTLS/REALITY 官方仓库 README",
         used_in="§6 REALITY 原理与抗探测"),
    dict(path="xray/REALITY-README.en.md", kind="raw",
         repo="XTLS/REALITY", ref="main", rpath="README.en.md",
         title="XTLS/REALITY README（英文原文）",
         used_in="§6 REALITY 原理与抗探测"),
    dict(path="xray/Xray-install-README.md", kind="raw",
         repo="XTLS/Xray-install", ref="main", rpath="README.md",
         title="Xray 官方安装脚本说明",
         used_in="§5.5 离线安装 / §3.1 安装 Xray"),

    # ── Xray 官方示例配置（可直接复制的 json5/jsonc） ─────────────────────
    dict(path="examples/XTLS-REALITY/README.md", kind="raw",
         repo="XTLS/Xray-examples", ref="main", rpath="VLESS-TCP-XTLS-Vision-REALITY/README.md",
         title="示例：VLESS-TCP-XTLS-Vision-REALITY（中文）",
         used_in="§6.3 服务端/客户端配置"),
    dict(path="examples/XTLS-REALITY/REALITY.ENG.md", kind="raw",
         repo="XTLS/Xray-examples", ref="main", rpath="VLESS-TCP-XTLS-Vision-REALITY/REALITY.ENG.md",
         title="示例：VLESS-TCP-XTLS-Vision-REALITY 说明（英文详解）",
         used_in="§6.2 REALITY 的 dest / serverNames 怎么选"),
    dict(path="examples/XTLS-REALITY/config_server.jsonc", kind="raw",
         repo="XTLS/Xray-examples", ref="main", rpath="VLESS-TCP-XTLS-Vision-REALITY/config_server.jsonc",
         title="示例：REALITY 服务端配置",
         used_in="§6.3.1 服务端 config.json"),
    dict(path="examples/XTLS-REALITY/config_client.jsonc", kind="raw",
         repo="XTLS/Xray-examples", ref="main", rpath="VLESS-TCP-XTLS-Vision-REALITY/config_client.jsonc",
         title="示例：REALITY 客户端配置",
         used_in="§6.3.2 客户端 config.json"),
    dict(path="examples/VLESS-TCP-XTLS-Vision/README.md", kind="raw",
         repo="XTLS/Xray-examples", ref="main", rpath="VLESS-TCP-XTLS-Vision/README.md",
         title="示例：VLESS-TCP-XTLS-Vision（无 TLS，直连）",
         used_in="§6.4 对比：Vision 裸 TCP 与 REALITY 的差别"),
    dict(path="examples/VLESS-TCP-XTLS-Vision/config_server.jsonc", kind="raw",
         repo="XTLS/Xray-examples", ref="main", rpath="VLESS-TCP-XTLS-Vision/config_server.jsonc",
         title="示例：Vision 服务端配置",
         used_in="§6.4 对比实验"),
    dict(path="examples/VLESS-TCP-XTLS-Vision/config_client.jsonc", kind="raw",
         repo="XTLS/Xray-examples", ref="main", rpath="VLESS-TCP-XTLS-Vision/config_client.jsonc",
         title="示例：Vision 客户端配置",
         used_in="§6.4 对比实验"),
    dict(path="examples/VLESS-TCP-REALITY/README.md", kind="raw",
         repo="XTLS/Xray-examples", ref="main",
         rpath="VLESS-TCP-REALITY (without being stolen)/README.md",
         title="示例：VLESS-TCP-REALITY（防 RST 偷取）",
         used_in="§6.5 防 RST 攻击"),
    dict(path="examples/VLESS-TCP-REALITY/config_server.jsonc", kind="raw",
         repo="XTLS/Xray-examples", ref="main",
         rpath="VLESS-TCP-REALITY (without being stolen)/config_server.jsonc",
         title="示例：防 RST 服务端配置",
         used_in="§6.5 防 RST 攻击"),
    dict(path="examples/VLESS-TCP-REALITY/config_client.jsonc", kind="raw",
         repo="XTLS/Xray-examples", ref="main",
         rpath="VLESS-TCP-REALITY (without being stolen)/config_client.jsonc",
         title="示例：防 RST 客户端配置",
         used_in="§6.5 防 RST 攻击"),
    dict(path="examples/Hysteria2/README.md", kind="raw",
         repo="XTLS/Xray-examples", ref="main", rpath="Hysteria2/README.md",
         title="示例：Xray 作为 Hysteria2 客户端",
         used_in="§9.2 让 Xray 也走 Hysteria2"),
    dict(path="examples/Hysteria2/client.jsonc", kind="raw",
         repo="XTLS/Xray-examples", ref="main", rpath="Hysteria2/client.jsonc",
         title="示例：Xray Hysteria2 客户端 outbound",
         used_in="§9.2 让 Xray 也走 Hysteria2"),

    # ── 内核 / 客户端 ─────────────────────────────────────────────────────
    dict(path="mihomo/README.md", kind="raw",
         repo="MetaCubeX/mihomo", ref="Meta", rpath="README.md",
         title="Mihomo（Clash.Meta 内核）README",
         used_in="§9.1 Mihomo 客户端配置"),
    dict(path="v2rayN/README.md", kind="raw",
         repo="2dust/v2rayN", ref="master", rpath="README.md",
         title="v2rayN（Windows / Linux / macOS 图形客户端）README",
         used_in="§9.3 图形客户端导入"),

    # ── 官方安装脚本原文（教程里被 shell 执行的那些） ──────────────────────
    dict(path="scripts/xray-install-release.sh", kind="url",
         url="https://github.com/XTLS/Xray-install/raw/main/install-release.sh",
         title="Xray 官方安装脚本 install-release.sh",
         used_in="§3.1 安装 Xray / §5.5 离线安装"),
    dict(path="scripts/sing-box-install.sh", kind="url",
         url="https://sing-box.app/install.sh",
         title="sing-box 官方安装脚本 install.sh",
         used_in="§8.0 安装 sing-box"),
    dict(path="scripts/sing-box-gpg.key", kind="url",
         url="https://sing-box.app/gpg.key",
         title="sing-box 仓库 GPG 公钥（校验 apt 源签名用）",
         used_in="§8.0 安装 sing-box（apt 源签名）"),
    dict(path="scripts/hysteria2-install.sh", kind="url",
         url="https://get.hy2.sh/",
         title="Hysteria 2 官方一键安装脚本",
         used_in="§5.1 部署 Hysteria 2 服务端"),
]


# ─────────────────────────────────────────────────────────────────────────────
# HTTP
# ─────────────────────────────────────────────────────────────────────────────

def http_get(url: str, timeout: int = 45) -> bytes:
    req = urllib.request.Request(url, headers={"User-Agent": UA})
    with urllib.request.urlopen(req, timeout=timeout) as r:
        return r.read()


def resolve_url(res: dict) -> str:
    if res["kind"] in ("url", "html"):
        return res["url"]
    rpath = urllib.parse.quote(res["rpath"])  # 目录名里有空格和括号，必须转义
    return f"https://raw.githubusercontent.com/{res['repo']}/{res['ref']}/{rpath}"


def head_commit(res: dict) -> str:
    """取该文件在 GitHub 上的最后一次 commit（可作为「这是哪一版」的凭据）。

    GitHub API 有 60 次/小时的匿名配额，所以结果缓存到 references/.commits.json，
    重复抓取时不会重新查询、配额耗尽时也不影响下载本身。
    """
    if "rpath" not in res:
        return ""
    key = f"{res['repo']}@{res['ref']}:{res['rpath']}"
    cache_file = OUT / ".commits.json"
    cache: dict[str, str] = {}
    if cache_file.is_file():
        try:
            cache = json.loads(cache_file.read_text(encoding="utf-8"))
        except json.JSONDecodeError:
            cache = {}
    if key in cache:
        return cache[key]

    api = (f"https://api.github.com/repos/{res['repo']}/commits"
           f"?path={urllib.parse.quote(res['rpath'], safe='')}&sha={res['ref']}&per_page=1")
    sha = ""
    try:
        import json as _json
        data = _json.loads(http_get(api, timeout=30).decode())
        if isinstance(data, list) and data:
            sha = data[0]["sha"][:12]
    except Exception as e:  # 配额/网络问题不该中断整批抓取
        print(f"    (commit 查询跳过 {res['rpath']}: {e})", file=sys.stderr)
    cache[key] = sha
    try:
        cache_file.write_text(json.dumps(cache, ensure_ascii=False, indent=1),
                              encoding="utf-8")
    except OSError:
        pass
    return sha


# ─────────────────────────────────────────────────────────────────────────────
# HTML -> Markdown
#
# Hysteria 官方站是 VitePress + Pygments，直接丢给 pandoc 会坏两处：
#   1. 代码块被 Pygments 的 <span>/<a> 逐行切碎，pandoc 当成缩进段落 -> 围栏和语言标记全丢；
#      tabbed-set 的标签还会和正文粘成 "ACMEOwn certificate" 这种一行。
#   2. 邮箱被 Cloudflare 换成 <a class="__cf_email__" data-cfemail="…">，
#      模板里的 email 直接变成 "[email protected]"，照抄就废了。
# 先把这两类结构还原，再交给 pandoc 处理正文。
# ─────────────────────────────────────────────────────────────────────────────

def _decode_cf_email(html: str) -> str:
    """还原 Cloudflare 邮件保护：data-cfemail 是 hex(首字节=key) + 逐字节异或。

    必须整体替换 <a>…</a>（含方括号占位文字），只换 data-cfemail 属性会留下 "[email protected]"。
    """
    pat = re.compile(
        r'<a[^>]*data-cfemail="([0-9a-fA-F]+)"[^>]*>\s*\[email[^\]]*\]\s*</a>', re.S
    )

    def repl(m: re.Match) -> str:
        raw = m.group(1)
        try:
            key = int(raw[:2], 16)
            return "".join(chr(int(raw[i:i + 2], 16) ^ key)
                           for i in range(2, len(raw), 2))
        except ValueError:
            return m.group(0)

    return pat.sub(repl, html)


def _code_blocks_to_pre(html: str) -> str:
    """把 Pygments 的 <div class="language-x highlight"><pre>…</pre></div>
    还原成 <pre><code class="language-x">纯文本</code></pre>。"""
    pat = re.compile(
        r'<div class="language-([\w+-]+)[^"]*">\s*<pre[^>]*>(.*?)</pre>\s*</div>',
        re.S,
    )

    def repl(m: re.Match) -> str:
        lang, inner = m.group(1), m.group(2)
        # 丢掉行号锚点（空 <a>）和高亮用的 <span>，只留文本；空白必须原样保留
        inner = re.sub(r'<a[^>]*id="__codelineno[^"]*"[^>]*>\s*</a>', "", inner)
        text = html_mod.unescape(re.sub(r"<[^>]+>", "", inner))
        text = text.strip("\n").rstrip()
        return (f'\n\n<pre><code class="language-{lang}">'
                f"{html_mod.escape(text, quote=False)}</code></pre>\n\n")

    return pat.sub(repl, html)


def _flatten_tabs(html: str) -> str:
    """tabbed-set -> 依次输出「标签 + 代码块」，避免标签文字和正文粘连。"""
    pat = re.compile(
        r'<div class="tabbed-set[^"]*"[^>]*>(.*?)<div class="tabbed-content">(.*?)'
        r'(?=<div class="tabbed-set|</article>)',
        re.S,
    )

    def repl(m: re.Match) -> str:
        head, content = m.group(1), m.group(2)
        labels = re.findall(r"<label[^>]*>(.*?)</label>", head, re.S)
        labels = [re.sub(r"<[^>]+>", "", x).strip() for x in labels]
        blocks = re.findall(
            r'<div class="tabbed-block">(.*?)(?=<div class="tabbed-block">|$)', content, re.S
        )
        out = []
        for i, b in enumerate(blocks):
            name = labels[i] if i < len(labels) else f"方案 {i + 1}"
            out.append(f"\n\n<p><strong>{html_mod.escape(name)}</strong></p>\n\n{b.strip()}\n")
        return "".join(out) if out else content

    return pat.sub(repl, html)


def html_to_md(html: str, source_url: str) -> str:
    """抽出 <article> 正文 -> 还原代码块/标签页/邮箱 -> pandoc 转 Markdown。"""
    m = re.search(r"<article[^>]*>(.*?)</article>", html, re.S)
    body = m.group(1) if m else html

    body = re.sub(r"<button[^>]*>.*?</button>", "", body, flags=re.S)
    body = re.sub(r'<a[^>]*class="[^"]*header-anchor[^"]*"[^>]*>.*?</a>', "", body, flags=re.S)
    body = re.sub(r"<input[^>]*/?>", "", body)          # tabbed-set 的 radio
    body = re.sub(r'<div class="tabbed-labels">.*?</div>', "", body, flags=re.S)

    body = _decode_cf_email(body)      # 必须在剥 <pre> 之前，否则 data-cfemail 已被丢掉
    body = _code_blocks_to_pre(body)
    body = _flatten_tabs(body)
    # 还原后残留的容器标签（不碰 pre/code/span/a）
    body = re.sub(r"</?(div|section|label|form)\b[^>]*>", "\n", body)

    r = subprocess.run(
        ["pandoc", "-f", "html", "-t", "gfm", "--wrap=none"],
        input=body, capture_output=True, text=True, check=True,
    )
    md = re.sub(r"\n{3,}", "\n\n", r.stdout).strip()
    header = (f"<!-- 原文: {source_url} -->\n"
              f"<!-- 由 fetch_references.py 从官方渲染页抽取正文并转为 Markdown；\n"
              f"     代码块已还原为围栏代码块，Cloudflare 隐藏的邮箱已解码。 -->\n\n")
    return header + md


# ─────────────────────────────────────────────────────────────────────────────
# 抓取主流程
# ─────────────────────────────────────────────────────────────────────────────

def fetch_one(res: dict, today: str) -> dict:
    dest = OUT / res["path"]
    dest.parent.mkdir(parents=True, exist_ok=True)
    url = resolve_url(res)
    commit = head_commit(res)

    raw = http_get(url)
    if res["kind"] == "html":
        text = html_to_md(raw.decode("utf-8", "replace"), url)
        data = text.encode("utf-8")
        mode = "HTML→MD"
    else:
        data = raw
        mode = "raw"

    dest.write_bytes(data)
    return dict(
        path=res["path"], title=res["title"], used_in=res["used_in"],
        url=url, commit=commit, size=len(data), mode=mode,
        sha256=hashlib.sha256(data).hexdigest(), date=today,
    )


def human_size(n: int) -> str:
    """小于 1 KB 时保留一位小数，否则会显示成 '0 KB' 让人以为抓空了。"""
    return f"{n / 1024:.1f} KB" if n < 1024 else f"{n / 1024:.0f} KB"


def write_index(records: list[dict]) -> None:
    by_group: dict[str, list[dict]] = {}
    for r in records:
        by_group.setdefault(r["path"].split("/")[0], []).append(r)

    group_names = {
        "hysteria": "Hysteria 2 官方文档",
        "sing-box": "sing-box 官方文档（含官方中文版）",
        "xray": "Xray / REALITY 官方文档",
        "examples": "Xray 官方示例配置（可直接复制）",
        "mihomo": "Mihomo（Clash.Meta 内核）",
        "v2rayN": "v2rayN（Windows 客户端）",
        "scripts": "教程中被直接执行的官方脚本",
    }

    L: list[str] = []
    L.append("# references/ —— 官方一手资料存档\n")
    L.append("本目录由 `fetch_references.py` 自动抓取，内容是《VLESS + Hysteria2 "
             "自建节点部署指南》引用的**官方原文**，用于离线查阅与直接复制配置。\n")
    L.append(f"- 抓取日期：{records[0]['date']}")
    L.append(f"- 文件数：{len(records)}")
    L.append("- 完整校验值见 [`MANIFEST.json`](MANIFEST.json)（SHA256 + 字节数），"
             "或运行 `python3 fetch_references.py --verify`\n")
    L.append("> ⚠️ 上游文档会更新。本目录是**快照**，不是镜像；"
             "要最新内容请以表中 URL 为准。表里的 `commit` 是抓取时该文件的上游 commit，"
             "可以直接拿来对比差异。\n")
    L.append("> 许可证：各文件版权归原作者/原项目所有，本目录仅作学习存档。"
             "Xray/REALITY 为 MPL-2.0，Hysteria/sing-box 为 GPL-3.0，"
             "转载或再分发请遵循各自许可证。\n")

    L.append("## 目录\n")
    for g, rs in by_group.items():
        L.append(f"### {group_names.get(g, g)}（{len(rs)} 个）\n")
        L.append("| 文件 | 内容 | 指南中对应章节 | 大小 | SHA256（前 12） |")
        L.append("|---|---|---|---|---|")
        for r in rs:
            L.append(f"| [`{r['path']}`]({r['path']}) | {r['title']} | "
                     f"{r['used_in']} | {human_size(r['size'])} | "
                     f"`{r['sha256'][:12]}` |")
        L.append("")
        L.append("<details><summary>来源 URL 与 commit</summary>\n")
        for r in rs:
            c = f" &nbsp;·&nbsp; commit `{r['commit']}`" if r["commit"] else ""
            L.append(f"- `{r['path']}` ← <{r['url']}>{c}")
        L.append("\n</details>\n")

    L.append("---\n")
    L.append("## 怎么用这些文件\n")
    L.append("```bash")
    L.append("# 校验本地文件与抓取时一致（防篡改 / 防手动改坏）")
    L.append("python3 fetch_references.py --verify")
    L.append("")
    L.append("# 重新抓取全部（上游更新后）")
    L.append("python3 fetch_references.py")
    L.append("")
    L.append("# 直接看某份原文")
    L.append("less references/sing-box/tls.zh.md")
    L.append("```\n")
    L.append("**复制配置时注意**：官方示例里的 `id` / `password` / `privateKey` / "
             "`shortId` 是公开示例值，**必须换成你自己生成的**，否则等于没加密。")

    (OUT / "MANIFEST.json").write_text(
        json.dumps(
            {"fetched": records[0]["date"], "generator": "fetch_references.py",
             "files": records},
            ensure_ascii=False, indent=1,
        ) + "\n",
        encoding="utf-8",
    )
    (OUT / "INDEX.md").write_text("\n".join(L) + "\n", encoding="utf-8")


def verify() -> int:
    manifest_path = OUT / "MANIFEST.json"
    if not manifest_path.is_file():
        sys.exit("没有 references/MANIFEST.json，请先跑一次抓取")
    manifest = json.loads(manifest_path.read_text(encoding="utf-8"))
    records = manifest["files"]
    bad = 0
    for r in records:
        f = OUT / r["path"]
        if not f.is_file():
            print(f"  ✗ 缺失    {r['path']}")
            bad += 1
            continue
        data = f.read_bytes()
        got = hashlib.sha256(data).hexdigest()
        if got != r["sha256"]:
            print(f"  ✗ 不一致  {r['path']}  ({len(data)} != {r['size']} 字节)")
            bad += 1
        elif len(data) != r["size"]:
            print(f"  ✗ 大小不符 {r['path']}")
            bad += 1
        else:
            print(f"  ✓ {r['path']}")
    print(f"\n  {len(records) - bad}/{len(records)} 个文件与抓取时完全一致"
          f"（SHA256 + 字节数）")
    if bad:
        print("  有文件被改动或删除。重跑 `python3 fetch_references.py` 可恢复官方原文。")
    return 1 if bad else 0


def main() -> None:
    ap = argparse.ArgumentParser()
    ap.add_argument("--verify", action="store_true", help="只校验本地文件 SHA256")
    args = ap.parse_args()

    if args.verify:
        sys.exit(verify())

    today = _dt.date.today().isoformat()
    OUT.mkdir(exist_ok=True)
    print(f"抓取 {len(RESOURCES)} 份官方资料 -> {OUT}/\n")

    records, failed = [], []
    for i, res in enumerate(RESOURCES, 1):
        tag = f"[{i:2}/{len(RESOURCES)}] {res['path']}"
        try:
            r = fetch_one(res, today)
            records.append(r)
            c = f" @{r['commit']}" if r["commit"] else ""
            print(f"  ✓ {tag}  {human_size(r['size'])}  {r['mode']}{c}")
        except Exception as e:  # 单个资源失败不该中断整批
            failed.append((res["path"], e))
            print(f"  ✗ {tag}  {type(e).__name__}: {e}")

    if records:
        write_index(records)
        print(f"\n  索引: {OUT / 'INDEX.md'}")
    if failed:
        print(f"\n  {len(failed)} 个失败:")
        for p, e in failed:
            print(f"    {p}: {e}")
        sys.exit(1)
    print(f"  全部 {len(records)} 份抓取成功")


if __name__ == "__main__":
    main()
