#!/usr/bin/env python3
"""下载教程正文涉及的软件二进制，并记录版本与校验值。

默认目标平台是教程正文所用的 Linux x86_64（VPS 端），外加 v2rayN 的
Windows 客户端包。下载后按各自格式解包到 downloads/<软件>/，并生成：

    downloads/README.md    版本、来源 URL、SHA256、安装位置
    downloads/SHA256SUMS   可直接 `sha256sum -c` 校验

Xray 官方提供 .dgst 签名摘要文件，脚本会拿它做交叉校验；其余项目官方未随
附件发布校验文件，因此这里只记录本地计算的 SHA256，供后续比对。

    python3 download_software.py
    python3 download_software.py --force          # 忽略本地缓存重新下载
    python3 download_software.py --only hysteria2 # 只下指定软件
"""

from __future__ import annotations

import argparse
import hashlib
import shutil
import sys
import tarfile
import urllib.error
import urllib.request
import zipfile
from dataclasses import dataclass, field
from pathlib import Path

HERE = Path(__file__).resolve().parent
OUTDIR = HERE / "downloads"
UA = "Mozilla/5.0 (compatible; NJFU-CS-Note-downloader/1.0)"
CHUNK = 1 << 16


@dataclass
class Software:
    slug: str
    name: str
    version: str
    url: str
    kind: str                      # zip / tar.gz / gz / raw
    platform: str
    binary: str = ""               # 解包后主程序名
    dgst_url: str = ""             # 官方校验文件
    note: str = ""
    files: list[str] = field(default_factory=list)


SOFTWARE = [
    Software(
        slug="xray-core",
        name="Xray-core",
        version="v26.3.27",
        url="https://github.com/XTLS/Xray-core/releases/download/"
            "v26.3.27/Xray-linux-64.zip",
        dgst_url="https://github.com/XTLS/Xray-core/releases/download/"
                 "v26.3.27/Xray-linux-64.zip.dgst",
        kind="zip",
        platform="linux/amd64",
        binary="xray",
        note="REALITY 服务端核心，含 geoip/geosite 数据文件",
    ),
    Software(
        slug="hysteria2",
        name="Hysteria 2",
        version="v2.8.2",
        url="https://github.com/apernet/hysteria/releases/download/"
            "app/v2.8.2/hysteria-linux-amd64",
        kind="raw",
        platform="linux/amd64",
        binary="hysteria",
        note="单文件静态二进制，chmod +x 后直接运行",
    ),
    Software(
        slug="sing-box",
        name="sing-box",
        version="v1.14.2",
        url="https://github.com/SagerNet/sing-box/releases/download/"
            "v1.14.2/sing-box-1.14.2-linux-amd64.tar.gz",
        kind="tar.gz",
        platform="linux/amd64",
        binary="sing-box",
        note="官方 GPG 公钥见 references/scripts/sing-box-gpg.key",
    ),
    Software(
        slug="mihomo",
        name="Mihomo",
        version="v1.19.31",
        url="https://github.com/MetaCubeX/mihomo/releases/download/"
            "v1.19.31/mihomo-linux-amd64-v1.19.31.gz",
        kind="gz",
        platform="linux/amd64",
        binary="mihomo",
        note="老 CPU 可改用同版本 mihomo-linux-amd64-compatible-*.gz",
    ),
    Software(
        slug="v2rayn",
        name="v2rayN",
        version="7.24.9",
        url="https://github.com/2dust/v2rayN/releases/download/"
            "7.24.9/v2rayN-windows-64.zip",
        kind="zip",
        platform="windows/amd64",
        binary="v2rayN.exe",
        note="墙内 Windows 客户端，内核已随包附带（7.24.9 起不再单发 With-Core 包）",
    ),
]


def sha256_of(path: Path) -> str:
    h = hashlib.sha256()
    with path.open("rb") as f:
        for chunk in iter(lambda: f.read(CHUNK), b""):
            h.update(chunk)
    return h.hexdigest()


def fetch(url: str, dest: Path) -> None:
    dest.parent.mkdir(parents=True, exist_ok=True)
    req = urllib.request.Request(url, headers={"User-Agent": UA})
    with urllib.request.urlopen(req, timeout=120) as r, dest.open("wb") as f:
        while chunk := r.read(CHUNK):
            f.write(chunk)


def official_sha256(url: str) -> str | None:
    """从 Xray 的 .dgst 里取 SHA2-256 做交叉校验。"""
    try:
        req = urllib.request.Request(url, headers={"User-Agent": UA})
        text = urllib.request.urlopen(req, timeout=60).read().decode("utf-8", "replace")
    except urllib.error.URLError:
        return None
    for line in text.splitlines():
        if line.upper().startswith("SHA2-256"):
            return line.split("=", 1)[1].strip().lower()
    return None


def unpack(soft: Software, archive: Path, workdir: Path) -> Path:
    """按格式解包，返回主程序所在目录。"""
    dest = OUTDIR / soft.slug
    if dest.exists():
        shutil.rmtree(dest)
    dest.mkdir(parents=True)

    if soft.kind == "zip":
        with zipfile.ZipFile(archive) as z:
            z.extractall(dest)
    elif soft.kind == "tar.gz":
        with tarfile.open(archive, "r:gz") as t:
            t.extractall(dest, filter="data")
    elif soft.kind == "gz":
        import gzip
        target = dest / (soft.binary or archive.stem)
        with gzip.open(archive, "rb") as src, target.open("wb") as out:
            shutil.copyfileobj(src, out, CHUNK)
    else:                                   # raw：单文件直接落位
        target = dest / (soft.binary or archive.name)
        shutil.copy2(archive, target)

    found = list(dest.rglob(soft.binary)) if soft.binary else []
    if found:
        found[0].chmod(0o755)
        return found[0].parent
    return dest


