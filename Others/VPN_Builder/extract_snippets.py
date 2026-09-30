#!/usr/bin/env python3
"""把教程正文里的代码块抽成独立文件，并在正文中标注保存路径。

每个围栏代码块按「所属标题 + 序号」命名后写入 snippets/，围栏后面插入一行
指向该文件的说明，同时生成 snippets/INDEX.md 汇总表。

脚本是幂等的：再次运行会先清掉上一轮插入的标记行再重新插入，因此可以放心
在改动教程后重复执行。

    python3 extract_snippets.py
    python3 extract_snippets.py --check      # 只校验，不写文件
"""

from __future__ import annotations

import argparse
import re
import sys
from pathlib import Path

HERE = Path(__file__).resolve().parent
GUIDE = HERE / "VLESS-Hysteria2-自建节点部署指南.md"
OUTDIR = HERE / "snippets"

FENCE_RE = re.compile(r"^(?P<indent>\s{0,3})(?P<fence>`{3,}|~{3,})\s*(?P<lang>\S*)")
HEADING_RE = re.compile(r"^(?P<hashes>#{1,6})\s+(?P<text>.+?)\s*#*\s*$")

# 正文里由本脚本插入的两行，用来在重复运行时精确定位并整体清除
MARK_PREFIX = "<!-- snippet:"
MARK_REF_RE = re.compile(r"^>\s*代码已另存为\s*")

EXT_BY_LANG = {
    "bash": "sh", "sh": "sh", "shell": "sh", "console": "sh", "zsh": "sh",
    "yaml": "yaml", "yml": "yaml",
    "json": "json", "jsonc": "json",
    "ini": "ini", "conf": "conf", "toml": "toml",
    "text": "txt", "": "txt",
}

# 文件名里必须去掉，否则在 Windows / 各类归档格式下会出问题
UNSAFE_RE = re.compile(r'[\\/:*?"<>|\x00-\x1f]')
DASH_RE = re.compile(r"-{2,}")


def strip_existing(lines: list[str]) -> list[str]:
    """删掉上一轮插入的「空行 + 标记行 + 说明行」，让脚本可以重复执行。

    必须连同标记行前面那个空行一起删：inject() 每次会多写一个空行，只删标记和
    说明行的话空行会逐次累积，教程每跑一次就长 63 行。
    """
    out: list[str] = []
    skip_next_ref = False
    for line in lines:
        if skip_next_ref:
            skip_next_ref = False
            if MARK_REF_RE.match(line):
                continue
        if line.startswith(MARK_PREFIX):
            if out and not out[-1].strip():
                out.pop()
            skip_next_ref = True
            continue
        out.append(line)
    return out


def collapse_blank_runs(lines: list[str]) -> list[str]:
    """把围栏外连续的空行压成一个，顺便清掉历史版本遗留下的空行堆积。

    围栏内的空行属于代码内容，必须原样保留。
    """
    out: list[str] = []
    infence = False
    for line in lines:
        if FENCE_RE.match(line):
            infence = not infence
        if not infence and not line.strip() and out and not out[-1].strip():
            continue
        out.append(line)
    return out


def find_blocks(lines: list[str]) -> list[dict]:
    """扫描围栏代码块，并记录每块所属的最近一级标题。"""
    blocks: list[dict] = []
    heading = ""
    i = 0
    while i < len(lines):
        m = HEADING_RE.match(lines[i])
        if m:
            heading = m.group("text")
        f = FENCE_RE.match(lines[i])
        if not f:
            i += 1
            continue
        fence = f.group("fence")
        lang = f.group("lang").lower()
        start = i
        body: list[str] = []
        i += 1
        while i < len(lines):
            close = FENCE_RE.match(lines[i])
            # 结束围栏：同类符号、长度不短于开头、且后面没有语言标记
            if (close and close.group("fence")[0] == fence[0]
                    and len(close.group("fence")) >= len(fence)
                    and not close.group("lang")):
                break
            body.append(lines[i])
            i += 1
        blocks.append({
            "open": start,          # 围栏起始行下标
            "close": i,             # 围栏结束行下标
            "lang": lang,
            "heading": heading,
            "body": body,
        })
        i += 1
    return blocks


def slugify(text: str, fallback: str) -> str:
    """把标题转成文件名片段；中文保留，只清掉不安全的字符。"""
    s = UNSAFE_RE.sub(" ", text)
    s = re.sub(r"`+|\*+|\[|\]|\(|\)", " ", s)
    s = re.sub(r"\s+", "-", s.strip())
    s = DASH_RE.sub("-", s).strip("-.")
    if not s:
        return fallback
    return s[:48]


