#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
WRKY基因家族选择压力分析 (Ka/Ks)
使用 KaKs_Calculator 批量计算 - Windows 修复版
"""

import os
import subprocess
from Bio import SeqIO

# ===== 路径配置 =====
kaks_exe = r"D:\Documents\Github\CladeCheck\task3\KaKs_Calculator.Windows.Command\KaKs_Calculator.exe"
cds_file = r"D:\Documents\Github\CladeCheck\task3\WRKY_CDS_final.fasta"
pairs_file = r"D:\Documents\Github\CladeCheck\task3\gene_pairs.txt"
work_dir = r"D:\Documents\Github\CladeCheck\task3\kaks_analysis"
os.makedirs(work_dir, exist_ok=True)

# ===== 验证 =====
if not os.path.exists(kaks_exe):
    print(f"❌ 错误: 找不到 {kaks_exe}")
    exit(1)

# ===== 读取CDS =====
print("读取CDS序列...")
cds_records = {record.id: str(record.seq) for record in SeqIO.parse(cds_file, "fasta")}
print(f"  读取了 {len(cds_records)} 条")

# ===== 读取基因对（只取前20对测试）=====
print("读取基因对...")
pairs = []
with open(pairs_file, 'r') as f:
    for line in f:
        parts = line.strip().split()
        if len(parts) >= 2 and parts[0] != parts[1]:
            pairs.append((parts[0], parts[1]))

MAX_PAIRS = 20  # 先测试20对
pairs_to_analyze = pairs[:MAX_PAIRS]
print(f"  总共 {len(pairs)} 对，测试前 {len(pairs_to_analyze)} 对")

# ===== 批量分析 =====
results = []
for idx, (gene1, gene2) in enumerate(pairs_to_analyze, 1):
    print(f"\n[{idx}/{len(pairs_to_analyze)}] {gene1[:20]} vs {gene2[:20]}")
    
    seq1 = cds_records.get(gene1)
    seq2 = cds_records.get(gene2)
    
    if not seq1 or not seq2:
        print(f"   ❌ 序列缺失")
        results.append([gene1, gene2, "N/A", "N/A", "N/A", "序列缺失"])
        continue
    
    # 准备输入文件（.axt 格式）
    axt_file = os.path.join(work_dir, f"pair_{idx:04d}.axt")
    with open(axt_file, 'w') as f:
        f.write(f">{gene1}\n{seq1}\n>{gene2}\n{seq2}\n")
    
    # 输出文件
    kaks_output = os.path.join(work_dir, f"pair_{idx:04d}.kaks")
    
    # 修复：正确调用 Windows 可执行文件
    # 方法：使用 shell=True 并将参数作为字符串
    cmd = f'"{kaks_exe}" -i "{axt_file}" -o "{kaks_output}" -m NG'
    
    print(f"   命令: {cmd[:80]}...")
    
    try:
        # 使用 Popen 并等待完成
        process = subprocess.Popen(
            cmd,
            shell=True,
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            text=True
        )
        stdout, stderr = process.communicate(timeout=30)
        
        if process.returncode != 0:
            print(f"   ❌ 运行失败，返回码 {process.returncode}")
            if stderr:
                print(f"   错误: {stderr[:100]}")
            results.append([gene1, gene2, "N/A", "N/A", "N/A", "运行失败"])
            continue
        
        # 解析结果
        if os.path.exists(kaks_output) and os.path.getsize(kaks_output) > 0:
            Ka, Ks, Ka_Ks = "N/A", "N/A", "N/A"
            with open(kaks_output, 'r') as f:
                for line in f:
                    if line.startswith('#') or line.startswith('Method') or line.startswith('---'):
                        continue
                    line = line.strip()
                    if line and not line.startswith('Sequence'):
                        parts = line.split()
                        if len(parts) >= 3:
                            try:
                                Ka = float(parts[0])
                                Ks = float(parts[1])
                                Ka_Ks = float(parts[2])
                            except:
                                pass
                            break
            
            try:
                if float(Ka_Ks) > 1:
                    status = "正选择 (>1)"
                elif float(Ka_Ks) < 1:
                    status = "纯化选择 (<1)"
                else:
                    status = "中性选择 (=1)"
            except:
                status = "解析失败"
            
            print(f"   ✅ Ka={Ka}, Ks={Ks}, Ka/Ks={Ka_Ks} ({status})")
            results.append([gene1, gene2, str(Ka), str(Ks), str(Ka_Ks), status])
        else:
            print(f"   ❌ 结果文件为空")
            results.append([gene1, gene2, "N/A", "N/A", "N/A", "无输出"])
            
    except subprocess.TimeoutExpired:
        process.kill()
        print(f"   ❌ 超时")
        results.append([gene1, gene2, "N/A", "N/A", "N/A", "超时"])
    except Exception as e:
        print(f"   ❌ 错误: {str(e)[:80]}")
        results.append([gene1, gene2, "N/A", "N/A", "N/A", f"错误"])

# ===== 保存结果 =====
output_csv = os.path.join(work_dir, "kaks_summary.csv")
with open(output_csv, 'w', encoding='utf-8') as f:
    f.write("Gene1,Gene2,Ka,Ks,Ka_Ks,Interpretation\n")
    for row in results:
        f.write(",".join(row) + "\n")

# ===== 统计 =====
print("\n" + "="*60)
print("📊 统计结果")
print("="*60)

positive = sum(1 for r in results if "正选择" in r[5])
purifying = sum(1 for r in results if "纯化选择" in r[5])

print(f"总分析对数: {len(results)}")
print(f"正选择 (Ka/Ks > 1): {positive} 对")
print(f"纯化选择 (Ka/Ks < 1): {purifying} 对")
print(f"\n结果保存至: {output_csv}")