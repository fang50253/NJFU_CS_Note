import numpy as np
import matplotlib.pyplot as plt
from sklearn import datasets
from sklearn.cluster import KMeans
from sklearn.decomposition import PCA
# 加载鸢尾花数据集
iris = datasets.load_iris()
X = iris.data  # 特征数据
y = iris.target  # 目标（标签），用于验证聚类结果，但不是必需的
# 初始化KMeans模型，设置聚类数为3（与鸢尾花种类数相同）
kmeans = KMeans(n_clusters=3, random_state=42)
# 训练模型
kmeans.fit(X)
# 获取聚类中心
centroids = kmeans.cluster_centers_
# 获取聚类标签
labels = kmeans.labels_
# 使用PCA降维到2D以便可视化
pca = PCA(n_components=2)
X_pca = pca.fit_transform(X)
 
# 可视化聚类结果
plt.figure(figsize=(10, 6))
for i in range(3):
    plt.scatter(X_pca[labels == i, 0], X_pca[labels == i, 1], label=f'Cluster {i+1}')
plt.scatter(centroids[:, 0], centroids[:, 1], s=300, c='red', label='Centroids')
plt.title('KMeans Clustering of Iris Dataset')
plt.xlabel('PCA Feature 1')
plt.ylabel('PCA Feature 2')
plt.legend()
plt.show()
# --------------------------------------------------------
#聚类评价
from sklearn.metrics import silhouette_score, adjusted_rand_score, adjusted_mutual_info_score, homogeneity_score, completeness_score, v_measure_score
 
# 由于KMeans是无监督学习，通常不直接与标签对比，但我们可以计算轮廓系数看看聚类的效果：
silhouette_avg = silhouette_score(X, labels)
print(f'Silhouette Score: {silhouette_avg}')
