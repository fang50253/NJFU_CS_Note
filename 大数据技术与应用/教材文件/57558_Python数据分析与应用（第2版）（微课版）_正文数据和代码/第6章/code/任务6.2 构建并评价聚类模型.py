# 代码6-6
import pandas as pd
from sklearn.manifold import TSNE
import matplotlib.pyplot as plt
# 读取数据集
customer = pd.read_csv('../data/customer.csv', encoding='gbk')
customer_data = customer.iloc[:, :-1]
customer_target = customer.iloc[:, -1]
# Kmeans聚类
from sklearn.cluster import KMeans
kmeans = KMeans(n_clusters=4, 
                random_state=6).fit(customer_data)
# 使用TSNE进行数据降维，降成两维
tsne = TSNE(n_components=2, init='random',
            random_state=2). fit(customer_data)
df = pd.DataFrame(tsne.embedding_)  # 将原始数据转换为DataFrame
df['labels'] = kmeans.labels_  # 将聚类结果存储进df数据表
# 提取不同标签的数据
df1 = df[df['labels'] == 0]
df2 = df[df['labels'] == 1] 
df3 = df[df['labels'] == 2]
df4 = df[df['labels'] == 3]
# 绘制图形
fig = plt.figure(figsize=(9, 6))  # 设定空白画布，并制定大小
# 用不同的颜色表示不同数据
plt.plot(df1[0], df1[1], 'bo', df2[0], df2[1], 'r*', 
         df3[0], df3[1], 'gD', df4[0], df4[1], 'kD')
plt.savefig('../tmp/聚类结果.jpg', dpi=1080) 
plt.show()  # 显示图片



# 代码6-7
from sklearn.metrics import fowlkes_mallows_score
for i in range(1, 7):
    # 构建并训练模型
    kmeans = KMeans(n_clusters=i, 
                  random_state=6).fit(customer_data) 
    score = fowlkes_mallows_score(customer_target, kmeans.labels_)
    print('customer数据聚%d类FMI评价分值为：%f' % (i, score))



# 代码6-8
from sklearn.metrics import silhouette_score
silhouettteScore = []
for i in range(2, 10):
    # 构建并训练模型
    kmeans = KMeans(n_clusters=i,
                    random_state=6).fit(customer_data) 
    score = silhouette_score(customer_data, kmeans.labels_)
    silhouettteScore.append(score)
plt.figure(figsize=(10, 6))
plt.plot(range(2, 10), silhouettteScore,
linewidth=1.5, linestyle='-')
plt.savefig('../tmp/轮廓系数.jpg', dpi=1080) 
plt.show()



# 代码6-9
from sklearn.metrics import calinski_harabasz_score
for i in range(2, 5):
    # 构建并训练模型
    kmeans = KMeans(n_clusters=i, 
                    random_state=2).fit(customer_data) 
    score = calinski_harabasz_score(customer_data, kmeans.labels_)
    print('customer数据聚%d类calinski_harabaz指数为：%f' % (i, score))	
