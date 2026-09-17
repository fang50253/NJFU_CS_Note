"""
assembly.py

使用 GetOrganelle 进行叶绿体组装
"""

# import os
# from config import *
# from utils.cmd import run_command


# def run_assembly(sample):

#     read1 = os.path.join(QC_DIR, f"{sample}_clean_1.fastq")
#     read2 = os.path.join(QC_DIR, f"{sample}_clean_2.fastq")

#     outdir = os.path.join(ASSEMBLY_DIR, sample)

#     os.makedirs(outdir, exist_ok=True)

#     cmd = f"""
#     {GETORGANELLE} \
#     -1 {read1} \
#     -2 {read2} \
#     -o {outdir} \
#     -F embplant_pt \
#     -R 10 \
#     -k 21,45,65,85,105
#     """

#     run_command(cmd)

"""
使用 GetOrganelle 进行叶绿体组装
"""

import os
import time
from config import *
from utils.cmd import run_command


# def run_assembly(sample):
#     read1 = os.path.join(QC_DIR, f"{sample}_clean_1.fastq")
#     read2 = os.path.join(QC_DIR, f"{sample}_clean_2.fastq")
#     outdir = os.path.join(ASSEMBLY_DIR, sample)
    
#     # 检查输入文件
#     if not os.path.exists(read1):
#         print(f"Warning: {read1} not found, skipping {sample}")
#         return
    
#     os.makedirs(outdir, exist_ok=True)
    
#     # 检查是否已经完成
#     expected_output = os.path.join(outdir, "path_1.fasta")
#     if os.path.exists(expected_output):
#         print(f"Assembly for {sample} already exists, skipping")
#         return
    
#     cmd = f"""
#     {GETORGANELLE} \
#     -1 {read1} \
#     -2 {read2} \
#     -o {outdir} \
#     -F embplant_pt \
#     -R 10 \
#     -k 21,45,65,85,105 \
#     --max-reads 1000000 \
#     --overwrite
#     """
    
#     # 运行命令（这会等待完成）
#     print(f"\n=== Assembling {sample} ===")
#     start_time = time.time()
#     run_command(cmd)
#     end_time = time.time()
    
#     # 验证输出
#     if os.path.exists(expected_output):
#         print(f"✓ {sample} assembly completed in {end_time - start_time:.2f} seconds")
#     else:
#         print(f"✗ {sample} assembly failed: output not found")
#         raise RuntimeError(f"Assembly failed for {sample}")
    
def run_assembly(sample):
    read1 = os.path.join(QC_DIR, f"{sample}_clean_1.fastq")
    read2 = os.path.join(QC_DIR, f"{sample}_clean_2.fastq")
    outdir = os.path.join(ASSEMBLY_DIR, sample)
    
    # 检查输入文件
    if not os.path.exists(read1):
        print(f"Warning: {read1} not found, skipping {sample}")
        return
    
    os.makedirs(outdir, exist_ok=True)
    
    # 检查是否已经完成（检查多种可能的输出文件）
    possible_outputs = [
        os.path.join(outdir, "path_1.fasta"),
        os.path.join(outdir, "embplant_pt.K105.complete.graph1.1.path_sequence.fasta"),
        os.path.join(outdir, "embplant_pt.K105.complete.graph1.2.path_sequence.fasta"),
        os.path.join(outdir, "embplant_pt.K105.scaffolds.graph1.1.path_sequence.fasta"),  # 新增：scaffold 输出
        os.path.join(outdir, "embplant_pt.K105.scaffolds.graph1.2.path_sequence.fasta"),  # 新增：scaffold 输出
        os.path.join(outdir, "embplant_pt.fasta")
    ]
    
    already_done = any(os.path.exists(f) for f in possible_outputs)
    if already_done:
        print(f"Assembly for {sample} already exists, skipping")
        return
    
    cmd = f"""
    {GETORGANELLE} \
    -1 {read1} \
    -2 {read2} \
    -o {outdir} \
    -F embplant_pt \
    -R 10 \
    -k 21,45,65,85,105 \
    --max-reads 1000000 \
    --overwrite
    """
    
    # 运行命令
    print(f"\n=== Assembling {sample} ===")
    start_time = time.time()
    run_command(cmd)
    end_time = time.time()
    
    # 验证输出（检查多种可能的文件名）
    found_output = None
    for output in possible_outputs:
        if os.path.exists(output):
            found_output = output
            break
    
    if found_output:
        print(f"✓ {sample} assembly completed in {end_time - start_time:.2f} seconds")
        print(f"  Output: {found_output}")
        
        # 创建一个标准命名的软链接供后续步骤使用
        standard_name = os.path.join(outdir, "path_1.fasta")
        if not os.path.exists(standard_name) and found_output != standard_name:
            # 如果软链接不存在，创建它
            os.symlink(os.path.basename(found_output), standard_name)
            print(f"  Created symlink: {standard_name}")
    else:
        print(f"✗ {sample} assembly failed: output not found")
        print(f"  Directory contents: {os.listdir(outdir)[:10]}")
        raise RuntimeError(f"Assembly failed for {sample}")