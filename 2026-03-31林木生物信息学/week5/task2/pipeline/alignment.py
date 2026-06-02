"""
alignment.py

使用 MAFFT 进行多序列比对
"""

import os
from config import *
from utils.cmd import run_command


def run_alignment():

    input_fasta = os.path.join(ALIGN_DIR, "cp_genomes.fasta")

    output = os.path.join(ALIGN_DIR, "alignment.fasta")

    cmd = f"""
    {MAFFT} --auto {input_fasta} > {output}
    """

    run_command(cmd)