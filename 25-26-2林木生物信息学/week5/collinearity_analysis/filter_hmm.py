# 保存为 filter_hmm.py
import re

hmm_file = r"D:\Documents\Github\CladeCheck\task3\hmm_result.txt"
output_file = r"D:\Documents\Github\CladeCheck\task3\final_WRKY_ids.txt"

passed_ids = []
with open(hmm_file, 'r') as f:
    for line in f:
        # HMMER输出的表格行不以#开头
        if not line.startswith('#'):
            parts = line.strip().split()
            if len(parts) >= 5:
                try:
                    evalue = float(parts[4])  # E-value通常在第5列
                    if evalue < 1e-5:
                        seq_id = parts[0]  # 序列ID在第1列
                        passed_ids.append(seq_id)
                except ValueError:
                    continue

unique_passed = sorted(set(passed_ids))
with open(output_file, 'w') as f:
    for uid in unique_passed:
        f.write(uid + '\n')

print(f"通过HMMER验证的成员数量: {len(unique_passed)}")
print(f"结果保存至: {output_file}")