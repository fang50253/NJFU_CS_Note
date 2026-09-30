# 保存为 protparam_fixed.py
import requests
import time
import re

protein_file = r"D:\Documents\Github\CladeCheck\task3\WRKY_protein_final.fasta"
output_file = r"D:\Documents\Github\CladeCheck\task3\WRKY_physicochemical.tsv"

def parse_fasta(fasta_path):
    """解析FASTA文件"""
    sequences = []
    with open(fasta_path) as f:
        current_id = None
        current_seq = []
        for line in f:
            line = line.strip()
            if line.startswith('>'):
                if current_id and current_seq:
                    sequences.append((current_id, ''.join(current_seq)))
                current_id = line[1:].split()[0]
                current_seq = []
            elif current_id:
                current_seq.append(line)
        if current_id and current_seq:
            sequences.append((current_id, ''.join(current_seq)))
    return sequences

def fetch_protparam(seq_id, sequence):
    """调用ProtParam API获取理化参数"""
    url = "https://web.expasy.org/cgi-bin/protparam/protparam"
    
    # 模拟表单提交
    data = {
        "sequence": sequence,
        "submit": "Compute parameters"
    }
    
    try:
        response = requests.post(url, data=data, timeout=60)
        if response.status_code == 200:
            text = response.text
            
            # 调试：保存第一个序列的返回页面（可选）
            # if seq_id == parse_fasta(protein_file)[0][0]:
            #     with open("debug_protparam.html", "w") as f:
            #         f.write(text)
            
            # 方法1：查找表格中的数据
            # 氨基酸数量 - 通常在 "Number of amino acids" 后
            aa_count = "N/A"
            mw = "N/A"
            pI = "N/A"
            gravy = "N/A"
            
            # 尝试多种匹配模式
            # 氨基酸数量
            patterns_aa = [
                r'Number of amino acids\s*</td><td[^>]*>(\d+)',
                r'Number of amino acids[:\s]*(\d+)',
                r'<td>Number of amino acids</td>\s*<td>(\d+)</td>',
            ]
            for pattern in patterns_aa:
                match = re.search(pattern, text, re.IGNORECASE)
                if match:
                    aa_count = match.group(1)
                    break
            
            # 分子量
            patterns_mw = [
                r'Molecular weight\s*</td><td[^>]*>(\d+\.?\d*)',
                r'Molecular weight[:\s]*([\d.]+)',
                r'<td>Molecular weight</td>\s*<td>([\d.]+)</td>',
            ]
            for pattern in patterns_mw:
                match = re.search(pattern, text, re.IGNORECASE)
                if match:
                    mw = match.group(1)
                    break
            
            # 等电点
            patterns_pi = [
                r'Theoretical pI\s*</td><td[^>]*>(\d+\.?\d*)',
                r'Theoretical pI[:\s]*([\d.]+)',
                r'<td>Theoretical pI</td>\s*<td>([\d.]+)</td>',
            ]
            for pattern in patterns_pi:
                match = re.search(pattern, text, re.IGNORECASE)
                if match:
                    pI = match.group(1)
                    break
            
            # GRAVY
            patterns_gravy = [
                r'Grand average of hydropathicity\s*</td><td[^>]*>(-?\d+\.?\d*)',
                r'Grand average of hydropathicity[:\s]*(-?[\d.]+)',
                r'<td>Grand average of hydropathicity</td>\s*<td>(-?[\d.]+)</td>',
            ]
            for pattern in patterns_gravy:
                match = re.search(pattern, text, re.IGNORECASE)
                if match:
                    gravy = match.group(1)
                    break
            
            # 如果仍然全是N/A，尝试更宽松的匹配（查找任何数字）
            if aa_count == "N/A":
                # 在页面开头附近查找第一个数字（通常是氨基酸数量）
                match = re.search(r'<pre>(.*?)</pre>', text, re.DOTALL)
                if match:
                    pre_content = match.group(1)
                    numbers = re.findall(r'\d+', pre_content)
                    if numbers:
                        aa_count = numbers[0]
            
            return (seq_id, aa_count, mw, pI, gravy)
        else:
            print(f"  HTTP错误: {response.status_code}")
            return (seq_id, "Error", "Error", "Error", "Error")
    except Exception as e:
        print(f"  异常: {str(e)[:80]}")
        return (seq_id, "Error", "Error", "Error", "Error")

# 测试模式：先测试5条序列
def test_mode():
    print("=" * 60)
    print("测试模式：先分析前5条序列，确认解析正常")
    print("=" * 60)
    
    sequences = parse_fasta(protein_file)
    test_seqs = sequences[:5]
    
    print(f"\n{'ID':<25} {'AA':<8} {'MW(kDa)':<12} {'pI':<8} {'GRAVY':<10}")
    print("-" * 70)
    
    for seq_id, seq in test_seqs:
        result = fetch_protparam(seq_id, seq)
        print(f"{result[0]:<25} {result[1]:<8} {result[2]:<12} {result[3]:<8} {result[4]:<10}")
        time.sleep(0.5)
    
    print("\n如果上面显示N/A或Error，说明网页解析仍有问题。")
    print("如果显示正常数值，可以运行完整分析。")
    return input("\n是否继续完整分析？(y/n): ").lower() == 'y'

# 完整分析模式
def full_analysis():
    print("正在读取FASTA文件...")
    sequences = parse_fasta(protein_file)
    print(f"共 {len(sequences)} 条序列待分析\n")
    
    with open(output_file, 'w') as f:
        f.write("Gene_ID\tAmino_Acids\tMolecular_Weight_kDa\tTheoretical_pI\tGRAVY\n")
    
    for i, (seq_id, seq) in enumerate(sequences, 1):
        print(f"正在分析 [{i}/{len(sequences)}]: {seq_id}")
        result = fetch_protparam(seq_id, seq)
        
        with open(output_file, 'a') as f:
            f.write(f"{result[0]}\t{result[1]}\t{result[2]}\t{result[3]}\t{result[4]}\n")
        
        time.sleep(0.5)
    
    print(f"\n✅ 完成！结果保存至: {output_file}")

# 主程序
if __name__ == "__main__":
    if test_mode():
        full_analysis()
    else:
        print("已取消分析。")