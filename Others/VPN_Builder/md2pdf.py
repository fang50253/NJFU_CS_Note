#!/usr/bin/env python3
"""
md2pdf.py — 把中文 Markdown 技术文档转成 PDF（macOS / pandoc + xelatex 链路）

用法:
    python3 md2pdf.py <输入.md> [-o 输出.pdf]

解决三个实际问题:
  1. 中文字体    —— 用 Hiragino Sans GB 作 CJK 字体，避免默认字体缺字变方块
  2. emoji/符号 —— ✅❌⚠ 等在 LaTeX 里没有字形，会静默丢失；先替换成字体确实有的字符
  3. 表格溢出    —— pandoc 默认把表格列输出成 l（不换行），5 列表会直接冲出纸面；
                    这里按各列内容长度重新分配 p{} 宽度

依赖: pandoc, xelatex, fontspec, xeCJK, fvextra, longtable, booktabs
"""

from __future__ import annotations

import argparse
import re
import shutil
import subprocess
import sys
import tempfile
import unicodedata
from pathlib import Path

# ─────────────────────────────────────────────────────────────────────────────
# 1. 字符替换：目标字体（Arial Unicode MS）确实含有替换后的字符
# ─────────────────────────────────────────────────────────────────────────────

# emoji 在 LaTeX 中无字形，且多由多个码位组成（含 U+FE0F 变体选择符），逐个映射
EMOJI_MAP = {
    "✅": "✓",   # WHITE HEAVY CHECK MARK      -> CHECK MARK
    "❌": "✗",   # CROSS MARK                   -> BALLOT X
    "⚠": "▲",   # WARNING SIGN                 -> BLACK UP-POINTING TRIANGLE
    "❗": "!",   # HEAVY EXCLAMATION            -> ASCII
    "ℹ": "i",           # INFORMATION SOURCE
    "①": "(1)", "②": "(2)", "③": "(3)", "④": "(4)",
    "🇨🇳": "",          # 国旗（区域指示符，两码位）
    "🎯": "", "💡": "", "🔑": "", "🔴": "",
}
# 变体选择符 / 零宽字符：必须单独清掉，否则会变成不可见空隙
INVISIBLE = dict.fromkeys(
    [0xFE0E, 0xFE0F, 0x200B, 0x200C, 0x200D, 0x2060, 0xFEFF], None
)


def sanitize(text: str) -> tuple[str, int]:
    """替换 emoji / 清掉零宽字符。返回 (清洗后文本, 替换次数)。"""
    n = 0
    for src, dst in EMOJI_MAP.items():
        c = text.count(src)
        if c:
            text = text.replace(src, dst)
            n += c
    text = text.translate(INVISIBLE)
    return text, n


# ─────────────────────────────────────────────────────────────────────────────
# 2. LaTeX 模板
# ─────────────────────────────────────────────────────────────────────────────

