import re

# 读取原树文件
with open('results/alignment/alignment.fasta.treefile', 'r') as f:
    tree = f.read()

# 清理序列名（只清理名称部分，保留分支长度后的冒号）
def clean_name(match):
    name = match.group(1)
    # 将名称中的冒号替换为下划线
    clean_name = name.replace(':', '_')
    return clean_name + ':'

# 匹配模式：序列名（不包含空格和括号）后跟冒号（分支长度分隔符）
# 注意：不要匹配分支长度数字后的冒号
pattern = r'([a-zA-Z0-9_\-\[\]\(\)\{\}]+):'
tree_cleaned = re.sub(pattern, clean_name, tree)

# 保存清理后的树文件
with open('results/alignment/alignment_clean.treefile', 'w') as f:
    f.write(tree_cleaned)

print("Tree file cleaned successfully!")
print("\nFirst 500 characters of cleaned tree:")
print(tree_cleaned[:500])

# 检查是否还有需要清理的冒号
if ':' in tree_cleaned.replace(':', '', tree_cleaned.count(':') - tree.count(':')):
    print("\nWARNING: Some colons may still remain in sequence names")
else:
    print("\n✓ All sequence names cleaned")
