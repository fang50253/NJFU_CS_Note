# 保存为 prepare_kaks_input.py
from Bio import SeqIO
import os

cds_file = r"D:\Documents\Github\CladeCheck\task3\WRKY_CDS_final.fasta"
pairs_file = r"D:\Documents\Github\CladeCheck\task3\gene_pairs.txt"
out_dir = r"D:\Documents\Github\CladeCheck\task3\kaks_input"

os.makedirs(out_dir, exist_ok=True)

print("读取CDS序列...")
cds = {r.id: str(r.seq) for r in SeqIO.parse(cds_file, "fasta")}

print("读取基因对...")
pairs = []
with open(pairs_file) as f:
    for line in f:
        parts = line.strip().split()
        if len(parts) >= 2:
            pairs.append(parts[:2])

# 只取前50对测试
pairs = pairs[:]
print(f"准备 {len(pairs)} 个基因对...")

for i, (p1, p2) in enumerate(pairs):
    seq1 = cds.get(p1)
    seq2 = cds.get(p2)
    if not seq1 or not seq2:
        continue
    
    # 写入 AXT 格式
    with open(f"{out_dir}/pair_{i+1}.axt", 'w') as f:
        f.write(f">{p1}\n{seq1}\n>{p2}\n{seq2}\n")

print(f"输入文件已保存到 {out_dir}")