PREAMBLE = r"""
%% ---- 字体 ----
\usepackage{fontspec}
\usepackage{xeCJK}
\setmainfont{Arial Unicode MS}      % 正文字体：覆盖面广，含箭头/框线/✓✗/▲
\setmonofont{Menlo}                % 等宽：代码块用，含 ─│┌┐└┘
\setCJKmainfont{Hiragino Sans GB}  % 中文字体
\setCJKmonofont{Hiragino Sans GB}  % 代码块里的中文
\setCJKsansfont{Hiragino Sans GB}
\newfontfamily{\cjkfont}{Hiragino Sans GB}
\XeTeXlinebreaklocale "zh"
\XeTeXlinebreakskip = 0pt plus 1pt minus 0.1pt  % 允许在 CJK 字符间断行

%% ---- 页面 ----
\usepackage[a4paper,top=20mm,bottom=20mm,left=18mm,right=18mm]{geometry}

%% ---- 表格 ----
\usepackage{longtable,booktabs,array}
\setlength{\LTpre}{0.6\baselineskip}
\setlength{\LTpost}{0.8\baselineskip}
\newlength{\tblavail}   % 整表可用宽度，由 refit_tables 在每张表前赋值
\renewcommand{\arraystretch}{1.25}
\setlength{\tabcolsep}{4pt}

%% ---- 代码块 ----
\usepackage{fvextra}
\usepackage{xcolor}
\definecolor{codebg}{HTML}{F7F7F9}
\definecolor{codeborder}{HTML}{DDDDDD}
\DefineVerbatimEnvironment{Highlighting}{Verbatim}{fontsize=\small,baselinestretch=1.12,
  breaklines=true,breakanywhere=true,breaknonspaceingroup=true,
  commandchars=\\\{\},frame=none,fillcolor=codebg}
\fvset{listparameters={\setlength{\topsep}{0.3ex}\setlength{\partopsep}{0pt}}}
\setlength{\emergencystretch}{3em}   % 防止长行冲出边界

%% ---- 标题 ----
\usepackage{titlesec}
\titleformat{\section}{\Large\bfseries\cjkfont}{\thesection}{1em}{}
\titleformat{\subsection}{\large\bfseries\cjkfont}{\thesubsection}{1em}{}
\titleformat{\subsubsection}{\normalsize\bfseries\cjkfont}{\thesubsubsection}{1em}{}
\titlespacing*{\section}{0pt}{1.6ex plus .2ex}{0.8ex}
\titlespacing*{\subsection}{0pt}{1.3ex plus .2ex}{0.5ex}
\titlespacing*{\subsubsection}{0pt}{1.1ex plus .2ex}{0.4ex}

%% ---- 其它 ----
\usepackage{xurl}                 % 允许 URL 在任意字符间断行
\usepackage{footnotehyper}
\usepackage{bookmark}
\hypersetup{colorlinks=true,linkcolor=blue!45!black,urlcolor=blue!55!black}
\sloppy
\emergencystretch=3em
\setcounter{secnumdepth}{3}
\setcounter{tocdepth}{2}
\setlength{\parskip}{0.35em}
\renewcommand{\arraystretch}{1.25}

%% 行内代码里的长 token（密钥、base64、命令参数）没有空格可断，
%% 在窄表格列里会整段溢出，这里补断点
\let\oldtexttt\texttt
\renewcommand{\texttt}[1]{\oldtexttt{\seqsplitbreakable{#1}}}
\makeatletter
\newcommand{\seqsplitbreakable}[1]{%
  \begingroup
  \def\do##1{\ifx\relax##1\else\allowbreak##1\fi}%
  \seqsplit{\do}#1\relax
  \endgroup
}
\makeatother
\usepackage{seqsplit}
"""


def build_latex(md_text: str) -> tuple[str, int, int]:
    """跑 pandoc 生成 .tex，并对表格列宽、中文标题 ID 做后处理。"""
    import tempfile as _tf

    with _tf.NamedTemporaryFile("w", suffix=".md", delete=False, encoding="utf-8") as f:
        f.write(md_text)
        tmp_md = f.name

    raw_tex = Path(tmp_md).with_suffix(".raw.tex")
    try:
        subprocess.run(
            ["pandoc", tmp_md, "-f", "gfm+yaml_metadata_block", "-t", "latex",
             "--standalone", "--no-highlight" if False else "--highlight-style=tango",
             "-o", str(raw_tex)],
            check=True, capture_output=True, text=True,
        )
        tex = raw_tex.read_text(encoding="utf-8")
    finally:
        Path(tmp_md).unlink(missing_ok=True)
        raw_tex.unlink(missing_ok=True)

    tex, n_fixed = refit_tables(tex)
    tex, n_ids = shorten_cjk_ids(tex)
    tex = add_texttt_breaks(tex)
    tex = break_joined_identifiers(tex)
    tex = inject_preamble(tex, PREAMBLE)
    return tex, n_fixed, n_ids


def add_texttt_breaks(tex: str) -> str:
    """在 \\texttt{} 内的 . / - \\_ 后插入 \\allowbreak。

    窄表格列里 `\\texttt{obfs.salamander.password}`、
    `\\texttt{CAP\\_NET\\_ADMIN}` 是不可断的整体，会整段溢出列宽。
    allowbreak 只在确实排不下时才生效，正文宽处不会触发。
    """
    def fix(m: re.Match) -> str:
        inner = re.sub(r"([./_\-])", lambda g: g.group(1) + r"\allowbreak ", m.group(1))
        return r"\texttt{" + inner + "}"
    return re.sub(r"\\texttt\{([^{}]*)\}", fix, tex)


