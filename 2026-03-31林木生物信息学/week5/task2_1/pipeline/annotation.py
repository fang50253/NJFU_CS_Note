"""
annotation.py

这里提供自动化框架
实际注释建议使用 GeSeq
"""

import os
from config import *
from utils.logger import logger


def annotate(sample):

    fasta = os.path.join(
        ASSEMBLY_DIR,
        sample,
        "final_assembly.fasta"
    )

    if not os.path.exists(fasta):
        logger.warning(f"{sample} assembly not found")
        return

    logger.info(f"{sample} ready for annotation (upload to GeSeq)")