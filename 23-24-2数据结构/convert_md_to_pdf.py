#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""将 数据结构笔记.md 转换为 PDF。
流程：
  1. 读取原 markdown，修正不标准的公式定界符 [\] -> $$，保存为 _modify.md
  2. 用 Python markdown 库转成 HTML
  3. 用 KaTeX 渲染公式
  4. 用系统 Chrome headless 打印成 PDF
"""
import os
import re
import subprocess
import tempfile
import markdown
from pathlib import Path

BASE_DIR = Path("/Users/fang50253/Desktop/Files/Documents/NJFU_My_Github/NJFU_CS_Note/23-24-2数据结构")
SRC = BASE_DIR / "数据结构笔记.md"
MOD = BASE_DIR / "数据结构笔记_modify.md"
OUT = BASE_DIR / "数据结构笔记.pdf"

CHROME = "/Applications/Google Chrome.app/Contents/MacOS/Google Chrome"

# 1. 读取并修正公式定界符
content = SRC.read_text(encoding="utf-8")

# 将 \[ ... \] 块级公式替换为 $$ ... $$（多行可能）
content = re.sub(r"\\\[(.*?)\\\]", r"$$\1$$", content, flags=re.S)

MOD.write_text(content, encoding="utf-8")
print("已保存修正后的文件:", MOD)

# 2. markdown -> HTML
html_body = markdown.markdown(content, extensions=["extra", "tables", "fenced_code", "toc"])

# 3. 组装完整 HTML（含 KaTeX 渲染）
html = f"""<!DOCTYPE html>
<html lang="zh-CN">
<head>
<meta charset="utf-8">
<link rel="stylesheet"
  href="https://cdn.jsdelivr.net/npm/katex@0.16.9/dist/katex.min.css">
<script defer
  src="https://cdn.jsdelivr.net/npm/katex@0.16.9/dist/katex.min.js"></script>
<script defer
  src="https://cdn.jsdelivr.net/npm/katex@0.16.9/dist/contrib/auto-render.min.js"
  onload="renderMath()"></script>
<script>
function renderMath(){{
  renderMathInElement(document.body, {{
    delimiters: [
      {{left: '$$', right: '$$', display: true}},
      {{left: '$', right: '$', display: false}}
    ],
    throwOnError: false
  }});
}}
</script>
<style>
  body {{ font-family: -apple-system, "PingFang SC", "Microsoft YaHei", sans-serif;
          font-size: 12px; line-height: 1.6; color: #222; }}
  h1 {{ font-size: 22px; border-bottom: 2px solid #333; padding-bottom: 5px; }}
  h2 {{ font-size: 18px; border-bottom: 1px solid #999; padding-bottom: 3px; }}
  h3 {{ font-size: 15px; }}
  table {{ border-collapse: collapse; }}
  table, th, td {{ border: 1px solid #aaa; }}
  th, td {{ padding: 4px 8px; }}
  pre {{ background: #f5f5f5; padding: 8px; border-radius: 4px; }}
  code {{ background: #f0f0f0; padding: 1px 4px; border-radius: 3px; }}
  img {{ max-width: 100%; }}
  .katex {{ font-size: 1.05em; }}
</style>
</head>
<body>
{html_body}
</body>
</html>
"""

html_path = BASE_DIR / "数据结构笔记.html"
html_path.write_text(html, encoding="utf-8")
print("已生成 HTML:", html_path)

# 4. Chrome headless -> PDF
# 等待 KaTeX 渲染完成后再打印
cmd = [
    CHROME,
    "--headless",
    "--disable-gpu",
    "--no-sandbox",
    "--print-to-pdf=" + str(OUT),
    "--print-to-pdf-no-header",
    "--no-pdf-header-footer",
    "--virtual-time-budget=8000",
    "file://" + str(html_path),
]
print("正在用 Chrome 生成 PDF ...")
subprocess.run(cmd, check=True, timeout=120)

print("PDF 已生成:", OUT)
print("大小:", OUT.stat().st_size, "bytes")