def break_joined_identifiers(tex: str) -> str:
    """在 VLESS+REALITY、TCP+UDP 这类拼接词中间的 `+` 后加断点。

    连续拉丁字母/数字之间没有天然断点，在窄列里会整段溢出。
    用 lambda 做替换：re.sub 的替换模板会把 `\a` 当成 BEL 转义，字符串会被吃掉。
    """
    return re.sub(r"(?<=[A-Za-z0-9])\+(?=[A-Za-z0-9])",
                  lambda m: r"+\allowbreak ", tex)


# ─────────────────────────────────────────────────────────────────────────────
# 3. 表格列宽：l/r/c -> p{}
# ─────────────────────────────────────────────────────────────────────────────

ROW_BORDER = (r"\toprule", r"\midrule", r"\bottomrule",
              r"\endhead", r"\endfirsthead", r"\endfoot", r"\endlastfoot")


def logical_rows(body: list[str]) -> list[str]:
    """把 pandoc 拆到多个物理行的表格行合并回一条逻辑行。

    pandoc 按 Markdown 源码的换行折行，一个逻辑行可能横跨 3~4 个物理行。
    若逐物理行 split_row，续行的文字会被算进第 1 列，导致首列宽度被严重高估
    （实测某 3 列表首列真实仅 5 字符，却被分配到 60% 表宽）。
    """
    rows: list[str] = []
    buf: list[str] = []
    for line in body:
        if line.startswith(ROW_BORDER) or not line.strip():
            continue
        buf.append(line)
        if line.rstrip().endswith(r"\\"):
            rows.append(" ".join(buf))
            buf = []
    if buf:
        rows.append(" ".join(buf))
    return rows


def refit_tables(tex: str) -> tuple[str, int]:
    """把 longtable 的 l/r/c 列改成按内容长度分配比例的 p{} 列。

    pandoc 对 GFM 管道表格输出 `@{}lll@{}`，列不换行 -> 长内容直接溢出纸面。
    这里按各列最长单元格估算权重，再转成 \\dimexpr 宽度。
    返回 (新 tex, 改写张数)。
    """
    lines = tex.split("\n")
    out: list[str] = []
    i = 0
    fixed = 0
    # 一张表：从 \begin{longtable} 到 \end{longtable}
    while i < len(lines):
        m = re.match(r"^(\\begin\{longtable\}\[\]\{)(@\{\})([lrcp]+)(@\{\})\}$", lines[i])
        if not m:
            out.append(lines[i])
            i += 1
            continue

        # 收集到 \end{longtable} 为止
        j = i
        while j < len(lines) and not lines[j].startswith(r"\end{longtable}"):
            j += 1
        body = lines[i + 1 : j]
        ncol = len(m.group(3))

        # 逐列最长可见文本长度（按逻辑行统计，不能逐物理行）
        rows = logical_rows(body)
        widths = []
        for c in range(ncol):
            best = 1
            for row in rows:
                cells = split_row(row, ncol)
                if c < len(cells):
                    best = max(best, visual_len(cells[c]))
            widths.append(min(best, 90))
        permille = allocate_permille(widths)
        colspec = "@{}" + "".join(
            rf"p{{\dimexpr\tblavail*{pm}/1000\relax}}" for pm in permille
        ) + "@{}"
        setunit = (
            rf"\setlength{{\tblavail}}{{\dimexpr\linewidth"
            rf"-{2 * (ncol - 1)}\tabcolsep\relax}}"
        )

        out.append(setunit)
        out.append(m.group(1) + colspec + "}")
        out.extend(body)
        out.append(r"\end{longtable}")
        fixed += 1
        i = j + 1
    return "\n".join(out), fixed