def build_name(block: dict, ordinal: int) -> str:
    ext = EXT_BY_LANG.get(block["lang"], "txt")
    slug = slugify(block["heading"], f"block-{ordinal:02d}")
    return f"{ordinal:02d}-{slug}.{ext}"


def write_snippets(blocks: list[dict], check: bool) -> list[dict]:
    """落盘每个代码块，返回索引条目。"""
    entries = []
    for ordinal, block in enumerate(blocks, 1):
        name = build_name(block, ordinal)
        body = "\n".join(block["body"]).strip("\n") + "\n"
        target = OUTDIR / name
        if not check:
            target.write_text(body, encoding="utf-8")
        entries.append({
            "name": name,
            "lang": block["lang"] or "text",
            "heading": block["heading"],
            "open": block["open"] + 1,   # 1-based，供 INDEX 定位
            "lines": len(block["body"]),
            "body": body,
        })
    return entries


def inject(lines: list[str], entries: list[dict]) -> list[str]:
    """在每个围栏结束后插入标记行与说明行。"""
    by_close = {e["open"]: e for e in entries}
    out: list[str] = []
    i = 0
    while i < len(lines):
        out.append(lines[i])
        f = FENCE_RE.match(lines[i])
        if f:
            fence = f.group("fence")
            j = i + 1
            while j < len(lines):
                close = FENCE_RE.match(lines[j])
                if (close and close.group("fence")[0] == fence[0]
                        and len(close.group("fence")) >= len(fence)
                        and not close.group("lang")):
                    break
                j += 1
            out.extend(lines[i + 1:j + 1])
            entry = by_close.get(i + 1)
            if entry:
                rel = f"snippets/{entry['name']}"
                out.append("")
                out.append(f"{MARK_PREFIX}{rel} -->")
                out.append(f"> 代码已另存为 [`{rel}`]({rel})"
                           f"（{entry['lines']} 行，{entry['lang']}）")
            i = j + 1
            continue
        i += 1
    return out


def write_index(entries: list[dict]) -> None:
    rows = ["| # | 文件 | 语言 | 行数 | 所属章节 |",
            "|---|------|------|------|----------|"]
    for n, e in enumerate(entries, 1):
        head = e["heading"].replace("|", "\\|") or "(无标题)"
        rows.append(f"| {n} | [`{e['name']}`]({e['name']}) | {e['lang']} "
                    f"| {e['lines']} | {head} |")
    body = (
        "# 正文代码块存档\n\n"
        f"本目录由 `extract_snippets.py` 自动生成，共 {len(entries)} 个文件，"
        "与 `../VLESS-Hysteria2-自建节点部署指南.md` 中的代码块一一对应。\n\n"
        "重新生成：\n\n```bash\npython3 extract_snippets.py\n```\n\n"
        + "\n".join(rows) + "\n"
    )
    (OUTDIR / "INDEX.md").write_text(body, encoding="utf-8")


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--check", action="store_true",
                    help="只统计不写文件")
    args = ap.parse_args()

    if not GUIDE.exists():
        print(f"找不到教程文件: {GUIDE}", file=sys.stderr)
        return 1

    raw = GUIDE.read_text(encoding="utf-8")
    lines = collapse_blank_runs(strip_existing(raw.split("\n")))
    blocks = find_blocks(lines)
    if not blocks:
        print("没有找到任何围栏代码块", file=sys.stderr)
        return 1

    OUTDIR.mkdir(exist_ok=True)
    entries = write_snippets(blocks, args.check)

    if not args.check:
        new_lines = inject(lines, entries)
        GUIDE.write_text("\n".join(new_lines), encoding="utf-8")
        write_index(entries)
        # 清理上一轮遗留、本轮不再对应的文件
        keep = {e["name"] for e in entries} | {"INDEX.md"}
        for old in OUTDIR.iterdir():
            if old.is_file() and old.name not in keep:
                old.unlink()

    by_lang: dict[str, int] = {}
    for e in entries:
        by_lang[e["lang"]] = by_lang.get(e["lang"], 0) + 1
    dist = ", ".join(f"{k}×{v}" for k, v in sorted(by_lang.items()))
    print(f"代码块 {len(entries)} 个 ({dist})")
    print(f"输出目录: {OUTDIR.name}/" + ("  (--check, 未写入)" if args.check else ""))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
