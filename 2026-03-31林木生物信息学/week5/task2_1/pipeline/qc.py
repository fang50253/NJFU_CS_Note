"""
qc.py

使用 fastp 进行 reads 质量控制
"""

import os
from config import *
from utils.cmd import run_command


def run_qc(sample):
    """
    对单个样本进行质控
    """

    input1 = os.path.join(DATA_DIR, f"{sample}_1.fastq")
    input2 = os.path.join(DATA_DIR, f"{sample}_2.fastq")

    out1 = os.path.join(QC_DIR, f"{sample}_clean_1.fastq")
    out2 = os.path.join(QC_DIR, f"{sample}_clean_2.fastq")

    html = os.path.join(QC_DIR, f"{sample}.html")

    cmd = f"""
    {FASTP} \
    -i {input1} \
    -I {input2} \
    -o {out1} \
    -O {out2} \
    -h {html}
    """

    run_command(cmd)