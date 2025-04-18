import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt
from scipy.stats import chi2_contingency
import numpy as np

# 读取数据
data = pd.read_excel("./data_ebike by delivery rider.xlsx")

# 设置画图样式
plt.rcParams['font.sans-serif'] = ['Arial Unicode MS']
plt.rcParams['axes.unicode_minus'] = False

# 1. 骑手行为与事故类型的关系分析
rider_behavior_columns = [
    'Inattention_Rider', 'Vehicle_Rider', 'Yield_Rider', 'Riding_Rider', 'Helmet_Rider', 'Speeding_Rider', 'Drunk_Rider'
]
accident_columns = ['Accident_Type']

# 按事故类型分组，计算骑手行为的平均值
heatmap_data = data.groupby('Accident_Type')[rider_behavior_columns].mean()

# 绘制热图并保存
plt.figure(figsize=(10, 6))
sns.heatmap(heatmap_data.T, annot=True, cmap='YlGnBu', vmin=0, vmax=1)
plt.title("骑手行为 与 事故类型 的平均出现率")
plt.xlabel("事故类型")
plt.ylabel("骑手行为")
plt.tight_layout()
plt.savefig("rider_behavior_vs_accident_type.jpg", dpi=300)

# 2. 骑手行为对伤亡等级的影响（卡方检验）
injury_level_column = 'Highest_Injury_Level'

# 创建一个交叉表
contingency_table = pd.crosstab(data[injury_level_column], data[rider_behavior_columns[0]])

# 卡方检验
chi2, p, dof, expected = chi2_contingency(contingency_table)
print(f"卡方值: {chi2}")
print(f"P值: {p}")

# 3. 骑手年龄与事故类型的关联分析
age_bins = [0, 18, 30, 40, 50, 60, 100]
age_labels = ['<18', '18-30', '30-40', '40-50', '50-60', '>60']
data['Age_Group'] = pd.cut(data['Rider_Age'], bins=age_bins, labels=age_labels)

# 绘制骑手年龄与事故类型的关系
plt.figure(figsize=(12, 6))
sns.countplot(x='Age_Group', hue='Accident_Type', data=data)
plt.title("骑手年龄 与 事故类型 的关系")
plt.xlabel("骑手年龄段")
plt.ylabel("事故发生次数")
plt.tight_layout()
plt.savefig("rider_age_vs_accident_type.jpg", dpi=300)

# 4. 骑手身份与事故责任分配的分析（卡方检验）
rider_identity_column = 'Rider_Identity'

# 创建交叉表
contingency_table_identity = pd.crosstab(data['Accident_Responsibility'], data[rider_identity_column])

# 卡方检验
chi2, p, dof, expected = chi2_contingency(contingency_table_identity)
print(f"\n骑手身份与事故责任的卡方值: {chi2}")
print(f"骑手身份与事故责任的P值: {p}")

# 5. 骑手行为与伤亡等级的卡方检验
for behavior in rider_behavior_columns:
    contingency_table_injury = pd.crosstab(data[behavior], data[injury_level_column])
    chi2, p, dof, expected = chi2_contingency(contingency_table_injury)
    print(f"\n{behavior} 与 伤亡等级的卡方值: {chi2}")
    print(f"{behavior} 与 伤亡等级的P值: {p}")

# 6. 骑手交通方式与事故责任分配的分析
plt.figure(figsize=(12, 6))
sns.countplot(x='Rider_Transportation_Mode', hue='Accident_Responsibility', data=data)
plt.title("骑手交通方式 与 事故责任 的关系")
plt.xlabel("骑手交通方式")
plt.ylabel("事故责任次数")
plt.tight_layout()
plt.savefig("rider_transportation_vs_accident_responsibility.jpg", dpi=300)

# 7. 骑手行为与事故时间段的关系
plt.figure(figsize=(12, 6))
sns.countplot(x='Accident_Time_Period', hue='Inattention_Rider', data=data)
plt.title("骑手注意力与事故时间段的关系")
plt.xlabel("事故时间段")
plt.ylabel("发生次数")
plt.tight_layout()
plt.savefig("rider_inattention_vs_accident_time_period.jpg", dpi=300)

# 8. 骑手年龄与最高伤情等级的关系
plt.figure(figsize=(12, 6))
sns.boxplot(x='Rider_Age', y='Highest_Injury_Level', data=data)
plt.title("骑手年龄与最高伤情等级的关系")
plt.xlabel("骑手年龄")
plt.ylabel("最高伤情等级")
plt.tight_layout()
plt.savefig("rider_age_vs_highest_injury_level.jpg", dpi=300)


from sklearn.linear_model import LogisticRegression
from sklearn.model_selection import train_test_split
from sklearn.metrics import classification_report, confusion_matrix
import matplotlib.pyplot as plt
import seaborn as sns

# 设定伤亡等级为二分类（假设：0为轻微伤/无伤，1为重伤/死亡）
data['Serious_Injury'] = data['Highest_Injury_Level'].apply(lambda x: 1 if x >= 2 else 0)

# 骑手行为列（你也可以加其他行为进去）
behavior_cols = [
    'Inattention_Rider', 'Vehicle_Rider', 'Yield_Rider', 'Riding_Rider',
    'Helmet_Rider', 'Speeding_Rider', 'Drunk_Rider'
]

X = data[behavior_cols]
y = data['Serious_Injury']

# 拆分训练集/测试集
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.3, random_state=42)

# 训练逻辑回归模型
model = LogisticRegression(max_iter=1000)
model.fit(X_train, y_train)

# 模型评估
y_pred = model.predict(X_test)
print("Classification Report:\n", classification_report(y_test, y_pred))
print("Confusion Matrix:\n", confusion_matrix(y_test, y_pred))

# 保存混淆矩阵热图
plt.figure(figsize=(6, 5))
sns.heatmap(confusion_matrix(y_test, y_pred), annot=True, fmt='d', cmap='Blues')
plt.title('混淆矩阵：伤亡预测')
plt.xlabel('预测值')
plt.ylabel('真实值')
plt.tight_layout()
plt.savefig('混淆矩阵.jpg')
plt.close()

# 保存逻辑回归系数可视化
coeffs = pd.Series(model.coef_[0], index=behavior_cols)
plt.figure(figsize=(10, 6))
coeffs.sort_values().plot(kind='barh', color='orange')
plt.title('骑手行为对严重伤亡的影响（逻辑回归系数）')
plt.xlabel('影响程度')
plt.tight_layout()
plt.savefig('逻辑回归系数.jpg')
plt.close()