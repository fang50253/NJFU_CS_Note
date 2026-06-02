"""
phylogeny.py

使用 IQ-TREE 构建系统发育树
"""

import os
from config import *
from utils.cmd import run_command


def build_tree():

    alignment = os.path.join(ALIGN_DIR, "alignment.fasta")

    cmd = f"""
    {IQTREE} \
    -s {alignment} \
    -m MFP \
    -bb 1000 \
    -nt AUTO
    """

    run_command(cmd)