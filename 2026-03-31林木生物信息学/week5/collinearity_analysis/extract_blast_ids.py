#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
提取BLAST结果中的Subject ID（第二列）
"""

import os

# 设置文件路径
blast_file = r"D:\Documents\Github\CladeCheck\task3\blast_result.txt"
output_file = r"D:\Documents\Github\CladeCheck\task3\candidate_ids.txt"

# 检查文件是否存在
if not os.path.exists(blast_file):
    print(f"错误：找不到文件 {blast_file}")
    print("请确认文件名和路径是否正确")
    exit(1)

# 读取BLAST结果，提取第二列
subject_ids = []
line_count = 0

with open(blast_file, 'r', encoding='utf-8') as f:
    for line in f:
        line_count += 1
        # 跳过以 # 开头的注释行
        if line.startswith('#'):
            continue
        # 按空白字符分割（支持空格和制表符）
        parts = line.strip().split()
        if len(parts) >= 2:
            subject_id = parts[1]  # 第二列
            subject_ids.append(subject_id)

# 去重并保持顺序（可选：排序）
unique_ids = sorted(set(subject_ids))

# 输出结果
with open(output_file, 'w', encoding='utf-8') as f:
    for uid in unique_ids:
        f.write(uid + '\n')

# 打印统计信息
print(f"共处理 {line_count} 行")
print(f"提取到 {len(subject_ids)} 条记录（含重复）")
print(f"去重后得到 {len(unique_ids)} 个唯一ID")
print(f"结果已保存到: {output_file}")

# 显示前10个ID作为示例
print("\n前10个ID示例：")
for i, uid in enumerate(unique_ids[:10]):
    print(f"  {i+1}. {uid}")