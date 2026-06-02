"""
assembly.py

使用 GetOrganelle 进行叶绿体组装
"""

import os
from config import *
from utils.cmd import run_command


def run_assembly(sample):

    read1 = os.path.join(QC_DIR, f"{sample}_clean_1.fastq")
    read2 = os.path.join(QC_DIR, f"{sample}_clean_2.fastq")

    outdir = os.path.join(ASSEMBLY_DIR, sample)

    os.makedirs(outdir, exist_ok=True)

    cmd = f"""
    {GETORGANELLE} \
    -1 {read1} \
    -2 {read2} \
    -o {outdir} \
    -F embplant_pt \
    -R 10 \
    -k 21,45,65,85,105
    """

    run_command(cmd)