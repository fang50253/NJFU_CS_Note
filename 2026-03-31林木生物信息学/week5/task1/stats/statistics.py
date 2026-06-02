"""
statistics.py

统计严格比例、宽松比例、异常样本
支持生成三种图表和统计表：
1）柱状图：展示严格/宽松通过率对比
2）条形图：展示异常样本缺失频次排序
3）饼图：展示判定结果分布
"""

from collections import defaultdict
import os


class ResultStats:

    def __init__(self):

        self.total = 0
        self.strict_pass = 0
        self.tolerant_pass = 0

        # 记录失败样本
        self.failure_samples = defaultdict(int)
        
        # 记录详细的判定结果分布
        self.both_pass = 0      # strict和tolerant都通过
        self.strict_only = 0    # 只有strict通过
        self.tolerant_only = 0  # 只有tolerant通过
        self.both_fail = 0      # 都失败

    def add_result(self, strict, tolerant, missing_samples):

        self.total += 1

        if strict:
            self.strict_pass += 1

        if tolerant:
            self.tolerant_pass += 1
        
        # 记录详细的判定结果
        if strict and tolerant:
            self.both_pass += 1
        elif strict and not tolerant:
            self.strict_only += 1
        elif not strict and tolerant:
            self.tolerant_only += 1
        else:
            self.both_fail += 1

        for s in missing_samples:
            self.failure_samples[s] += 1

    def print_summary(self):

        print("\n===== 总统计 =====")

        print("树总数:", self.total)

        print("Strict比例:",
              self.strict_pass / self.total)

        print("Tolerant比例:",
              self.tolerant_pass / self.total)

        print("\n最容易破坏单系的样本:")

        for k, v in sorted(self.failure_samples.items(),
                           key=lambda x: -x[1]):

            print(k, v)

    def generate_bar_chart(self, output_path="output/bar_chart.png"):
        """
        1）柱状图：展示严格/宽松通过率对比
        """
        try:
            import matplotlib.pyplot as plt
            import matplotlib
            
            # 设置中文字体支持
            matplotlib.rcParams['font.sans-serif'] = ['Arial Unicode MS', 'SimHei', 'DejaVu Sans']
            matplotlib.rcParams['axes.unicode_minus'] = False
            
            # 准备数据
            categories = ['Strict\nMonophyly', 'Tolerant\nMonophyly']
            passed = [self.strict_pass, self.tolerant_pass]
            failed = [self.total - self.strict_pass, self.total - self.tolerant_pass]
            
            # 创建柱状图
            x = range(len(categories))
            width = 0.35
            
            fig, ax = plt.subplots(figsize=(10, 6))
            bars1 = ax.bar([i - width/2 for i in x], passed, width, 
                          label='Passed', color='#2ecc71', alpha=0.8)
            bars2 = ax.bar([i + width/2 for i in x], failed, width, 
                          label='Failed', color='#e74c3c', alpha=0.8)
            
            # 添加标签和标题
            ax.set_xlabel('Test Type', fontsize=12)
            ax.set_ylabel('Number of Trees', fontsize=12)
            ax.set_title('Monophyly Test Results Comparison', fontsize=14, fontweight='bold')
            ax.set_xticks(list(x))
            ax.set_xticklabels(categories)
            ax.legend()
            
            # 在柱子上添加数值标签
            for bars in [bars1, bars2]:
                for bar in bars:
                    height = bar.get_height()
                    if height > 0:
                        ax.text(bar.get_x() + bar.get_width()/2., height,
                               f'{int(height)}',
                               ha='center', va='bottom', fontsize=10)
            
            plt.tight_layout()
            
            # 确保输出目录存在
            os.makedirs(os.path.dirname(output_path), exist_ok=True)
            
            # 保存图片
            plt.savefig(output_path, dpi=300, bbox_inches='tight')
            plt.close()
            
            print(f"\n柱状图已保存到: {output_path}")
            
        except ImportError:
            print("\n警告: matplotlib 未安装，无法生成柱状图")
            print("请运行: pip install matplotlib")

    def generate_horizontal_bar_chart(self, output_path="output/horizontal_bar_chart.png", top_n=10):
        """
        2）条形图：展示异常样本缺失频次排序（横向条形图）
        """
        try:
            import matplotlib.pyplot as plt
            import matplotlib
            
            # 设置中文字体支持
            matplotlib.rcParams['font.sans-serif'] = ['Arial Unicode MS', 'SimHei', 'DejaVu Sans']
            matplotlib.rcParams['axes.unicode_minus'] = False
            
            # 获取前N个失败样本
            sorted_samples = sorted(self.failure_samples.items(), key=lambda x: -x[1])[:top_n]
            
            if not sorted_samples:
                print("\n没有失败样本，跳过生成条形图")
                return
            
            samples = [item[0] for item in sorted_samples]
            counts = [item[1] for item in sorted_samples]
            
            # 创建横向条形图
            fig, ax = plt.subplots(figsize=(12, max(6, len(samples) * 0.5)))
            
            colors = plt.cm.RdYlGn_r([count / max(counts) if max(counts) > 0 else 0 for count in counts])
            bars = ax.barh(range(len(samples)), counts, color=colors, alpha=0.8)
            
            # 添加标签和标题
            ax.set_yticks(range(len(samples)))
            ax.set_yticklabels(samples, fontsize=10)
            ax.set_xlabel('Failure Count', fontsize=12)
            ax.set_title(f'Top {top_n} Samples Causing Monophyly Violation', fontsize=14, fontweight='bold')
            
            # 反转y轴，使最高频的在最上面
            ax.invert_yaxis()
            
            # 在条形上添加数值标签
            for i, (bar, count) in enumerate(zip(bars, counts)):
                ax.text(count + 0.2, i, str(count), va='center', fontsize=9)
            
            plt.tight_layout()
            
            # 确保输出目录存在
            os.makedirs(os.path.dirname(output_path), exist_ok=True)
            
            # 保存图片
            plt.savefig(output_path, dpi=300, bbox_inches='tight')
            plt.close()
            
            print(f"条形图已保存到: {output_path}")
            
        except ImportError:
            print("\n警告: matplotlib 未安装，无法生成条形图")
            print("请运行: pip install matplotlib")

    def generate_pie_chart(self, output_path="output/pie_chart.png"):
        """
        3）饼图：展示判定结果分布
        """
        try:
            import matplotlib.pyplot as plt
            import matplotlib
            
            # 设置中文字体支持
            matplotlib.rcParams['font.sans-serif'] = ['Arial Unicode MS', 'SimHei', 'DejaVu Sans']
            matplotlib.rcParams['axes.unicode_minus'] = False
            
            # 准备数据
            labels = ['Both Pass', 'Strict Only', 'Tolerant Only', 'Both Fail']
            sizes = [self.both_pass, self.strict_only, self.tolerant_only, self.both_fail]
            colors = ['#2ecc71', '#3498db', '#f39c12', '#e74c3c']
            explode = (0.05, 0.05, 0.05, 0.05)  # 稍微分离各个扇形
            
            # 只保留非零值的扇形
            filtered_data = [(l, s, c) for l, s, c in zip(labels, sizes, colors) if s > 0]
            if filtered_data:
                labels, sizes, colors = zip(*filtered_data)
                
                # 创建饼图
                fig, ax = plt.subplots(figsize=(10, 8))
                wedges, texts, autotexts = ax.pie(
                    sizes, 
                    explode=explode[:len(sizes)],
                    labels=labels, 
                    colors=colors,
                    autopct='%1.1f%%',
                    shadow=True,
                    startangle=90,
                    textprops={'fontsize': 11}
                )
                
                # 设置百分比文本样式
                for autotext in autotexts:
                    autotext.set_fontsize(10)
                    autotext.set_fontweight('bold')
                
                ax.set_title('Distribution of Test Results', fontsize=14, fontweight='bold')
                
                plt.tight_layout()
                
                # 确保输出目录存在
                os.makedirs(os.path.dirname(output_path), exist_ok=True)
                
                # 保存图片
                plt.savefig(output_path, dpi=300, bbox_inches='tight')
                plt.close()
                
                print(f"饼图已保存到: {output_path}")
            else:
                print("\n没有有效数据，跳过生成饼图")
            
        except ImportError:
            print("\n警告: matplotlib 未安装，无法生成饼图")
            print("请运行: pip install matplotlib")

    def generate_statistics_table(self, output_path="output/statistics_table.txt"):
        """
        生成详细的统计表格
        """
        # 确保输出目录存在
        os.makedirs(os.path.dirname(output_path), exist_ok=True)
        
        with open(output_path, 'w', encoding='utf-8') as f:
            # 写入总体统计
            f.write("=" * 60 + "\n")
            f.write("单系检验统计报告\n")
            f.write("=" * 60 + "\n\n")
            
            f.write("1 总体统计\n")
            f.write("-" * 60 + "\n")
            f.write(f"{'指标':<30} {'数值':<10}\n")
            f.write("-" * 60 + "\n")
            f.write(f"{'树的总数':<30} {self.total:<10}\n")
            f.write(f"{'Strict通过数':<30} {self.strict_pass:<10}\n")
            f.write(f"{'Strict通过率':<30} {self.strict_pass/self.total*100:.2f}%\n")
            f.write(f"{'Tolerant通过数':<30} {self.tolerant_pass:<10}\n")
            f.write(f"{'Tolerant通过率':<30} {self.tolerant_pass/self.total*100:.2f}%\n")
            f.write("\n")
            
            # 写入失败样本统计
            f.write("2 失败样本统计（按出现次数排序）\n")
            f.write("-" * 60 + "\n")
            f.write(f"{'样本名称':<30} {'失败次数':<10} {'占比':<10}\n")
            f.write("-" * 60 + "\n")
            
            sorted_samples = sorted(self.failure_samples.items(), 
                                   key=lambda x: -x[1])
            
            for sample, count in sorted_samples:
                percentage = (count / self.total) * 100
                f.write(f"{sample:<30} {count:<10} {percentage:.2f}%\n")
            
            f.write("\n")
            f.write("=" * 60 + "\n")
        
        print(f"统计表格已保存到: {output_path}")
    
    def generate_csv_table(self, output_path="output/statistics_table.csv"):
        """
        生成CSV格式的统计表格，便于在Excel中查看
        """
        # 确保输出目录存在
        os.makedirs(os.path.dirname(output_path), exist_ok=True)
        
        with open(output_path, 'w', encoding='utf-8-sig') as f:
            # 写入总体统计
            f.write("单系检验统计报告\n\n")
            
            f.write("总体统计\n")
            f.write("指标,数值\n")
            f.write(f"树的总数,{self.total}\n")
            f.write(f"Strict通过数,{self.strict_pass}\n")
            f.write(f"Strict通过率,{self.strict_pass/self.total*100:.2f}%\n")
            f.write(f"Tolerant通过数,{self.tolerant_pass}\n")
            f.write(f"Tolerant通过率,{self.tolerant_pass/self.total*100:.2f}%\n\n")
            
            # 写入失败样本统计
            f.write("失败样本统计（按出现次数排序）\n")
            f.write("样本名称,失败次数,占比(%)\n")
            
            sorted_samples = sorted(self.failure_samples.items(), 
                                   key=lambda x: -x[1])
            
            for sample, count in sorted_samples:
                percentage = (count / self.total) * 100
                f.write(f"{sample},{count},{percentage:.2f}\n")
        
        print(f"CSV统计表格已保存到: {output_path}")
