"""
alignment.py

使用 MAFFT 进行多序列比对
"""

# import os
# from config import *
# from utils.cmd import run_command


# def run_alignment():

#     input_fasta = os.path.join(ALIGN_DIR, "cp_genomes.fasta")

#     output = os.path.join(ALIGN_DIR, "alignment.fasta")

#     cmd = f"""
#     {MAFFT} --auto {input_fasta} > {output}
#     """

#     run_command(cmd)

"""
alignment.py

使用 MAFFT 进行多序列比对
"""

import os
from config import *
from utils.cmd import run_command


def run_alignment():

    # 确保输出目录存在
    os.makedirs(ALIGN_DIR, exist_ok=True)
    
    input_fasta = os.path.join(ALIGN_DIR, "cp_genomes.fasta")
    output = os.path.join(ALIGN_DIR, "alignment.fasta")
    
    # ===== 新增：收集所有 assembly 结果 =====
    print("Collecting assembly results...")
    
    fasta_files = []
    assembly_dir = ASSEMBLY_DIR  # results/assembly/
    
    if os.path.exists(assembly_dir):
        for sample_dir in os.listdir(assembly_dir):
            sample_path = os.path.join(assembly_dir, sample_dir)
            if not os.path.isdir(sample_path):
                continue
            
            # 查找可能的输出文件
            possible_names = [
                "path_1.fasta",
                "embplant_pt.K105.complete.graph1.1.path_sequence.fasta",
                "embplant_pt.K105.scaffolds.graph1.1.path_sequence.fasta",
                "embplant_pt.fasta"
            ]
            
            for name in possible_names:
                fasta_path = os.path.join(sample_path, name)
                if os.path.exists(fasta_path):
                    fasta_files.append(fasta_path)
                    print(f"  Found: {sample_dir}/{name}")
                    break
    
    if not fasta_files:
        print("No assembly files found! Please run assembly first.")
        return
    
    # 合并所有 fasta 文件
    print(f"\nMerging {len(fasta_files)} assembly files into {input_fasta}...")
    with open(input_fasta, 'w') as out_f:
        for f in fasta_files:
            with open(f, 'r') as in_f:
                out_f.write(in_f.read())
            out_f.write('\n')  # 添加换行分隔不同的序列
    
    # 检查合并后的文件
    if not os.path.exists(input_fasta) or os.path.getsize(input_fasta) == 0:
        print("Error: Failed to create cp_genomes.fasta")
        return
    
    # ===== 原有的 MAFFT 比对 =====
    cmd = f"""
    {MAFFT} --auto {input_fasta} > {output}
    """
    
    print(f"\nRunning MAFFT alignment...")
    run_command(cmd)
    print(f"Alignment completed: {output}")