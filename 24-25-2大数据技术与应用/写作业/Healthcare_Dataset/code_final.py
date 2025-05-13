import scipy
import sklearn
import matplotlib
import numpy as np
import pandas as pd
import seaborn as sns
from sklearn.svm import SVC
import matplotlib.pyplot as plt
import matplotlib.ticker as mtick
from sklearn.decomposition import PCA
from scipy.stats import chi2_contingency
from sklearn.pipeline import make_pipeline
from sklearn.preprocessing import StandardScaler
from sklearn.model_selection import train_test_split
from sklearn.metrics import classification_report, confusion_matrix
from sklearn.metrics import mean_absolute_error, mean_squared_error, r2_score
from sklearn.metrics import classification_report, cohen_kappa_score, roc_curve, auc, roc_auc_score


print("numpy version:", np.__version__)
print("pandas version:", pd.__version__)
print("seaborn version:", sns.__version__)
print("matplotlib version:", matplotlib.__version__)
print("scikit-learn version:", sklearn.__version__)
print("scipy version:", scipy.__version__)

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
plt.savefig('02数据缺失情况.png')

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
plt.savefig('04相关系数热力图.png')

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
plt.savefig('06保险公司和账单金额箱线图.png')
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
plt.savefig('06检查结果和账单金额箱线图.png')
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
plt.savefig('06用药情况和账单金额箱线图.png')
quantiles_medication = data_cleaned.groupby('Medication')['Billing Amount'].quantile([0.25, 0.5, 0.75]).unstack()
quantiles_medication.columns = ['25%', '50%', '75%']
quantiles_medication = quantiles_medication.round(2)
print("不同用药情况账单金额的分位数统计：")
print(quantiles_medication)

# 7.独立性检验性别VS病情
contingency_table = pd.crosstab(data['Gender'], data['Medical Condition'])
print("\n交叉表（性别 vs. 病情）:")
print(contingency_table)
chi2, p, dof, expected = chi2_contingency(contingency_table)
print("\n卡方检验结果:")
print(f"Chi2统计量: {chi2:.4f}")
print(f"自由度: {dof}")
print(f"p值: {p:.4f}")
alpha = 0.05
if p < alpha:
    print("结论：性别与患病种类之间存在显著统计关联。")
else:
    print("结论：性别与患病种类之间不存在显著统计关联。")
plt.figure(figsize=(10, 6))
sns.heatmap(contingency_table, annot=True, cmap="YlGnBu", fmt="d")
plt.title("性别 vs. 患病种类 - 交叉分布热力图")
plt.ylabel("性别")
plt.xlabel("患病种类")
plt.tight_layout()
plt.savefig("07患病情况与性别的关系.png")

# 8.账单金额和住院天数之间的关系
correlation = data['Billing Amount'].corr(data['Length of Stay'])
plt.figure(figsize=(8, 6))  # 可选：设置图像大小
print("账单金额与住院天数的相关系数：", round(correlation, 4))
sns.regplot(x='Length of Stay', y='Billing Amount', data=data, line_kws={"color":"red"})
plt.title('住院天数与账单金额的关系')
plt.savefig("08住院天数与账单金额的关系.png")


# 9.不同疾病患病人数的柱状图（按性别分组）
disease_gender_counts = data.groupby(['Medical Condition', 'Gender']).size().unstack().fillna(0)
disease_gender_counts['Total'] = disease_gender_counts.sum(axis=1)
disease_gender_counts = disease_gender_counts.sort_values(by='Total', ascending=False).drop(columns='Total')
plt.figure(figsize=(14, 6))
bar_width = 0.4
index = np.arange(len(disease_gender_counts))
plt.bar(index - bar_width/2, disease_gender_counts['Male'], width=bar_width, label='男')
plt.bar(index + bar_width/2, disease_gender_counts['Female'], width=bar_width, label='女')
plt.xlabel('疾病名称')
plt.ylabel('患病人数')
plt.title('不同疾病患病人数统计（按性别）')
plt.xticks(index, disease_gender_counts.index, rotation=45, ha='right')
plt.legend()
plt.tight_layout()
plt.savefig("09不同疾病患病人数统计_柱状图_按性别.png")

