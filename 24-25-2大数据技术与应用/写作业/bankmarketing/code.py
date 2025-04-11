# -*- coding:utf-8 -*-
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns

from sklearn.preprocessing import LabelEncoder, StandardScaler
from sklearn.model_selection import train_test_split
from sklearn.decomposition import PCA
from sklearn.ensemble import RandomForestClassifier
from sklearn.metrics import classification_report, confusion_matrix
from sklearn.cluster import KMeans

import matplotlib.pyplot as plt
import matplotlib

# matplotlib.rcParams['font.family'] = 'PingFang SC'  # 或 'Heiti SC'，或你电脑中任意一个支持中文的字体
plt.rcParams['font.sans-serif'] = ['Arial Unicode MS']
matplotlib.rcParams['axes.unicode_minus'] = False   # 解决负号显示问题

# 读取数据
df = pd.read_csv("./bankmarketing.csv",encoding="gbk")

# 打印数据基本信息
print("数据集形状:", df.shape)
print("前5行:\n", df.head())

# 编码所有object列
label_cols = df.select_dtypes(include='object').columns
label_encoders = {}
for col in label_cols:
    le = LabelEncoder()
    df[col] = le.fit_transform(df[col])
    label_encoders[col] = le

# 划分特征和标签
X = df.drop(columns='y')
y = df['y']

# 标准化
scaler = StandardScaler()
X_scaled = scaler.fit_transform(X)

# 降维可视化
pca = PCA(n_components=2)
X_pca = pca.fit_transform(X_scaled)

plt.figure(figsize=(8, 6))
plt.scatter(X_pca[:, 0], X_pca[:, 1], c=y, cmap='coolwarm', alpha=0.5)
plt.title("PCA降维可视化")
plt.xlabel("PC1"); plt.ylabel("PC2")
plt.colorbar(label='y')
plt.grid(True)
plt.savefig("pic1.png")

# 划分训练集和测试集
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

# 训练随机森林
model = RandomForestClassifier(random_state=42)
model.fit(X_train, y_train)

# 预测并评估
y_pred = model.predict(X_test)
print("分类报告:\n", classification_report(y_test, y_pred))

# 混淆矩阵
conf_matrix = confusion_matrix(y_test, y_pred)
sns.heatmap(conf_matrix, annot=True, fmt="d", cmap='Blues')
plt.title("混淆矩阵")
plt.xlabel("预测值")
plt.ylabel("真实值")
plt.savefig("pic2.png")

# 特征重要性分析
importances = model.feature_importances_
feature_names = X.columns
feature_importance_df = pd.DataFrame({'Feature': feature_names, 'Importance': importances})
feature_importance_df.sort_values(by='Importance', ascending=False, inplace=True)

plt.figure(figsize=(10, 6))
sns.barplot(data=feature_importance_df, x='Importance', y='Feature')
plt.title("特征重要性")
plt.tight_layout()
plt.savefig("pic3.png")

# 聚类分析（可选）
kmeans = KMeans(n_clusters=3, random_state=42)
clusters = kmeans.fit_predict(X_scaled)

plt.figure(figsize=(8,6))
plt.scatter(X_pca[:, 0], X_pca[:, 1], c=clusters, cmap='viridis', alpha=0.6)
plt.title("KMeans聚类 + PCA可视化")
plt.xlabel("PC1")
plt.ylabel("PC2")
plt.grid(True)
plt.savefig("pic4.png")

