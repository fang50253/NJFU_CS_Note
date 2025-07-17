import numpy as np
import matplotlib.pyplot as plt
from sklearn import datasets
from sklearn.cluster import DBSCAN
from sklearn.preprocessing import StandardScaler
 
# 加载鸢尾花数据集
iris = datasets.load_iris()
X = iris.data  # 特征数据
y = iris.target  # 真实标签，用于验证
 
# 数据标准化
scaler = StandardScaler()
X_scaled = scaler.fit_transform(X)
 
# 应用DBSCAN算法
dbscan = DBSCAN(eps=0.5, min_samples=5)  # eps是邻域的大小，min_samples是形成稠密区域所需的最小样本数
clusters = dbscan.fit_predict(X_scaled)
 
# 可视化结果
# 由于鸢尾花数据集是4维的，我们通常选择其中两个维度进行可视化
plt.figure(figsize=(12, 6))
 
# 选择两个特征进行可视化，例如第0和第1个特征
plt.subplot(121)
plt.scatter(X_scaled[:, 0], X_scaled[:, 1], c=clusters, cmap='viridis', marker='o', edgecolor='k', s=50)
plt.title('DBSCAN Clustering on the First Two Features')
plt.xlabel('Feature 1')
plt.ylabel('Feature 2')
 
# 可选：选择不同的两个特征进行可视化，例如第2和第3个特征
plt.subplot(122)
plt.scatter(X_scaled[:, 2], X_scaled[:, 3], c=clusters, cmap='viridis', marker='o', edgecolor='k', s=50)
plt.title('DBSCAN Clustering on the Third and Fourth Features')
plt.xlabel('Feature 3')
plt.ylabel('Feature 4')
 
plt.show()