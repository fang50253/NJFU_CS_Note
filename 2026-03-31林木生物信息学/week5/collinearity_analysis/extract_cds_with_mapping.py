# 保存为 extract_cds_with_mapping.py
import re

cds_file = r"D:\Documents\Github\CladeCheck\task3\ncbi_dataset_Populus_trichocarpa\ncbi_dataset\data\GCF_000002775.5\cds_from_genomic.fna"
final_id_file = r"D:\Documents\Github\CladeCheck\task3\final_WRKY_ids.txt"
output_cds = r"D:\Documents\Github\CladeCheck\task3\WRKY_CDS_final.fasta"

# 读取最终WRKY的蛋白ID列表
with open(final_id_file, 'r') as f:
    target_protein_ids = set(line.strip() for line in f if line.strip())
print(f"需要提取的蛋白ID数量: {len(target_protein_ids)}")

# 解析CDS文件，建立 XP_ID -> CDS序列 的映射
cds_mapping = {}
current_id = None
current_seq = []

with open(cds_file, 'r') as f:
    for line in f:
        line = line.strip()
        if line.startswith('>'):
            # 保存上一条序列
            if current_id and current_seq:
                cds_mapping[current_id] = ''.join(current_seq)
            # 提取新的序列ID（匹配 XP_xxxxx.x 格式）
            match = re.search(r'XP_\d+\.\d+', line)
            if match:
                current_id = match.group(0)
            else:
                current_id = None
            current_seq = []
        elif current_id:
            current_seq.append(line)
    
    # 保存最后一条
    if current_id and current_seq:
        cds_mapping[current_id] = ''.join(current_seq)

print(f"CDS文件中找到 {len(cds_mapping)} 条有XP_ID的序列")

# 提取目标序列
extracted_count = 0
with open(output_cds, 'w') as out:
    for protein_id in target_protein_ids:
        if protein_id in cds_mapping:
            seq = cds_mapping[protein_id]
            out.write(f'>{protein_id}\n')
            for i in range(0, len(seq), 80):
                out.write(seq[i:i+80] + '\n')
            extracted_count += 1
        else:
            print(f"警告: 未找到CDS序列对应蛋白ID {protein_id}")

print(f"成功提取 {extracted_count} / {len(target_protein_ids)} 条CDS序列")
print(f"输出文件: {output_cds}")