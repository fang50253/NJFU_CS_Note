"""
config.py

存放整个流程的配置参数
"""

import os

# ===============================
# 基础路径
# ===============================

BASE_DIR = os.path.dirname(os.path.abspath(__file__))

DATA_DIR = os.path.join(BASE_DIR, "data")
RESULT_DIR = os.path.join(BASE_DIR, "results")

QC_DIR = os.path.join(RESULT_DIR, "qc")
ASSEMBLY_DIR = os.path.join(RESULT_DIR, "assembly")
ANNOTATION_DIR = os.path.join(RESULT_DIR, "annotation")
ALIGN_DIR = os.path.join(RESULT_DIR, "alignment")
TREE_DIR = os.path.join(RESULT_DIR, "tree")

LOG_DIR = os.path.join(BASE_DIR, "logs")

# ===============================
# 软件路径（根据自己环境修改）
# ===============================

FASTP = "fastp"
GETORGANELLE = "get_organelle_from_reads.py"
MAFFT = "mafft"
IQTREE = "iqtree2"

# ===============================
# 样本列表
# ===============================

SAMPLES = [
    "SRR13324544",
    "SRR13324572",
    "SRR7341535",
    "SRR12893418",
    "SRR35181806",
    "SRR10197854",
    "SRR14460963"
]