def allocate_permille(widths: list[int], floor: int = 90) -> list[int]:
    """把各列宽度份额换算成整数千分比，且总和恰好 1000。

    floor 是每列的最小千分比（默认 9%）。内容短但含 CJK 的列若被压到 1%，
    一个字都放不下必须硬溢出，所以先按比例分配，再把过窄列抬到 floor，
    差额按比例从其它列扣除。

    \\dimexpr 只接受整数因子，写 `*0.6` 会报 calc Error，因此用千分比整数
    `*600/1000`；最后用最大余数法凑整，避免各自四舍五入后总和变成 999/1001。
    """
    n = len(widths)
    total = sum(widths) or n
    pm = [w * 1000.0 / total for w in widths]

    for _ in range(n + 1):
        short = [i for i, v in enumerate(pm) if v < floor]
        if not short:
            break
        need = sum(floor - pm[i] for i in short)
        pm = [floor if i in short else v for i, v in enumerate(pm)]
        donors = [i for i, v in enumerate(pm) if v > floor]
        pool = sum(pm[i] for i in donors)
        if pool <= need:
            break
        for i in donors:
            pm[i] -= need * pm[i] / pool

    out = [int(v) for v in pm]
    while sum(out) > 1000:
        out[max(range(n), key=lambda i: out[i])] -= 1
    rem = 1000 - sum(out)
    order = sorted(range(n), key=lambda i: pm[i] - out[i], reverse=True)
    for k in range(rem):
        out[order[k % n]] += 1
    return out


def split_row(row: str, ncol: int) -> list[str]:
    """把 longtable 的一行拆成 ncol 个单元格（尊重 {} 分组）。"""
    if ncol == 1:
        return [row]
    cells, depth, cur = [], 0, []
    for ch in row:
        if ch == "{":
            depth += 1
        elif ch == "}":
            depth -= 1
        if ch == "&" and depth == 0:
            cells.append("".join(cur))
            cur = []
        else:
            cur.append(ch)
    cells.append("".join(cur))
    return cells


def visual_len(cell: str) -> int:
    """估算显示宽度：CJK 记 2，拉丁记 1，忽略命令与转义。"""
    cell = re.sub(r"\\[a-zA-Z@]+", "x", cell)
    cell = re.sub(r"[{}$&\\]", "", cell)
    cell = re.sub(r"\\\[.*?\\\]", "x", cell)
    w = 0
    for ch in cell:
        if unicodedata.east_asian_width(ch) in ("W", "F"):
            w += 2
        else:
            w += 1
    return w


# ─────────────────────────────────────────────────────────────────────────────
# 3.5 中文标题 ID -> 短 ASCII ID
#
# pandoc 把 CJK 标题 ID 按 UTF-8 逐字节转义后塞进 \label{} / \hyperref[]：
#     \hyperref[32-ssh-ux52a0ux56faux5148ux6d3bux4e0bux6765]{§3.2}
# 这串 39 字符在 p{} 列里没有任何断点，整格直接冲出纸面（实测超宽 582pt，
# 约两倍页宽），是 Overfull \hbox 的主因。改成 sec1/sec2… 即可。
# ─────────────────────────────────────────────────────────────────────────────

CJK_ID = re.compile(r"\b[0-9A-Za-z.\-]*ux[0-9a-fA-F]{4}[0-9A-Za-z.\-]*\b")


def shorten_cjk_ids(tex: str) -> int:
    mapping: dict[str, str] = {}

    def repl(m: re.Match) -> str:
        old = m.group(0)
        if old not in mapping:
            mapping[old] = f"sec{len(mapping) + 1}"
        return mapping[old]

    return CJK_ID.sub(repl, tex), len(mapping)


# ─────────────────────────────────────────────────────────────────────────────
# 4. 模板注入
# ─────────────────────────────────────────────────────────────────────────────

