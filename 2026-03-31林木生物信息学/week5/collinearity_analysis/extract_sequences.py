#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
根据ID列表从FASTA文件中提取序列
"""

import os

# 文件路径
fasta_file = r"D:\Documents\Github\CladeCheck\task3\ncbi_dataset_Populus_trichocarpa\ncbi_dataset\data\GCF_000002775.5\protein.faa"
id_file = r"D:\Documents\Github\CladeCheck\task3\candidate_ids.txt"
output_file = r"D:\Documents\Github\CladeCheck\task3\candidate_WRKY.fasta"

# 读取需要提取的ID列表（去重后的781个）
print(f"正在读取ID列表: {id_file}")
with open(id_file, 'r') as f:
    target_ids = set(line.strip() for line in f if line.strip())
print(f"需要提取的ID数量: {len(target_ids)}")

# 解析FASTA文件并提取序列
print(f"正在解析FASTA文件: {fasta_file}")
extracted = {}
current_id = None
current_seq = []

with open(fasta_file, 'r') as f:
    for line in f:
        line = line.strip()
        if line.startswith('>'):
            # 保存上一条序列
            if current_id and current_seq:
                extracted[current_id] = ''.join(current_seq)
            # 开始新序列
            current_id = line[1:].split()[0]  # 取第一个空格前的部分作为ID
            current_seq = []
        else:
            if current_id:
                current_seq.append(line)
    
    # 保存最后一条序列
    if current_id and current_seq:
        extracted[current_id] = ''.join(current_seq)

print(f"FASTA文件中共有 {len(extracted)} 条序列")

# 写入提取的序列
print(f"正在写入输出文件: {output_file}")
found_count = 0
with open(output_file, 'w') as f:
    for seq_id in target_ids:
        if seq_id in extracted:
            f.write(f">{seq_id}\n")
            # 每行80个字符格式化输出
            seq = extracted[seq_id]
            for i in range(0, len(seq), 80):
                f.write(seq[i:i+80] + '\n')
            found_count += 1
        else:
            print(f"警告: 未找到序列 {seq_id}")

print(f"成功提取 {found_count} / {len(target_ids)} 条序列")
print(f"输出文件: {output_file}")