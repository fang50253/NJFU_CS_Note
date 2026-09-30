# 保存为 extract_gene_structure.py
import re

gff_file = r"D:\Documents\Github\CladeCheck\task3\ncbi_dataset_Populus_trichocarpa\ncbi_dataset\data\GCA_000002775.4\genomic.gff"
id_file = r"D:\Documents\Github\CladeCheck\task3\final_WRKY_ids.txt"
output_file = r"D:\Documents\Github\CladeCheck\task3\WRKY_gene_structure.csv"

# 读取WRKY ID列表
with open(id_file, 'r') as f:
    wrky_ids = set(line.strip() for line in f if line.strip())

print(f"需要提取结构信息的WRKY基因数量: {len(wrky_ids)}")

# 解析GFF文件
gene_structure = {}

with open(gff_file, 'r') as f:
    for line in f:
        if line.startswith('#'):
            continue
        
        parts = line.strip().split('\t')
        if len(parts) < 9:
            continue
        
        seqid, source, feature_type, start, end, score, strand, frame, attributes = parts
        start, end = int(start), int(end)
        
        # 提取基因ID（从attributes中）
        gene_id_match = re.search(r'ID=gene-(\S+?)[;$]', attributes)
        if not gene_id_match:
            gene_id_match = re.search(r'Name=(\S+?)[;$]', attributes)
        
        if gene_id_match:
            gene_id = gene_id_match.group(1)
            if gene_id in wrky_ids:
                if gene_id not in gene_structure:
                    gene_structure[gene_id] = {'exons': [], 'utr': [], 'cds': [], 'strand': strand, 'seqid': seqid}
                
                if feature_type == 'exon':
                    gene_structure[gene_id]['exons'].append((start, end))
                elif feature_type == 'five_prime_UTR' or feature_type == 'three_prime_UTR':
                    gene_structure[gene_id]['utr'].append((start, end))
                elif feature_type == 'CDS':
                    gene_structure[gene_id]['cds'].append((start, end))

# 统计并输出
print(f"成功匹配到结构的基因数量: {len(gene_structure)}")

with open(output_file, 'w') as out:
    out.write("Gene_ID\tChromosome\tStrand\tExon_Count\tExon_Positions\n")
    for gene_id, info in gene_structure.items():
        exon_count = len(info['exons'])
        exon_positions = ";".join([f"{s}-{e}" for s, e in sorted(info['exons'])])
        out.write(f"{gene_id}\t{info['seqid']}\t{info['strand']}\t{exon_count}\t{exon_positions}\n")

print(f"结果保存至: {output_file}")