import os
import re

assembly_dir = "results/assembly"

for sample in os.listdir(assembly_dir):
    sample_path = os.path.join(assembly_dir, sample)
    if not os.path.isdir(sample_path):
        continue
    
    # 查找所有 fasta 文件
    for fasta_file in os.listdir(sample_path):
        if fasta_file.endswith('.fasta'):
            fasta_path = os.path.join(sample_path, fasta_file)
            
            # 读取并修改序列名称
            with open(fasta_path, 'r') as f:
                content = f.read()
            
            # 将序列名称中的冒号替换为下划线
            lines = content.split('\n')
            new_lines = []
            for line in lines:
                if line.startswith('>'):
                    # 清理序列名
                    new_name = re.sub(r'[:]', '_', line)
                    new_lines.append(new_name)
                else:
                    new_lines.append(line)
            
            # 保存修改
            with open(fasta_path, 'w') as f:
                f.write('\n'.join(new_lines))
            
            print(f"Cleaned: {fasta_path}")

print("All sequences renamed")
