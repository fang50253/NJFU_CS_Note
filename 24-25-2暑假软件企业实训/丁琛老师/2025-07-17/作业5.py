# 导入必要的库
from sklearn.datasets import load_iris
from sklearn.cluster import KMeans, DBSCAN
from sklearn.metrics import silhouette_score
from sklearn.preprocessing import StandardScaler

# 加载数据
iris = load_iris()
X = iris.data  # 只取特征部分

# 数据标准化（DBSCAN对尺度敏感）
scaler = StandardScaler()
X_scaled = scaler.fit_transform(X)

# ========== KMeans 聚类 ==========
kmeans = KMeans(n_clusters=3, random_state=42)
kmeans_labels = kmeans.fit_predict(X_scaled)

# 计算 KMeans 的轮廓系数
kmeans_score = silhouette_score(X_scaled, kmeans_labels)
print(f'KMeans 轮廓系数: {kmeans_score:.4f}')

# ========== DBSCAN 聚类 ==========
dbscan = DBSCAN(eps=0.8, min_samples=5)
dbscan_labels = dbscan.fit_predict(X_scaled)

# 排除 -1 的点（噪声），若全是噪声无法计算轮廓系数
if len(set(dbscan_labels)) > 1 and -1 in dbscan_labels:
    filtered_X = X_scaled[dbscan_labels != -1]
    filtered_labels = dbscan_labels[dbscan_labels != -1]
    dbscan_score = silhouette_score(filtered_X, filtered_labels)
    print(f'DBSCAN 轮廓系数（排除噪声）: {dbscan_score:.4f}')
elif len(set(dbscan_labels)) > 1:
    dbscan_score = silhouette_score(X_scaled, dbscan_labels)
    print(f'DBSCAN 轮廓系数: {dbscan_score:.4f}')
else:
    dbscan_score = -1
    print("DBSCAN 聚类结果无有效簇，无法计算轮廓系数。")