def inject_preamble(tex: str, preamble: str) -> str:
    m = re.search(r"^\\begin\{document\}$", tex, re.M)
    if not m:
        raise RuntimeError("pandoc 输出里找不到 \\begin{document}")
    head = tex[: m.start()]
    tail = tex[m.start():]

    # 去掉 pandoc 默认 preamble 里的重复 / 冲突包声明
    head = re.sub(r"\\usepackage\[[^\]]*\]\{longtable\}\n", "", head)
    head = re.sub(r"\\usepackage\[[^\]]*\]\{booktabs\}\n", "", head)
    head = re.sub(r"\\usepackage\[[^\]]*\]\{array\}\n", "", head)
    head = re.sub(r"\\usepackage\[[^\]]*\]\{graphicx\}\n", "", head)
    head = re.sub(r"\\usepackage\[[^\]]*\]\{xcolor\}\n", "", head)
    head = re.sub(r"\\usepackage\[[^\]]*\]\{hyperref\}\n", "", head)
    head = re.sub(r"\\usepackage\[[^\]]*\]\{geometry\}\n", "", head)
    head = re.sub(r"\\usepackage\[\documentclass\]\{hyperref\}\n", "", head)
    head = re.sub(r"\\usepackage\{amsmath,amssymb\}\n", "", head)
    head = re.sub(r"\\usepackage\{graphicx\}\n", "", head)
    head = re.sub(r"\\usepackage\{textcomp\}\n", "", head)
    head = re.sub(r"\\providecommand\)\[[^\]]*\]\{", "\\\\providecommand\\\\]{", head)
    # 清掉 pandoc 的 \tightlist 定义（我们自己重定义）
    head = re.sub(r"\\providecommand\{\\tightlist\}\{.*?\n\}\n", "", head, flags=re.S)

    return head + preamble + "\n" + tail


# ─────────────────────────────────────────────────────────────────────────────
# 5. 编译
# ─────────────────────────────────────────────────────────────────────────────

def compile_pdf(tex: str, out_pdf: Path, workdir: Path) -> None:
    texfile = workdir / "doc.tex"
    texfile.write_text(tex, encoding="utf-8")

    for pass_no in (1, 2):
        r = subprocess.run(
            ["xelatex", "-interaction=nonstopmode", "-halt-on-error",
             "-file-line-error", "doc.tex"],
            cwd=workdir, capture_output=True, text=True,
        )
        if pass_no == 1:
            log = (workdir / "doc.log").read_text(encoding="utf-8", errors="replace")
            missing = re.findall(r"Missing character: There is no (.*?) \(U\+([0-9A-F]+)\)", log)
            if missing:
                uniq = sorted({f"U+{cp} {ch}" for ch, cp in missing})
                print(f"  ⚠️  {len(missing)} 处缺字形 -> {', '.join(uniq[:12])}")
        if r.returncode != 0 or not (workdir / "doc.pdf").exists():
            log = (workdir / "doc.log").read_text(encoding="utf-8", errors="replace")
            errs = [l for l in log.split("\n") if re.search(r"^.*:[0-9]+: ", l)][:15]
            sys.stderr.write("xelatex 失败：\n" + "\n".join(errs) + "\n")
            sys.stderr.write(r.stdout[-2000:] + "\n")
            raise SystemExit(1)

    final = workdir / "doc.pdf"
    shutil.copyfile(final, out_pdf)


# ─────────────────────────────────────────────────────────────────────────────

def main() -> None:
    ap = argparse.ArgumentParser(description="中文 Markdown -> PDF")
    ap.add_argument("source", type=Path)
    ap.add_argument("-o", "--output", type=Path, default=None)
    args = ap.parse_args()

    if not args.source.is_file():
        sys.exit(f"找不到文件: {args.source}")
    for tool in ("pandoc", "xelatex"):
        if shutil.which(tool) is None:
            sys.exit(f"缺少依赖: {tool}")

    out = args.output or args.source.with_suffix(".pdf")

    raw = args.source.read_text(encoding="utf-8")
    cleaned, n_sub = sanitize(raw)
    print(f"  字符替换: {n_sub} 处 emoji -> ✓✗▲ 等")

    tex, n_tab, n_ids = build_latex(cleaned)
    print(f"  表格列宽重算: {n_tab} 张表")
    print(f"  中文标题 ID 缩短: {n_ids} 个")

    with tempfile.TemporaryDirectory() as td:
        compile_pdf(tex, out, Path(td))

    size = out.stat().st_size / 1024
    print(f"  ✓ 输出: {out}  ({size:.0f} KB)")


if __name__ == "__main__":
    main()
