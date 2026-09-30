# 保存为 protparam_local.py
from Bio import SeqIO
from Bio.SeqUtils import ProtParam
import sys

protein_file = r"D:\Documents\Github\CladeCheck\task3\WRKY_protein_final.fasta"
output_file = r"D:\Documents\Github\CladeCheck\task3\WRKY_physicochemical.tsv"

print("正在读取FASTA文件...")
sequences = list(SeqIO.parse(protein_file, "fasta"))
print(f"共 {len(sequences)} 条序列\n")

with open(output_file, 'w') as out:
    out.write("Gene_ID\tAmino_Acids\tMolecular_Weight_kDa\tTheoretical_pI\tGRAVY\n")
    
    for i, record in enumerate(sequences, 1):
        seq_id = record.id
        seq_str = str(record.seq)
        
        print(f"处理 [{i}/{len(sequences)}]: {seq_id}")
        
        try:
            analyzer = ProtParam.ProteinAnalysis(seq_str)
            
            aa_count = len(seq_str)
            mw = analyzer.molecular_weight() / 1000
            pI = analyzer.isoelectric_point()
            gravy = analyzer.gravy()
            
            out.write(f"{seq_id}\t{aa_count}\t{mw:.2f}\t{pI:.2f}\t{gravy:.4f}\n")
        except Exception as e:
            print(f"  错误: {e}")
            out.write(f"{seq_id}\tError\tError\tError\tError\n")

print(f"\n✅ 完成！结果保存至: {output_file}")