# 10.每月入院人数折线图（按Date of Admission统计）
data['Date of Admission'] = pd.to_datetime(data['Date of Admission'], errors='coerce')
data_valid_dates = data.dropna(subset=['Date of Admission'])
data_valid_dates['Month'] = data_valid_dates['Date of Admission'].dt.to_period('M').astype(str)
monthly_counts = data_valid_dates['Month'].value_counts().sort_index()
monthly_df = pd.DataFrame({
    'Month': monthly_counts.index,
    'Count': monthly_counts.values
})
monthly_df['Month_Num'] = np.arange(len(monthly_df))
plt.figure(figsize=(12, 6))
sns.lineplot(x='Month_Num', y='Count', data=monthly_df, marker='o', label='每月入院人数')
sns.regplot(x='Month_Num', y='Count', data=monthly_df, scatter=False, color='red', label='趋势回归线')
plt.xticks(ticks=monthly_df['Month_Num'], labels=monthly_df['Month'], rotation=45, ha='right')
plt.xlabel("月份")
plt.ylabel("入院人数")
plt.title("每月入院人数及趋势回归线")
plt.legend()
plt.tight_layout()
plt.savefig("10每月入院人数_含趋势线.png")




# 11.划分数据集
features = ['Hospital', 'Gender', 'Age', 'Length of Stay']
target = 'Billing Amount'
X = pd.get_dummies(data_cleaned[features], drop_first=True)
y = data_cleaned[target]
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)
print("训练集 X 的形状:", X_train.shape)
print("测试集 X 的形状:", X_test.shape)
print("训练集 y 的形状:", y_train.shape)
print("测试集 y 的形状:", y_test.shape)


# 12.使用PCA进行降维
features = ['Hospital', 'Gender', 'Age', 'Length of Stay', 'Insurance Provider',
            'Test Results', 'Medication']
target = 'Medical Condition'
X = pd.get_dummies(data_cleaned[features], drop_first=True)
y = data_cleaned[target]
X_train, X_test, y_train, y_test = train_test_split(
    X, y, test_size=0.2, random_state=42)
scaler = StandardScaler()
X_train_scaled = scaler.fit_transform(X_train)
X_test_scaled = scaler.transform(X_test)
svm_model = SVC(kernel='rbf', C=1.0, gamma='scale', random_state=42)
svm_model.fit(X_train_scaled, y_train)
y_pred = svm_model.predict(X_test_scaled)
print("分类报告：")
print(classification_report(y_test, y_pred))
print("混淆矩阵：")
cm=confusion_matrix(y_test, y_pred)
print(cm)
plt.figure(figsize=(10, 8))
labels = svm_model.classes_
sns.heatmap(cm, annot=True, fmt="d", cmap="Blues", xticklabels=labels, yticklabels=labels)
plt.xlabel("预测值")
plt.ylabel("实际值")
plt.title("SVM 混淆矩阵")
plt.tight_layout()
plt.savefig("12混淆矩阵.png")

# 13.分类模型的评价
print("\n分类性能报告：")
print(classification_report(y_test, y_pred))
kappa = cohen_kappa_score(y_test, y_pred)
print(f"\nCohen's Kappa 系数：{kappa:.4f}")
report_dict = classification_report(y_test, y_pred, output_dict=True)
report_df = pd.DataFrame(report_dict).transpose()
report_df = report_df.loc[report_df.index[:-3]]
report_df[['precision', 'recall', 'f1-score']].plot(kind='bar', figsize=(12, 6))
plt.title('每类的 Precision、Recall 和 F1-Score')
plt.ylabel('得分')
plt.ylim(0, 1.1)
plt.xticks(rotation=45)
plt.tight_layout()
plt.savefig('13svm分类模型的评价.png')