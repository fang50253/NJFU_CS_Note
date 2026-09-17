# 保存为 extract_final_sequences.py（覆盖原文件）
import re

# 文件路径
final_id_file = r"D:\Documents\Github\CladeCheck\task3\final_WRKY_ids.txt"
protein_fasta = r"D:\Documents\Github\CladeCheck\task3\ncbi_dataset_Populus_trichocarpa\ncbi_dataset\data\GCF_000002775.5\protein.faa"
cds_fasta = r"D:\Documents\Github\CladeCheck\task3\ncbi_dataset_Populus_trichocarpa\ncbi_dataset\data\GCF_000002775.5\cds_from_genomic.fna"
output_protein = r"D:\Documents\Github\CladeCheck\task3\WRKY_protein_final.fasta"
output_cds = r"D:\Documents\Github\CladeCheck\task3\WRKY_CDS_final.fasta"

def read_ids(file_path):
    """读取ID列表"""
    with open(file_path) as f:
        return set(line.strip() for line in f if line.strip())

def extract_protein(id_set, fasta_file, output_file):
    """提取蛋白序列（ID完全匹配）"""
    extracted = {}
    current_id = None
    current_seq = []
    
    with open(fasta_file) as f:
        for line in f:
            line = line.strip()
            if line.startswith('>'):
                if current_id and current_seq:
                    extracted[current_id] = ''.join(current_seq)
                seq_id = line[1:].split()[0]
                current_id = seq_id if seq_id in id_set else None
                current_seq = []
            elif current_id:
                current_seq.append(line)
        if current_id and current_seq:
            extracted[current_id] = ''.join(current_seq)
    
    with open(output_file, 'w') as out:
        for seq_id, seq in extracted.items():
            out.write(f'>{seq_id}\n')
            for i in range(0, len(seq), 80):
                out.write(seq[i:i+80] + '\n')
    
    print(f"蛋白序列: 成功提取 {len(extracted)} 条")
    return extracted

def extract_cds(id_set, cds_file, output_file):
    """提取CDS序列（从标题行中提取XP_ID进行匹配）"""
    extracted = {}
    current_xp_id = None
    current_seq = []
    
    with open(cds_file) as f:
        for line in f:
            line = line.strip()
            if line.startswith('>'):
                # 保存上一条序列
                if current_xp_id and current_seq:
                    extracted[current_xp_id] = ''.join(current_seq)
                
                # 从标题行中提取XP_xxxxx.x格式的ID
                match = re.search(r'XP_\d+\.\d+', line)
                if match:
                    current_xp_id = match.group(0)
                    # 检查这个ID是否在目标集合中
                    if current_xp_id not in id_set:
                        current_xp_id = None
                else:
                    current_xp_id = None
                current_seq = []
            elif current_xp_id:
                current_seq.append(line)
        
        # 保存最后一条序列
        if current_xp_id and current_seq:
            extracted[current_xp_id] = ''.join(current_seq)
    
    with open(output_file, 'w') as out:
        for seq_id, seq in extracted.items():
            out.write(f'>{seq_id}\n')
            for i in range(0, len(seq), 80):
                out.write(seq[i:i+80] + '\n')
    
    print(f"CDS序列: 成功提取 {len(extracted)} 条")
    return extracted

if __name__ == "__main__":
    final_ids = read_ids(final_id_file)
    print(f"需要提取 {len(final_ids)} 个最终WRKY成员的序列")
    
    extract_protein(final_ids, protein_fasta, output_protein)
    extract_cds(final_ids, cds_fasta, output_cds)
    
    print(f"\n蛋白序列输出: {output_protein}")
    print(f"CDS序列输出: {output_cds}")