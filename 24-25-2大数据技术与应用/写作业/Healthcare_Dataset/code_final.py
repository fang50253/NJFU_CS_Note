import pandas as pd
import numpy as np
import seaborn as sns
import matplotlib.pyplot as plt

# 0.设置中文字体和负号显示
plt.rcParams['font.sans-serif'] = ['Arial Unicode MS']  # 设置中文字体
plt.rcParams['axes.unicode_minus'] = False  # 显示负号

# 1.首先导入数据集并使用info函数查看具体数据
data= pd.read_csv('modified_healthcare_dataset.csv',encoding='gbk')
print(data.info())

# 2.使用Pandas+Seaborn+Matplotlib查看是否存在数据缺失
plt.figure(figsize=(12, 6))
sns.heatmap(data.isnull(), cbar=False, cmap='viridis', yticklabels=False)
plt.title('Missing Values Heatmap')
plt.xlabel('Columns')
plt.ylabel('Records')
plt.savefig('missing_values_heatmap.png')

# 3.重复值分析
duplicate_rows = data.duplicated()
num_duplicates = duplicate_rows.sum()
print(f"Number of duplicate rows: {num_duplicates}")
if num_duplicates > 0:
    print("Duplicate rows:")
    print(data[duplicate_rows].head())
data_cleaned = data.drop_duplicates()
print(data_cleaned.info())

# 4.数据相关系数热力图
plt.figure(figsize=(12, 6))
numeric_df = data_cleaned.select_dtypes(include='number')
correlation_matrix = numeric_df.corr()
sns.heatmap(correlation_matrix, annot=True, cmap='coolwarm', fmt=".2f",square=True)
plt.title("数值型字段相关系数矩阵")
plt.tight_layout()
plt.savefig('correlation_matrix_heatmap.png')

# 5.将数据按照医院划分，统计账单金额的箱线图
plt.figure(figsize=(12, 6))
sns.boxplot(data=data_cleaned, x='Hospital', y='Billing Amount')
plt.title('各医院账单金额分布（箱线图）')
plt.xlabel('医院名称')
plt.ylabel('账单金额')
plt.xticks(rotation=45, ha='right')
plt.tight_layout()
plt.savefig('billing_amount_boxplot_by_hospital.png')
quantiles = data_cleaned.groupby('Hospital')['Billing Amount'].quantile([0.25, 0.5, 0.75])
quantiles = quantiles.unstack()
quantiles.columns = ['25%', '50%', '75%']
quantiles = quantiles.round(2)
print("各医院账单金额的分位数统计：")
print(quantiles)

