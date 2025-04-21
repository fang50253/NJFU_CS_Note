import pandas as pd
import numpy as np
import seaborn as sns
import matplotlib.pyplot as plt
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler
from sklearn.decomposition import PCA
from sklearn.svm import SVC
from sklearn.metrics import classification_report, confusion_matrix
from sklearn.pipeline import make_pipeline

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

# 6.其他的类似分析
# 保险公司
plt.figure(figsize=(12, 6))
sns.boxplot(data=data_cleaned, x='Insurance Provider', y='Billing Amount')
plt.title('各保险公司账单金额分布（箱线图）')
plt.xlabel('保险公司')
plt.ylabel('账单金额')
plt.xticks(rotation=45, ha='right')
plt.tight_layout()
plt.savefig('billing_boxplot_by_insurance.png')
quantiles_insurance = data_cleaned.groupby('Insurance Provider')['Billing Amount'].quantile([0.25, 0.5, 0.75]).unstack()
quantiles_insurance.columns = ['25%', '50%', '75%']
quantiles_insurance = quantiles_insurance.round(2)
print("各保险公司账单金额的分位数统计：")
print(quantiles_insurance)

# 检查结果
plt.figure(figsize=(12, 6))
sns.boxplot(data=data_cleaned, x='Test Results', y='Billing Amount')
plt.title('各类检查结果对应账单金额分布（箱线图）')
plt.xlabel('检查结果')
plt.ylabel('账单金额')
plt.xticks(rotation=45, ha='right')
plt.tight_layout()
plt.savefig('billing_boxplot_by_test_results.png')
quantiles_tests = data_cleaned.groupby('Test Results')['Billing Amount'].quantile([0.25, 0.5, 0.75]).unstack()
quantiles_tests.columns = ['25%', '50%', '75%']
quantiles_tests = quantiles_tests.round(2)
print("各类检查结果账单金额的分位数统计：")
print(quantiles_tests)

# 用药情况
plt.figure(figsize=(12, 6))
medication_order = data_cleaned.groupby('Medication')['Billing Amount'].mean().sort_values().index
sns.boxplot(data=data_cleaned, x='Medication', y='Billing Amount')
plt.title('不同用药情况账单金额分布（箱线图）')
plt.xlabel('用药情况')
plt.ylabel('账单金额')
plt.xticks(rotation=45, ha='right')
plt.tight_layout()
plt.savefig('billing_boxplot_by_medication.png')
quantiles_medication = data_cleaned.groupby('Medication')['Billing Amount'].quantile([0.25, 0.5, 0.75]).unstack()
quantiles_medication.columns = ['25%', '50%', '75%']
quantiles_medication = quantiles_medication.round(2)
print("不同用药情况账单金额的分位数统计：")
print(quantiles_medication)