def process(soft: Software, force: bool) -> dict | None:
    archive = OUTDIR / "_archives" / Path(soft.url).name
    meta = OUTDIR / soft.slug / ".source.json"

    if archive.exists() and not force:
        print(f"  已有缓存 {archive.name}")
    else:
        print(f"  下载 {soft.name} {soft.version} …", flush=True)
        try:
            fetch(soft.url, archive)
        except urllib.error.URLError as e:
            print(f"    ✗ 下载失败: {e}", file=sys.stderr)
            return None

    digest = sha256_of(archive)
    size_mb = archive.stat().st_size / 1048576

    verified = ""
    if soft.dgst_url:
        expect = official_sha256(soft.dgst_url)
        if expect:
            verified = "官方 .dgst 一致" if expect == digest else "!! 与官方 .dgst 不符"
            if expect != digest:
                print(f"    ✗ {verified}", file=sys.stderr)
                return None
        else:
            verified = "未能取得官方 .dgst"

    bindir = unpack(soft, archive, OUTDIR)
    rel = bindir.relative_to(HERE)
    soft.files = sorted(
        str(p.relative_to(bindir)) for p in bindir.rglob("*") if p.is_file()
    )
    meta.write_text(
        f'{{"name": "{soft.name}", "version": "{soft.version}",\n'
        f' "url": "{soft.url}", "platform": "{soft.platform}",\n'
        f' "sha256": "{digest}", "verified": "{verified}"}}\n',
        encoding="utf-8",
    )
    print(f"    ✓ {size_mb:.1f} MB  {digest[:16]}…  {verified or '本地计算'}")
    return {
        "soft": soft, "sha256": digest, "size_mb": size_mb,
        "dir": rel, "verified": verified,
    }


def write_reports(results: list[dict]) -> None:
    sums = "".join(f"{r['sha256']}  _archives/{Path(r['soft'].url).name}\n"
                   for r in results)
    (OUTDIR / "SHA256SUMS").write_text(sums, encoding="utf-8")

    lines = [
        "# 教程涉及的软件离线包",
        "",
        f"由 `download_software.py` 生成于本机，共 {len(results)} 个。",
        "平台以教程正文的 Linux x86_64 VPS 为主，另附 Windows 客户端。",
        "",
        "| 软件 | 版本 | 平台 | 大小 | SHA256(前16) | 校验 |",
        "|------|------|------|------|--------------|------|",
    ]
    for r in results:
        s = r["soft"]
        lines.append(
            f"| [{s.name}]({s.slug}/) | `{s.version}` | `{s.platform}` "
            f"| {r['size_mb']:.1f} MB | `{r['sha256'][:16]}…` "
            f"| {r['verified'] or '本地计算'} |"
        )
    lines += ["", "## 明细", ""]
    for r in results:
        s = r["soft"]
        lines += [
            f"### {s.name} {s.version}",
            "",
            f"- 来源：<{s.url}>",
            f"- 平台：`{s.platform}`",
            f"- 原始包 SHA256：`{r['sha256']}`",
            f"- 校验方式：{r['verified'] or '官方未随附件发布校验文件，此处为本地计算值'}",
            f"- 解包位置：`{r['dir']}/`",
        ]
        if s.binary:
            lines.append(f"- 主程序：`{r['dir']}/{s.binary}`")
        if s.note:
            lines.append(f"- 说明：{s.note}")
        lines += ["", "包含文件：", ""]
        lines += [f"    - `{f}`" for f in s.files]
        lines.append("")
    lines += [
        "## 重新下载 / 校验",
        "",
        "```bash",
        "python3 download_software.py --force   # 重新下载",
        "cd downloads && shasum -a 256 -c SHA256SUMS   # 校验原始包",
        "```",
        "",
    ]
    (OUTDIR / "README.md").write_text("\n".join(lines), encoding="utf-8")


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--force", action="store_true", help="忽略本地缓存重新下载")
    ap.add_argument("--only", action="append", default=[],
                    help="只处理指定 slug（可重复）")
    args = ap.parse_args()

    targets = [s for s in SOFTWARE if not args.only or s.slug in args.only]
    if not targets:
        print(f"没有匹配的软件，可选: "
              f"{', '.join(s.slug for s in SOFTWARE)}", file=sys.stderr)
        return 1

    OUTDIR.mkdir(exist_ok=True)
    results = []
    for soft in targets:
        print(f"{soft.name} {soft.version}")
        r = process(soft, args.force)
        if r:
            results.append(r)

    if results and len(results) == len(targets):
        write_reports(results)
        print(f"\n✓ {len(results)} 个软件就绪 -> {OUTDIR}/")
        print("  报告: downloads/README.md, downloads/SHA256SUMS")
        return 0
    print(f"\n部分失败：成功 {len(results)}/{len(targets)}", file=sys.stderr)
    return 1


if __name__ == "__main__":
    raise SystemExit(main())
